#pragma once
#pragma warning(disable:4996)
#include <string>
#include <algorithm>

inline bool file_exists(const std::string& name) 
{
	std::string full_path = "roms/" + name;
	if (FILE* file = fopen(full_path.c_str(), "r")) 
	{
		fclose(file);
		return true;
	}
	
	return false;
}

char* get_commandline_flags(char** begin, char** end, const std::string& option)
{
	char** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}