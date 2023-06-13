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
            mainFrame.Content = new Pages.Login();
            //Console.WriteLine(Encoding.UTF8.GetString(BitConverter.GetBytes(12302).Length));
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            //sends to the login page
            Login login = new Login();
            this.Content = login;
        }
        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            //sends to the signup page
            Signup signup = new Signup();
            this.Content = signup;
        }
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

    }
}
