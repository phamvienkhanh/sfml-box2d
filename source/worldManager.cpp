#include "worldManager.h"
#include "DebugDraw.h"

WorldManager* WorldManager::s_intance = nullptr;

void WorldManager::init()
{
    m_gravity = b2Vec2(0.f, 9.8f);
    m_world   = new b2World(m_gravity);
}

void WorldManager::CreateWorldBound(unsigned int width, unsigned int height)
{
    float  widthInMeters    = width / SCALE;
    float  heightInMeters   = height / SCALE;
    b2Vec2 lowerLeftCorner  = b2Vec2(0, 0);
    b2Vec2 lowerRightCorner = b2Vec2(widthInMeters, 0);
    b2Vec2 upperLeftCorner  = b2Vec2(0, heightInMeters);
    b2Vec2 upperRightCorner = b2Vec2(widthInMeters, heightInMeters);

    // static container body, with the collisions at screen borders
    b2BodyDef screenBorderDef;
    screenBorderDef.position.Set(0, 0);
    screenBorderDef.type = b2_staticBody;
    b2Body* screenBorderBody = m_world->CreateBody(&screenBorderDef);
    b2EdgeShape screenBorderShape;

    // Create fixtures for the four borders (the border shape is re-used)
    screenBorderShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
    screenBorderBody->CreateFixture(&screenBorderShape, 0);
    screenBorderShape.SetTwoSided(lowerRightCorner, upperRightCorner);
    screenBorderBody->CreateFixture(&screenBorderShape, 0);
    screenBorderShape.SetTwoSided(upperRightCorner, upperLeftCorner);
    screenBorderBody->CreateFixture(&screenBorderShape, 0);
    screenBorderShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
    screenBorderBody->CreateFixture(&screenBorderShape, 0);
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

void WorldManager::SetDrawDebug(sf::RenderWindow* widown)
{
    SFMLDebugDraw* mydbDraw = new SFMLDebugDraw(widown);
    m_world->SetDebugDraw(mydbDraw);

    /* Set initial flags for what to draw */
	mydbDraw->SetFlags(b2Draw::e_shapeBit); //Only draw shapes
}

void WorldManager::DrawDebug()
{
    m_world->DebugDraw();
}

WorldManager::WorldManager()
{
    init();
}