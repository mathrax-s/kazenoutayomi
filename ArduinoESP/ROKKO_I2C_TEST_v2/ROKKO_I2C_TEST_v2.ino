#include <M5StickC.h>

// 最後に電圧確認した時間
int lastVinTime = 0;

// AXPを電源オフする
void axp_halt() {
  Wire1.beginTransmission(0x34);
  Wire1.write(0x32);
  Wire1.endTransmission();
  Wire1.requestFrom(0x34, 1);
  uint8_t buf = Wire1.read();

  Wire1.beginTransmission(0x34);
  Wire1.write(0x32);
  Wire1.write(buf | 0x80); // halt bit
  Wire1.endTransmission();
}


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
int slider_data[2] = {0, 0};
int address[2] = {10, 11};
float vin;


void loop()
{

  vin = (M5.Axp.GetVinData() * 1.7);
  if ( (M5.Axp.GetVinData() * 1.7) < 3.0 ) {
    if ( lastVinTime + 5000 < millis() ) {
      // 3.0V以下が5秒以上で電源オフ
      axp_halt();
    }
  } else {
    // 最終電圧確認時間更新
    lastVinTime = millis();
  }

  for (int i = 0; i < 2; i++) {
    Wire.requestFrom(address[i], 1, true);
    while (Wire.available() > 0) {
      byte val = Wire.read();
      Serial.print("\t");
      Serial.println(val);
      slider_data[i] = val;
    }
  }
  M5.Lcd.fillScreen( TFT_BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Address %d", address);
  M5.Lcd.println("");
  M5.Lcd.printf("ID 10: %d", slider_data[0]);
  M5.Lcd.println("");
  M5.Lcd.printf("ID 11: %d", slider_data[1]);
  M5.Lcd.println("");
  M5.Lcd.printf("%f", vin);
  M5.Lcd.println("");
  delay(20);

}
