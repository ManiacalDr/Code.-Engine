#include <iostream>
#include <queue>

using namespace std;

/*
Sobject creates event
Event is passed to Robject
*/

#ifndef EVENT_SYSTEM
#define EVENT_SYSTEM


//Enum for events, to specify which events we're calling
//example event call "es.addEvent(renderer, UPDATE, args[], 30);
enum EVENTS {UPDATE, CREATE, DESTROY};

//We can change BaseObject, lines 19-58 are just for testing purposes
class BaseObject
{
	public:
		virtual int Update()
		{
			cout << "base UPDATE\n";
			return 1;
		}
		virtual int Create()
		{
			cout << "base CREATE\n"; 
			return 1;
		}
		virtual int Destroy()
		{
			cout << "base DESTROY\n";
			return 1;
		}
};

class DerivedObject : public BaseObject
{
	public:
		int Update()
		{
			cout << "UPDATE\n";
			return 1;
		}
		int Create()
		{
			cout << "CREATE\n"; 
			return 1;
		}
		int Destroy()
		{
			cout << "DESTROY\n";
			return 1;
		}
};

//Contains message type + arguments
struct Event
{
	//Receiving Object/System
	BaseObject rObj;
	
	//Which function to call
	int evNum;
	
	//Arguments needed for function, need to research how to do this
	
};

class EventSys
{
	public:
	
	//Create queue of Events
	//Queue should cycle through every frame, repeat events get added back
	//Events on a delay should be added back + subtract delay by a frame
	
	queue<Event> events;
	
	
	//Constructor that sets up things
	EventSys()
	{
		nextEvent();
	}
	
	//Add event to queue
	//Needs arguments + delay
	int addEvent(BaseObject r, int en)
	{
		Event temp;
		temp.rObj = r;
		temp.evNum = en;
		
		events.push(temp);
		
		//return fail or success
		return 1;
	}
	
	//Process nextEvent by calling the rObj event
	//nextEvent() should be called until entire queue is ran through and
	//restarted every frame, maybe in the main loop?
	int nextEvent()
	{
		//Will need to add checks to see if the rObj has the event functions, avoid errors
		//Also add an if statement for delays, only call the event if delay is 0
		
		//Might need to pass by reference if this acts funky
		Event temp = events.front();
		
		switch (temp.evNum)
		{
			case UPDATE:
				temp.rObj.Update();
				events.push(temp);
				break;
			case CREATE:
				temp.rObj.Create();
				break;
			case DESTROY:
				temp.rObj.Destroy();
				break;
			//Add more events n stuff
			default:
				cout << "DEFAULT\n";
				break;
		}
		
		//Remove from queue, or add back if delay > 0
		events.pop();
		
		//return fail or success
		return 1;
	}
};

#endif