using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Input;

namespace GameLoop
{
    class Game
    {
        public Size Resolution { get; set; }


        public void Load()
        {

        }

        public void Unload()
        {

        }


        public void Update(TimeSpan gameTime)
        {
            double gameTimeElapsed = gameTime.TotalMilliseconds / 1000;
        }

        public void Draw (Graphics gfx)
        {
            gfx.FillRectangle(new SolidBrush(Color.CornflowerBlue), new Rectangle(0, 0, Resolution.Width, Resolution.Height));
        }

    }
}
