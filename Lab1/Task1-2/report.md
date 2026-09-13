**`Lab1/Task1-2/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 1-2 RGB LED —Layering Three Inputs

- **學生姓名**：林玉惠
- **學生學號**：113511209
- **完成日期**：2026-09-13

---

### 1. 實驗目標(可參考課程投影片寫法)
- 掌握 RGB LED 與三個獨立輸入（按鈕、序列埠、可變電阻）的應用與疊加。
- 運用digitalRead、Serial.read與analogRead 搭配 map() 函式。
- 學習透過 Arduino IDE「序列埠監控器（Serial Monitor）」接收開發板訊息並進行控制。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1
- 可變電阻 x 1
- 按鈕 x 1
- RGB LED x 1
- 限流電阻 x 3
- 導線 x 7

### 3. 操作說明與成果
1. 電路組裝：連接按鈕至接腳2、可變電阻接到A0，並將 RGB LED 的三個顏色接腳分別透過限流電阻連接至 PWM 輸出接腳（9、10、11），共用腳接地。
2. 燒錄程式：使用 USB 線連接 Arduino Uno 至電腦，開啟 Task1-2.ino 程式並點擊「上傳」。
3. 開啟 Arduino IDE 的 Serial Monitor，將鮑率（Baud rate）設為 9600 baud，畫面印出 Green Light Brightness Controller 標題。
4. 實驗成果：
    旋轉可變電阻可調整藍燈的亮度變化。
    按下按鈕可切換紅燈狀態。
    在序列埠輸入 1 或 0 可控制綠燈開關，並於Serial Monitor印出 Green Light Brightness: [數值]。
5. 顏色變化：
    藍色（起始狀態）：透過可變電阻調整並點亮藍燈，此時 LED 呈現單一的藍色。
    紫色（疊加紅色）：在藍燈亮的時候，按下按鈕加入紅燈。藍光與紅光混合後會呈現紫色。
    白色（疊加綠色）：在紫色的基礎上，透過序列埠輸入「1」點亮綠燈。當紅、綠、藍同時達到最大亮度疊加時就會呈現白色。


