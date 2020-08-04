#include "contactListener.h"
#include <iostream>

ContactListener::ContactListener(){}

ContactListener::~ContactListener(){}

void ContactListener::BeginContact(b2Contact* contact)
{
    auto bodyA = contact->GetFixtureA()->GetBody();
    auto bodyB = contact->GetFixtureB()->GetBody();

    std::cout << contact->GetFixtureA()->GetShape()->m_radius << std::endl;
    std::cout << contact->GetFixtureB()->GetShape()->m_radius << std::endl;

    if(bodyA->GetType() == b2_dynamicBody)
    {

       /* auto currentVecl = bodyA->GetLinearVelocity();
        std::cout << "=== x : " << currentVecl.x << " y: " << currentVecl.y << " === " << std::endl;
        b2Vec2 newVecl = b2Vec2(currentVecl.x, -1 * currentVecl.y);
        bodyA->SetLinearVelocity(newVecl);*/
    }
    else if(bodyB->GetType() == b2_dynamicBody)
    { 
       /* auto currentVecl = bodyB->GetLinearVelocity();
        std::cout << "=== x : " << currentVecl.x << " y: " << currentVecl.y << " === " << std::endl;
        b2Vec2 newVecl = b2Vec2(currentVecl.x, -1 * currentVecl.y);
        bodyB->SetLinearVelocity(newVecl);*/
    }


    std::cout << "======= contact ====="<< std::endl;
}

void ContactListener::EndContact(b2Contact* contact)
{

}

