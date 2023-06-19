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
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        public Room()
        {
            InitializeComponent();
            if (User.Instance().GetIsRoomAdmin())
            {
                leaveRoomButton.Visibility = Visibility.Collapsed;
            }
            else
            {
                closeRoomButton.Visibility = Visibility.Collapsed;
                startGameButton.Visibility = Visibility.Collapsed;
            }
        }
        private void threadGetRoomState()
        {
            //will be future implemented
        }
        private void GetRoomState()
        {

            //will be future implemented
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();
        }
        private void CloseRoom_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void StartGame_Click(object sender, RoutedEventArgs e)
        {

        }
        private void LeaveRoom_Click(object sender, RoutedEventArgs e)
        {

        }
        
    }
}
