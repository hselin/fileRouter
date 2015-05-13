// Framework Exception types
// Copyright(c) 1993-2006_2007, David R. Cheriton, all rights reserved.

#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <stdio.h>

#include "Ptr.h"
#include "PtrInterface.h"

/*
  Log class type
*/

namespace Fwk {

using namespace std;

class Log : public Fwk::PtrInterface <Log>
{
public:
  typedef Fwk::Ptr <Log const> PtrConst;
  typedef Fwk::Ptr <Log> Ptr;

  enum Priority {
    null__,
    critical__, // condition requires immediate corrective action.
    error__,    // condition requires corrective action
    warning__,  // operator should be aware, but system can continue
    status__,   // Status update - informational only
    debug__,    // Detailing normal processing for debug purposes.
    info__
  };

  static inline Priority null()      { return null__; }
  static inline Priority critical()  { return critical__; }
  static inline Priority error()     { return error__; }
  static inline Priority warning()   { return warning__; }
  static inline Priority status()    { return status__; }
  static inline Priority debug()     { return debug__; }
  static inline Priority info()      { return info__; }

  //accessors

  //mutators
  virtual void entryNew(Priority, const char *format, ...) throw();
  virtual void vEntryNew(Priority, const char *format, va_list vaList) throw();

  //creators
  static Log::Ptr LogNew(const std::string &);
  static Log::Ptr LogNew();

protected:
  //where to direct the output
  FILE *outputFile_;

  //helper functions
  std::string priorityString(Priority p);

  //constructors
  Log(FILE *outputFile) : outputFile_(outputFile) {}
  Log(const Log &);
};


}

#endif /* LOG_H */
