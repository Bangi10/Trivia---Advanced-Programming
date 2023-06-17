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
    /// Interaction logic for Login.xaml
    /// </summary>
    /// 
    public partial class Login : Page
    {
        public Login()
        {
            InitializeComponent();
        }


        private void Login_Click(object sender, RoutedEventArgs e)
        {
            //needs to add playerm if he doesnt exists
            LoginRequest request = new LoginRequest(username.Text, password.Text);
            byte[] requestBuffer = JsonSerialization.serializeRequest<LoginRequest>(request, RequestsCodes.LOGIN);
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
                    case (byte)ResponseCodes.LOGIN.SUCCESS:
                        User.Instance(request.username);
                        NavigationService?.Navigate(new MainMenu());
                        break;
                    case (byte)ResponseCodes.LOGIN.NAME_NOT_EXISTS:
                        ErrorLabel.Content = "username doesn't exist";
                        break;
                    case (byte)ResponseCodes.LOGIN.PASSWORD_MISMATCH:
                        ErrorLabel.Content = "username and password doesn't match";
                        break;
                    case (byte)ResponseCodes.LOGIN.USER_ALREADY_LOGINED:
                        ErrorLabel.Content = "user already logined";
                        break;
                }
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //no need to logout, user didn't connect login yet
            Application.Current.Shutdown();
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Start());

        }

    }
}
