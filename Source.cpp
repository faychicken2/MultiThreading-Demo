// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <Windows.h>
#include <mutex>
#include <tchar.h>
#include <stdio.h>

std::mutex Locker; //Lock and unlock the code that all the threads are trying to use at the same time.
bool IsAborted = false;
int TotalRocketsOnMarsLaunched = 0;

using namespace std::literals::chrono_literals;

// Function that launched the rocket
void SubStationLaunchControl1()
{
	Locker.lock(); // lock the thread so only this thread can talk at once
	Sleep(1000); // sleep for 1 sec
	//std::cout << "Rocket " << x << " Has Launched!!!" << std::endl; // printing the rocket has launched to user
	std::cout << "\n\n\t*** Welcome to Sub Station 1 ***\n";
	std::cout << "\nThe thread ID at Sub Station 1 is: " << std::this_thread::get_id() << std::endl;
	int counter = 0;
	while (IsAborted == false)
	{
		std::cout << "Rocket " << ++counter << " Has Launched from Sub Station Launch Control\n" << std::endl; // printing the rocket has launched to user	
		std::cout << "Total rockets launched on Mars " << ++TotalRocketsOnMarsLaunched << std::endl;
		std::this_thread::sleep_for(5s);
	}

	Locker.unlock(); // unlocking the thread
}


int main()
{
	//setting up tthreads run the launch function 
	std::cout << "\n\n At Misson Control the Space Ranger will Launch the first 3 rockets, then turn over control to a substation.\n\n";
	int missionControlLaunchCounter = 0;
	std::cout << "\nThe Main thread ID at Mission Control is: " << std::this_thread::get_id() << std::endl;
	for (int i = 0; i <= 2; i++)
	{
		std::cout << "Rocket " << ++missionControlLaunchCounter << " Has Launched from Misson Control(Main) by the Space Ranger.\n" << std::endl; // printing the rocket has launched to user	
		std::cout << "Total rockets launched on Mars " << ++TotalRocketsOnMarsLaunched << std::endl;
	}
	std::cout << "\nTo Turn launch control over to a space cadet at sub station 1 ";
	system("pause");
	// spin up new thread
	std::thread SubStationLaunchControl1Thread(SubStationLaunchControl1);
	// This main thread will contine on!
	std::cout << "\nMessage from Mission Control, Rocket Launch Control has been transferred to Sub Station 1\n";
	std::cout << "\nSpace Ranger at Mission Control to abort Sub Station one Launches ";
	std::cout << "\nThe Main thread ID at Mission Control is: " << std::this_thread::get_id() << std::endl;
	system("pause");
	// This will flip the abort switch
	IsAborted = true;
	// Wait for child thread to finished
	SubStationLaunchControl1Thread.join();
	// Hey The Space Ranger at Mission Control has aborted the lanches at sub station 1 by the space cadet.
	std::cout << "\n\nMessage from Mission Control: Hey The Space Ranger at Mission Control has aborted the lanches at sub station 1 by the space cadet.\n";
	// todo: stats on number of rocket launches total, and for mission control.
	return 0;


}