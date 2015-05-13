#include <algorithm>

#include "../common/Util.h"

#include "../crypto/CryptoInterface.h"

#include "TFSValueTypes.h"


namespace TFS
{

/*
  ==========================================================
  Implementation for WorldWideName
  ==========================================================
*/
U64 WorldWideName::counter_ = 0;

string WorldWideName::value() const
{
    return Fwk::U64HexString(id_);
}

/*
  ==========================================================
  Implementation for ObjectPathComponent
  ==========================================================
*/

bool ObjectPathComponent::equal(ObjectPathComponent *component) const
{
    if(this->componentString_.compare(component->componentString_) == 0)
        return true;

    return false;
}

/*
  ==========================================================
  Implementation for ObjectPath
  ==========================================================
*/

bool ObjectPath::absolutePath() const
{
    if(this->pathString_.at(0) == ObjectPath::pathDelimiter_)
        return true;

    return false;
}

bool ObjectPath::root() const
{
    if(absolutePath() == false)
        return false;

    if(this->pathString_.length() != 1)
        return false;

    return true;
}

bool ObjectPath::equal(ObjectPath *path) const
{
    if(this->pathString_.compare(path->pathString_) == 0)
        return true;

    return false;
}

bool ObjectPath::lessThan(ObjectPath *path) const
{
    if(this->pathString_.compare(path->pathString_) < 0)
        return true;

    return false;
}

ObjectPath ObjectPath::prefix()
{
    string p = Fwk::prefix(this->pathString_, ObjectPath::pathDelimiter_);

    if(p.length() == 0)
    {
        if(absolutePath())
        {
            //return root
            return ObjectPath();
        }
    }

    return ObjectPath(p.c_str());
}

ObjectPathComponent ObjectPath::lastComponent()
{
    return ObjectPathComponent(Fwk::lastWord(this->pathString_, ObjectPath::pathDelimiter_).c_str());
}



/*
  ==========================================================
  Implementation for ObjectType
  ==========================================================
*/

bool ObjectType::directory() const
{
    if(this->value_ == typeDirectory_)
        return true;

    return false;
}

bool ObjectType::regularFile() const
{
    if(this->value_ == typeRegularFile_)
        return true;

    return false;
}




/*
  ==========================================================
  Implementation for ObjectPermission
  ==========================================================
*/


U16 ObjectPermission::unixPermission() const
{
    return ((U16) (this->access_ & 0xFFFF));
}

bool ObjectPermission::equal(ObjectPermission *permission) const
{
    if(this->uid_ != permission->uid_)
        return false;

    if(this->gid_ != permission->gid_)
        return false;

    if(this->access_ != permission->access_)
        return false;

    return true;
}


void ObjectPermission::unixPermissionIs(U16 up)
{
    if((this->access_ & 0xFFFF) == up)
        return;

    this->access_ &= ~(0xFFFF);
    this->access_ |= up;
}

/*
  ==========================================================
  Implementation for HandleID
  ==========================================================
*/

U64 HandleID::counter_ = 0;

bool HandleID::lessThan(HandleID *id) const
{
    if(this->value_ < id->value_)
        return true;

    return false;
}


/*
  ==========================================================
  Implementation for OpenFlag
  ==========================================================
*/

bool OpenFlag::append() const
{
    if(this->value_ & flagAppend_)
        return true;

    return false;
}

void OpenFlag::add(U64 flag)
{
    this->value_ |= flag;
}



/*
  ==========================================================
  Implementation for ResourceLocation
  ==========================================================
*/

bool ResourceLocation::equal(ResourceLocation *rl) const
{
    if(this->value_.compare(rl->value_) == 0)
        return true;

    return false;
}

/*
  ==========================================================
  Implementation for BlockID
  ==========================================================
*/


string BlockID::hexString() const
{
    if(defaultID_)
        return "";

    string hexString = Fwk::byteArrayHexString(byteArray_, sizeof(byteArray_));
    std::transform(hexString.begin(), hexString.end(), hexString.begin(), ::toupper);

    return hexString;
}

BlockID::BlockID(U8 *blockBuffer, U64 blockSize)
{
    defaultID_ = false;
    Crypto::sha256(byteArray_, sizeof(byteArray_), blockBuffer, blockSize);
    //hexString_ = Fwk::byteArrayHexString(byteArray, sizeof(byteArray));
    //std::transform(hexString_.begin(), hexString_.end(), hexString_.begin(), ::toupper);
}

/*
  ==========================================================
  Implementation for BlockOperationStatus
  ==========================================================
*/

bool BlockOperationStatus::success() const
{
    U32 status = value_ & 0xFFFFFFFF;

    if(status & 0x1)
    {
        return false;
    }

    return true;
}


void BlockOperationStatus::successIs(bool s)
{
    if(s)
    {
        //set success to true
        value_ &= ~0x1;
    }
    else
    {
        //set success to false
        value_ |= 0x1;
    }
}

} //namespace