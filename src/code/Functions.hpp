#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#pragma once

#include <string>
#include "Algorithm.hpp"

using namespace std;

string Colorize(unsigned short type);
bool mine(Algorithm algorithm);