**`Lab1/Task1-1/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 1-1 Using the variable resistor to adjust LED lightness

- **學生姓名**：林玉惠
- **學生學號**：113511209
- **完成日期**：2026-09-13

---

### 1. 實驗目標(可參考課程投影片寫法)
- 學習並掌握可變電阻與函式 int analogRead(pin) 的使用方式。
- 透過類比讀取值來動態調整 PWM 輸出，控制 LED 的亮度（數值越大，LED 越亮）。
- 學習透過 Arduino IDE 的 Serial Monitor 接收與印出感測器數值。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1
- 麵包版 x 1
- 可變電阻 x 1
- LED x 1

### 3. 操作說明與成果
1. 將可變電阻的兩端分別接 5V 與 GND，中間訊號腳接至類比接腳（A0）；LED 正極接至 PWM 輸出接腳（11），負極接 GND。
2. 使用 USB 線連接 Arduino Uno 至電腦，並點擊「上傳」。
3. 開啟監控器：開啟 Arduino IDE 的 Serial Monitor，將鮑率（Baud rate）設為 9600 baud。
4. 實驗成果：
   旋轉可變電阻時，LED 的亮度會隨之改變。
   序列埠監控器成功每0.3秒印出一次格式 Data is [數值] 的類比回傳值（範圍為 0 至 1023）。
5. 操作影片：請參閱同目錄下 `video/Task1-1.mp4` 之實際操作畫面。
