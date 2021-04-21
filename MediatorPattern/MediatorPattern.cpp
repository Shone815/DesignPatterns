#include <iostream>
using namespace std;

enum OPERATION
{
    DOA = 1,
    DOB = 1 << 1,
    DOC = 1 << 2,
    DOD = 1 << 3,
};

/**
 * Mediator接口声明了Component使用的方法，用于将各种事件通知Mediator。
 * Mediator可以对这些事件作出反应，并将执行传递给其他Component。
 */
class BaseComponent;
class Mediator
{
public:
    virtual void notify(BaseComponent *sender, unsigned int operation) const = 0;
};

/**
 * BaseComponent提供在Component对象中存储Mediator实例的基本功能。
 */
class BaseComponent
{
public:
    BaseComponent(Mediator *mediator = nullptr) : m_mediator(mediator) {}

    void setMediator(Mediator *mediator)
    {
        this->m_mediator = mediator;
    }

protected:
    Mediator *m_mediator;
};

/**
 * 具体Component实现各种功能。它们不依赖于其他Component。
 * 它们也不依赖于任何具体的Mediator类。
 */
class Component1 : public BaseComponent
{
public:
    void testA()
    {
        // ...
        cout << "Component1： test A" << endl;
        this->m_mediator->notify(this, DOA);
        // ...
    }
    void notifyA()
    {
        cout << "Component1： notify A" << endl;
    }
    void testB()
    {
        cout << "Component1： test B" << endl;
        this->m_mediator->notify(this, DOA | DOB);
    }
    void notifyB()
    {
        cout << "Component1： notify B" << endl;
    }
};

class Component2 : public BaseComponent
{
public:
    void testC()
    {
        cout << "Component1： test C" << endl;
        this->m_mediator->notify(this, DOC);
    }
    void notifyC()
    {
        cout << "Component1： notify C" << endl;
    }
    void testD()
    {
        cout << "Component1： test D" << endl;
        this->m_mediator->notify(this, DOD);
    }
    void notifyD()
    {
        cout << "Component1： notify D" << endl;
    }
};

/**
 * ConcreteMediator通过协调几个Component来实现合作行为。
 */
class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator(Component1 *component1, Component2 *component2)
        : m_component1(component1), m_component2(component2)
    {
        this->m_component1->setMediator(this);
        this->m_component2->setMediator(this);
    }

    void notify(BaseComponent *sender, unsigned int operation) const override
    {
        // 注意DOA里面不能再调用testA，否则自己调用自己，就会无限循环！
        if (operation & DOA)
        {
            m_component1->notifyA();
        }
        if (operation & DOB)
        {
            m_component1->notifyB();
        }
        if (operation & DOC)
        {
            m_component2->notifyC();
        }
        if (operation & DOD)
        {
            m_component2->notifyD();
        }
    }

private:
    Component1 *m_component1;
    Component2 *m_component2;
};

void clientCode()
{
    Component1 *component1 = new Component1();
    Component2 *component2 = new Component2();
    Mediator *mediator = new ConcreteMediator(component1, component2);

    component1->testA();
    component1->testB();
    component2->testC();
    component2->testD();

    component1->notifyA();
    component1->notifyB();

    mediator->notify(component2, DOC | DOD);

    delete component1;
    delete component2;
    delete mediator;
}

int main(void)
{
    clientCode();
    return 0;
}