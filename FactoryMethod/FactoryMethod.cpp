#include <iostream>
using namespace std;

/**
 * Product 的接口声明了具体products必须实现的所有操作
 */
class Product
{
public:
    Product() {}
    virtual ~Product() {}
    virtual string doMultiTaskPerProduct() const = 0;
};

/**
 * ConcreteProduct 提供了基类Product接口的各种实现
 */
class ConcreteProduct1 : public Product
{
public:
    virtual string doMultiTaskPerProduct() const override
    {
        return "do ConcreteProduct1 task";
    }
};

class ConcreteProduct2 : public Product
{
public:
    virtual string doMultiTaskPerProduct() const override
    {
        return "do ConcreteProduct2 task";
    }
};

/**
 * Factory类声明了返回Product类对象的工厂方法。
 * Factory的子类通常提供此方法的实现。
 */
class Factory
{
public:
    virtual ~Factory() {}
    virtual Product *factoryMethod() const = 0;

    /**
     * 需要注意的是，Factory的主要责任不是创造产品。
     * 通常，它包含一些核心业务逻辑，这些逻辑依赖于由工厂方法factoryMethod返回的产品对象。
     * Factory子类可以通过覆盖factoryMethod并从它返回不同类型的产品来间接更改该业务逻辑。
     * doProcess就是其中一个重要的业务逻辑。
     */
    string doProcess() const
    {
        // 调用factoryMethod创建一个Product对象
        Product *product = this->factoryMethod();
        // 对创建的Product对象进行操作。
        string result = "Creating product " + product->doMultiTaskPerProduct();
        delete product;
        return result;
    }
};

class ConcreteFactory1 : public Factory
{
public:
    /**
     * 注意，factoryMethod的返回类型仍然使用抽象的产品类型，即使具体的产品实际上是从factoryMethod返回的。
     * 这样，Factory可以独立于具体的产品类。
     */
    virtual Product *factoryMethod() const override
    {
        return new ConcreteProduct1();
    }
};

class ConcreteFactory2 : public Factory
{
public:
    virtual Product *factoryMethod() const override
    {
        return new ConcreteProduct2();
    }
};

void clientCode()
{
    /**
     * 使用时，Product 就隐藏起来了。仅仅调用Factory的doProcess即可完成所需操作。
     */
    Factory *fac = new ConcreteFactory1();
    cout << fac->doProcess() << endl;

    delete fac;
    fac = new ConcreteFactory2();
    cout << fac->doProcess() << endl;
    delete fac;
}

int main(void)
{
    clientCode();
    return 0;
}