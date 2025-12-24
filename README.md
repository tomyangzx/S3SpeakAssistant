# ESP32-S3 1.54" TFT Test (ST7789)

Quick PlatformIO project to smoke-test a 1.54" ST7789-based TFT on an ESP32-S3 DevKit.

## Hardware Assumptions
- ESP32-S3 DevKitC (or similar S3 board with native USB)
- 1.54" TFT using ST7789 controller, 240x240 resolution
- SPI interface, backlight pin exposed

## Wiring (adjust as needed)
| TFT pin | ESP32-S3 pin (default in code) |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SCL / SCK | IO12 |
| SDA / MOSI | IO11 |
| CS | IO10 |
| DC | IO9 |
| RST | IO14 |
| BL (backlight) | IO48 (or tie to 3V3) |
| MISO | Not used (set to -1 in code) |

Update the pin constants near the top of [src/main.cpp](src/main.cpp) if your wiring differs.

## Build, Flash, Monitor
1. Install PlatformIO (VS Code extension or CLI).
2. Connect the ESP32-S3 via USB; select the correct COM port.
3. From the repo root:
   - Build & upload: `pio run -t upload`
   - Serial monitor: `pio device monitor -b 115200`

## What You Should See
- On boot, a color-bar pattern and gradient render to verify addressing.
- The loop then cycles solid colors with a step counter in the corner.
- Serial prints: `S3 TFT smoke test starting...`

## Tweaks
- Change `TFT_WIDTH`, `TFT_HEIGHT`, or `SCREEN_ROTATION` in [src/main.cpp](src/main.cpp) to match your module.
- If your display needs an offset (common on 240x135 parts), adjust the library call to `init(width, height, xStart, yStart)`.
- For PWM backlight control, drive `PIN_TFT_BL` with `ledcWrite()` instead of tying high.

## Libraries
- Adafruit ST7735 and ST7789 Library
- Adafruit GFX Library

## Notes
- The sketch targets `esp32-s3-devkitc-1` with Arduino framework; update `platformio.ini` if you use a different board.
- Keep the existing board images; they are references for the hardware.
