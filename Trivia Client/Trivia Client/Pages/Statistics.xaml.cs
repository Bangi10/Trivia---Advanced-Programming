using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
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
            usernameLabel.Content = User.Instance().GetUsername();
        }
        public class userStatistics
        {
            public int NumOfCorrectAnswers { get; set; }
            public int NumOfPlayerGames { get; set; }
            public int NumOfTotalAnswers { get; set; }
            public float PlayerAverageAnswerTime { get; set; }
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
                    User user = User.Instance();
                    string statistics = response.statistics;
                    userStatistics j = JsonSerializer.Deserialize<userStatistics>(statistics);
                    user.setAvgTimeForAnswer(j.PlayerAverageAnswerTime);
                    user.setRightAnswers(j.NumOfCorrectAnswers);
                    user.setTotalAnswers(j.NumOfTotalAnswers);
                    user.setGamesPlayed(j.NumOfPlayerGames);
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
                if (response.status == (byte)ResponseCodes.ROOM.GOT_HIGH_SCORE)
                {
                    if (response.statistics[0] != "{}")
                    {
                        string firstName = response.statistics[0];
                        char[] trimChars = { '{', '}', '"','"','}'};
                        firstName = firstName.Trim(trimChars);
                        string firstPointsAndSecondName = response.statistics[1];
                        string separatingString = ",";
                        string[] firstPointsAndSecondNameSplited = firstPointsAndSecondName.Split(separatingString, System.StringSplitOptions.RemoveEmptyEntries);
                        string firstPoints = firstPointsAndSecondNameSplited[0];
                        Application.Current.Properties["first"] = firstName;
                        Application.Current.Properties["firstPoints"] = firstPoints;
                        if (response.statistics.Count()>2)
                        {
                            string secondName = firstPointsAndSecondNameSplited[1].Trim(trimChars);
                            Application.Current.Properties["second"] = secondName;
                            string secondPointsAndThirdName = response.statistics[2];
                            string[] secondPointsAndThirdNameSplited = secondPointsAndThirdName.Split(separatingString, System.StringSplitOptions.RemoveEmptyEntries);
                            string secondPoints = secondPointsAndThirdNameSplited[0];
                            Application.Current.Properties["secondPoints"] = secondPoints;
                            if (response.statistics.Count()>=4)
                            {
                                string thirdName = secondPointsAndThirdNameSplited[1].Trim(trimChars);
                                Application.Current.Properties["third"] = thirdName;
                                string[] separatingStrings = { ",", "}" };
                                string thirdPointsAndfourthName = response.statistics[3];
                                string[] thirdPointsAndfourthNameSplited = secondPointsAndThirdName.Split(separatingString, System.StringSplitOptions.RemoveEmptyEntries);
                                string thirdPoints = secondPointsAndThirdNameSplited[0];
                                Application.Current.Properties["thirdPoints"] = thirdPoints;
                            }
                            else
                            {
                                Application.Current.Properties["third"] = "";
                                Application.Current.Properties["thirdPoints"] = "";
                            }
                        }
                        else
                        {
                            Application.Current.Properties["second"] = "";
                            Application.Current.Properties["secondPoints"] = "";
                            Application.Current.Properties["third"] = "";
                            Application.Current.Properties["thirdPoints"] = "";
                        }
                    }
                    NavigationService?.Navigate(new HighScores());
                }
            }
        }
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            //it doesnt matter what type it is as long as we send to seriailiz "RequestsCodes.LOGOUT"
            SignupRequest request = new SignupRequest();
            byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.LOGOUT);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);
            var readTuple = comm.readBytes();
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                ErrorLabel.Content = response.message;
            }
            else
            {
                switch (code)
                {
                    case (byte)ResponseCodes.LOGOUT.SUCCESS:
                        NavigationService?.Navigate(new Start());
                        break;
                    case (byte)ResponseCodes.LOGOUT.NAME_NOT_EXISTS:
                        ErrorLabel.Content = "username doesn't exist";
                        break;
                    case (byte)ResponseCodes.LOGOUT.USER_NOT_LOGINED:
                        ErrorLabel.Content = "usern isnt logined";
                        break;
                }
            }
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());

        }
    }
}
