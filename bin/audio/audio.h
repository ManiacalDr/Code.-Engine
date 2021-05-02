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


};
#endif