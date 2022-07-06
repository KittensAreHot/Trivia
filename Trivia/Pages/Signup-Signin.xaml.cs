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
    /// Interaction logic for Signup_Signin.xaml
    /// </summary>
    public partial class Signup_Signin : Page
    {
        public Signup_Signin()
        {
            InitializeComponent();
        }

        private void SigninButtonClick(object sender, RoutedEventArgs e)
        {
            DoubleAnimation offsetAnimation = new DoubleAnimation(0.15, new Duration(TimeSpan.FromSeconds(0.5)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            Window window = Window.GetWindow(this);
            Grid WindowContent = window.FindName("WindowContent") as Grid;

            (WindowContent.Background as LinearGradientBrush).GradientStops[0].BeginAnimation(GradientStop.OffsetProperty, offsetAnimation);

            LoginScreenClose();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.Signin());
            };
        }

        private void SignupButtonClick(object sender, RoutedEventArgs e)
        {
            DoubleAnimation offsetAnimation = new DoubleAnimation(0.85, new Duration(TimeSpan.FromSeconds(0.5)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            Window window = Window.GetWindow(this);
            Grid WindowContent = window.FindName("WindowContent") as Grid;

            (WindowContent.Background as LinearGradientBrush).GradientStops[1].BeginAnimation(GradientStop.OffsetProperty, offsetAnimation);
            
            LoginScreenClose();
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(0.3)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.Signup());
            };
        }

        private void LoginScreen_Loaded(object sender, RoutedEventArgs e)
        {
            DoubleAnimation opacityAnim = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromSeconds(1)))
            {
                EasingFunction = new QuadraticEase
                {
                    EasingMode = EasingMode.EaseOut
                }
            };
            SigninButton.BeginAnimation(OpacityProperty, opacityAnim);
            SignupButton.BeginAnimation(OpacityProperty, opacityAnim);
            ButtonSeperator.BeginAnimation(OpacityProperty, opacityAnim);
            SigninButton.IsEnabled = true;
            SignupButton.IsEnabled = true;
        }

        private void LoginScreenClose()
        {
            DoubleAnimation opacityAnim = new DoubleAnimation(1, 0, new Duration(TimeSpan.FromSeconds(0.3)))
            {
                EasingFunction = new QuadraticEase
                {
                    EasingMode = EasingMode.EaseOut
                }
            };
            SigninButton.IsEnabled = false;
            SignupButton.IsEnabled = false;
            SigninButton.BeginAnimation(OpacityProperty, opacityAnim);
            SignupButton.BeginAnimation(OpacityProperty, opacityAnim);
            ButtonSeperator.BeginAnimation(OpacityProperty, opacityAnim);
        }
    }
}
