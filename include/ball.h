#ifndef __BALL_H__
#define __BALL_H__

#include "precompile.h"
#include "IPhysicsObject.h"

class Ball : public IPhysicsObject
{
private:
    b2Body*        m_body;
    b2BodyDef*     m_bodyDef;
    b2Shape*       m_shape;
    b2FixtureDef*  m_fixtureDef;

public:
    virtual b2BodyDef*    GetBodyDef()    override;
    virtual b2Body*       GetBody()       override;
    virtual b2FixtureDef* GetFixtureDef() override;

    virtual void SetBody(b2Body* body) override;

    Ball(int x, int y);
    ~Ball();
};

#endif
