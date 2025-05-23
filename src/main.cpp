#include <M5Unified.h>
#include <M5Unified.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(115200);

  if (!bno.begin()) {
    M5.Display.println("BNO055 not found!");
    while (1);
  }

  bno.setExtCrystalUse(true);
  delay(1000);
}

void loop() {
  imu::Quaternion quat = bno.getQuat();
  Serial.printf("%.4f,%.4f,%.4f,%.4f\n", quat.w(), quat.x(), quat.y(), quat.z());
  delay(30); // 約33Hzで送信（30ms間隔）
}
