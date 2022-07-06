using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Trivia
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Border_Loaded(object sender, RoutedEventArgs e)
        {
            Border border = sender as Border;
            if (!Double.IsNaN(border.Height))
            {
                border.CornerRadius = new CornerRadius(border.Height / 2);
            }
            else if (!Double.IsNaN(border.ActualHeight))
            {
                border.CornerRadius = new CornerRadius(border.ActualHeight / 2);
            }
        }
    }
}
