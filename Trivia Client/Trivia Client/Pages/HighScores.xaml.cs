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
    /// Interaction logic for RecordsTable.xaml
    /// </summary>
    public partial class HighScores : Page
    {
        public HighScores()
        {
            InitializeComponent();
            first.Text = $"{Application.Current.Properties["first"].ToString()}";
            firstPoints.Text = $"{Application.Current.Properties["firstPoints"].ToString()}";
            second.Text = $"{Application.Current.Properties["second"].ToString()}";
            secondPoints.Text = $"{Application.Current.Properties["secondPoints"].ToString()}";
            third.Text = $"{Application.Current.Properties["third"].ToString()}";
            thirdPoints.Text = $"{Application.Current.Properties["thirdPoints"].ToString()}";
        }
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.LOGOUT"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.LOGOUT);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            Application.Current.Shutdown();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.Statistics());

        }
    }
}
