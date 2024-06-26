#pragma once
#include "ConsoleTools.h"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <iomanip>

//Conversions from Byte to X. Do (bytes * CONV_X) for conversion.
#define CONV_GB 9.3132257461548E-10
#define CONV_MB 1.0E-6

//Keyboard Definitions
#define KB_Q 0x51

class RAMMonitor
{
public:
	static void runRAMMonitor();
};

