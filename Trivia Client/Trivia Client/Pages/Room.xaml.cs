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
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            bool successLogout = Helper.Logout();
            if (successLogout)
            {
                Application.Current.Shutdown();
            }
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());

        }
    }
}
