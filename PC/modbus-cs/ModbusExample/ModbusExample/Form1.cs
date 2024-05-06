using NModbus;
using NModbus.Data;
using NModbus.IO;
using NModbus.Utility;
using NModbus.Device;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Threading;
using NModbus.Extensions.Enron;

namespace ModbusExample
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte slaveId = 1;
            int port = 502;
            IPAddress address = new IPAddress(new byte[] { 192, 168, 0, 100 });
            TcpClient masterTcpClient = new TcpClient(address.ToString(), port);

            var factory = new ModbusFactory();
            IModbusMaster master = factory.CreateMaster(masterTcpClient);

            ushort startAddress = 100;
            ushort[] registers = new ushort[] { 1, 10, 100 };

            

            //master.WriteMultipleRegisters(slaveId, startAddress, registers);

            // read five register values
            ushort[] inputs = master.ReadInputRegisters(slaveId, startAddress, 1);
            //ushort[] inputs = master.ReadHoldingRegisters(slaveId, startAddress, 3);
            master.WriteSingleRegister(slaveId, startAddress, 1);
            for (int i = 0; i < 1; i++)
            {
                Console.WriteLine($"Register {(startAddress + i)}={(inputs[i])}");
            }
            masterTcpClient.Close();

        }
    }
}
