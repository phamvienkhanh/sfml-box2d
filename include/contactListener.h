#include <box2d/box2d.h>

class ContactListener : public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);


public:
    ~ContactListener();
    ContactListener();
};
