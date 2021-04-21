#include <iostream>
using namespace std;

/**
 * 模板方法模式
 * 抽象类定义了一个模板方法，该方法包含一些算法的骨架，(通常)由抽象的原始操作的调用组成。
 * 具体的子类应该实现这些操作，但不要破坏模板方法本身。
 */
class AbstractClass
{
public:
    /**
     * 模板方法定义的算法框架
     */
    void templateMethod() const
    {
        this->baseOperation1();
        this->requiredOperation1();
        this->baseOperation2();
        this->hook1();
        this->requiredOperation2();
        this->baseOperation3();
        this->hook2();
    }
    virtual ~AbstractClass() {}

protected:
    /**
     * 以下操作已经有了实现，并不可被重载
     */
    void baseOperation1() const
    {
        cout << "AbstractClass : I am doing the bulk of the work baseOperation1!" << endl;
    }

    void baseOperation2() const
    {
        cout << "AbstractClass : I am doing the bulk of the work baseOperation2!" << endl;
    }

    void baseOperation3() const
    {
        cout << "AbstractClass : I am doing the bulk of the work baseOperation3!" << endl;
    }

    /**
     * 以下操作是纯虚函数，必须被子类重载，用于扩展
     */
    virtual void requiredOperation1() const = 0;
    virtual void requiredOperation2() const = 0;

    /**
     * 以下操作是普通虚函数，可以被子类重载，也可以作为默认函数不被子类重载。属于可选扩展。
     * 注：若被子类重载，最好加上override关键字才能保证一定会被重写，以避免拼写等低级错误。
     */
    virtual void hook1() const {}
    virtual void hook2() const {}
};

/**
 * 具体类必须实现基类的所有抽象操作。注意要加override关键字。
 * 它们还可以用默认实现覆盖某些操作。
 */
class ConcreteClass1 : public AbstractClass
{
protected:
    void requiredOperation1() const override
    {
        cout << "ConcreteClass1 : Implemented requiredOperation1." << endl;
    }

    void requiredOperation2() const override
    {
        cout << "ConcreteClass1 : Implemented requiredOperation2." << endl;
    }
};

/**
 * 通常，具体类只覆盖基类操作的一小部分。
 */
class ConcreteClass2 : public AbstractClass
{
protected:
    void requiredOperation1() const override
    {
        cout << "ConcreteClass2 : Implemented requiredOperation1." << endl;
    }

    void requiredOperation2() const override
    {
        cout << "ConcreteClass2 : Implemented requiredOperation2." << endl;
    }

    void hook1() const override
    {
        cout << "ConcreteClass2 : Overriden hook1." << endl;
    }
};

/**
 * 客户端代码调用模板方法来执行算法。
 * 客户端代码不需要知道它所处理的对象的具体类，只要它通过对象基类的接口来处理它们就可以了。
 */
void ClientCode(AbstractClass *p_class)
{
    // ...
    p_class->templateMethod();
    // ...
}

int main()
{
    cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 *concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    cout << endl;
    cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 *concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;

    return 0;
}