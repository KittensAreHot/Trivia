using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using System.Windows.Threading;

namespace Trivia.Pages
{
    /// <summary>
    /// Interaction logic for GameBrowser.xaml
    /// </summary>
    public partial class GameBrowser : Page
    {
        private readonly List<Controls.GameRoom> gameRooms;
        private DispatcherTimer timer;
        private string filterName;
        private uint selectedRoom = 0;
        private bool isSelected = false;
        private RoomInfo RoomInfo;

        public GameBrowser()
        {
            InitializeComponent();
            gameRooms = new List<Controls.GameRoom>();
            filterName = "";
        }
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            DoubleAnimation opacityAnim = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromSeconds(1)))
            {
                EasingFunction = new QuadraticEase
                {
                    EasingMode = EasingMode.EaseOut
                }
            };
            GameBrowserContent.BeginAnimation(OpacityProperty, opacityAnim);
            JoinButton.IsEnabled = false;
            BackButton.IsEnabled = true;


            this.timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(3)
            };
            timer.Tick += ReloadRooms;
            timer.Start();

        }

        private void ReloadRooms(object sndr, EventArgs evnt)
        {
            //Might need to play with the selected room to keep it selected when refreshing
            List<RoomInfo> rooms = Client.Client.GetRooms();
            gameRooms.Clear();
            for (int i = 0; i < rooms.Count; i++)
            {
                Controls.GameRoom gameRoom = new Trivia.Controls.GameRoom();
                gameRoom.MouseLeftButtonUp += GameRoomClicked;
                gameRoom.Room = rooms[i];                

                gameRooms.Add(gameRoom);
            }

            LoadRooms();
        }

        private void LoadRooms()
        {
            RoomList.Children.Clear();
            foreach (Controls.GameRoom room in this.gameRooms)
            {
                string GameName = room.Name;
                if (GameName.ToLower().Contains(filterName.ToLower()) && !room.Room.Active)
                {
                    RoomList.Children.Add(room);
                }
            }
            if (isSelected)
            {
                foreach (Controls.GameRoom room in gameRooms)
                {
                    if (room.Room.ID == selectedRoom)
                    {
                        moreProperties.GameRoomSelected.SetIsSelected(room.ContentWrapper, true);
                        room.ContentWrapper.Background = new SolidColorBrush(Color.FromArgb(0, 221, 221, 221));
                        JoinButton.IsEnabled = true;
                        return;
                    }
                }
                isSelected = false;
                JoinButton.IsEnabled = false;
            }
        }

        private void CloseContent()
        {
            DoubleAnimation opacityAnim = new DoubleAnimation(1, 0, new Duration(TimeSpan.FromSeconds(0.3)))
            {
                EasingFunction = new QuadraticEase
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            BackButton.IsEnabled = false;
            this.timer.Stop();
            GameBrowserContent.BeginAnimation(OpacityProperty, opacityAnim);
        }

        private void BackButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

            CloseContent();
            this.timer.Stop();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.GoBack();
            };
        }

        private void SearchBar_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox searchBar = sender as TextBox;
            clearSearch.Visibility = searchBar.Text.Length == 0 ? Visibility.Hidden : Visibility.Visible;
        }

        private void SearchButton_Click(object sender, RoutedEventArgs e)
        {
            filterName = SearchBar.Text;
            timer.Stop();
            LoadRooms();
            timer.Start();
        }

        private void ClearSearch_Click(object sender, RoutedEventArgs e)
        {
            SearchBar.Text = "";
            clearSearch.Visibility = Visibility.Hidden;

            filterName = SearchBar.Text;
            timer.Stop();
            LoadRooms();
            timer.Start();
        }

        private void GameRoomClicked(object sender, MouseButtonEventArgs e)
        {
            Controls.GameRoom gameRoom = sender as Controls.GameRoom;

            foreach (Controls.GameRoom room in gameRooms)
            {
                if (moreProperties.GameRoomSelected.GetIsSelected(room.ContentWrapper))
                {
                    moreProperties.GameRoomSelected.SetIsSelected(room.ContentWrapper, false);
                    room.ContentWrapper.Background = new SolidColorBrush(Color.FromArgb(0, 221, 221, 221));
                }
            }

            this.RoomInfo = gameRoom.Room;

            gameRoom.ContentWrapper.Background = new SolidColorBrush(Color.FromArgb(128, 221, 221, 221));
            this.selectedRoom = gameRoom.Room.ID;
            isSelected = true;
            moreProperties.GameRoomSelected.SetIsSelected(gameRoom.ContentWrapper, true);
            JoinButton.IsEnabled = true;
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            CloseContent();
            this.timer.Stop();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.RoomCreation());
            };
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {
            if (!Client.Client.JoinRoom(selectedRoom))
            {
                return;
            }

            CloseContent();
            this.timer.Stop();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.GameRoom(this.RoomInfo));
            };
        }
    }
}
