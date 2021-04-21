/**
 * 适配器模式。
 * 这里仅仅演示了对象适配器模式。
 * 由于类适配器（多继承）模式使用并不多，因此不推荐列出来。
 */

#include <iostream>
using namespace std;

/**
 * Target定义客户端代码可使用的特定领域的接口。
 */
class Target
{
public:
    virtual ~Target() {}
    virtual string request() const
    {
        return "Target: This is the request from default target.";
    }
};

/**
 * Adaptee包含一些有用的行为，但是它的接口与现有的客户机代码不兼容。
 * 在客户端代码能够使用它之前，Adaptee需要进行一些调整。
 */
class Adaptee
{
public:
    string oldRequest() const
    {
        return "Adaptee: This is an old resquest from Adaptee.";
    }
};

/**
 * Adapter使Adaptee的接口与目标的接口兼容。
 */
class Adapter : public Target
{
public:
    Adapter(Adaptee *adaptee) : m_adaptee(adaptee) {}
    string request() const override
    {
        string str = m_adaptee->oldRequest();
        return "Adapter: override request from oldRequest: " + str;
    }

protected:
    Adaptee *m_adaptee;
};

void clientCode()
{
    Target *target = new Target();
    Adaptee *adaptee = new Adaptee();
    Target *adapter = new Adapter(adaptee);

    cout << target->request() << endl;
    cout << adaptee->oldRequest() << endl;
    cout << adapter->request() << endl;

    delete adapter;
    delete adaptee;
    delete target;
}

int main(void)
{
    clientCode();
    return 0;
}