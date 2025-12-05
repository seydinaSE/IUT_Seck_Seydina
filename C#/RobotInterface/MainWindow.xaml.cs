using System.IO.Ports;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ExtendedSerialPort_NS;
using System.Windows.Threading;

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    public partial class MainWindow : Window
    {
        byte CalculateChecksum;
        bool toogle;
        string receivedText;
        ExtendedSerialPort serialPort1;
        DispatcherTimer timerAffichage;
        Robot robot = new Robot();


        public MainWindow()
        {
            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
               

        }
        


        public void TimerAffichage_Tick(object sender, EventArgs e)
        {

            /*  if (robot.receivedText != "")
                  //TextBoxréception.Text += receivedText;
                  TextBoxréception.Text += robot.receivedText;

                  robot.receivedText = "";
              robot.receivedText = robot.byteListReceived.ToString();
            */

            while (robot.byteListReceived.Count > 0)
            {
                TextBoxréception.Text += "0x"+robot.byteListReceived.Dequeue().ToString("X2")+" "; //X2 c'est pour convertir en Hexadécimal 
               
            }
         

        }

        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
           
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);
                
            }
          
        }


        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
               
                //TextBoxréception.Text += ("Reçu : " + textBoxEmission.Text);
                serialPort1.Write(textBoxEmission.Text);

                //receivedText =textBoxEmission.Text ;
                
                textBoxEmission.Text = "";
            }
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {

            TextBoxréception.Text += ("Reçu : " + textBoxEmission.Text + "\n");
            textBoxEmission.Text = "";

            if (toogle == false)
            {
                buttonEnvoyer.Background = Brushes.RoyalBlue;
                toogle = !toogle;
            }
            else
            {
                buttonEnvoyer.Background = Brushes.Beige;
                toogle = !toogle;

            }
        }
      

        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {
            TextBoxréception.Text = "";
        }

        private void Test_Click(object sender, RoutedEventArgs e)
        {
          
            byte[] bytesliste = new byte[20];
            for (byte i = 0; i < 20; i++)
            {
                bytesliste[i]= (byte)(2 * i);
                
            }

            serialPort1.Write(bytesliste, 0, bytesliste.Length);



        }
        private byte CalculateChecksum(int msgFunction,int msgPayloadLength, byte[] msgPayload)
        {

            byte checksum = 0x00;
            checksum ^= 0xFE;

            checksum ^= 0x00;
            checksum^=(byte)
        }
    }
}