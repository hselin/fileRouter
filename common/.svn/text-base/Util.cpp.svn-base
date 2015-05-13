#include <string>
#include <vector>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sstream>
#include <iomanip>

#include <unistd.h>

#include <fcntl.h>

#include <sys/mman.h>



#include "Util.h"

namespace Fwk
{

using namespace std;

vector <string> words(string s, char delimiter)
{
    vector <string> v;

    size_t found = string::npos;
    size_t startPos = 0;
    string subString;

    while(1)
    {
        found = s.find(delimiter, startPos);

        if(found != string::npos)
        {
            subString = s.substr(startPos, found - startPos);

            if(subString.length() > 0)
                v.push_back(subString);

            startPos = found + 1; //delimiter.length();
        }
        else
        {
            subString = s.substr(startPos, string::npos);

            if(subString.length() > 0)
                v.push_back(subString);

            break;
        }
    }

    return v;
}

string prefix(string s, char delimiter)
{
    if(s.at(s.length() - 1) == delimiter)
    {
        s.erase(s.length() - 1);
    }

    size_t found = string::npos;

    found = s.rfind(delimiter);

    //if no delimiter found then there is no prefix
    if(found == string::npos)
        return "";
    else
        return s.substr(0, found);
}

string lastWord(string s, char delimiter)
{
    if(s.at(s.length() - 1) == delimiter)
    {
        s.erase(s.length() - 1);
    }

    size_t found = string::npos;

    found = s.rfind(delimiter);

    //if no delimiter found then everything is last word
    if(found == string::npos)
        return s.substr(0, string::npos);
    else
        return s.substr(found + 1, string::npos);
}


string U64DecString(U64 ull)
{
  std::stringstream out; 
  out << ull;
  return out.str();
}

string U64HexString(U64 ull)
{
    char output[17] = {0};

    sprintf(output, "%016llx", ull);

    return string(output);
}


/*
string firstWord(string s, char delimiter)
{
        return "";
}
*/

string byteArrayHexString(const uint8_t byteArray[], uint64_t byteArrayLength)
{
    //char output[512] = {0};

    //DBG_ASSERT(511 >= (length * 2));

    std::stringstream ss;

    for(uint64_t i = 0; i<byteArrayLength; i++)
    {
        ss << std::setfill ('0') << std::setw(2) << std::hex << (uint32_t) byteArray[i];
    }

    std::string result(ss.str());

    return ss.str();
}

#if 0
vector <string> byteArrayHexString(const uint8_t byteArray[], uint64_t byteArrayLength)
{
    std::stringstream ss;

    for(uint64_t i = 0; i<byteArrayLength; i++)
    {
        ss << std::setfill ('0') << std::setw(2) << std::hex << (uint32_t) byteArray[i];
    }

    std::string result(ss.str());

    return ss.str();
}
#endif

bool dirExist(string dirPath)
{
    struct stat st;

    if(stat(dirPath.c_str(), &st) == 0)
    {
        if(S_ISDIR(st.st_mode))
            return true;
    }

    return false;
}

bool mkDir(string dirPath)
{
    if(mkdir(dirPath.c_str(), S_IRWXU) == 0)
        return true;

    return false;
}

bool createDirPath(string dirPath, char delimiter)
{
    //int status = 0;
    //struct stat st;

    if(dirExist(dirPath))
    {
        return true;
    }

    //create parent dir
    string parentDirPath = prefix(dirPath, delimiter);
    bool parentDirStatus = createDirPath(parentDirPath, delimiter);

    if(parentDirStatus == false)
        return false;

    //now create us
    return mkDir(dirPath);
}


uint8_t *fileMap(string filePath, uint64_t mapSize)
{
    int fd = open(filePath.c_str(), O_RDONLY|O_DIRECT, S_IRWXU);

    if(fd == -1)
    {
        return NULL;
    }

    return (uint8_t *) mmap(NULL, mapSize, PROT_READ, MAP_SHARED, fd, 0);
}


bool fileExist(string filePath)
{
    struct stat st;

    if(stat(filePath.c_str(), &st) == 0)
    {
        if(S_ISREG(st.st_mode))
            return true;
    }

    return false;
}

bool fileWrite(string filePath, uint8_t *buffer, uint64_t bufferSize)
{
    //int fd = open(filePath.c_str(), O_CREAT|O_RDWR|O_TRUNC|O_DIRECT, S_IRWXU);
    int fd = open(filePath.c_str(), O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);

    if(fd == -1)
    {
        DBG_ASSERT(1);
        perror("error open: ");
        return false;
    }


    int writeAmount = 0;
    //uint64_t amountWrote = 0;

    while(bufferSize)
    {
        writeAmount = write(fd, buffer, bufferSize);

        if(writeAmount <= 0)
        {
            DBG_ASSERT(1);
            perror("error write: ");
            break;
        }
        
        bufferSize -= writeAmount;
        buffer += writeAmount;
    }
    
    fsync(fd);
    close(fd);

    if(bufferSize != 0)
    {
        printf("bufferSize: 0xllx\n", bufferSize);
        return false;
    }

    return true;
}

} //namespace
