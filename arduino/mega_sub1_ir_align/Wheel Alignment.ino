#include <Wire.h>
#include <Adafruit_VL53L0X.h>

const byte S1_OutputPin = 8;
const byte S2_OutputPin = 9;
const byte S3_OutputPin = 10;
const byte S4_OutputPin = 11;

#define XSHUT_PIN1 2
#define XSHUT_PIN2 3
#define XSHUT_PIN3 4
#define XSHUT_PIN4 5

#define ADDR1 0x30
#define ADDR2 0x31
#define ADDR3 0x32
#define ADDR4 0x33

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println(F("시작: 4개 센서 초기화"));

  Wire.begin();
  pinMode(XSHUT_PIN1, OUTPUT);
  pinMode(XSHUT_PIN2, OUTPUT);
  pinMode(XSHUT_PIN3, OUTPUT);
  pinMode(XSHUT_PIN4, OUTPUT);
  digitalWrite(XSHUT_PIN1, LOW);
  digitalWrite(XSHUT_PIN2, LOW);
  digitalWrite(XSHUT_PIN3, LOW);
  digitalWrite(XSHUT_PIN4, LOW);
  delay(10);

  // 센서1
  Serial.println(F("센서1 활성화 (XSHUT1 HIGH)"));
  digitalWrite(XSHUT_PIN1, HIGH);
  delay(10);
  bool ok1 = lox1.begin(ADDR1);
  Serial.print(F("lox1.begin(0x30) 반환: "));
  Serial.println(ok1 ? F("성공") : F("실패"));

  // 센서2
  Serial.println(F("센서2 활성화 (XSHUT2 HIGH)"));
  digitalWrite(XSHUT_PIN2, HIGH);
  delay(10);
  bool ok2 = lox2.begin(ADDR2);
  Serial.print(F("lox2.begin(0x31) 반환: "));
  Serial.println(ok2 ? F("성공") : F("실패"));

  // 센서3
  Serial.println(F("센서3 활성화 (XSHUT3 HIGH)"));
  digitalWrite(XSHUT_PIN3, HIGH);
  delay(10);
  bool ok3 = lox3.begin(ADDR3);
  Serial.print(F("lox3.begin(0x32) 반환: "));
  Serial.println(ok3 ? F("성공") : F("실패"));

  // 센서4
  Serial.println(F("센서4 활성화 (XSHUT4 HIGH)"));
  digitalWrite(XSHUT_PIN4, HIGH);
  delay(10);
  bool ok4 = lox4.begin(ADDR4);
  Serial.print(F("lox4.begin(0x33) 반환: "));
  Serial.println(ok4 ? F("성공") : F("실패"));

  Serial.println(F("↪️ setup() 완료, loop() 진입"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t m1, m2, m3, m4;
  lox1.rangingTest(&m1, false);
  lox2.rangingTest(&m2, false);
  lox3.rangingTest(&m3, false);
  lox4.rangingTest(&m4, false);

  Serial.print(F("S1: "));
  if (m1.RangeStatus != 4) {
    Serial.print(m1.RangeMilliMeter), Serial.println(F(" mm"));

    if (m1.RangeMilliMeter <= 80) {
      digitalWrite(S1_OutputPin, HIGH);
    } else {
      digitalWrite(S1_OutputPin, LOW);
    }

  }
  else {
    Serial.println(F("Out of range"));
    digitalWrite(S1_OutputPin, LOW);
  }
  
  Serial.print(F("S2: "));
  if (m2.RangeStatus != 4) {
    Serial.print(m2.RangeMilliMeter), Serial.println(F(" mm"));

    if (m2.RangeMilliMeter <= 80) {
      digitalWrite(S2_OutputPin, HIGH);
    } else {
      digitalWrite(S2_OutputPin, LOW);
    }

  }
  else {
    Serial.println(F("Out of range"));
    digitalWrite(S2_OutputPin, LOW);
  }
  
  Serial.print(F("S3: "));
  if (m3.RangeStatus != 4) {
    Serial.print(m3.RangeMilliMeter), Serial.println(F(" mm"));

    if (m3.RangeMilliMeter <= 80) {
      digitalWrite(S3_OutputPin, HIGH);
    } else {
      digitalWrite(S3_OutputPin, LOW);
    }

  }
  else {
    Serial.println(F("Out of range"));
    digitalWrite(S3_OutputPin, LOW);
  }
  
  Serial.print(F("S4: "));
  if (m4.RangeStatus != 4) {
    Serial.print(m4.RangeMilliMeter), Serial.println(F(" mm"));
    
    if (m4.RangeMilliMeter <= 76) {
      digitalWrite(S4_OutputPin, HIGH);
    } else {
      digitalWrite(S4_OutputPin, LOW);
    }

  }
  else {
    Serial.println(F("Out of range"));
    digitalWrite(S4_OutputPin, LOW);
  }

  Serial.println();
  delay(100);
}
