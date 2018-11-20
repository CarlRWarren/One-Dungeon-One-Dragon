#include "achievementSave.h"
#include <iostream>
#include <fstream>
#include <string>

void achievementSave::Save()
{
		std::ofstream myfile;
		myfile.open("achievement.txt");

		myfile.close();
}

void achievementSave::Load()
{
}
