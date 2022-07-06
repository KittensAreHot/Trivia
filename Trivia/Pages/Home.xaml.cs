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
    /// Interaction logic for Home.xaml
    /// </summary>
    public partial class Home : Page
    {
        public Home()
        {
            InitializeComponent();
        }

        private void LogoutButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Label lbl = sender as Label;

            
            if (lbl.IsEnabled)
            {
                if (!Client.Client.Signout())
                {
                    return;
                }
                lbl.IsEnabled = false;

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
            PlayButton.IsEnabled = false;
            StatisticsButton.IsEnabled = false;
            LogoutButton.IsEnabled = false;
            PlayButton.BeginAnimation(OpacityProperty, opacityAnim);
            StatisticsButton.BeginAnimation(OpacityProperty, opacityAnim);
            ButtonSeparator.BeginAnimation(OpacityProperty, opacityAnim);
            LogoutButton.BeginAnimation(OpacityProperty, opacityAnim);
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
            PlayButton.BeginAnimation(OpacityProperty, opacityAnim);
            StatisticsButton.BeginAnimation(OpacityProperty, opacityAnim);
            LogoutButton.BeginAnimation(OpacityProperty, opacityAnim);
            ButtonSeparator.BeginAnimation(OpacityProperty, opacityAnim);
            PlayButton.IsEnabled = true;
            StatisticsButton.IsEnabled = true;
            LogoutButton.IsEnabled = true;
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e)
        {

            PlayButton.IsEnabled = false;

            CloseContent();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.GameBrowser());
            };
        }
    }
}
