#ifndef __COMMON_CONFIG_H
#define __COMMON_CONFIG_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string.h>
#include <vector>
#include <sstream>
#include<queue>

#ifdef _WIN32
	#include <Windows.h>
	#include <Psapi.h>
	#include <io.h>
	#include <direct.h>
	#include <psapi.h>
	#pragma comment(lib,"psapi.lib")
	#include<process.h>  
#else
	#include <sys/wait.h>
	#include <algorithm>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/time.h>
	#include <dirent.h>
	#include <pthread.h>
#endif
using namespace std;

#endif
