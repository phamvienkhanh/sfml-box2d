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
    // settings.attributeFlags = sf::ContextSettings::Debug;
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test", sf::Style::Default, settings);
    Window.setFramerateLimit(60);

    World->SetDrawDebug(&Window);
    World->CreateWorldBound(800, 600);



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


        // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        // {
        //     int MouseX = sf::Mouse::getPosition(Window).x;
        //     int MouseY = sf::Mouse::getPosition(Window).y;
        //     Ball* ball = new Ball(MouseX, MouseY);
        //     World->AddObject(ball);
        // }
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

        World->DrawDebug();
        Window.draw(text);
        Window.display();

        float curTime = clock.restart().asSeconds();
        float fps = 1.f / curTime;
        text.setString(std::to_string(int(fps)));
    }

	return 0;
}

