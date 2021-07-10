#pragma once

bool file_exists(const std::string& name);
char* get_commandline_flags(char** begin, char** end, const std::string& option);