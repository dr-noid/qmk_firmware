# dr-noid / Vanguard65

Port of my [dymium65 keymap](../../../../dotmod/dymium65/keymaps/dr-noid/readme.md).

## Layout notes

- Caps Lock and Backspace are **swapped on every layer** (Backspace sits on the
  Caps key, Caps Lock on the 2u Backspace key).
- The knob is top-**left** on this board (it was top-right on the dymium).
- Right-hand 3-key column: `Print Screen` / `Delete` / `Home`.

## keycodes

- F13 (fn + prtsc) -> mute discord
- F14 (fn + delete) -> deafen discord

- F15 (fn + encoder ccw) -> decrease brightness
- F16 (fn + encoder cw) -> increase brightness

- `fn` + `GUI` -> toggle GUI
- `fn` + `Caps Lock` (the 2u backspace key) -> toggle QWERTY / Canary layout
- `fn` + `right alt` -> alt layer (holds `QK_BOOT` on the prtsc key)

I use [twinkle-tray](https://github.com/xanderfrangos/twinkle-tray) for brightness control

## Slider -> monitor brightness

The slider sends its absolute position as **MIDI CC 90** (0-127). Firmware side
it is smoothed (4x EMA), calibrated to the real travel endpoints and rate
limited, so ADC jitter never reaches the host but the exact ends of the throw
still land on 0 and 127.

`host/slider_brightness.py` runs on the Windows host, listens for CC 90 and
calls [Twinkle Tray](https://github.com/xanderfrangos/twinkle-tray)'s CLI
(`--MonitorNum=1 --Set=<percent>`, available since v1.13.0, requires Twinkle
Tray to already be running):

```
py -m pip install mido python-rtmidi
py host/slider_brightness.py
```

Edit `MONITORS` in the script if you want more than the first display, and
`SLIDER_RAW_MIN` / `SLIDER_RAW_MAX` in `keymap.c` if the ends of the physical
travel do not quite reach 0 / 100%.

fn + encoder still sends F15/F16 for stepped brightness.

## VIA

`VIA_ENABLE = yes`. This board has no `via.json` in the QMK repo -- Keebfront
publish it on their site; load it through VIA's *Design* tab (or drop it in
VIA's design files) to get the board recognised. `TG_LAYOUT` is `QK_KB_0`, so
VIA can address it as a custom keycode.

## Canary layout (row stagger)

Reference: [github.com/Apsu/Canary](https://github.com/Apsu/Canary)

```
w l y p k   z x o u ;
c r s t b   f n e i a '
j v d g q   m h / , .
```
