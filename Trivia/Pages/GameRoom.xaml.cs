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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Trivia.Pages
{
    /// <summary>
    /// Interaction logic for GameRoom.xaml
    /// </summary>
    public partial class GameRoom : Page
    {
        private const int MINPLAYERS = 2;
        private DispatcherTimer timer;
        private readonly RoomInfo room;

        public GameRoom(RoomInfo room)
        {
            InitializeComponent();
            this.room = room;
            RoomName.Content = room.Name;

            for (int i = 0; i < room.MaxPlayers; i++) //creates player slots
            {
                Label playerSlot = new Label()
                {
                    Style = this.FindResource("PlayerSlot") as Style
                };
                if (i % 3 == 0)
                {
                    PlayerCol1.Children.Add(playerSlot);
                }
                else if (i % 3 == 1)
                {
                    PlayerCol2.Children.Add(playerSlot);
                }
                else if (i % 3 == 2)
                {
                    PlayerCol3.Children.Add(playerSlot);
                }
            }
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
            GamePanel.BeginAnimation(OpacityProperty, opacityAnim);
            LeaveButton.IsEnabled = true;
            StartButton.IsEnabled = room.IsOwner;


            UpdatePanel(null, new EventArgs()); //the event doesn't use any arguments so we can use this input as "void paremeters"
            this.timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(3)
            };
            timer.Start();
            timer.Tick += UpdatePanel;
        }


        private void UpdatePanel(object sender, EventArgs e)
        {
            Client.GetRoomStateResponse roomState = Client.Client.GetRoomState();

            UpdatePlayerPanel(roomState.Players);

            if(!room.IsOwner && roomState.Status != 0)
            {
                LeaveRoomAnim();
                return; // <-- return will never be reached but I keep it for conciseness
            }

            if (roomState.GameStarted)
            {
                StartRoomAnim();
            }

            if (room.IsOwner)
            {
                int numOfPlayer = 0;
                numOfPlayer += PlayerCol1.Children.Count;
                numOfPlayer += PlayerCol2.Children.Count;
                numOfPlayer += PlayerCol3.Children.Count;
                if (numOfPlayer >= MINPLAYERS)
                {
                    StartButton.IsEnabled = true;
                }
                if (numOfPlayer < MINPLAYERS)
                {
                    StartButton.IsEnabled = false;
                }
            }
        }

        private void UpdatePlayerPanel(List<string> players)
        {
            for (int i = 0; i < players.Count; i++)
            {
                switch (i % 3)
                {
                    case 0:
                        (PlayerCol1.Children[i - 0] as Label).Content = players[i];
                        break;
                    case 1:
                        (PlayerCol2.Children[i - 1] as Label).Content = players[i];
                        break;
                    case 2:
                        (PlayerCol3.Children[i - 2] as Label).Content = players[i];
                        break;
                }
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

            StartButton.IsEnabled = false;
            LeaveButton.IsEnabled = false;
            this.timer.Stop();
            GamePanel.BeginAnimation(OpacityProperty, opacityAnim);
        }

        private void LeaveButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.room.IsOwner)
            {
                if (!Client.Client.CloseRoom())
                {
                    return;
                }
            }
            else
            {
                if (!Client.Client.LeaveRoom())
                {
                    return;
                }
            }

            LeaveRoomAnim();
        }

        private void LeaveRoomAnim()
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

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            if (!Client.Client.StartRoom())
            {
                return;
            }

            StartRoomAnim();
        }

        private void StartRoomAnim()
        {
            //this allows the user to know that the game is starting
            ColorAnimation gradientTopAnimation = new ColorAnimation(Color.FromRgb(0, 223, 204), new Duration(TimeSpan.FromSeconds(2)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };
            ColorAnimation gradientBottomAnimation = new ColorAnimation(Color.FromRgb(209, 0, 214), new Duration(TimeSpan.FromSeconds(2)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            Window window = Window.GetWindow(this);
            Grid WindowContent = window.FindName("WindowContent") as Grid;

            (WindowContent.Background as LinearGradientBrush).GradientStops[0].BeginAnimation(GradientStop.ColorProperty, gradientTopAnimation);
            (WindowContent.Background as LinearGradientBrush).GradientStops[1].BeginAnimation(GradientStop.ColorProperty, gradientBottomAnimation);


            CloseContent();
            ColorAnimation gradientTopRevertAnimation = new ColorAnimation(Color.FromRgb(0, 132, 116), new Duration(TimeSpan.FromSeconds(0.3)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };
            ColorAnimation gradientBottomRevertAnimation = new ColorAnimation(Color.FromRgb(144, 0, 147), new Duration(TimeSpan.FromSeconds(0.3)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            (WindowContent.Background as LinearGradientBrush).GradientStops[0].BeginAnimation(GradientStop.ColorProperty, gradientTopAnimation);
            (WindowContent.Background as LinearGradientBrush).GradientStops[1].BeginAnimation(GradientStop.ColorProperty, gradientBottomAnimation);
            this.timer.Stop();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.GameQuestion());
            };
        }
    }
}
