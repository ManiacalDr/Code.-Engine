#pragma once
#ifndef audio_H
#define audio_H
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>



class Playaudio
{

  public:

	  void DragonRoar()
	  {
		  PlaySound(TEXT("assets\\audio\\DragonRoar.wav"), NULL, SND_SYNC);
	  }

	  void DragonSteps()
	  {
		  PlaySound(TEXT("assets\\audio\\footstepsDragon.wav"), NULL, SND_SYNC);
	  }

	 

	  void RainBird()
	  {
		  PlaySound(TEXT("assets\\audio\\BirdinRain.wav"), NULL, SND_SYNC);

	  }

	  void FirstTheme()
	  {
		  PlaySound(TEXT("assets\\audio\\StrongTheme.wav"), NULL, SND_SYNC);

	  }

	  void Crickets()
	  {
		  PlaySound(TEXT("assets\\audio\\Crickets.wav"), NULL, SND_SYNC);

	  }

	  void RainStorm()
	  {
		  PlaySound(TEXT("assets\\audio\\RainStorm.wav"), NULL, SND_SYNC);

	  }
	  void ThunderStorm()
	  {
		  PlaySound(TEXT("assets\\audio\\ThunderStorm.wav"), NULL, SND_SYNC);

	  }




};
#endif