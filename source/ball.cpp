#include "ball.h"

sf::Color randomColor()
{
    sf::Uint8 r = std::rand() % 256;
    sf::Uint8 g = std::rand() % 256;
    sf::Uint8 b = std::rand() % 256;

    return sf::Color(r, g, b);
}

Ball::Ball(int x, int y)
{
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position = b2Vec2(x/SCALE, y/SCALE);
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->linearVelocity = b2Vec2(10, 0);
    m_bodyDef->linearDamping = 0.5f;

    sf::Color* colorR = new sf::Color(randomColor()); 
    m_bodyDef->userData = (void*)(colorR);

    m_shape = new b2CircleShape();
    m_shape->m_radius = 16/SCALE;

    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->density = 1.f;
    m_fixtureDef->friction = 0.7f;
    m_fixtureDef->restitution = 0.7f;
    m_fixtureDef->shape = m_shape;
}

b2Body* Ball::GetBody()
{
    return m_body;
}

void Ball::SetBody(b2Body* body)
{
    m_body = body;
}

b2BodyDef* Ball::GetBodyDef()
{
    return m_bodyDef;
}

b2FixtureDef* Ball::GetFixtureDef()
{
    return m_fixtureDef;
}

Ball::~Ball()
{
}