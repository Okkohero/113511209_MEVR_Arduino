**`Lab3/Task3-2/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 3-2 LED Control with Serial Communication

- **學生姓名**：[林玉惠]
- **學生學號**：[113511209]
- **完成日期**：2026-09-30

---

### 1. 實驗目標(可參考課程投影片寫法)
- 掌握 C# Windows Forms 視窗應用程式與 Arduino 透過 UART 序列埠（Serial Port）之雙向通訊技術。
- 實現電腦端向 Arduino 傳輸指令以控制 LED 開關。   
- 學習在 Arduino 端讀取外接實體按鈕輸入狀態，並透過序列埠即時回傳給電腦。
- 掌握 C# SerialPort.DataReceived 非同步事件監聽機制，並運用 Invoke 安全更新主執行緒 UI 畫面。

### 2. 設備與元件

- Arduino Uno 開發板 x 1
- USB 傳輸線 x 1
- LED 燈泡 x 1
- 按鈕 x 1
- 麵包板與杜邦線 若干
- 個人電腦（已安裝 .NET SDK、VS Code 及 Arduino IDE）

### 3. 操作說明與成果
1. 電路連接與燒錄：將實體按鈕一端接至 Arduino Pin 2，另一端接 GND，程式內啟用 INPUT_PULLUP 內部上拉電阻。將 Arduino 連接至電腦，開啟專案 .ino 檔編譯並燒錄至開發板。
2. 啟動 C# 視窗程式：確認裝置管理員中 Arduino 連接之 COM 埠代號，於 C# 程式碼設定對應埠號與鮑率 9600 baud。確保關閉 Arduino IDE 之序列埠監控器，於終端機執行 dotnet run 啟動上位機圖形介面。   
3. 實驗成果：
    下行控制（PC -> Arduino）：點擊視窗上的「開啟」按鈕時，C# 傳送 "ON" 字串，Arduino 接收後將 Pin 13 設為 HIGH ，C# 端按鈕變綠；點擊「關閉」按鈕時傳送 "OFF"，LED 熄滅且按鈕變紅。   
    上行回傳（Arduino -> PC）：按下 Arduino 外接實體按鈕時，微控制器透過序列埠回傳 "BUTTON_PRESSED"，C# 視窗即時更新文字為紅色的 Arduino 狀態: Button Pressed!；放開按鈕時回傳 "BUTTON_RELEASED"，C# 視窗恢復為灰色的 Arduino 狀態: Button Released。   
4. 操作影片：請參閱同目錄下 video/Task3-2.mp4 之實際操作畫面。
