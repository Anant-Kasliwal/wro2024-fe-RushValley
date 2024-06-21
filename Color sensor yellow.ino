#include <Wire.h>
#include <TCS34725.h>

TCS34725 tcs = TCS34725();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  tcs.begin();
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Calculate the color values
  float red = r / 256.0;
  float green = g / 256.0;
  float blue = b / 256.0;

  // Convert to hex values
  String hexRed = String(red, HEX);
  String hexGreen = String(green, HEX);
  String hexBlue = String(blue, HEX);

  // Pad with zeros if necessary
  if (hexRed.length() < 2) hexRed = "0" + hexRed;
  if (hexGreen.length() < 2) hexGreen = "0" + hexGreen;
  if (hexBlue.length() < 2) hexBlue = "0" + hexBlue;

  // Create the full hex color code
  String hexColor = "#" + hexRed + hexGreen + hexBlue;

  // Check if the detected color is #CCFF00
  if (hexColor == "#CCFF00") {
    Serial.println("ALERT: Detected color #CCFF00");
  }

  delay(100);
}