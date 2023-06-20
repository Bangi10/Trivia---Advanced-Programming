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
    /// Interaction logic for MyStats.xaml
    /// </summary>
    public partial class MyStats : Page
    {
        public MyStats()
        {
            InitializeComponent();
            numOfGamesPlayed.Text = $"{Application.Current.Properties["numOfGamesPlayed"].ToString()}";
            numOfRightAnswers.Text = $"{Application.Current.Properties["numOfRightAnswers"].ToString()}";
            numOfWrongAnswers.Text = $"{Application.Current.Properties["numOfWrongAnswers"].ToString()}";
            avgTimeForAnswer.Text = $"{Application.Current.Properties["avgTimeForAnswer"].ToString()}";
            usernameLabel.Content = User.Instance().GetUsername();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.Statistics());
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();
        }
    }
}
