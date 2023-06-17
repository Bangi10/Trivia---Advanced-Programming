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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        public Statistics()
        {
            InitializeComponent();
        }
        private void MyStats_Click(object sender, RoutedEventArgs e)
        {
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.GET_STATISTICS"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.GET_STATISTICS);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            //getting getPersonalStatusResponse response
            var readTuple = comm.readBytes();
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;
            //checking if response is successful
            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                ErrorLabel.Content = response.message;
            }
            else if (code == (byte)ResponseCodes.ROOM.GOT_PERSONAL_STATS)
            {
                GetPersonalStatusResponse response = JsonSerialization.deserializeResponse<GetPersonalStatusResponse>(jsonBuffer);
                if (response.status == (byte)ResponseCodes.ROOM.GOT_PERSONAL_STATS)
                {

                    int avg = Convert.ToInt32(response.statistics[4][0]);

                    Application.Current.Properties["avgTimeForAnswer"] = response.statistics[4][0];
                    Application.Current.Properties["numOfRightAnswers"] = response.statistics[1][0];
                    int totalAnswers = Convert.ToInt32(response.statistics[2][0]);
                    int rightAnswers = Convert.ToInt32(response.statistics[1][0]);
                    int wrongAnswers = totalAnswers - rightAnswers;
                    Application.Current.Properties["numOfWrongAnswers"] = wrongAnswers.ToString();
                    Application.Current.Properties["numOfGamesPlayed"] = response.statistics[3][0];
                    NavigationService?.Navigate(new MyStats());
                }
                else
                {
                    ErrorLabel.Content = "you dont have stats right now";
                }
            }
        }
        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.GET_STATISTICS"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.GET_HIGH_SCORE);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            //getting GetHighScoreResponse response
            var readTuple = comm.readBytes();
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;
            //checking if response is successful
            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                ErrorLabel.Content = response.message;
            }
            else if (code == (byte)ResponseCodes.ROOM.GOT_HIGH_SCORE)
            {
                GetHighScoreResponse response = JsonSerialization.deserializeResponse<GetHighScoreResponse>(jsonBuffer);
                if (response.status == (byte)ResponseCodes.ROOM.GOT_PERSONAL_STATS)
                {
                    Application.Current.Properties["first"] = response.statistics[0];
                    Application.Current.Properties["firstPoints"] = response.statistics[1];
                    Application.Current.Properties["second"] = response.statistics[2];
                    Application.Current.Properties["secondPoints"] = response.statistics[3];
                    Application.Current.Properties["third"] = response.statistics[4];
                    Application.Current.Properties["thirdPoints"] = response.statistics[5];
                    NavigationService?.Navigate(new HighScores());
                }
                else
                {
                    ErrorLabel.Content = "nobody have score right now";
                }
            }
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //logout
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.LOGOUT"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.LOGOUT);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            Application.Current.Shutdown();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());

        }
    }
}
