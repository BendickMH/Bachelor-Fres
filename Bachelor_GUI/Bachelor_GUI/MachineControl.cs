using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Net.Sockets;
using System.Net;
using System.Management;
using System.IO;



namespace Bachelor_GUI
{
    public partial class MachineControl : Form
    {
        private delegate void oppdaterSerialMonitor(string mld);
        private delegate void SetTextDeleg(string text);
        private delegate void streamGC();

        // Port:
        private SerialPort comPort;
        private int selectedBaud;

        // Flow control
        private bool paused;
        private bool stopped;
        private char[] acceptedLetters = new char[]{'G','M'};

        public MachineControl()
        {
            InitializeComponent();
        }

        // Kjører i load: Oppdaterer nødvendig GUI
        private void MachineControl_Load(object sender, EventArgs e)
        {
            updateComPort();
            updateBaud();
            xStepSizetxtbx.Text = "1";
            yStepSizetxtbox.Text = "1";
            zStepSizetxtbx.Text = "1";
        }

        // Kobling til valgt seriell port:
        private void connectBtn_Click(object sender, EventArgs e)
        {
            if(comPort != null && comPort.IsOpen)
            {
                comPort.Close();
                if (!comPort.IsOpen)
                {
                    PortInfo.Text = $"Not Connected";
                    connectBtn.Text = "Connect";
                    ComPortCB.Enabled = true;
                }
            }
            else if(ComPortCB.SelectedIndex >= 0)
            {
                try
                {
                    ComPortCB.Enabled = false; // Deaktiverer valg av comporter
                    comPort = new SerialPort(ComPortCB.SelectedItem.ToString(), selectedBaud, Parity.None, 8, StopBits.One);
                    comPort.Handshake = Handshake.None;
                    comPort.DataReceived += new SerialDataReceivedEventHandler(MottaData);
                    comPort.WriteTimeout = 500;
                    comPort.Open();
                    comPort.Write("\r\n\r\n");
                    if (comPort.IsOpen)
                    {
                        PortInfo.Text = $"Connected to {ComPortCB.SelectedItem.ToString()}";
                        connectBtn.Text = "Disconnect";
                    }
                }
                catch
                {
                    MessageBox.Show("Error", "Error 2", MessageBoxButtons.OK);
                }
            }
        }

        // Gui behandling:
      
