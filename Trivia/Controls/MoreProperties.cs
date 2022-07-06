using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace moreProperties
{
    public class GameRoomSelected : UIElement
    {
        public static readonly DependencyProperty IsSelectedProperty =
        DependencyProperty.RegisterAttached(
      "IsSelected",
      typeof(bool),
      typeof(GameRoomSelected),
      new FrameworkPropertyMetadata(defaultValue: false,
          flags: FrameworkPropertyMetadataOptions.AffectsRender)
    );

        // Declare a get accessor method.
        public static bool GetIsSelected(UIElement target) =>
            (bool)target.GetValue(IsSelectedProperty);

        // Declare a set accessor method.
        public static void SetIsSelected(UIElement target, bool value) =>
            target.SetValue(IsSelectedProperty, value);
    }
}
