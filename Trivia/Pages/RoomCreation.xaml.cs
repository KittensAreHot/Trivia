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
    /// Interaction logic for RoomCreation.xaml
    /// </summary>
    public partial class RoomCreation : Page
    {
        public RoomCreation()
        {
            InitializeComponent();
        }

        private void BackButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            CloseContent();
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
            this.Content.BeginAnimation(OpacityProperty, opacityAnim);
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            DoubleAnimation opacityAnim = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromSeconds(0.3)))
            {
                EasingFunction = new QuadraticEase
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            BackButton.IsEnabled = true;
            this.Content.BeginAnimation(OpacityProperty, opacityAnim);

            MaximumPlayersSlider.Value = MaximumPlayersSlider.MinValue;
            QuestionCountSlider.Value = QuestionCountSlider.MinValue;
            QuestionTimeSlider.Value = QuestionTimeSlider.MinValue;
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (RoomNameBox.Text.Length == 0)
            {
                CreateButton.IsEnabled = false;
            }
            else
            {
                CreateButton.IsEnabled = true;
            }
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            RoomInfo newRoom = new RoomInfo(0, RoomNameBox.Text, (uint)MaximumPlayersSlider.Value, (uint)QuestionCountSlider.Value, (uint)QuestionTimeSlider.Value, false, new List<string>() { Client.Client.username }, true);

            if (!Client.Client.CreateRoom(newRoom.Name, newRoom.MaxPlayers, newRoom.NumberOfQuestions, newRoom.QuestionTime))
            {
                return;
            }

            CloseContent();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new GameRoom(newRoom));
            };
        }
    }
}
