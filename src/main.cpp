#include <M5Unified.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void rotatePoint(float &x, float &y, float &z, imu::Quaternion q) {
  float qw = q.w(), qx = q.x(), qy = q.y(), qz = q.z();
  float nx = (1 - 2 * (qy * qy + qz * qz)) * x + (2 * (qx * qy - qw * qz)) * y + (2 * (qx * qz + qw * qy)) * z;
  float ny = (2 * (qx * qy + qw * qz)) * x + (1 - 2 * (qx * qx + qz * qz)) * y + (2 * (qy * qz - qw * qx)) * z;
  float nz = (2 * (qx * qz - qw * qy)) * x + (2 * (qy * qz + qw * qx)) * y + (1 - 2 * (qx * qx + qy * qy)) * z;
  x = nx;
  y = ny;
  z = nz;
}

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

  // 下方向ベクトルを回転
  float dx = 0, dy = 0, dz = -1;
  rotatePoint(dx, dy, dz, quat);

  // XY成分だけ送信
  Serial.printf("%.3f,%.3f\n", dx, dy);

  delay(30);  // 約33Hz送信（滑らか＋軽い）
}
