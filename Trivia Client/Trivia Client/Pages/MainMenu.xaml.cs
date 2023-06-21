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
            //welcomeTextBox.Text = $"welcome {Application.Current.Properties["Name"].ToString()}";
            usernameLabel.Content = User.Instance().GetUsername();
        }
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
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
            bool successLogout = Helper.Logout();
            if (successLogout) 
            {
                NavigationService?.Navigate(new Start());
            }
        }
        
        
    }
}
