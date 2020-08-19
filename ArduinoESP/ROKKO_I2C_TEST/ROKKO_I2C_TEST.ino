#include <M5StickC.h>

void setup()
{
  // initialize the M5StickC object
  M5.begin();
  Wire.begin(32, 33);
  //  Wire1.begin(21, 22);

  M5.Lcd.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);

  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("M5StickC I2C Tester");

  delay(1000);
  M5.Lcd.fillScreen( BLACK );
  Serial.begin(115200);
}

int textColor = YELLOW;
int counter = 50;
int slider_data = 0;
int address = 10;

void loop()
{
  Wire.requestFrom(address, 1, true);
  while (Wire.available() > 0) {
    byte val = Wire.read();
    Serial.print("\t");
    Serial.println(val);
    slider_data = val;
  }

  M5.Lcd.fillScreen( TFT_BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Address %d", address);
  M5.Lcd.println("");
  M5.Lcd.printf("%d", slider_data);
  M5.Lcd.println("");
  delay(20);

}
