// 자이로센서 라이브러리 -----------------------------------------------------------------------------
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>


// 자이로센서 변수 및 객체 선언 -----------------------------------------------------------------------
MPU6050 accelgyro; // 자이로센서 객체 생성

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

const int MPU_ADDR = 0x68; // 자이로센서 주소
const double RADIAN_TO_DEGREE = 180 / 3.14159; // 라디안값 도로 바꾸기

double roll; // x축 기준 회전값
double pitch; // y축 기준 회전 값


// 핀 번호 설정 -----------------------------------------------------------------------------------
int buzzerPin = 5;


void setup() {
  // 시리얼 모니터 시작
  Serial.begin(115200);

  // 자이로센서 setup ------------------------------------------
  Wire.begin();

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 
 }


void loop() {
 exit(0);
 deadlift();
}



// 데드리프트 측정 함수
int deadlift() {

  while (true) {
    gyroGet(&roll, &pitch);
    if (pitch > -45) {
      tone(buzzerPin, 500, 40);
      Serial.println(0);
      delay(60);
      while (true) {
        gyroGet(&roll, &pitch);
        if (pitch < -65) {
          tone(buzzerPin, 600, 50);
          Serial.println(1);
          delay(80);
          return 1;
        }
      }
    }
    delay(100);
  }
}

// 자이로 값 측정 함수
void gyroGet(double* ptrRoll, double* ptrPitch) {
  // 자이로 값 측정
  accelgyro.getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);

  // 가속도센서 값 이용해서 roll, pitch 계산
  double angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;
  double angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;

  // 출력
  *ptrRoll = angleAcX;
  *ptrPitch = angleAcY;
}
