using System;
using System.Data;
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
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        public Signup()
        {
            InitializeComponent();
        }

        //adding new player and sending him to the MainMenu
        private void Signup_Click(object sender, RoutedEventArgs e)
        {
            //sending signup request
            if (username.Text == "")
                ErrorLabel.Content = "you need to enter a name";
            else if (password.Text == "")
                ErrorLabel.Content = "you need to enter a password";
            else if (email.Text == "")
                ErrorLabel.Content = "you need to enter email";
            else
            {
                SignupRequest request = new SignupRequest(username.Text, password.Text, email.Text);
                byte[] requestBuffer = JsonSerialization.serializeRequest<SignupRequest>(request, RequestsCodes.SIGNUP);
                ClientCommuinactor comm = ClientCommuinactor.Instance;
                comm.sendBytes(requestBuffer);
                //getting signup response
                var readTuple = comm.readBytes();
                byte[] jsonBuffer = readTuple.Item1;
                byte code = readTuple.Item2;
                //checking if response is successful
                if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
                {
                    ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                    ErrorLabel.Content = response.message;
                }
                else
                {
                    switch (code)
                    {
                        case (byte)ResponseCodes.SIGNUP.SUCCESS:
                            User.Instance(request.username);
                            Application.Current.Properties["Name"] = username.Text;
                            NavigationService?.Navigate(new MainMenu());
                            break;
                        case (byte)ResponseCodes.SIGNUP.NAME_ALREADY_EXISTS:
                            ErrorLabel.Content = "username with this name already exists";
                            break;
                    }
                }
            }
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            //logout
            Application.Current.Shutdown();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Start());

        }
    }
}
