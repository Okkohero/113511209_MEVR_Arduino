using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;

namespace LEDSerialControl
{
    public partial class Form1 : Form
    {
        private SerialPort? _serialPort;
        private Button btnOn = null!;
        private Button btnOff = null!;
        private Label lblButtonStatus = null!;

        public Form1()
        {
            InitializeComponent();
            InitializeSerial();
        }

        // 動態生成 UI 元件（自動置中排版）
        private void InitializeComponent()
        {
            this.Text = "LED 控制面板";
            this.ClientSize = new Size(650, 360);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.MinimumSize = new Size(500, 300);

            // 建立垂直排版的置中容器
            TableLayoutPanel mainLayout = new TableLayoutPanel
            {
                Dock = DockStyle.Fill,
                ColumnCount = 1,
                RowCount = 2,
            };
            mainLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 55F)); // 上半部放按鈕
            mainLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 45F)); // 下半部放狀態文字

            // 放按鈕的水平容器（讓按鈕水平並排且置中）
            FlowLayoutPanel buttonPanel = new FlowLayoutPanel
            {
                AutoSize = true,
                Anchor = AnchorStyles.None, 
                FlowDirection = FlowDirection.LeftToRight,
                WrapContents = false
            };

            // 1. 建立 ON 按鈕（加大尺寸至 160x70，字體 16pt）
            btnOn = new Button
            {
                Text = "開啟",
                Size = new Size(160, 70),
                Font = new Font("微軟正黑體", 16F, FontStyle.Bold),
                Margin = new Padding(20),
                Cursor = Cursors.Hand
            };
            btnOn.Click += btnOn_Click;

            // 2. 建立 OFF 按鈕
            btnOff = new Button
            {
                Text = "關閉",
                Size = new Size(160, 70),
                Font = new Font("微軟正黑體", 16F, FontStyle.Bold),
                Margin = new Padding(20),
                Cursor = Cursors.Hand
            };
            btnOff.Click += btnOff_Click;

            buttonPanel.Controls.Add(btnOn);
            buttonPanel.Controls.Add(btnOff);

            // 3. 建立狀態標籤（字體加大至 18pt，永遠置中）
            lblButtonStatus = new Label
            {
                Text = "Arduino 狀態: Button Released!",
                Dock = DockStyle.Fill,
                Font = new Font("微軟正黑體", 18F, FontStyle.Bold),
                ForeColor = Color.DimGray,
                TextAlign = ContentAlignment.TopCenter // 位於下半部的靠上置中位置
            };

            // 將區塊加入主容器
            mainLayout.Controls.Add(buttonPanel, 0, 0);
            mainLayout.Controls.Add(lblButtonStatus, 0, 1);

            // 將容器加入視窗
            this.Controls.Add(mainLayout);
        }

        private void InitializeSerial()
        {
            try
            {
                _serialPort = new SerialPort("COM5", 9600);
                _serialPort.DataReceived += new SerialDataReceivedEventHandler(SerialPort_DataReceived);
                _serialPort.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"無法開啟序列埠: {ex.Message}");
            }
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                if (_serialPort != null && _serialPort.IsOpen)
                {
                    string incomingData = _serialPort.ReadLine().Trim();

                    this.Invoke(new Action(() =>
                    {
                        if (incomingData == "BUTTON_PRESSED")
                        {
                            lblButtonStatus.Text = "Arduino 狀態: Button Pressed!";
                            lblButtonStatus.ForeColor = Color.Red;
                        }
                        else if (incomingData == "BUTTON_RELEASED")
                        {
                            lblButtonStatus.Text = "Arduino 狀態: Button Released!";
                            lblButtonStatus.ForeColor = Color.DimGray;
                        }
                    }));
                }
            }
            catch (Exception)
            {
                // 預防視窗關閉時產生的例外
            }
        }

        // 點擊 ON 按鈕
        private void btnOn_Click(object? sender, EventArgs e)
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.WriteLine("ON");
                btnOn.BackColor = Color.LightGreen;
                btnOff.BackColor = SystemColors.Control;
                this.Text = "LED 狀態: 已開啟 (ON)";
            }
        }

        // 點擊 OFF 按鈕
        private void btnOff_Click(object? sender, EventArgs e)
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.WriteLine("OFF");
                btnOn.BackColor = SystemColors.Control;
                btnOff.BackColor = Color.LightCoral;
                this.Text = "LED 狀態: 已關閉 (OFF)";
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.Close();
            }
            base.OnFormClosing(e);
        }
    }
}