        // Oppdatering av comport listen:
        public void updateComPort()
        {
           string[] portNames = SerialPort.GetPortNames();

            foreach(string s in portNames)
            {
                ComPortCB.Items.Add(s);
            }
            if(ComPortCB.Items.Count > 0)
            {
                ComPortCB.SelectedIndex = 0;
            }

            PortInfo.Text = "Not Connected";
        }
        // Oppdatering av baudrate listen:
        public void updateBaud()
        {
            int[] baudRates = new int[8]{ 9600, 19200, 38400, 57600, 74880, 115200, 230400, 250000};
            foreach(int bd in baudRates)
            {
                baudRateList.Items.Add(bd);
            }
            if(baudRateList.Items.Count > 0)
            {
                baudRateList.SelectedIndex = 5;
                selectedBaud = (int)baudRateList.SelectedItem;
            }
        }
        // Oppdatering av endret baudrate:
        private void baudRateList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (baudRateList.Items.Count > 0)
            {
                selectedBaud = (int)baudRateList.SelectedItem;
                try
                {
                    if (comPort != null && comPort.IsOpen)
                    {
                        comPort.BaudRate = selectedBaud;
                    }
                }
                catch (Exception except)
                {
                    // Legg inn exception handling
                }
            }
        }
        // Oppdater Serial Monitor:
        public void updateSerialMonitor(string mld)
        {
            SerialMonitorLB.Items.Add(mld);
            int nItems = (int)(SerialMonitorLB.Height / SerialMonitorLB.ItemHeight);
            SerialMonitorLB.TopIndex = SerialMonitorLB.Items.Count - nItems;
        }
        // Send kommando fra kommando linjen:
        private void CommandTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (CommandTextBox.Text != "")
            {
                if (e.KeyCode == Keys.Enter)
                {
                    sendCommand(CommandTextBox.Text);
                    CommandTextBox.Text = "";
                }
            }
        }
        // Rens seriell monitor:
        private void clearMonitorBtn_Click(object sender, EventArgs e)
        {
            SerialMonitorLB.Items.Clear();
        }

        // Seriell kommunikasjon:

        // Send kommando
        public void sendCommand(string cmd)
        {
            if (comPort != null)
            {
                try
                {
                    cmd = cmd + "\n";
                    comPort.Write(cmd);
                    skrivTilMonitor(cmd);
                }
                catch (Exception unntak)
                {
                    // Finn en exception handling
                }
            }
            else
            {
                // do nothing;
            }

        }
        // Skriv mottatt Melding:
        public void skrivTilMonitor(string data)
        {
            string mld = data;
            oppdaterSerialMonitor updateSM = new oppdaterSerialMonitor(this.updateSerialMonitor);
            this.Invoke(updateSM, mld);
        }
        // Motta data:
        void MottaData(object sender, SerialDataReceivedEventArgs e)
        {
            while (comPort.BytesToRead > 0)
            {
                string data = comPort.ReadLine();
                this.BeginInvoke(new SetTextDeleg(si_MottaData), new object[] { data });
            }
        }
        // ??:
        private void si_MottaData(string data) { updateSerialMonitor(data); }
        // Fil åpning:
        private void BrowseButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            DialogResult res = openFileDialog.ShowDialog();
            if(res == DialogResult.OK)
            {
                GCListBox.Items.Clear();
                string filename = openFileDialog.FileName;
                try
                {
                    fileNametxtbx.Text = filename;
                    string[] fileLines = File.ReadAllLines(filename);
                    foreach(var line in fileLines)
                    {
                        GCListBox.Items.Add(line);
                    }
                }
                catch (IndexOutOfRangeException f)
                { 
                }
            }
        }
        // Start G-Kode strømming
        private void startBtn_Click(object sender, EventArgs e)
        {
            if (GCListBox.Items.Count > 0)
            {
                startBtn.Enabled = false;
                pauseBtn.Enabled = true;
                stopBtn.Enabled = true;
                Thread streamGC = new Thread(streamGcode);
                streamGC.Start();
            }
            else
            {
                // Do nothing
            }

        }
        public void streamGcode()
        {
            bool waitingForOk;

            foreach (string item in GCListBox.Items)
            {
                waitingForOk = true;

                if (!stopped)
                {
                    if (!paused)
                    {


                        if (item.StartsWith("G") || item.StartsWith("M"))
                        {
                            sendCommand(item);
                            Thread.Sleep(100);
                            while (waitingForOk)
                            {
                                if (SerialMonitorLB.Items[SerialMonitorLB.Items.Count - 1].ToString().Contains("ok"))
                                {
                                    waitingForOk = false;
                                }
                                Thread.Sleep(1000);
                            }
                        }
                        else
                        {
                            skrivTilMonitor($"Skipped line: {item}");
                        }
                    }
                    else 
                    {
                        while(paused)
                        { 
                            // wait for unpause
                        }
                    }
                }
            }
            startBtn.Enabled = true;
            pauseBtn.Enabled = false;
            stopBtn.Enabled = false;
        }

        // Jogging:

        private void JogXNBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91X-{xStepSizetxtbx.Text}F10000");
        }
        private void JogXPBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91X{xStepSizetxtbx.Text}F10000");
        }
        private void JogYPBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91Y{yStepSizetxtbox.Text}F10000");
        }

        private void JogYNBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91Y-{yStepSizetxtbox.Text}F10000");
        }

        private void JogZPBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91Z{zStepSizetxtbx.Text}F10000");
        }

        private void JogZNBtn_Click(object sender, EventArgs e)
        {
            sendCommand($"$J=G21G91Z-{zStepSizetxtbx.Text}F10000");
        }

        // Ubrukt og uheldig
        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }
        private void label4_Click(object sender, EventArgs e)
        {

        }
        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void pauseBtn_Click(object sender, EventArgs e)
        {
            paused = !paused;
        }

        private void stopBtn_Click(object sender, EventArgs e)
        {
            stopped = !stopped;
            stopSequence();
        }

        private void stopSequence()
        {

            paused = false;
            
        }

        private void ZeroBtn_Click(object sender, EventArgs e)
        {
            sendCommand("G10 P0 L20 X0 Y0 Z0");
        }

        private void unlockBtn_Click(object sender, EventArgs e)
        {
            sendCommand("$X");
        }
    }
}
