// Framework Exception types
// Copyright(c) 1993-2006_2007, David R. Cheriton, all rights reserved.

#ifndef FWK_EXCEPTION_H
#define FWK_EXCEPTION_H

#include <string.h>

#include "Ptr.h"
#include "PtrInterface.h"


namespace Fwk {

using namespace std;

class Exception
{
public:
    enum Type {
        invalid__ = 0,
        internalException__,
        nameInUseException__,
        nameNotFoundException__,
        unexpectedTypeException__,
        illegalParameterException__,
        ioException__,
        resourceNotFoundException__,
    };

    Exception::Type type() const { return type_; }

    virtual const char* what() const throw() { return what_.c_str(); }

    Exception(Exception::Type type, string what) : type_(type), what_(what) {}

protected:
    Exception::Type type_;
    string what_;
};

class InternalException : public Fwk::Exception
{
public:
    InternalException(string what) : Exception(Exception::internalException__, what) {}
};

class NameInUseException : public Fwk::Exception
{
public:
    NameInUseException(string what) : Exception(Exception::nameInUseException__, what) {}
};

class NameNotFoundException : public Fwk::Exception
{
public:
    NameNotFoundException(string what) : Exception(Exception::nameNotFoundException__, what) {}
};

class UnexpectedTypeException : public Fwk::Exception
{
public:
    UnexpectedTypeException(string what) : Exception(Exception::unexpectedTypeException__, what) {}
};

class IllegalParameterException : public Fwk::Exception
{
public:
    IllegalParameterException(string what) : Exception(Exception::illegalParameterException__, what) {}
};

class IOException : public Fwk::Exception
{
public:
    IOException(string what) : Exception(Exception::ioException__, what) {}
};

class ResourceNotFoundException : public Fwk::Exception
{
public:
    ResourceNotFoundException(string what) : Exception(Exception::resourceNotFoundException__, what) {}
};

}

#endif /* EXCEPTION_H */
