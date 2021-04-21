#include <iostream>
using namespace std;

/**
 * Implementation类定义了所有相关实现类的接口。它不需要跟Abstraction抽象类接口进相匹配。
 * 实际上，这两个类的接口可以完全不同。
 * 通常，Implementation类用于提供原始操作，而Abstraction类定义了基于原始操作更高层次的操作。
 */
class Implementation
{
public:
    virtual ~Implementation() {}
    virtual string implement() const = 0;
};

/**
 * 每个具体的Implementation子类与特定平台相关，并实现与这个平台API相关的Implementation类接口。
 */
class ConcreteImplementation1 : public Implementation
{
public:
    virtual string implement() const override
    {
        return "ConcreteImplementation1 implementation.\n";
    }
};

class ConcreteImplementation2 : public Implementation
{
public:
    virtual string implement() const override
    {
        return "ConcreteImplementation2 implementation.\n";
    }
};

/**
 * 抽象类定了两个层次结构中的控制接口。它维护对实现层对象的引用，并将所有实际工作委托给这个实现层对象。
 */
class Abstraction
{
public:
    Abstraction(Implementation *impl) : m_impl(impl) {}
    virtual ~Abstraction() {}
    virtual string operation() const
    {
        return "Base Abstraction operation with " + this->m_impl->implement();
    }

protected:
    /**
     * @var Implementation
     */
    Implementation *m_impl;
};

/**
 * 可以扩展多个Abstraction子类，并不需要改变Implementation类
 */
class ConcreteAbstraction1 : public Abstraction
{
public:
    ConcreteAbstraction1(Implementation *impl) : Abstraction(impl) {}
    virtual string operation() const override
    {
        return "ConcreteAbstraction1 operation with " + this->m_impl->implement();
    }
};

class ConcreteAbstraction2 : public Abstraction
{
public:
    ConcreteAbstraction2(Implementation *impl) : Abstraction(impl) {}
    virtual string operation() const override
    {
        return "ConcreteAbstraction2 operation with " + this->m_impl->implement();
    }
};

void clientCode()
{
    Implementation *impl = new ConcreteImplementation1;
    Abstraction *a = new ConcreteAbstraction1(impl);
    cout << a->operation();
    delete a;
    a = new ConcreteAbstraction2(impl);
    cout << a->operation();
    delete a;
    a = new Abstraction(impl);
    cout << a->operation();
    delete a;
    delete impl;
    impl = new ConcreteImplementation2;
    a = new ConcreteAbstraction2(impl);
    cout << a->operation();

    delete a;
    delete impl;
}

int main()
{
    clientCode();
    return 0;
}