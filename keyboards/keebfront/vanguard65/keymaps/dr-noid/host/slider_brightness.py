"""Map the Vanguard65 slider to monitor brightness via Twinkle Tray.

The keyboard sends its slider position as MIDI CC 90 (0-127). This listens for
that and calls Twinkle Tray's CLI to set an absolute brightness percentage.

Run this with *Windows* Python, not WSL python -- the MIDI device and Twinkle
Tray both live on the host.

    py -m pip install mido python-rtmidi
    py slider_brightness.py

Twinkle Tray must already be running (its CLI talks to the running instance).
"""

import os
import subprocess
import sys
import time

import mido

# --- config ---------------------------------------------------------------

PORT_MATCH = "Vanguard65"   # substring of the MIDI input port name
SLIDER_CC = 90
MONITORS = [1]              # Twinkle Tray --MonitorNum values, 1-indexed
MIN_PERCENT = 5             # never black out the panel entirely
MAX_PERCENT = 100
APPLY_INTERVAL = 0.15       # seconds; DDC/CI writes are slow, do not spam them
MIN_DELTA = 2               # ignore sub-2% wobble
SHOW_OVERLAY = True         # flash Twinkle Tray's on-screen level indicator

TWINKLE_TRAY = os.path.join(
    os.environ.get("LOCALAPPDATA", ""), "Programs", "twinkle-tray", "Twinkle Tray.exe"
)

# --- implementation -------------------------------------------------------


def to_percent(cc_value: int) -> int:
    span = MAX_PERCENT - MIN_PERCENT
    return MIN_PERCENT + round(cc_value * span / 127)


def set_brightness(percent: int) -> None:
    for monitor in MONITORS:
        args = [TWINKLE_TRAY, f"--MonitorNum={monitor}", f"--Set={percent}"]
        if SHOW_OVERLAY:
            args.append("--Overlay")
        subprocess.Popen(args, creationflags=getattr(subprocess, "DETACHED_PROCESS", 0))


def find_port() -> str:
    ports = mido.get_input_names()
    for name in ports:
        if PORT_MATCH.lower() in name.lower():
            return name
    sys.exit(f"No MIDI input matching {PORT_MATCH!r}. Available: {ports}")


def main() -> None:
    if not os.path.exists(TWINKLE_TRAY):
        sys.exit(f"Twinkle Tray not found at {TWINKLE_TRAY}")

    port = find_port()
    print(f"Listening on {port} (CC {SLIDER_CC}) -> monitors {MONITORS}")

    target = None
    applied = None
    next_apply = 0.0

    with mido.open_input(port) as inport:
        while True:
            # Drain everything queued so a fast sweep does not run us behind.
            for msg in inport.iter_pending():
                if msg.type == "control_change" and msg.control == SLIDER_CC:
                    target = to_percent(msg.value)

            now = time.monotonic()
            if target is not None and now >= next_apply:
                if applied is None or abs(target - applied) >= MIN_DELTA or target in (
                    MIN_PERCENT,
                    MAX_PERCENT,
                ):
                    if target != applied:
                        set_brightness(target)
                        applied = target
                        next_apply = now + APPLY_INTERVAL

            time.sleep(0.01)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
