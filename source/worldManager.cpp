#include "worldManager.h"

WorldManager* WorldManager::s_intance = nullptr;

void WorldManager::init()
{
    m_gravity = b2Vec2(0.f, 9.8f);
    m_world = new b2World(m_gravity);
}

WorldManager* WorldManager::GetInstance()
{
    if(s_intance == nullptr) {
        s_intance = new WorldManager();
    }

    return s_intance;
}

void WorldManager::SetContactListener(b2ContactListener* contactListener)
{
    m_world->SetContactListener(contactListener);
}

void WorldManager::AddObject(IPhysicsObject* physicsObject)
{
    auto bodyDef    = physicsObject->GetBodyDef();
    auto fixtureDef = physicsObject->GetFixtureDef();

    if(bodyDef != nullptr && fixtureDef != nullptr)
    {
        b2Body* body = m_world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
    }
}

b2Body* WorldManager::GetBodyList()
{
    return m_world->GetBodyList();
}

void WorldManager::Update()
{
    m_world->Step(1/60.f, 8, 3);
}

WorldManager::WorldManager()
{
    init();
}