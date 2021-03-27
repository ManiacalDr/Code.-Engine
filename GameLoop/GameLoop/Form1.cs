using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameLoop
{
    public partial class Form1 : Form
    {
        Timer graphicsTimer;
        GameLoop loop;

        public Form1()
        {
            InitializeComponent();
           
            Paint += Form1_Paint;
            
            graphicsTimer = new Timer();
            graphicsTimer.Interval = 1000 / 120;
            graphicsTimer.Tick += GraphicsTimer_Tick;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Rectangle resolution = Screen.PrimaryScreen.Bounds;

           
            Game myGame = new Game();
            myGame.Resolution = new Size(resolution.Width, resolution.Height);

           
            loop = new GameLoop();
            loop.Load(myGame);
            loop.Start();
            graphicsTimer.Start();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            
            loop.Draw(e.Graphics);
        }

        private void GraphicsTimer_Tick(object sender, EventArgs e)
        {
           
            Invalidate();
        }
    }
}
