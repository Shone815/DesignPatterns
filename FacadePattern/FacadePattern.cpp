#include <iostream>
using namespace std;

/**
 * 子系统可以直接接受来自facade或客户机的请求。
 * 在任何情况下，对于子系统来说，Facade仍然是另一个客户机，它不是子系统的一部分。
 */
class SubSystem1
{
public:
    string operation1() const
    {
        return "SubSystem1: operation1 Ready!\n";
    }
    //...
    string operationN() const
    {
        return "SubSystem1: operationN Ready!\n";
    }
};

class SubSystem2
{
public:
    string operation1() const
    {
        return "SubSystem2: operation1 Ready!\n";
    }
    //...
    string operationN() const
    {
        return "SubSystem2: operationN Ready!\n";
    }
};

/**
 * Facade类为一个或几个子系统的复杂逻辑提供了一个简单的接口。
 * Facade将客户机请求委托给子系统中的适当对象。
 * Facade还负责管理它们的生命周期。
 * 所有这些都使客户机免受子系统不必要的复杂性的干扰。
 */
class Facade
{
public:
    Facade(SubSystem1 *subsystem1 = nullptr, SubSystem2 *subsystem2 = nullptr)
    {
        this->m_ss1 = subsystem1 ? subsystem1 : new SubSystem1;
        this->m_ss2 = subsystem2 ? subsystem2 : new SubSystem2;
    }
    ~Facade()
    {
        delete m_ss1;
        delete m_ss2;
    }

    /**
     * Facade的方法是子系统复杂功能的方便快捷方式。
     * 然而，客户机只能获得子系统的一小部分功能。其余功能可以在另外方法中使用。
     */
    string operation()
    {
        string result = "Facade intializes subsystems:\n";
        result += this->m_ss1->operation1();
        result += this->m_ss2->operation1();
        result += "Facade orders subsystems to performs the action:\n";
        result += this->m_ss1->operationN();
        result += this->m_ss2->operationN();
        return result;
    }

protected:
    SubSystem1 *m_ss1;
    SubSystem2 *m_ss2;
};

/**
 * 客户端代码通过Facade提供的简单接口与复杂的子系统一起工作。
 * 当facade管理子系统的生命周期时，客户机甚至可能不知道子系统的存在。
 * 这种方法可以让你的复杂性得以控制。
 */
void clientCode()
{
    Facade *facade = new Facade();
    cout << facade->operation();
    delete facade;

    cout << endl;
    /**
     * 客户端代码可能已经创建了一些子系统的对象。
     * 在这种情况下，使用这些对象初始化Facade而不是让Facade创建新实例。
     */
    SubSystem1 *ss1 = new SubSystem1();
    SubSystem2 *ss2 = new SubSystem2();
    facade = new Facade(ss1, ss2);
    cout << facade->operation();
    delete facade;
}

int main(void)
{
    clientCode();
    return 0;
}