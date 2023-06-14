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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        public JoinRoom()
        {
            InitializeComponent();
            
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());
        }
        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {

        }
        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //logout
            Application.Current.Shutdown();

        }
        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;
            ComboBoxItem selectedComboBoxItem = (ComboBoxItem)roomsList.SelectedItem;
            string selectedValue = selectedComboBoxItem.Content.ToString();

            // Do something with the selected value
            selectedRoom.Content = "Selected Room: " + selectedValue;
        }
    }
}
