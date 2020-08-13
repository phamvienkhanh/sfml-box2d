#ifndef __WORLDMANAGER_H_
#define __WORLDMANAGER_H_

#include "precompile.h"
#include "IPhysicsObject.h"

#define World WorldManager::GetInstance()

class WorldManager
{
public:
    static WorldManager* GetInstance();

    b2Body* GetBodyList();
    
    void SetContactListener(b2ContactListener* contactListener); 
    void AddObject(IPhysicsObject* physicsObject);

    void Update();

    WorldManager();
private:
    void init();

private:
    static WorldManager* s_intance;

    b2Vec2   m_gravity;
    b2World* m_world;
};

#endif
