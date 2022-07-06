using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using Trivia.Pages;

namespace Trivia.Controls
{
    /// <summary>
    /// Interaction logic for GameRoom.xaml
    /// </summary>
    public partial class GameRoom : UserControl
    {
        public GameRoom()
        {
            InitializeComponent();
        }

        private void GameRoomHover(object sender, MouseEventArgs e)
        {
            if (!moreProperties.GameRoomSelected.GetIsSelected(ContentWrapper))
            {
                ContentWrapper.Background = new SolidColorBrush(Color.FromArgb(26, 255, 255, 255));
            }
        }

        private void GameRoomUnhover(object sender, MouseEventArgs e)
        {
            if (!moreProperties.GameRoomSelected.GetIsSelected(ContentWrapper))
            {
                ContentWrapper.Background = new SolidColorBrush(Color.FromArgb(00, 255, 255, 255));
            }
        }


        [Bindable(true)]
        public RoomInfo Room
        {
            get => (RoomInfo)GetValue(RoomProperty);
            set => SetValue(RoomProperty, value);
        }
        public static readonly DependencyProperty RoomProperty =
         DependencyProperty.Register("Room", typeof(RoomInfo), typeof(GameRoom), new PropertyMetadata(new RoomInfo(0,"No Name", 0, 0, 0, false, new List<string>(), false), new PropertyChangedCallback(OnChanged)));

        private static void OnChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            GameRoom gameRoom = (GameRoom)d;
            gameRoom.GameName.Content = gameRoom.Room.Name;
            int playersNum = gameRoom.Room.PlayerList == null ? 0 : gameRoom.Room.PlayerList.Count;
            gameRoom.GamePlayers.Content = playersNum.ToString() + "/" + gameRoom.Room.MaxPlayers.ToString();
        }
    }
}
