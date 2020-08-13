#ifndef __IOBJECT_H__
#define __IOBJECT_H__

#include "precompile.h"

class IPhysicsObject
{
public:
    virtual b2BodyDef*    GetBodyDef()    = 0;
    virtual b2Body*       GetBody()       = 0;
    virtual b2FixtureDef* GetFixtureDef() = 0;


    virtual void SetBody(b2Body*) = 0;
};

#endif
