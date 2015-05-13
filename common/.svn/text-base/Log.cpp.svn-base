#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <queue>

#include "Log.h"


#ifdef _MSC_VER
  #pragma warning(disable: 4996)
#endif

namespace Fwk {

using namespace std;

/*
  ==========================================================
  Implementation for Log
  ==========================================================
*/

//creates a new log
Log::Ptr Log::LogNew(const std::string &logFileName) {
  //use stderr as default log output
  FILE *outputFile = stderr;

  if(logFileName.compare("") != 0) {
    outputFile = fopen(logFileName.c_str() , "a+");
    
    if(outputFile == NULL)
      outputFile = stderr;
  }

  return new Log(outputFile);
}


Log::Ptr Log::LogNew()
{
  return new Log(stderr);
}

//convert log entry level to string
std::string Log::priorityString(Priority p) {
  switch(p) {
    case null__ :     return "NULL";
    case critical__ : return "CRITICAL";
    case error__ :    return "ERROR";
    case warning__ :  return "WARNING";
    case status__ :   return "STATUS";
    case debug__ :    return "DEBUG";
    case info__:      return "INFO";
    default:          return "UNDEFINED";
  }
}

//create a new log entry
void Log::entryNew(Priority p, const char *format, ...) throw() {
  //exception free execution
  try{
    va_list ap;
    va_start(ap, format);

    std::string time = "time";

    fprintf(outputFile_, "%s | %s ", time.c_str(), priorityString(p).c_str());
    vfprintf(outputFile_, format, ap);    
    fprintf(outputFile_, "\n");

    fflush(outputFile_);
    va_end(ap);
  } catch (...) {}
}

void Log::vEntryNew(Priority p, const char *format, va_list vaList) throw() {
  //exception free execution
  try{
    std::string time = "time";

    fprintf(outputFile_, "%s | %s ", time.c_str(), priorityString(p).c_str());
    vfprintf(outputFile_, format, vaList);    
    fprintf(outputFile_, "\n");

    fflush(outputFile_);
  } catch (...) {}
}

} //namespace
