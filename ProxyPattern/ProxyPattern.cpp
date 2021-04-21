#include <iostream>
#include <memory>
using namespace std;

/**
 * Subject接口为RealSubject和Proxy声明了公共操作。
 * 只要客户机使用这个接口处理RealSubject，就可以向它传递一个Proxy，而不是真正的Subject。
 */
class Subject
{
public:
    virtual void operation() const = 0;
};

/**
 * RealSubject包含一些核心业务逻辑。通常，真正的受试者能够做一些有用的工作，但这些工作可能非常缓慢或敏感
 * 例如，纠正输入数据。Proxy可以在不修改RealSubject代码的情况下解决这些问题。
 */
class RealSubject : public Subject
{
public:
    void operation() const override
    {
        cout << "RealSubject: operation.\n";
    }
};

/**
 * Proxy 和RealSubject有相同的接口
 */
class Proxy : public Subject
{
public:
    Proxy(RealSubject *subject) : m_subject(new RealSubject(*subject)) {}

    /**
     * 代理模式最常见的应用是延迟加载、缓存、控制访问、日志记录等。
     * 代理可以执行这些操作之一，然后根据结果将执行传递给链接的RealSubject对象中的相同方法。
     */
    void operation() const override
    {
        // doEncrypt
        // ...
        cout << "Encrypt done" << endl;
        if (this->checkpwd())
        {
            this->m_subject->operation();
        }
        cout << "Decrypt done" << endl;
    }

private:
    /**
     * Proxy维护对RealSubject类的对象的引用。它可以是惰性加载的，也可以由客户端传递给Proxy。
     * 这里使用只能指针，因此没有在析构函数中delete它。
     */
    unique_ptr<Subject> m_subject;

    bool checkpwd() const
    {
        cout << "Checkpwd...\n";
        return true;
    }
};

void clientCode()
{
    RealSubject *subject = new RealSubject();
    subject->operation();

    Proxy *proxy = new Proxy(subject);
    proxy->operation();
    delete subject;
}

int main(void)
{
    clientCode();
    return 0;
}