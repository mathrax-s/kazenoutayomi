#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOSC.h>

extern int lastVinTime;

#define SYSTEM_NO 1

const char* ssid = "ssid";
const char* pwd = "pass";


#if SYSTEM_NO==1
// WiFi stuff
const IPAddress ip(192, 168, 11, 201);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);


// for ArduinoOSC
const int send_port = 55555;
String osc_address = "/system1";
const int send_port_to_system1 = 12345;
const int recv_port_from_system2 = 12345;
const int send_port_to_system2 = 54321;
const int recv_port_from_system1 = 54321;

#define maxSensor  6
int slider_data[maxSensor] = {0, 0, 0, 0, 0, 0};
int address[maxSensor] = {10, 11, 12, 13, 14, 15};
float average[maxSensor] = {0, 0, 0, 0, 0, 0};

#elif SYSTEM_NO==2
// WiFi stuff
const IPAddress ip(192, 168, 11, 202);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);

// for ArduinoOSC
const int send_port = 55556;
String osc_address = "/system2";
const int send_port_to_system1 = 12345;
const int recv_port_from_system2 = 12345;
const int send_port_to_system2 = 54321;
const int recv_port_from_system1 = 54321;

#define maxSensor  7
int slider_data[maxSensor] = {0, 0, 0, 0, 0, 0, 0};
int address[maxSensor] = {10, 11, 12, 13, 14, 15, 16};
float average[maxSensor] = {0, 0, 0, 0, 0, 0, 0};
#endif

const char* host1 = "192.168.11.101";
const char* host2 = "192.168.11.102";
const char* system1 = "192.168.11.201";
const char* system2 = "192.168.11.202";


int sleeptime = 0;
int sleepdone = 0;

int sleeptime_btnA = 0;
int sleepdone_btnA = 0;

int textColor = YELLOW;
float vin;
float vbat;
uint32_t tout = 0;
int sensorCount = 0;
int r;


int autoProfile[5] = {10, 20, 40, 80, 120};
int autoTime = 0;
int velocity[5] = {20, 40, 60, 80, 100};
int debug = 0;
int i2c_err_num[maxSensor];
String i2c_err;

int lcd_page = 0;
int busy_count = 0;

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


