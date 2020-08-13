#include "precompile.h"
#include "contactListener.h"
#include "worldManager.h"
#include "ball.h"

void logging(int num)
{
    std::cout << num << std::endl;
}

int main()
{
    /** Prepare the window */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
    settings.attributeFlags = sf::ContextSettings::Debug;
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test", sf::Style::Default, settings);
    Window.setFramerateLimit(60);

    ContactListener* _contactListener = new ContactListener();
    World->SetContactListener(_contactListener);

    sf::Font font;
    font.loadFromFile("MesloLGS NF Regular.ttf");
    sf::Text text(" ", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    sf::Clock clock;
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
                    // logging(World->GetBodyCount());
                    Ball* ball = new Ball(MouseX, MouseY);
                    World->AddObject(ball);
                }
            }
            else if (event.type == sf::Event::Closed)
            {
                Window.close();
            }
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int MouseX = sf::Mouse::getPosition(Window).x;
            int MouseY = sf::Mouse::getPosition(Window).y;
            Ball* ball = new Ball(MouseX, MouseY);
            World->AddObject(ball);
        }
        World->Update();

        Window.clear(sf::Color::Black);
        int BodyCount = 0;
        for (b2Body* BodyIterator = World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                sf::CircleShape Sprite(16);
                sf::Color* colorRan = (sf::Color*)(BodyIterator->GetUserData());
                Sprite.setFillColor(*colorRan);
                Sprite.setOrigin(16.f, 16.f);
                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                Window.draw(Sprite);
                ++BodyCount;
            }
        }
        
        Window.draw(text);
        Window.display();

        float curTime = clock.restart().asSeconds();
        float fps = 1.f / curTime;
        text.setString(std::to_string(int(fps)));
    }

	return 0;
}

// void CreateBox(b2World& World, int MouseX, int MouseY)
// {
//     b2BodyDef BodyDef;
//     BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
//     BodyDef.type = b2_dynamicBody;
//     BodyDef.linearVelocity = b2Vec2(10, 0);
//     BodyDef.linearDamping = 0.5f;
//     sf::Color* colorR = new sf::Color(randomColor()); 
//     BodyDef.userData = (void*)(colorR);
//     b2Body* Body = World.CreateBody(&BodyDef);

//     b2CircleShape Shape;
//     Shape.m_radius = 16/SCALE;
//     b2FixtureDef FixtureDef;
//     FixtureDef.density = 1.f;
//     FixtureDef.friction = 0.7f;
//     FixtureDef.restitution = 0.7f;
//     FixtureDef.shape = &Shape;
//     Body->CreateFixture(&FixtureDef);
// }

// void CreateGround(b2World& World, float X, float Y)
// {
//     b2BodyDef BodyDef;
//     BodyDef.position = b2Vec2(400/SCALE, 0);
//     BodyDef.type = b2_staticBody;
//     b2Body* Body = World.CreateBody(&BodyDef);

//     b2PolygonShape Shape;
//     Shape.SetAsBox((800.f/2)/SCALE, (2.f/2)/SCALE);
//     b2FixtureDef FixtureDef;
//     FixtureDef.density = 0.f;
//     FixtureDef.shape = &Shape;
//     Body->CreateFixture(&FixtureDef);
    
//     b2BodyDef BodyDef2;
//     BodyDef2.position = b2Vec2(800/SCALE, 600/SCALE);
//     BodyDef2.type = b2_staticBody;
//     b2Body* Body2 = World.CreateBody(&BodyDef2);

//     b2PolygonShape Shape2;
//     Shape2.SetAsBox(2/SCALE, (600.f/2)/SCALE);
//     b2FixtureDef FixtureDef2;
//     FixtureDef2.density = 0.f;
//     FixtureDef2.shape = &Shape2;
//     Body2->CreateFixture(&FixtureDef2);

//     b2BodyDef BodyDef3;
//     BodyDef2.position = b2Vec2(X/SCALE, Y/SCALE);
//     BodyDef2.type = b2_staticBody;
//     b2Body* Body3 = World.CreateBody(&BodyDef3);

//     b2PolygonShape Shape3;
//     Shape3.SetAsBox((800.f/2)/SCALE, (2.f/2)/SCALE);
//     b2FixtureDef FixtureDef3;
//     FixtureDef3.density = 0.f;
//     FixtureDef3.shape = &Shape3;
//     Body3->CreateFixture(&FixtureDef3);

//     b2BodyDef BodyDef4;
//     BodyDef4.position = b2Vec2(0, 300/SCALE);
//     BodyDef4.type = b2_staticBody;
//     b2Body* Body4 = World.CreateBody(&BodyDef4);

//     b2PolygonShape Shape4;
//     Shape4.SetAsBox(2/SCALE, 300/SCALE);
//     b2FixtureDef FixtureDef4;
//     FixtureDef4.density = 0.f;
//     FixtureDef4.shape = &Shape4;
//     Body4->CreateFixture(&FixtureDef4);


// }
