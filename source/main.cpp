#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "contactListener.h"

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

/** Create the base for the boxes to land */
void CreateGround(b2World& World, float X, float Y);

/** Create the boxes */
void CreateBox(b2World& World, int MouseX, int MouseY);

int main()
{
    /** Prepare the window */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test", sf::Style::Default, settings);
    Window.setFramerateLimit(60);

    /** Prepare the world */
    b2Vec2 Gravity(0.f, 9.8f);
    b2World World(Gravity);

    ContactListener* _contactListener = new ContactListener();
    World.SetContactListener(_contactListener);
    CreateGround(World, 400.f, 500.f);

    /** Prepare textures */
    //sf::Texture GroundTexture;
    //sf::Texture BoxTexture;
    //GroundTexture.loadFromFile("ground.png");
    //BoxTexture.loadFromFile("box.png");

    while (Window.isOpen())
    {
        sf::Event event;
        while(Window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    int MouseX = sf::Mouse::getPosition(Window).x;
                    int MouseY = sf::Mouse::getPosition(Window).y;
                    CreateBox(World, MouseX, MouseY);
                }
            }
            else if (event.type == sf::Event::Closed)
            {
                Window.close();
            }
        }


        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int MouseX = sf::Mouse::getPosition(Window).x;
            int MouseY = sf::Mouse::getPosition(Window).y;
            CreateBox(World, MouseX, MouseY);
        }*/
        World.Step(1/60.f, 8, 3);

        Window.clear(sf::Color::White);
        int BodyCount = 0;
        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                //sf::Sprite Sprite;
                sf::CircleShape Sprite(16);
                //Sprite.setTexture(BoxTexture);
                Sprite.setFillColor(sf::Color::Red);
                Sprite.setOrigin(16.f, 16.f);
                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                Window.draw(Sprite);
                ++BodyCount;
            }
            else
            {
                //sf::Sprite GroundSprite;
                //GroundSprite.setTexture(GroundTexture);
                sf::RectangleShape GroundSprite(sf::Vector2f(Window.getSize().x, 32));
                GroundSprite.setFillColor(sf::Color::Black);
                GroundSprite.setOrigin(400.f, 8.f);
                GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                Window.draw(GroundSprite);
            }
        }
        Window.display();
    }

	return 0;
}

void CreateBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    BodyDef.linearVelocity = b2Vec2(10, 0);
    BodyDef.linearDamping = 0.5f;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2CircleShape Shape;
    Shape.m_radius = 16/SCALE;
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.restitution = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

void CreateGround(b2World& World, float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}
