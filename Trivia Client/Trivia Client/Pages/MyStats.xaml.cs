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
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.Statistics());
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
    }
}
