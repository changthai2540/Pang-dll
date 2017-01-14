/*=============================================================================================================
== PANG.DLL for Hsreina EMU
== Created by DaveDevils
=============================================================================================================*/
#define TITLE_DLL "PANG.DLL For HSReina Emulator"
#define VERSION_TYPE "For Pangya New Dev group"
#define	GENERAL_VER	"14012017"  // version of the dll

/*=============================================================================================================
== GENERAL CONFIGURATION 
=============================================================================================================*/
// 1 --> activate
// 0 --> OFF
#define __USE_CONSOLE  1 // if is define -> show the console
#define __USE_LOGGING  1 // if is define -> Logging to the file

#if __USE_LOGGING > 0
#define _LOG_ALLFUNC 1 // if is define -> logg all input/output of all function called by the emulator
#endif
/*=============================================================================================================
== FIX DEFINE
=============================================================================================================*/
#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;
#include "logger.h"
#include "minilzo.h"
#include "CompressUncompress.h"
typedef unsigned int uint; // Using UINT more simple than unsigned int

