using System;
using System.Collections.Generic;
using System.Linq;
using System.Media;
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
        SoundPlayer player = new SoundPlayer(@"sounds\stats.wav");
        public MyStats()
        {
            InitializeComponent();
            player.Load();
            player.Play();
            User user = User.Instance();
            numOfGamesPlayed.Text = user.GetGamesPlayed().ToString();
            numOfRightAnswers.Text = user.GetRightAnswers().ToString();
            numOfWrongAnswers.Text = (user.GetTotalAnswers()-user.GetRightAnswers()).ToString();
            avgTimeForAnswer.Text = user.GetAvgTimeForAnswer().ToString();
            usernameLabel.Content = user.GetUsername();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            player.Stop();
            NavigationService?.Navigate(new Pages.Statistics());
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();
        }
    }
}