/////
void setup() {

  //  Wire.begin(32, 33);
  pinMode(0, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  Wire.begin(0, 26, 100000UL);  //0...SDA, 26...SCL, 100kbps
  Wire.setTimeout(500);

  // initialize the M5StickC object
  M5.begin();

  M5.Lcd.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Axp.ScreenBreath(8);

  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Kaze no Utayomi");
  M5.Lcd.println("");
  M5.Lcd.println("System ");

  delay(1000);
  M5.Lcd.fillScreen( BLACK );

  Serial.begin(115200);
  Serial.println("ok");

  // WiFi stuff (no timeout setting for WiFi)
  wifi_start();
}

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

void parameter_reset() {
  sleeptime = 0;
}

void loop() {
  // PowerOff
  vin = (M5.Axp.GetVinData() * 1.7);
  vbat = M5.Axp.GetBatVoltage();
  if (debug == 0) {
    if ( (M5.Axp.GetVinData() * 1.7) < 3.0 ) {
      if ( lastVinTime + 5000 < millis() ) {
        // 3.0V以下が5秒以上で電源オフ
        axp_halt();
      }
    } else {
      // 最終電圧確認時間更新
      lastVinTime = millis();
    }
  }

  // Sensor Information
  for (int i = 0; i < maxSensor; i++) {
    Wire.requestFrom(address[i], 1);
    while (Wire.available() > 0) {
      byte val = Wire.read();
      slider_data[i] = val;
    }
    i2c_err_num[i] = Wire.lastError();
    average[i] = average[i] * 0.5 + (float)(slider_data[i]) * 0.5;
  }



  // OSC
  OscWiFi.parse();
  if (WiFi.status() != WL_CONNECTED) {
    //WIFI restart
    wifi_start();
  } else {
    String str = "";
    for (int i = 0; i < maxSensor; i++) {
      str += slider_data[i];
      str += ",";
    }
    OscWiFi.send(host1, send_port, osc_address, str);
    OscWiFi.send(host2, send_port, osc_address, str);
  }

  // Auto Composer
  int touch = 0;
  for (int i = 0; i < maxSensor; i++) {
    if (slider_data[i] != 0) {
      touch = 1;
      tout = 0;
      sleeptime = 0;
      if (sleepdone == 1) {
        sleepdone = 0;
        M5.Axp.ScreenBreath(8);
      }
    }
  }

  if (touch == 0) {
    if (sleepdone == 1) {
      tout++;
      if (tout > autoTime) {
        tout = 0;

        if (SYSTEM_NO == 1) {
          Serial.print("send ");
          r = random(20, 70);

          Serial.printf("%d ", sensorCount);

          Wire.beginTransmission(address[sensorCount]); //CHANNEL
          Wire.write(0);  //ADDRESS HIGH
          Wire.write(0);  //ADDRESS LOW
          Wire.write(r);  //NOTE
          Wire.write(velocity[random(5)]);  //VELOCITY

          Wire.endTransmission();

          Serial.println();

          sensorCount++;
          if (sensorCount >= maxSensor) {
            r = random(30, 50);
            sensorCount = 0;
          }

          OscWiFi.send(system2, send_port_to_system2, "/beat", r);
        }
      }
    }

    sleeptime++;
    if (sleeptime > 600) {
      sleeptime = 0;
      if (sleepdone == 0) {
        sleepdone = 1;
        M5.Axp.ScreenBreath(0);
        if (lcd_page == 0) {
          autoTime = autoProfile[random(5)];
        } else if (lcd_page == 1) {
          autoTime = 10;
        }
      }
    }
  }

  // LCD Display
  M5.update();
  if (M5.BtnA.wasPressed()) {
    M5.Axp.ScreenBreath(8);
    if (sleepdone == 1) {
      sleeptime = 0;
      sleepdone = 0;
    } else {
      lcd_page++;
      if (lcd_page > 1) {
        lcd_page = 0;
      }
    }
  }
  if (M5.BtnB.isPressed()) {
    esp_restart();
  }
  // 電源ボタンの状態取得（一度しか0以外のステータスは取得できない）
  int axpButton = M5.Axp.GetBtnPress();
  if ( axpButton == 2 ) {
    // 1秒未満電源ボタンを押して離した
    //    esp_restart();
    i2c_restart();
  }

  switch (lcd_page) {
    case 0:
      //TOUCH CHECK
      M5.Lcd.fillScreen( TFT_BLACK );
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.print("System ");
      M5.Lcd.print(SYSTEM_NO);
      M5.Lcd.println("");

      for (int i = 0; i < maxSensor; i++) {
        M5.Lcd.printf("%d: %d\t", i, slider_data[i]);
        slider_lcd(slider_data[i]);
        M5.Lcd.println("");
      }
      //    M5.Lcd.printf("%d\t", tout);
      //    M5.Lcd.println("");

      M5.Lcd.printf("vin: %f\t", vin);
      M5.Lcd.println("");
      //    M5.Lcd.printf("vbat:%f\t", vbat);
      //    M5.Lcd.println("");
      M5.Lcd.print("Err:\t");
      for (int i = 0; i < maxSensor; i++) {
        M5.Lcd.printf("%d \t", i2c_err_num[i]);
      }
      M5.Lcd.println("");
      M5.Lcd.print(Wire.getErrorText(i2c_err_num[0]));
      break;



    case 1:
      //I2C CHECK
      M5.Lcd.fillScreen( TFT_BLACK );
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.print("System ");
      M5.Lcd.print(SYSTEM_NO);
      M5.Lcd.println("");

      int busy_check = 0;
      for (int i = 0; i < maxSensor; i++) {
        if (i2c_err_num[i] == 5 || i2c_err_num[i] == 1) {
          busy_check = 1;
        }
        M5.Lcd.printf("%d \t", i2c_err_num[i]);
      }
      if (busy_check == 1) {
//        busy_count++;
//        if (busy_count > 0) {
          busy_check = 0;
          i2c_restart();
//        }
//      } else {
//        busy_count = 0;
      }
      M5.Lcd.println("");
      for (int i = 0; i < maxSensor; i++) {
        M5.Lcd.printf("%d: ", i);
        M5.Lcd.print(Wire.getErrorText(i2c_err_num[i]));
        M5.Lcd.println("");
      }
      M5.Lcd.print("IP = "); M5.Lcd.println(WiFi.localIP());

      break;
  }
  //  }
  delay(20);

}
