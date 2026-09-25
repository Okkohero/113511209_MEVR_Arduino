**`Lab3/Task3-1/report.md`（完整示範報告）**

```markdown
# 課題報告：Task 3-1 Timer Interrupt vs Blocking Delay

- **學生姓名**：[林玉惠]
- **學生學號**：[113511209]
- **完成日期**：2026-09-25

---

### 1. 實驗目標(可參考課程投影片寫法)
- 掌握 TimerOne 函式庫之使用方式，設定週期為 50ms 的 Timer Interrupt。   
- 學習撰寫 ISR，並在其中即時讀取按鈕狀態以控制 LED。   
- 比較 Timer Interrupt 與 Blocking Delay 在系統響應速度與即時性上的差異。

### 2. 設備與元件
- Arduino 開發板 x 1   
- 麵包板 x 1   
- 按鈕 x 2   
- LED x 2   
- 限流電阻 x 2
- 杜邦線數條   
- USB 連接線 x 1   
- 個人電腦（已安裝 Arduino IDE 與 TimerOne 函式庫）x 1  

### 3. 操作說明與成果
1. 電路組裝：將 Button A、LED A 與 Button B、LED B 連接至 Arduino 腳位，按鈕輸入使用內部上拉電阻（INPUT_PULLUP）。   
2. 安裝函式庫與燒錄：於 Arduino IDE 程式庫管理員安裝 TimerOne 函式庫，確認程式碼變數與腳位對應正確後，上傳至開發板。   
3. 實驗成果：
    Button A + LED A（中斷組）：每 50ms 觸發一次 ISR，按鈕按下與放開均能即時同步開關燈，不受主程式延遲影響。   
    Button B + LED B（阻斷組）：受 loop() 結尾 delay(1000) 影響，按鈕反應遲鈍；按下點亮後放開，LED B 仍會維持點亮最多約 1 秒才熄滅。   
4. 操作影片：請參閱同目錄下 video/Task3-1.mp4 之實際操作畫面。