#include <iostream>
#include <array>
using namespace std;

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
    virtual void visitorConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void visitorConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component
{
public:
    virtual ~Component() {}
    virtual void accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component
{
public:
    void accept(Visitor *visitor) const override
    {
        visitor->visitorConcreteComponentA(this);
    }

    string exclusionMethodOfConcreteComponentA() const
    {
        return "A";
    }
};

class ConcreteComponentB : public Component
{
public:
    void accept(Visitor *visitor) const override
    {
        visitor->visitorConcreteComponentB(this);
    }

    string specialMethodOfConcreteComponentB() const
    {
        return "B";
    }
};

class ConcreteVisitor1 : public Visitor
{
public:
    void visitorConcreteComponentA(const ConcreteComponentA *element) const override
    {
        cout << element->exclusionMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }
    void visitorConcreteComponentB(const ConcreteComponentB *element) const override
    {
        cout << element->specialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};
class ConcreteVisitor2 : public Visitor
{
public:
    void visitorConcreteComponentA(const ConcreteComponentA *element) const override
    {
        cout << element->exclusionMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void visitorConcreteComponentB(const ConcreteComponentB *element) const override
    {
        cout << element->specialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};

void clientCode()
{
    array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
    cout << "The client code works with all visitors via the base Visitor interface.\n";
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    for (const Component *comp : components)
    {
        comp->accept(visitor1);
    }

    cout << "It allows the same client code to work with different types of visitors.\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    for (const Component *comp : components)
    {
        comp->accept(visitor2);
    }

    for (const Component *comp : components)
    {
        delete comp;
    }
    delete visitor1, visitor2;
}

int main(void)
{
    clientCode();
    return 0;
}