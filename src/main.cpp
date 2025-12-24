#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <math.h>

// Adjust these pin assignments to match your wiring.
constexpr int PIN_TFT_SCLK = 12;
constexpr int PIN_TFT_MOSI = 11;
constexpr int PIN_TFT_MISO = -1;  // Not used by ST7789
constexpr int PIN_TFT_CS   = 10;
constexpr int PIN_TFT_DC   = 9;
constexpr int PIN_TFT_RST  = 14;
constexpr int PIN_TFT_BL   = 48;  // Backlight (tie to 3.3V if not PWM-controlled)

constexpr uint16_t TFT_WIDTH  = 240;
constexpr uint16_t TFT_HEIGHT = 240;
constexpr uint8_t SCREEN_ROTATION = 0;  // 0-3 for rotations

SPIClass tftSPI(FSPI);
Adafruit_ST7789 tft(&tftSPI, PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST);

void drawColorBars();
void drawTextDemo();

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\nS3 TFT smoke test starting...");

  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);

  // Start SPI with the chosen pins.
  tftSPI.begin(PIN_TFT_SCLK, PIN_TFT_MISO, PIN_TFT_MOSI, PIN_TFT_CS);

  tft.init(TFT_WIDTH, TFT_HEIGHT);
  tft.setRotation(SCREEN_ROTATION);
  tft.fillScreen(ST77XX_BLACK);

  drawColorBars();
  drawTextDemo();
}

void loop() {
  static uint8_t colorIndex = 0;
  constexpr uint16_t palette[] = {
    ST77XX_BLACK, ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
    ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW, ST77XX_WHITE
  };
  const uint8_t paletteSize = sizeof(palette) / sizeof(palette[0]);

  tft.fillScreen(palette[colorIndex]);
  tft.setTextWrap(false);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE, palette[colorIndex]);
  tft.setTextSize(2);
  tft.print("Step ");
  tft.print(colorIndex + 1);
  tft.print("/");
  tft.print(paletteSize);

  colorIndex = (colorIndex + 1) % paletteSize;
  delay(1200);
}

void drawColorBars() {
  const uint16_t bars[] = {
    ST77XX_RED, ST77XX_YELLOW, ST77XX_GREEN, ST77XX_CYAN,
    ST77XX_BLUE, ST77XX_MAGENTA, ST77XX_ORANGE, ST77XX_WHITE
  };
  const uint8_t count = sizeof(bars) / sizeof(bars[0]);
  const uint16_t barHeight = TFT_HEIGHT / count;

  for (uint8_t i = 0; i < count; ++i) {
    tft.fillRect(0, i * barHeight, TFT_WIDTH, barHeight, bars[i]);
  }

  // Simple radial gradient to check pixel addressing.
  const int16_t cx = TFT_WIDTH / 2;
  const int16_t cy = TFT_HEIGHT / 2;
  for (int16_t y = 0; y < TFT_HEIGHT; ++y) {
    for (int16_t x = 0; x < TFT_WIDTH; ++x) {
      int16_t dx = x - cx;
      int16_t dy = y - cy;
      uint16_t dist = sqrtf(dx * dx + dy * dy);
      uint8_t mix = min<uint16_t>(dist, 255);
      uint16_t color = tft.color565(mix, 0, 255 - mix);
      tft.drawPixel(x, y, color);
    }
  }
}

void drawTextDemo() {
  tft.fillRect(0, 0, TFT_WIDTH, 50, ST77XX_BLACK);
  tft.setCursor(8, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("ESP32-S3 + ST7789");

  tft.drawFastHLine(0, 40, TFT_WIDTH, ST77XX_WHITE);
  tft.drawFastVLine(0, 40, TFT_HEIGHT - 40, ST77XX_WHITE);
  tft.drawFastVLine(TFT_WIDTH - 1, 40, TFT_HEIGHT - 40, ST77XX_WHITE);
}
