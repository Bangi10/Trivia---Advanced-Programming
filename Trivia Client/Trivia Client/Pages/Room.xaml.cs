using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for Room.xaml
    /// </summary>
    ///
    public partial class Room : Page
    {
        private static object socketMutex = new Object();
        private bool isInThisPage;

        public Room()
        {
            InitializeComponent();
            usernameLabel.Content = User.Instance().GetUsername();
            isInThisPage = true;
            if (User.Instance().GetIsRoomAdmin())
            {
                leaveRoomButton.Visibility = Visibility.Collapsed;
            }
            else
            {
                closeRoomButton.Visibility = Visibility.Collapsed;
                startGameButton.Visibility = Visibility.Collapsed;
            }
            roomNameLabel.Content = "Room Name: " + User.Instance().GetRoom().name;
            maxPlayersLabel.Content = "Max Players: " + User.Instance().GetRoom().maxPlayers;
            numberOfQuestionsLabel.Content = "Number of Questions: " + User.Instance().GetRoom().numOfQuestionsInGame;
            timePerQuestionLabel.Content = "Time Per Question: " + User.Instance().GetRoom().timePerQuestion;


            Thread thread = new Thread(new ThreadStart(ThreadGetRoomState));
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
        }
        private void ThreadGetRoomState()
        {
            Thread.Sleep(100);

            while (isInThisPage)
            {
                GetRoomState();
                Thread.Sleep(333);
            }
        }
        private void GetRoomState()
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.GET_ROOM_STATE);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;
            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                //there will be a milisecond where this request won't fit the handler, and then it will stop because
                //of isInThisPage == false. thus no need to show message box here
            }
            else
            {
                GetRoomStateResponse response = JsonSerialization.deserializeResponse<GetRoomStateResponse>(jsonBuffer);
                if (isRoomClosed(response.players)) 
                {
                    //room deleted in server, handlers are changed in server, so all players "left room". all needed is to move screen on ui
                    this.Dispatcher.Invoke(() =>
                    {
                        isInThisPage = false;
                        NavigationService?.Navigate(new Pages.MainMenu());
                    });
                }
                else
                {
                    UpdatePlayersListUI(response.players);
                    if (response.hasGameBegun)
                    {
                        this.Dispatcher.Invoke(() =>
                        {
                            isInThisPage = false;
                            NavigationService?.Navigate(new Pages.Game());
                        });   

                    }
                }
            }
        }
        private void UpdatePlayersListUI(List<string> players)
        {
            this.Dispatcher.Invoke(() =>
            {
                playersList.Items.Clear();
                if (players != null && players.Count != 0)
                {
                    foreach (string player in players)
                    {
                        playersList.Items.Add(player);
                    }
                }
            });
            
        }
        private bool isRoomClosed(List<string> players)
        {
            //if no players, room closed
            return players == null || players.Count == 0;
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();
        }
        private void CloseRoom_Click(object sender, RoutedEventArgs e)
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.CLOSE_ROOM);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                MessageBox.Show(response.message);
            }
            else
            {
                isInThisPage = false;
                NavigationService?.Navigate(new Pages.MainMenu());

                User.Instance().SetIsRoomAdmin(false);
                User.Instance().ClearRoom();
            }
        }
        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.START_GAME);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                MessageBox.Show(response.message);
            }
            else
            {
                isInThisPage = false;
                NavigationService?.Navigate(new Pages.Game());

            }
        }
        private void LeaveRoom_Click(object sender, RoutedEventArgs e)
        {
            LeaveRoom();
        }
        private void LeaveRoom()
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.LEAVE_ROOM);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            if (Helper.isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                MessageBox.Show(response.message);
            }
            else
            {
                isInThisPage = false;
                NavigationService?.Navigate(new Pages.MainMenu());
                User.Instance().SetIsRoomAdmin(false);
                User.Instance().ClearRoom();
            }
        }
        
    }
}
