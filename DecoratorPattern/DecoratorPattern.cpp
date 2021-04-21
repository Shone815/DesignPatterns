#include <iostream>
using namespace std;

/**
 * 基类Component，提供可供Decorator修改的operation接口
 */
class Component
{
public:
    Component()
    {
        cout << "Create Component.\n";
    }
    virtual ~Component() {}
    virtual string operation() const = 0;
};

/**
 * 具体Component提供操作的默认实现1。这些类可能有几种变体。
 */
class ConcreteComponent1 : public Component
{
public:
    ConcreteComponent1()
    {
        cout << "Create ConcreteComponent1.\n";
    }
    // 子类可以加virtual，也可以不加。会自动成为virtual，但加上会更清晰
    virtual string operation() const override
    {
        return "ConcreteComponent1: operation.";
    }
};

/**
 * 具体Component提供操作的默认实现2。这些类可能有几种变体。
 */
class ConcreteComponent2 : public Component
{
public:
    ConcreteComponent2()
    {
        cout << "Create ConcreteComponent2.\n";
    }
    virtual string operation() const override
    {
        return "ConcreteComponent2: operation.";
    }
};

/**
 * Decorator基类，遵循与其他Component类相同的接口。
 * 这个类的主要目的是为所有的具体Decorator类定义包装接口。
 * 包装代码的默认实现可能包括用于存储包装Component的字段和初始化Component的方法。
 */
class Decorator : public Component
{
public:
    Decorator(Component *comp) : m_component(comp)
    {
        cout << "Create Decorator component.\n";
    }

    /**
     * Decorator将所有工作委托给被包装的Component。
     */
    virtual string operation() const override
    {
        return this->m_component->operation();
    }

protected:
    /**
     * @var Component
     */
    Component *m_component;
};

/**
 * Decorator具体实现1调用被包装的Component对象，并以某种方式修改其结果。
 */
class ConcreteDecorator1 : public Decorator
{
public:
    ConcreteDecorator1(Component *comp) : Decorator(comp)
    {
        cout << "Create ConcreteDecorator1 Decorator.\n";
    }

    /**
     * ConcreteDecorator可以调用operation()的父实现，而不是直接调用包装的对象。
     * 这种方法简化了Decorator类的扩展。
     */
    virtual string operation() const override
    {
        /**
         * Decorator可以在调用包装的对象之前或之后执行它们的operation() 。
         */
        return "ConcreteDecorator1(" + Decorator::operation() + ").";
    }
};

class ConcreteDecorator2 : public Decorator
{
public:
    ConcreteDecorator2(Component *comp) : Decorator(comp)
    {
        cout << "Create ConcreteDecorator2 Decorator.\n";
    }

    virtual string operation() const override
    {
        return "ConcreteDecorator2(" + Decorator::operation() + ").";
    }
};

/**
 * clientCode可使用Component接口处理所有对象。
 * 这样，它就可以独立于它所处理的Component的具体类。
 */
void clientCode()
{
    // 注意：ConcreteDecorator 可以装多个Decorator，但只能装一个ConcreteComponent。
    Component *ccomp1 = new ConcreteComponent1;
    cout << "ccomp1->operation(): " << ccomp1->operation() << endl;
    Component *cd1 = new ConcreteDecorator1(ccomp1);
    cout << "cd1->operation(): " << cd1->operation() << endl;
    Component *cd2 = new ConcreteDecorator1(cd1);
    cout << "cd2->operation(): " << cd2->operation() << endl;
    Component *cd3 = new ConcreteDecorator2(ccomp1);
    cout << "cd3->operation(): " << cd3->operation() << endl;
    Component *cd4 = new ConcreteDecorator2(cd2);
    cout << "cd4->operation(): " << cd4->operation() << endl;
    Component *cd5 = new ConcreteDecorator2(cd3);
    cout << "cd5->operation(): " << cd5->operation() << endl;

    Component *ccomp2 = new ConcreteComponent2;
    cout << "ccomp2->operation(): " << ccomp2->operation() << endl;
    Component *cd6 = new ConcreteDecorator2(cd2);
    cout << "cd6->operation(): " << cd6->operation() << endl;
    Component *cd7 = new ConcreteDecorator2(ccomp2);
    cout << "cd7->operation(): " << cd7->operation() << endl;

    delete ccomp1;
    delete ccomp2;
    delete cd1;
    delete cd2;
    delete cd3;
    delete cd4;
    delete cd5;
    delete cd6;
    delete cd7;
}

int main()
{
    clientCode();
    return 0;
}