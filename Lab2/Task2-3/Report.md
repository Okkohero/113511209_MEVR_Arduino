**`Lab2/Task2-3/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 2-3 External Interrupt vs Polling

- **學生姓名**：[林玉惠]
- **學生學號**：[113511209]
- **完成日期**：2026-09-24

---

### 1. 實驗目標(可參考課程投影片寫法)
- 學習使用 External Interrupt 機制來控制 LED 狀態。
- 學習實作 Polling 機制，透過不斷讀取腳位狀態來控制硬體，並用Edge detection 偵測按鈕按壓轉換的瞬間。
- 學習利用 `delay(2000)` 模擬系統處於 Busy 的狀態，藉此測試不同硬體控制機制的可靠性。
- 學習比較 External Interrupt 與 Polling 兩種機制的行為差異。
### 2. 設備與元件
- Arduino Uno 開發板 x 1
- LED x 2
- 按鈕開關 x 2
- 電阻 x 2
- 麵包板與連接線材若干
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果
1. **硬體接線**：將 Button A 接至腳位 2，LED A 接至腳位 13；將 Button B 接至腳位 3，LED B 接至腳位 12。
2. **燒錄程式**：使用 USB 線連接 Arduino，將下方附錄之程式碼編譯並點擊「上傳」。
3. **實驗成果**：
   - **Button A (External Interupt)**：不受主程式延遲的影響，按下按鈕瞬間能即時觸發硬體中斷並切換 LED A 的明暗狀態。
   - **Button B (Polling)**：受到主迴圈 `delay(2000)` 的影響，出現嚴重的反應遲鈍與漏接現象。必須在程式剛好結束延遲的瞬間按下，才能成功偵測到邊緣觸發並切換 LED B。此現象對比出在系統忙碌時，兩者即時性的差異。
4. **操作影片**：請參閱同目錄下 `video/Task2-3.mp4` 之實際操作畫面。