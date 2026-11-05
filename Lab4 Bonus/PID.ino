
#include <Servo.h>

// ===== 腳位設定 =====
#define trigPin 10
#define echoPin 11
#define servoPin 9

Servo myServo;

// ===== 校正資料 =====
const float setPoint = 11.5;
const int baseAngle = 140;

// ===== PD 參數 =====
float kp = 0.8;
float kd = 0.55;

// ===== 已測量的啟動角度 =====
// 球在15cm附近，129度開始往感測器滾動
const int startAngleFar = 129;

// ===== 馬達限制 =====
const int minAngle = 128;
const int maxAngle = 150;

const int maxStep = 2;

// ===== 採樣時間 =====
const unsigned long sampleTime = 40;

// ===== 靜摩擦補償參數 =====
const float stopSpeed = 0.8;
const float startError = 1.5;

// 啟動補償最多維持的時間
const unsigned long boostTime = 300;

// ===== 濾波變數 =====
float filteredDistance = 11.5;
float lastDistance = 11.5;
float filteredVelocity = 0;

bool initialized = false;

// ===== 啟動補償狀態 =====
bool boostActive = false;
unsigned long boostStart = 0;

// ===== 馬達與時間 =====
int currentAngle = baseAngle;

unsigned long lastTime = 0;
unsigned long lastValidTime = 0;

void setup() {

  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(baseAngle);

  delay(1000);

  lastTime = millis();
  lastValidTime = millis();

  Serial.println("Ball Balance PD + Friction");
  Serial.println("Target: 11.5 cm");
  Serial.println("Base: 140 deg");
  Serial.println("Far start angle: 129 deg");
}

void loop() {

  unsigned long now = millis();

  if (now - lastTime < sampleTime) {
    return;
  }

  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // ===== 讀取距離 =====
  float rawDistance = readDistance();

  if (rawDistance < 0) {
    invalidReading();
    return;
  }

  // ===== 第一次初始化 =====
  if (!initialized) {
    filteredDistance = rawDistance;
    lastDistance = rawDistance;
    filteredVelocity = 0;
    initialized = true;
  }

  // ===== 排除測距突波 =====
  if (abs(rawDistance - filteredDistance) > 6.0) {
    invalidReading();
    return;
  }

  lastValidTime = millis();

  // ===== 距離濾波 =====
  filteredDistance =
    filteredDistance * 0.65 +
    rawDistance * 0.35;

  float distance = filteredDistance;

  // ===== 速度計算 =====
  float velocity =
    (distance - lastDistance) / dt;

  lastDistance = distance;

  velocity = constrain(
    velocity, -25.0, 25.0
  );

  filteredVelocity =
    filteredVelocity * 0.7 +
    velocity * 0.3;

  // ===== PD 計算 =====
  float error = setPoint - distance;

  float P = kp * error;

  float D = -kd * filteredVelocity;

  float output = P + D;

  // ===== 遠端靜摩擦補償 =====
  // 球在遠端、幾乎停止時啟動
  bool needBoost =
    (error < -startError) &&
    (abs(filteredVelocity) < stopSpeed);

  if (!boostActive && needBoost) {
    boostActive = true;
    boostStart = millis();
  }

  if (boostActive) {

    // 球開始移動或到達時間上限，就停止補償
    if (filteredVelocity < -stopSpeed ||
        error >= -startError ||
        millis() - boostStart >= boostTime) {

      boostActive = false;
    }
    else {

      // 使馬達至少達到129度
      float boostOutput =
        startAngleFar - baseAngle;

      output = min(output, boostOutput);
    }
  }

  // ===== 輸出角度限制 =====
  int targetAngle =
    baseAngle + round(output);

  targetAngle = constrain(
    targetAngle,
    minAngle,
    maxAngle
  );

  // ===== 馬達平滑控制 =====
  targetAngle = constrain(
    targetAngle,
    currentAngle - maxStep,
    currentAngle + maxStep
  );

  currentAngle = targetAngle;

  myServo.write(currentAngle);

  // ===== 序列埠監控 =====
  Serial.print("SetPoint:");
  Serial.print(setPoint, 2);

  Serial.print(",Distance:");
  Serial.print(distance, 2);

  Serial.print(",Angle:");
  Serial.print(currentAngle);

  Serial.print(",Velocity:");
  Serial.print(filteredVelocity, 2);

  Serial.print(",Error:");
  Serial.print(error, 2);

  Serial.print(",Boost:");
  Serial.println(boostActive ? 1 : 0);
}

// ===== 超音波測距 =====
float readDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  unsigned long duration =
    pulseIn(echoPin, HIGH, 10000);

  if (duration == 0) {
    return -1;
  }

  float cm = duration * 0.0343 / 2.0;

  if (cm < 2 || cm > 35) {
    return -1;
  }

  return cm;
}

// ===== 測距異常保護 =====
void invalidReading() {

  if (millis() - lastValidTime > 300) {

    initialized = false;
    filteredVelocity = 0;
    boostActive = false;

    // 平緩回到水平位置
    if (currentAngle > baseAngle) {
      currentAngle--;
    }
    else if (currentAngle < baseAngle) {
      currentAngle++;
    }

    myServo.write(currentAngle);
  }
}
