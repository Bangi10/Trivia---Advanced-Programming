using System;
using System.Collections.Generic;
using System.ComponentModel;
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
            mainFrame.Content = new Pages.Start();
        }
        void DataWindow_Closing(object sender, CancelEventArgs e)
        {
            string msg = "Are you sure you want to exit?";
            MessageBoxResult result =
                MessageBox.Show(
                msg,
                "Data App",
                MessageBoxButton.YesNo,
                MessageBoxImage.Warning);
            if (result == MessageBoxResult.No)
            {
                // If user doesn't want to close, cancel closure
                e.Cancel = true;
            }
            else if (isLoggedIn())
            {
                bool successLogout = Helper.Logout();
            }
        }
        private bool isLoggedIn()
        {
            return (mainFrame.Content is not Pages.Start &&
                mainFrame.Content is not Pages.Login &&
                mainFrame.Content is not Pages.Signup);
        }

    }
}
