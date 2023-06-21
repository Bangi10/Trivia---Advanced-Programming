﻿using System;
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
            usernameLabel.Content = User.Instance().GetUsername();
        }
        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            int checkNum;
            if (!int.TryParse(maxPlayers.Text, out checkNum))
            {
                if (checkNum <= 0)
                    ErrorLabel.Content = "max players must be a positive number";
                else
                    ErrorLabel.Content = "max players must be a number";
            }
            else if (!int.TryParse(numberOfQuestions.Text, out checkNum))
            {
                if (checkNum <= 0)
                    ErrorLabel.Content = "number of questions must be a positive number";
                else
                    ErrorLabel.Content = "number of questions must be a number";
            }
            else if (!int.TryParse(timePerQuestion.Text, out checkNum))
            {
                if (checkNum <= 0)
                    ErrorLabel.Content = "time per question must be a positive number";
                else
                    ErrorLabel.Content = "time per question must be a number";
            }
            else
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
                    User.Instance().SetRoom(new RoomData(0, roomName.Text, Convert.ToUInt32(maxPlayers.Text), Convert.ToUInt32(numberOfQuestions.Text), Convert.ToUInt32(timePerQuestion.Text), 0));
                    NavigationService?.Navigate(new Room());
                }
            }
        }
        //private RoomData GetRoomFromServer(string _roomName)
        //{
        //    var rooms = GetRooms();
        //    RoomData requestedRoom = new RoomData();
        //    foreach (var room in rooms)
        //    {
        //        if (room.name == _roomName)
        //        {
        //            requestedRoom = room;
        //        }
        //    }
        //    return requestedRoom;
        //}
        private List<RoomData> GetRooms()
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.GET_ROOMS);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            Tuple<byte[], byte> readTuple;

            comm.sendBytes(requestBuffer);
            readTuple = comm.readBytes();

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
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());
        }
        

    }
}
