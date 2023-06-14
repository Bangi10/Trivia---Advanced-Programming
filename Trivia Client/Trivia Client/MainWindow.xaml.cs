using System;
using System.Collections.Generic;
using System.DirectoryServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Trivia_Client.Code;
using Trivia_Client.Pages;
using Json = System.Text.Json;

namespace Trivia_Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
<<<<<<< HEAD
            mainFrame.Content = new Pages.Start();
=======
            //Console.WriteLine(Encoding.UTF8.GetString(BitConverter.GetBytes(12302).Length));
>>>>>>> bcc1cbaf728fecb7780c9806e649b4dd789f7bef
        }

        

    }
}
