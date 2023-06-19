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
            if (Application.Current.Properties["first"].ToString() == "{}")
                ErrorLabel.Content = "nobody have score right now";
            else
            {
                first.Text = Application.Current.Properties["first"].ToString();
                firstPoints.Text = Application.Current.Properties["firstPoints"].ToString();
                second.Text = Application.Current.Properties["second"].ToString();
                secondPoints.Text = Application.Current.Properties["secondPoints"].ToString();
                third.Text = Application.Current.Properties["third"].ToString();
                thirdPoints.Text = Application.Current.Properties["thirdPoints"].ToString();
                congratsTextBox.Text = Application.Current.Properties["Name"].ToString();
                if (first.Text.Equals(Application.Current.Properties["Name"].ToString()) || 
                    second.Text.Equals(Application.Current.Properties["Name"].ToString()) ||
                    third.Text.Equals(Application.Current.Properties["Name"].ToString()))
                {
                    congratsTextBox.Text = "WOW you are at the top 3 best players\n you must be really smart or just lucky\neither way great job!!!";
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
            NavigationService?.Navigate(new Pages.Statistics());

        }
    }
}
