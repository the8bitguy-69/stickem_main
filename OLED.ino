#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C (SDA, SCL pins)
#define OLED_RESET -1   // Reset pin (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char myBitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3f, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x7e, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0xfc, 0x01, 0xe0, 0x03, 0xff, 0xff, 0xff, 
	0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x01, 0xf8, 0x03, 0x80, 0x00, 0x1f, 0xff, 0xff, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x41, 0x80, 0x00, 0x01, 0xf0, 0x07, 0x00, 0x00, 0x07, 0xff, 0xff, 
	0xe0, 0x07, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x0e, 0x00, 0x00, 0x03, 0xff, 0xff, 
	0xc0, 0x1f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0x01, 0xc0, 0x1e, 0x03, 0xf8, 0x03, 0xff, 0xff, 
	0x80, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0x01, 0x80, 0x02, 0x03, 0xfe, 0x03, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0xf8, 0x0c, 0x01, 0xff, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0xff, 0xff, 
	0x01, 0xff, 0xf0, 0x7f, 0xfc, 0x0f, 0xf1, 0xff, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x0f, 
	0x01, 0xff, 0xc0, 0x1f, 0xfc, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x01, 
	0x01, 0xff, 0x80, 0x08, 0x03, 0x9f, 0xf0, 0x00, 0x00, 0x7f, 0xfc, 0x07, 0xfc, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xf0, 0x03, 0x03, 0xff, 0xff, 0x07, 0xfc, 0x03, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x87, 0xfc, 0x1f, 0xff, 0x80, 
	0x00, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xc7, 0xf8, 0x7f, 0xfe, 0x00, 
	0x80, 0x7f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0x3f, 0xe0, 0x3c, 0x0f, 0xf9, 0xff, 0xf0, 0x01, 
	0xc0, 0x1f, 0xff, 0xff, 0xfc, 0x3f, 0xc1, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x07, 
	0xe0, 0x03, 0xff, 0xff, 0xfe, 0x3f, 0xc0, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x1f, 
	0x80, 0x00, 0x01, 0xff, 0xfe, 0x3f, 0xc0, 0x7f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xfc, 0x00, 0x7f, 
	0x00, 0x00, 0x00, 0x0f, 0xff, 0x7f, 0x80, 0x7f, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xfe, 0x01, 0xff, 
	0x00, 0x0f, 0x80, 0x07, 0xff, 0x7f, 0x80, 0x7f, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0x00, 0xff, 
	0x01, 0xff, 0xc0, 0x07, 0xff, 0xff, 0x80, 0x7f, 0x9f, 0xf8, 0x1f, 0xff, 0xf0, 0xff, 0x80, 0x7f, 
	0x01, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0x80, 0x7f, 0xcf, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xc0, 0x3f, 
	0x00, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfc, 0x7f, 0xc7, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0xe0, 0x1f, 
	0x80, 0x7f, 0xff, 0xff, 0xfc, 0x7f, 0xfc, 0x7f, 0xc1, 0xff, 0xff, 0x3f, 0xe0, 0x3f, 0xf0, 0x1f, 
	0xc0, 0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xfc, 0xff, 0xc0, 0x3f, 0xe0, 0x3f, 0xe0, 0x1f, 0xf8, 0x07, 
	0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x07, 
	0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xff, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x7e, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xff, 0xe0, 0x00, 0x00, 0x1f, 0xc0, 0x7e, 0x18, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0xff, 0xff, 0xc0, 0x0f, 0xff, 0xc0, 0x7f, 0xfc, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xfd, 0xff, 0xff, 0xf8, 0x00, 0x78, 0x1f, 0xe0, 0x0f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xfd, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xff, 0xff, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0xf3, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xe3, 0xfc, 0x3f, 0xc1, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc3, 0xf8, 0x1f, 0x80, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xc3, 0xf8, 0x1f, 0xc0, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xfc, 0x3f, 0xc3, 0xf8, 0x1f, 0xc0, 0xfc, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xf8, 0x00, 0x03, 0xf8, 0x1f, 0xc0, 0xfe, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x0c, 0x07, 0xf8, 0x00, 0x03, 0xf8, 0x1f, 0xc0, 0xfe, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1c, 0x07, 0xff, 0xe0, 0x01, 0xf8, 0x1f, 0xc0, 0xfe, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x1c, 0x07, 0xff, 0xff, 0xe1, 0xf8, 0x1f, 0xc0, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x10, 0x3c, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x10, 0x3c, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x70, 0x7c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc1, 0xe0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x83, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x07, 0xc1, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x0f, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x1f, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

extern unsigned long sr04_distance;
extern float yaw;
extern float velocityX;
extern float distanceX;
extern float temperatureValue;
extern float humidityValue;
extern float lightLevel;

int cursorY = 0;

void OLEDSetup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap, 128, 64, BLACK, WHITE);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void displayMPU6050() {
  //MPU6050
  display.setCursor(0, cursorY);
  display.print("Heading:");
  display.print((int)yaw);
  display.print((char)247);
  cursorY+=10;
}

void displayAHT10() {
  //AHT10
  display.setCursor(0, cursorY);
  display.print("Temperature:");
  display.print(temperatureValue);
  display.print((char)247);
  display.print("C");
  cursorY+=10;
  display.setCursor(0, cursorY);
  display.print("Humidity:");
  display.print(humidityValue);
  display.print("%rH");
  cursorY+=10;
}

void displayBH1750() {
  //BH1750
  display.setCursor(0, cursorY);
  display.print("Light:");
  display.print(lightLevel);
  display.print("Lux");
  cursorY+=10;
}

void displaySR04() {
  //HC-SR04
  display.setCursor(0, cursorY);
  display.print("Length:");
  display.print(sr04_distance);
  display.print("cm");
  cursorY+=10;
}

void displayOLED() {
  // Reset the cursorY before drawing
  cursorY = 0;
  display.display();
}

void clearOLED() {
  display.clearDisplay();
}
