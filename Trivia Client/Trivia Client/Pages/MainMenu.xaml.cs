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
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            //working but not as axpected
            MainMenuFrame.Content = new JoinRoom();

            //doesnt work but mabey it could help
            //JoinRoom joinRoom = new JoinRoom();
            //this.Content = joinRoom;
        }
        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            //working but not as axpected
            MainMenuFrame.Content = new CreateRoom();

            //doesnt work but mabey it could help
            //CreateRoom createRoom = new CreateRoom();
            //this.Content = createRoom;
        }
        private void Stats_Click(object sender, RoutedEventArgs e)
        {

            //working but not as axpected
            MainMenuFrame.Content = new Statistics();

            //doesnt work but mabey it could help
            //Statistics statistics = new Statistics();
            //this.Content = statistics;
        }
        private void HighScores_Click(object sender, RoutedEventArgs e)
        {

            //working but not as axpected
            MainMenuFrame.Content = new HighScores();

            //doesnt work but mabey it could help
            //HighScores highScore = new HighScores();
            //this.Content = highScore;
        }
        private void Logout_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
