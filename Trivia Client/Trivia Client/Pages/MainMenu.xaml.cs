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
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page
    {
        public MainMenu()
        {
            InitializeComponent();
            welcomeTextBox.Text = $"welcome {Application.Current.Properties["Name"].ToString()}";
        }
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            //logout
            Logout_Click(sender, e);
            Application.Current.Shutdown();
        }
        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new JoinRoom());
        }
        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new CreateRoom());
        }
        private void Stats_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Statistics());
        }
        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new HighScores());
        }
        private void Logout_Click(object sender, RoutedEventArgs e)
        {
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.LOGOUT"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.LOGOUT);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            NavigationService?.Navigate(new Start());
        }
    }
}
