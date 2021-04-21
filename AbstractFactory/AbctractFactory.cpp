#include <iostream>
using namespace std;

/**
 * 每个不同的Product 都应该有一个抽象基类
 * 
 */
class AbstractProductA
{
public:
    AbstractProductA() {}
    virtual ~AbstractProductA() {}
    virtual string doMultiTaskPerProductA() const = 0;
};
class ConcreteProductA1 : public AbstractProductA
{
public:
    string doMultiTaskPerProductA() const override
    {
        return "do ConcreteProductA1 task";
    }
};
class ConcreteProductA2 : public AbstractProductA
{
public:
    string doMultiTaskPerProductA() const override
    {
        return "do ConcreteProductA2 task";
    }
};

class AbstractProductB
{
public:
    AbstractProductB() {}
    virtual ~AbstractProductB() {}
    virtual string doMultiTaskPerProductB() const = 0;
};
class ConcreteProductB1 : public AbstractProductB
{
public:
    string doMultiTaskPerProductB() const override
    {
        return "do ConcreteProductB1 task";
    }
};
class ConcreteProductB2 : public AbstractProductB
{
public:
    string doMultiTaskPerProductB() const override
    {
        return "do ConcreteProductB2 task";
    }
};

/**
 * 抽象工厂接口声明了一组返回不同抽象产品的方法。
 * 这些产品被称为一个家庭，并通过一个高级主题或概念联系在一起。一个家庭的产品通常能够相互协作。
 * 一个产品系列可能有几个变种，但是一个变种的产品与另一个变种的产品互不兼容。
 */
class AbstractFactory
{
public:
    virtual ~AbstractFactory() {}

    virtual AbstractProductA *createProductA() const = 0;
    virtual AbstractProductB *createProductB() const = 0;

    void doSeries()
    {
        AbstractProductA *productA = this->createProductA();
        AbstractProductB *productB = this->createProductB();
        cout << "Creating AbstractProductA: " << productA->doMultiTaskPerProductA() << endl;
        cout << "Creating AbstractProductB: " << productB->doMultiTaskPerProductB() << endl;
        delete productA;
        delete productB;
    }
};

/**
 * AbstractFactory具体类生产属于单一变体的一系列产品。
 * 工厂保证产生的产品是兼容的。
 * 请注意，具体工厂的各种product方法返回一个抽象产品，而在方法内部则实例化一个具体产品。
 */
class ConcreteFactory1 : public AbstractFactory
{
public:
    ConcreteFactory1()
    {
        cout << "Creating ConcreteFactory1..." << endl;
    }
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA1();
    }
    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    ConcreteFactory2()
    {
        cout << "Creating ConcreteFactory2..." << endl;
    }
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA1();
    }
    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB1();
    }
};

void clientCode()
{
    AbstractFactory *fac = new ConcreteFactory1();
    fac->doSeries();
    delete fac;

    fac = new ConcreteFactory2();
    fac->doSeries();
    delete fac;
}

int main(void)
{
    clientCode();
    return 0;
}