using System;
using System.Collections.Generic;
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

namespace Trivia_Client.Pages
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        public Signup()
        {
            InitializeComponent();
        }

        //adding new player and sending him to the MainMenu
        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            SignupRequest signupRequest = new SignupRequest(Username.Text, Password.Text, Email.Text);
            byte[] requestBuffer = JsonSerialization.serializeRequest(signupRequest, RequestsCodes.SIGNUP);
            ClientCommuinactor.sendBytes(requestBuffer);
            NavigationService?.Navigate(new MainMenu());
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //logout
            Application.Current.Shutdown();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Start());
        }
    }
}
