#include <Servo.h>

// --- 腳位設定 ---
#define trigPin 10
#define echoPin 11
#define servoPin 9

Servo myServo;

// --- 系統參數 ---
int setPoint = 13;        // 目標位置 (公分)，假設軌道長 30，中心點為 15
int baseAngle = 120;      // 伺服馬達的水平基準角度 (需依實際硬體調整，讓板子維持水平)

// --- PID 參數 (需要根據你的硬體微調) ---
float kp = 5.0;   // 比例 (反應力度)
float ki = 0;  // 積分 (消除長期的微小誤差)
float kd = 5; // 微分 (預測趨勢，抑制震盪，這在小球平衡中非常重要！)

// --- PID 計算過程變數 ---
float priError = 0;
float integral = 0;
unsigned long lastTime = 0;
int sampleTime = 30; // 採樣時間 (毫秒)，固定頻率能讓 PID 更穩定

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(baseAngle); // 開機先回到水平位置
  
  delay(1000); // 等待機構穩定
  lastTime = millis();
}

void loop() {
  unsigned long now = millis();
  unsigned long dt = now - lastTime;
  
  // 只有當達到我們設定的採樣時間時，才進行一次 PID 計算
  if (dt >= sampleTime) {
    
    // 1. 取得過濾後的距離
    float dis = getFilteredDistance();
    
    // 2. 計算誤差 (目標位置 - 現在位置)
    float error = setPoint - dis;

    // 3. 比例項 (P)
    float Pvalue = error * kp;

    // 4. 積分項 (I)
    integral += (error * dt);
    // 防積分飽和機制 (Anti-Windup)：避免誤差累積過大導致馬達卡死
    if (integral > 1000) integral = 1000;
    else if (integral < -1000) integral = -1000;
    float Ivalue = integral * ki;

    // 5. 微分項 (D)
    // 微分代表小球的速度，加上 dt 可以精準計算出小球移動有多快
    float Dvalue = ((error - priError) / dt) * kd;

    // 6. 總和計算 PID 輸出值
    float PIDvalue = Pvalue + Ivalue + Dvalue;
    priError = error; // 記錄這次誤差給下次算 D 用

    // 7. 將 PID 輸出轉換為馬達角度
    // 注意正負號：如果球太遠(誤差為正)，馬達應該往哪個方向轉才能讓球滾回來？
    // 如果你的球動作方向相反，請把 "+ PIDvalue" 改成 "- PIDvalue"
    int servoAngle = baseAngle + (int)PIDvalue; 

    // 8. 限制馬達角度，避免機構卡死損壞 (假設安全範圍是 70 到 130 度)
    if (servoAngle > 200) servoAngle = 200;
    else if (servoAngle < 80) servoAngle = 80;

    // 9. 輸出到馬達
    myServo.write(servoAngle);

    // 10. 序列埠觀察 (用 Arduino IDE 的「序列埠繪圖家」看曲線非常方便)
    Serial.print("SetPoint:"); Serial.print(setPoint);
    Serial.print(", Distance:"); Serial.print(dis);
    Serial.print(", Angle:"); Serial.println(servoAngle);

    lastTime = now; // 重置時間
  }
}

// --- 超音波濾波讀取函數 ---
float getFilteredDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms 逾時
  
  if (duration == 0) return setPoint; // 如果沒讀到，假裝在中心點避免暴衝
  
  float cm = (float)duration / 29.0 / 2.0;
  
  // 軟體濾波保護
  static float lastValidCm = setPoint;
  
  // 假設軌道長 30cm，過濾掉不合理的極端值 (突波)
  // 軟體濾波保護

  
  // 假設軌道長 30cm，只接收合理範圍內的數值
  if (cm >= 2 && cm <= 35) {
    // 使用低通濾波 (Low-Pass Filter) 取代突波限制
    // 讓新數值佔 30%，舊數值佔 70%。這樣數值會平滑移動，且永遠不會死鎖
    lastValidCm = (lastValidCm * 0.7) + (cm * 0.3);
  }
  
  return lastValidCm;
}