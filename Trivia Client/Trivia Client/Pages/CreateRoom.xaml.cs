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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        public CreateRoom()
        {
            InitializeComponent();
        }
        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            //needs to add playerm if he doesnt exists
            CreateRoomRequest request = new CreateRoomRequest(roomName.Text, Convert.ToUInt32(maxPlayers.Text),
                                                              Convert.ToUInt32(numberOfQuestions.Text), Convert.ToUInt32(timePerQuestion.Text));
            byte[] requestBuffer = JsonSerialization.serializeRequest<CreateRoomRequest>(request, RequestsCodes.CREATE_ROOM);
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
            else if (code == (byte)ResponseCodes.ROOM.CREATED_ROOM)
            {
                User.Instance().SetIsRoomAdmin(true);
                NavigationService?.Navigate(new Room());
            }
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();

        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());
        }
        

    }
}
