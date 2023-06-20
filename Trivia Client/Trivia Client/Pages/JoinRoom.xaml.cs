using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Reflection;
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
using static Trivia_Client.Code.ResponseCodes;

namespace Trivia_Client.Pages
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private List<RoomData> rooms;
        private bool isInThisPage;
        private static object socketMutex = new Object();
        private static object roomsMutex = new Object();

        public JoinRoom()
        {
            InitializeComponent();
            usernameLabel.Content = User.Instance().GetUsername();
            isInThisPage = true;
            Thread thread = new Thread(new ThreadStart(ThreadUpdateRoomsAndPlayersInSelected));
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            isInThisPage = false;
            NavigationService?.Navigate(new Pages.MainMenu());
        }
        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            //needs to add playerm if he doesnt exists
            if (GetSelectedRoomName() == "None")
                return;
            string selectedRoomName = GetSelectedRoomName();
            JoinRoomRequest request = new JoinRoomRequest(GetRoomId(selectedRoomName));
            byte[] requestBuffer = JsonSerialization.serializeRequest<JoinRoomRequest>(request, RequestsCodes.JOIN_ROOM);
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
                ErrorLabel.Content = response.message;
            }
            else if (code == (byte)ResponseCodes.ROOM.JOIN_ROOM_FULL)
            {
                ErrorLabel.Content = "Room is full!";
            }
            else
            {
                User.Instance().SetIsRoomAdmin(false);
                User.Instance().SetRoom(GetRoom(selectedRoomName));
                isInThisPage = false;
                NavigationService?.Navigate(new Pages.Room());
            }
        }
        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            UpdateRoomsAndPlayersInSelected();
        }
        private void ThreadUpdateRoomsAndPlayersInSelected()
        {
            Thread.Sleep(100);
            while (isInThisPage)
            {
                UpdateRoomsAndPlayersInSelected();
                Thread.Sleep(333);
            }
        }
        private void UpdateRoomsAndPlayersInSelected()
        {
            string previouslySelected = GetSelectedRoomName();
            lock (roomsMutex)
            {
                rooms = GetRooms();
            }
            this.Dispatcher.Invoke(() =>
            {
                UpdateRoomsListUI(previouslySelected);
                if (previouslySelected != "None")
                {
                    List<string> players = GetPlayersInRoom(GetRoomId(previouslySelected)); ;
                    UpdatePlayersListUI(players);
                }
            });
        }
        private void UpdateRoomsListUI(string previouslySelected)
        {
            roomsList.Items.Clear();

            lock (roomsMutex)
            {
                if (rooms != null && rooms.Count != 0)
                {
                    availableRoomsLabel.Content = "";
                    foreach (RoomData roomData in rooms)
                    {
                        roomsList.Items.Add(roomData.name);
                    }
                    if (previouslySelected == "None" || !doesRoomExist(previouslySelected))
                    {
                        roomsList.SelectedIndex = 0;
                    }
                    else
                    {
                        roomsList.SelectedValue = previouslySelected;
                    }
                }
                else
                {
                    availableRoomsLabel.Content = "No available rooms at the moment";
                }
            }
            
        }
        private bool doesRoomExist(string roomName)
        {
            lock (roomsMutex)
            {
                foreach (RoomData roomData in rooms)
                {
                    if (roomData.name == roomName)
                        return true;
                }
            }
            return false;
        }
        private void UpdatePlayersListUI(List<string> players)
        {
            playersList.Items.Clear();
            if (players != null && players.Count != 0)
            {
                foreach (string player in players)
                {
                    playersList.Items.Add(player);
                }
            }
        }
        private uint GetRoomId(string roomName)
        {
            uint roomId = 0;
            lock(roomsMutex)
            {
                foreach (RoomData roomData in rooms)
                {
                    if (roomData.name == roomName)
                        roomId = roomData.id;
                }
            }
            return roomId;
        }
        private RoomData GetRoom(string roomName)
        {
            RoomData room = new RoomData();
            lock (roomsMutex)
            {
                foreach (RoomData roomData in rooms)
                {
                    if (roomData.name == roomName)
                        room = roomData;
                }
            }
            return room;
        }
        private static List<string> GetPlayersInRoom(uint roomId)
        {
            GetPlayersInRoomRequest request = new GetPlayersInRoomRequest(roomId);
            byte[] requestBuffer = JsonSerialization.serializeRequest<GetPlayersInRoomRequest>(request, RequestsCodes.GET_PLAYERS_IN_ROOM);
            ClientCommuinactor comm = ClientCommuinactor.Instance;

            Tuple<byte[], byte> readTuple;
            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            GetPlayersInRoomResponse response = JsonSerialization.deserializeResponse<GetPlayersInRoomResponse>(jsonBuffer);
            return response.players;

        }
        public static List<RoomData> GetRooms()
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.GET_ROOMS);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            lock (socketMutex)
            {
                comm.sendBytes(requestBuffer);
                readTuple = comm.readBytes();
            }
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            GetRoomsResponse response = JsonSerialization.deserializeResponse<GetRoomsResponse>(jsonBuffer);
            return response.rooms;
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            //will trigger DataWindow_Closing
            Application.Current.Shutdown();

        }
        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string selectedValue = GetSelectedRoomName();

            // Do something with the selected value
            selectedRoom.Content = "Selected Room: " + selectedValue;
        }
        private string GetSelectedRoomName()
        {
            string roomName = "None";
            this.Dispatcher.Invoke(() =>
            {
                var item = roomsList.SelectedItem;
                //ComboBoxItem selectedItem = (ComboBoxItem)item;
                
                if (item != null)
                {
                    roomName = item.ToString(); //selectedItem.Content.ToString();
                }
            });
            return roomName;
        }
    }
}
