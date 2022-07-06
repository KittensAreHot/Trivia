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
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        public Signup()
        {
            InitializeComponent();
        }

        private void BackButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Label lbl = sender as Label;
            if (lbl.IsEnabled)
            {
                lbl.IsEnabled = false;

                CloseContent();
                DispatcherTimer timer = new DispatcherTimer
                {
                    Interval = TimeSpan.FromSeconds(1)
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
            double finalWidthForm = UsernameInput.ActualWidth; //all widths are the same
            double finalWidthButton = SubmitButton.ActualWidth;
            UsernameInput.Width = finalWidthForm;
            UsernameInput.HorizontalAlignment = HorizontalAlignment.Left;
            EmailInput.Width = finalWidthForm;
            EmailInput.HorizontalAlignment = HorizontalAlignment.Left;
            PasswordInput.Width = finalWidthForm;
            PasswordInput.HorizontalAlignment = HorizontalAlignment.Left;
            SubmitButton.Width = finalWidthButton;
            SubmitButton.HorizontalAlignment = HorizontalAlignment.Left;
            Thickness start = new Thickness(0, 0, 0, 0);
            Thickness end = new Thickness(-(MainContent.ActualWidth + 150), 0, 0, 0);
            DoubleAnimation fadeOut = new DoubleAnimation(1, 0, new Duration(TimeSpan.FromSeconds(0.4)));
            ThicknessAnimation contentEnter = new ThicknessAnimation(start, end, new Duration(TimeSpan.FromSeconds(1)));
            var easeFunc = new QuadraticEase
            {
                EasingMode = EasingMode.EaseIn
            };
            contentEnter.EasingFunction = easeFunc;

            //Gradient animation
            DoubleAnimation offsetAnimation = new DoubleAnimation(1, new Duration(TimeSpan.FromSeconds(0.4)))
            {
                EasingFunction = new QuadraticEase()
                {
                    EasingMode = EasingMode.EaseOut
                }
            };

            Window window = Window.GetWindow(this);
            Grid WindowContent = window.FindName("WindowContent") as Grid;

            (WindowContent.Background as LinearGradientBrush).GradientStops[1].BeginAnimation(GradientStop.OffsetProperty, offsetAnimation);
            //End - Gradient animation
            BackButton.BeginAnimation(OpacityProperty, fadeOut);
            MainContent.BeginAnimation(MarginProperty, contentEnter);
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            double finalWidthForm = UsernameInput.ActualWidth; //all widths are the same
            double finalWidthButton = SubmitButton.ActualWidth;
            BackButton.IsEnabled = false;
            SubmitButton.IsEnabled = false;
            UsernameInput.Width = finalWidthForm;
            UsernameInput.HorizontalAlignment = HorizontalAlignment.Left;
            EmailInput.Width = finalWidthForm;
            EmailInput.HorizontalAlignment = HorizontalAlignment.Left;
            PasswordInput.Width = finalWidthForm;
            PasswordInput.HorizontalAlignment = HorizontalAlignment.Left;
            SubmitButton.Width = finalWidthButton;
            SubmitButton.HorizontalAlignment = HorizontalAlignment.Left;
            Thickness start = new Thickness(-(MainContent.ActualWidth + 150), 0, 0, 0);
            Thickness end = new Thickness(0, 0, 0, 0);
            ThicknessAnimation contentEnter = new ThicknessAnimation(start, end, new Duration(TimeSpan.FromSeconds(1)));
            DoubleAnimation fadeIn = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromSeconds(1)));
            
            var easeFunc = new QuadraticEase
            {
                EasingMode = EasingMode.EaseOut
            };
            fadeIn.EasingFunction = easeFunc;
            contentEnter.EasingFunction = easeFunc;
            contentEnter.Completed += (s, eventArg) =>
            {
                SubmitButton.IsEnabled = true;
                BackButton.IsEnabled = true;
                UsernameInput.Width = Double.NaN;
                UsernameInput.HorizontalAlignment = HorizontalAlignment.Stretch;
                EmailInput.Width = Double.NaN;
                EmailInput.HorizontalAlignment = HorizontalAlignment.Stretch;
                PasswordInput.Width = Double.NaN;
                PasswordInput.HorizontalAlignment = HorizontalAlignment.Stretch;
                SubmitButton.Width = Double.NaN;
                SubmitButton.HorizontalAlignment = HorizontalAlignment.Stretch;
            };

            BackButton.BeginAnimation(OpacityProperty, fadeIn);
            MainContent.BeginAnimation(MarginProperty, contentEnter);
        }

        private void UsernameInput_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox txtBox = sender as TextBox;
            if (txtBox.Text.Length != 0) {
                UsernamePlaceholder.Visibility = Visibility.Hidden;
            }
            else if (txtBox.Text.Length == 0) {
                UsernamePlaceholder.Visibility = Visibility.Visible;
            }
        }

        private void EmailInput_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox txtBox = sender as TextBox;
            if (txtBox.Text.Length != 0)
            {
                EmailPlaceholder.Visibility = Visibility.Hidden;
            }
            else if (txtBox.Text.Length == 0)
            {
                EmailPlaceholder.Visibility = Visibility.Visible;
            }

        }

        private void PasswordInput_PasswordChanged(object sender, RoutedEventArgs e)
        {
            PasswordBox txtBox = sender as PasswordBox;
            if (txtBox.Password.Length != 0)
            {
                PasswordPlaceholder.Visibility = Visibility.Hidden;
            }
            else if (txtBox.Password.Length == 0)
            {
                PasswordPlaceholder.Visibility = Visibility.Visible;
            }
        }

        private void SubmitButton_Click(object sender, RoutedEventArgs e)   
        {
            if (UsernameInput.Text == "" || EmailInput.Text == "" || PasswordInput.Password == "")
            {
                ErrorLabel.Content = "All fields shall be filled";
                ErrorLabel.Visibility = Visibility.Visible;
                return;
            }
            if (!Client.Client.IsConnected())
            {
                if (!Client.Client.StartClient())
                {
                    return;
                }
            }
            if (!Client.Client.Signup(UsernameInput.Text, EmailInput.Text, PasswordInput.Password))
            {
                ErrorLabel.Content = "Signup failed, try changing your username.";
                ErrorLabel.Visibility = Visibility.Visible;
                return;
            }
            
            CloseContent();
            BackButton.IsEnabled = false;
            SubmitButton.IsEnabled = false;
            DispatcherTimer timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            timer.Start();
            timer.Tick += (sndr, evnt) =>
            {
                timer.Stop();
                NavigationService.Navigate(new Trivia.Pages.Home());
            };
        }
    }
}
