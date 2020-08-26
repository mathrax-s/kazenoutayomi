/////
void wifi_start() {
  // WiFi stuff (no timeout setting for WiFi)
  WiFi.disconnect(true, true); // disable wifi, erase ap info
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);

  M5.Axp.ScreenBreath(8);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("WiFi connect ..");
  M5.Lcd.println("");
  int w_tout = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    M5.Lcd.print(".");
    delay(500);
    w_tout++;
    if (w_tout >= 40) {
      esp_restart();
    }
  }
  Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());
  M5.Lcd.print("IP = "); M5.Lcd.println(WiFi.localIP());
  if (SYSTEM_NO == 1) {
    OscWiFi.subscribe(recv_port_from_system2, "/beat", onOscReceived);
  } else if (SYSTEM_NO == 2) {
    OscWiFi.subscribe(recv_port_from_system1, "/beat", onOscReceived);
  }
  delay(1000);
  M5.Axp.ScreenBreath(0);
}



// I2C

//const char ERRORTEXT[] =
//     "OK\0"
//     "DEVICE\0"
//     "ACK\0"
//     "TIMEOUT\0"
//     "BUS\0"
//     "BUSY\0"
//     "MEMORY\0"
//     "CONTINUE\0"
//     "NO_BEGIN\0"
//     "\0";


void i2c_restart() {
  M5.Axp.ScreenBreath(8);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("");
  M5.Lcd.println("I2C restart !!");
  M5.Lcd.println("");
  delay(1000);

  Wire.begin(32, 33);

  pinMode(0, OUTPUT);
  pinMode(26, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(26, LOW);

  for (long c = 0; c < 100; c++) {
    digitalWrite(26, HIGH);
    delayMicroseconds(5);
    digitalWrite(26, LOW);
    delayMicroseconds(5);
  }

  pinMode(0, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  Wire.begin(0, 26, 100000UL);  //0...SDA, 26...SCL, 100kbps
  Wire.setTimeout(500);

  delay(1000);
  M5.Axp.ScreenBreath(0);
}


void slider_lcd(int val) {
  int m = constrain(map(val, 0, 100, 0, 20), 0, 20);
  M5.Lcd.print(" \t");
  for (int i = 0; i < m; i++) {
    M5.Lcd.print("-");
  }
}


void onOscReceived(const OscMessage& m)
{
  int rcvdata = m.arg<int>(0);
  //  delay(random(30));
  Serial.print("send ");
  Serial.printf("%d ", sensorCount);

  Wire.beginTransmission(address[sensorCount]); //CHANNEL
  Wire.write(0);  //ADDRESS HIGH
  Wire.write(0);  //ADDRESS LOW
  Wire.write(rcvdata);  //NOTE
  Wire.write(velocity[random(5)]);  //VELOCITY

  Wire.endTransmission();

  Serial.println();
  sensorCount++;
  if (sensorCount >= maxSensor) {
    sensorCount = 0;
  }
}
