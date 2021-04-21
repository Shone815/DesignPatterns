#include <iostream>
#include <vector>
using namespace std;

/**
 * 只有当你的产品非常复杂且需要大量配置时，使用Builder模式才有意义。
 * 不同于其他的创建型模式，不同的ConcreteBuilder可以生产不相关的产品。
 * 换句话说，不同ConcreteBuilder的结果可能并不总是遵循相同的接口。
 */
class Product1
{
public:
    vector<string> m_parts;
    void printAllParts() const
    {
        cout << "Current product has below parts: \n";
        for (auto &i : m_parts)
        {
            cout << i << endl;
        }
        cout << endl;
    }
};

enum BuilderSequense
{
    PART1 = 1 << 0,
    PART2 = 1 << 1,
    PART3 = 1 << 2,
};
class Builder
{
public:
    virtual ~Builder() {}
    virtual void buildPart1() const = 0;
    virtual void buildPart2() const = 0;
    virtual void buildPart3() const = 0;
};

class ConcreteBuilder1 : public Builder
{
    /**
     * 一个新的生成器实例应该包含一个空白的product对象，该对象将用于进一步的组装。
     */
public:
    ConcreteBuilder1()
    {
        this->reset();
    }
    ~ConcreteBuilder1()
    {
        delete product1;
    }
    void reset()
    {
        this->product1 = new Product1();
    }
    void buildPart1() const override
    {
        this->product1->m_parts.push_back("Part1");
        cout << "ConcreteBuilder1 building part1..." << endl;
    }
    void buildPart2() const override
    {
        this->product1->m_parts.push_back("Part2");
        cout << "ConcreteBuilder1 building part2..." << endl;
    }
    void buildPart3() const override
    {
        this->product1->m_parts.push_back("Part3");
        cout << "ConcreteBuilder1 building part3..." << endl;
    }

    /**
     * ConcreteBuilder应该提供他们自己的方法来检索结果。这是因为不同类型的ConcreteBuilder
     * 可能会创建完全不同的产品，它们不遵循相同的接口。因此，这些方法不能在Builder基类接口中
     * 声明(至少在静态类型编程语言中)。
     * 
     * 通常，在将最终结果返回给客户机后，Builder实例将准备开始生产另一个产品。这就是为什么
     * 通常在'getProduct'方法体的末尾调用reset方法的原因。但是，此行为不是强制性的，你也可
     * 以让Builder在处理前一个结果之前等待客户端代码的显式重置调用。
     */

    /**
     * 请小心这里的内存使用。一旦你调用GetProduct，这个函数的用户就有责任释放这块内存。
     * 使用智能指针来避免内存泄漏可能是一个更好的选择。
     */
    Product1 *getProduct()
    {
        Product1 *result = this->product1;
        this->reset();
        return result;
    }

private:
    Product1 *product1;
};

/**
 * Director只负责按特定顺序执行Builder步骤。它有助于根据特定的订单或配置生产产品。
 * 严格地说，Director类是可选的，因为客户机可以直接控制Builder。
 */
class Director
{
public:
    Director(Builder *builder) : m_builder(builder), m_buildMap(0) {}
    Director(Builder *builder, int32_t buildMap) : m_builder(builder), m_buildMap(buildMap) {}
    // const void buildFirstPart() // 表示函数返回值为const类型
    void buildFirstPart() const // 只能是类成员函数，表示不修改类对象数据
    {
        m_builder->buildPart1();
    }

    void buildFirstTwoPart() const
    {
        m_builder->buildPart1();
        m_builder->buildPart2();
    }

    void builAllPart() const
    {
        m_builder->buildPart1();
        m_builder->buildPart2();
        m_builder->buildPart3();
    }

    /**
     * 根据输入的buildMap按顺序进行相应的build工作。
     */
    void buildByDefine(int32_t buildMap = 0)
    {
        m_buildMap = (buildMap == 0) ? m_buildMap : buildMap;
        if (m_buildMap == 0)
        {
            cout << "Input buildmap is invalid!\n";
        }
        else
        {
            if (m_buildMap & BuilderSequense::PART1)
            {
                m_builder->buildPart1();
            }
            if (m_buildMap & BuilderSequense::PART2)
            {
                m_builder->buildPart2();
            }
            if (m_buildMap & BuilderSequense::PART3)
            {
                m_builder->buildPart3();
            }
        }
    }

private:
    Builder *m_builder;
    int32_t m_buildMap;
};

void clientCode()
{
    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    Director *director = new Director(builder);
    director->buildByDefine(2);
    director->buildByDefine(3);
    Product1 *product = builder->getProduct();
    product->printAllParts();
    builder->reset();
    delete product;

    director->buildByDefine(5);
    product = builder->getProduct();
    product->printAllParts();

    delete product;
    delete director;
    delete builder;
}

int main(void)
{
    clientCode();
    return 0;
}