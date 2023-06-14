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

            byte[] jsonBuffer = comm.readBytes();
            LoginResponse response = JsonSerialization.deserializeResponse<LoginResponse>(jsonBuffer);
            if (response)


            NavigationService?.Navigate(new Start());
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Start());

        }
        
    }
}
