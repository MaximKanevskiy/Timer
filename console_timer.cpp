#pragma comment(lib, "Winmm.lib")

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <chrono>
#include <thread>

static void calculate_time(unsigned short hours, unsigned short minutes, unsigned short seconds)
{
	unsigned int total_time = hours * 3600 + minutes * 60 + seconds;

	const char* loaders = "|/-\\";
	unsigned int loader_index = 0;

	unsigned int loader_time = 0;

	while (total_time > 0)
	{
		if (loader_time % 2 == 0)
		{
			std::cout << "\b\b" << loaders[loader_index++];

			if (loader_index >= sizeof(loaders) - 1)
			{
				loader_index = 0;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (loader_time % 2 == 0) total_time--;
		loader_time++;
	}

	std::cout << "\nTime out!\n\n";

	const TCHAR* sound_filename = _T("alarm.wav");
	PlaySound(sound_filename, NULL, SND_ASYNC | SND_FILENAME);
	Sleep(3000);
	PlaySound(NULL, 0, 0);
	system("cls");
}

int main()
{
	bool is_running = true;
	while (is_running)
	{
		std::cin >> is_running;

		if (is_running)
		{
			unsigned short hours;
			unsigned short minutes;
			unsigned short seconds;
			std::cout << "Time?\n";
			std::cin >> hours >> minutes >> seconds;
			calculate_time(hours, minutes, seconds);
		}
		else
		{
			std::cout << "Closing the program...\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			exit(0);
		}
	}
}