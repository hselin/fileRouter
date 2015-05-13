#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "Types.h"

/*
  utility functions
*/

#define DBG_ASSERT(s) (assert(s))
//#define DBG_ASSERT(s)

#define MIN(x, y) ((x < y) ? (x) : (y))
#define MAX(x, y) ((x > y) ? (x) : (y))

namespace Fwk
{

using namespace std;

//debug print
void dbgPrint(const char *format, ...);


vector <string> words(string s, char delimiter);
string prefix(string s, char delimiter);
string lastWord(string s, char delimiter);
string firstWord(string s, char delimiter);

string U64DecString(U64 ull);
string U64HexString(U64 ull);

string byteArrayHexString(const uint8_t buffer[], uint64_t length);

bool createDirPath(string dirPath, char delimiter);

bool dirExist(string dirPath);
bool mkDir(string dirPath);
bool fileExist(string filePath);
bool fileWrite(string filePath, uint8_t *buffer, uint64_t bufferSize);
uint8_t *fileMap(string filePath, uint64_t mapSize);

}

#endif