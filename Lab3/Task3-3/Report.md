**`Lab3/Task3-3/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 3-3 HC-05 Wireless LED Control

- **學生姓名**：[林玉惠]
- **學生學號**：[113511209]
- **完成日期**：2026-09-30

---

### 1. 實驗目標(可參考課程投影片寫法)
- 掌握 HC-05 藍牙模組之硬體配置與無線序列埠通訊原理。   
- 學習在 Arduino 端運用 SoftwareSerial 建立軟體序列埠與 HC-05 模組溝通，保留硬 體序列埠供除錯使用。實現電腦端（上位機）C# Windows Forms 應用程式透過藍牙無線序列埠（Bluetooth Serial Port）控制 Arduino 腳位上的 LED 燈。   
- 實現 Arduino 實體按鈕狀態即時經由藍牙無線回傳至 PC 端，並透過非同步事件與 Invoke 更新上位機 UI 畫面。

### 2. 設備與元件

- Arduino Uno 開發板 x 1
- HC-05 藍牙模組 x 1   
- USB 傳輸線 x 1
- LED x 1
- 按鈕 x 1
- 麵包板與杜邦線 若干
- 個人電腦（已安裝 .NET SDK、VS Code 及 Arduino IDE）

### 3. 操作說明與成果
1. 電路連接與燒錄：
    將 HC-05 模組之 VCC 接至 5V、GND 接至 GND；TXD 接至 Arduino Pin 10、RXD 接至 Pin 11。將按鈕接至 Arduino  Pin 2 與 GND。將 3-2 修改後的 SoftwareSerial 藍牙通訊程式燒錄至 Arduino Uno 開發板。
2. 藍牙配對與 COM 埠確認：開啟 Windows 藍牙設定，搜尋並配對 HC-05 模組。於藍牙設定「COM 連接埠」中確認對應之連出（Outgoing）虛擬序列埠代號。  
3. 啟動 C# 視窗程式：於 C# 程式碼中將序列埠指定為藍牙連出埠（COM5，鮑率 9600），於終端機執行 dotnet run 啟動上位機視窗程式，此時 HC-05 模組指示燈轉為慢閃，代表藍牙連線成功建立。
4. 實驗成果：
    無線下行控制（PC -> HC-05 -> Arduino）：點擊上位機「開啟」按鈕，透過藍牙發送 "ON" 指令，Arduino 接收後將 Pin 13 設為 HIGH，C# 端按鈕變綠；點擊「關閉」發送 "OFF"，LED 熄滅且按鈕變紅。
    無線上行回傳（Arduino -> HC-05 -> PC）：按下 Arduino 實體按鈕時，微控制器透 過藍牙回傳 "BUTTON_PRESSED"，C# 視窗即時更新文字為紅色的 Arduino 狀態: Button Pressed!；放開按鈕時回傳 "BUTTON_RELEASED"，C# 視窗恢復為灰色的 Arduino 狀態: Button Released!。
5. 操作影片：請參閱同目錄下 video/Task3-2.mp4 之實際操作畫面。
