#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
  
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  // Initialize the TCS34725 color sensor
  if (!tcs.begin()) {
    Serial.println("Color sensor not found. Check your wiring!");
    while (1);
  }
  
  // Set the integration time and gain
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
  tcs.setGain(TCS34725_GAIN_1X);
}

void loop() {
  // Read the RGB color values from the sensor
  uint16_t red, green, blue, clear;
  tcs.getRawData(&red, &green, &blue, &clear);
  
  // Calculate the color temperature and lux values
  float temperature = tcs.calculateColorTemperature(red, green, blue);
  float lux = tcs.calculateLux(red, green, blue);
  
  // Print the RGB values, color temperature, and lux on the serial monitor
  Serial.print("Red: "); Serial.print(red);
  Serial.print(" Green: "); Serial.print(green);
  Serial.print(" Blue: "); Serial.print(blue);
  Serial.print(" Color Temperature: "); Serial.print(temperature);
  Serial.print(" K Lux: "); Serial.println(lux);
  
  // Display the RGB values, color temperature, and lux on the OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Red: "); display.println(red);
  display.print("Green: "); display.println(green);
  display.print("Blue: "); display.println(blue);
  // display.print("Temperature: "); display.println(temperature);
  display.print("Lux: "); display.println(lux);
  display.display();
  
  delay(1000); // Delay for 1 second
}
