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

namespace Trivia.Controls
{
    /// <summary>
    /// Interaction logic for FormSlider.xaml
    /// </summary>
    public partial class FormSlider : UserControl
    {
        public FormSlider()
        {
            InitializeComponent();
        }

        [Bindable(true)]
        public float MaxValue
        {
            get => (float)GetValue(MaxValueProperty);
            set => SetValue(MaxValueProperty, value);
        }
        public static readonly DependencyProperty MaxValueProperty =
         DependencyProperty.Register("MaxValue", typeof(float), typeof(FormSlider), new UIPropertyMetadata(10f));

        [Bindable(true)]
        public float MinValue
        {
            get => (float)GetValue(MinValueProperty);
            set => SetValue(MinValueProperty, value);
        }
        public static readonly DependencyProperty MinValueProperty =
         DependencyProperty.Register("MinValue", typeof(float), typeof(FormSlider), new UIPropertyMetadata(0f));

        [Bindable(true)]
        public float TickVal
        {
            get => (float)GetValue(TickValProperty);
            set => SetValue(TickValProperty, value);
        }
        public static readonly DependencyProperty TickValProperty =
         DependencyProperty.Register("TickVal", typeof(float), typeof(FormSlider), new UIPropertyMetadata(1f));

        [Bindable(true)]
        public float Value
        {
            get => (float)GetValue(ValueProperty);
            set => SetValue(ValueProperty, value);
        }
        public static readonly DependencyProperty ValueProperty =
         DependencyProperty.Register("Value", typeof(float), typeof(FormSlider), new UIPropertyMetadata(1f));
    }
}
