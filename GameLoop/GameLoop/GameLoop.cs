using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Input;


namespace GameLoop
{
    class GameLoop
    {
        private Game tester;

   
        public bool Running { get; private set; }

       
        public void Load(Game gameObj)
        {
            tester = gameObj;
        }

       
        public async void Start()
        {
            if (tester == null)
                throw new ArgumentException("Game not loaded!");

            // Load game content
            tester.Load();

            // Set gameloop state
            Running = true;

            // Set previous game time
            DateTime _previousGameTime = DateTime.Now;

            while (Running)
            {
                // Calculate the time elapsed since the last game loop cycle
                TimeSpan GameTime = DateTime.Now - _previousGameTime;
                // Update the current previous game time
                _previousGameTime = _previousGameTime + GameTime;
                // Update the game
                tester.Update(GameTime);
                // Update Game at 60fps
                await Task.Delay(8);
            }
        }

     
        public void Stop()
        {
            Running = false;
            tester?.Unload();
        }

        public void Draw(Graphics gfx)
        {
            tester.Draw(gfx);
        }









    }
}
