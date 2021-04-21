#include <iostream>
#include <list>
using namespace std;

/**
 * 观察者模式
 * 目的：定义一个订阅机制来通知多个Observers正在观察的Subject发生的任何事件。
 *     可以自定义添加某些Observer，也可以删除Observer。
 * 注意，有许多不同的术语与此模式有相似的含义。
 *     只要记住主题也被称为发布者，观察者通常被称为订阅者，反之亦然。
 *     动词“observe”、“listen”或“track”通常都有相同的意思。
 */

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void update(const string &messageFromObject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify() = 0;
};

/**
 * Subject拥有一些重要的状态，并在状态改变时通知观察者。
 */
class Subject : public ISubject
{
public:
    virtual ~Subject()
    {
        cout << "Goodbye, the Subject is gone.\n";
    }

    /**
     * 订阅机制增删管理方法
     */
    void attach(IObserver *observer) override
    {
        m_listObserver.push_back(observer);
    }

    void detach(IObserver *observer) override
    {
        m_listObserver.remove(observer);
    }

    void notify() override
    {
        list<IObserver *>::iterator itor = m_listObserver.begin();
        howManyObserver();
        while (itor != m_listObserver.end())
        {
            (*itor)->update(m_message);
            ++itor;
        }
    }

    void createMessage(string msg = "Empty")
    {
        this->m_message = msg;
        notify();
    }

    void howManyObserver()
    {
        cout << "There are " << m_listObserver.size() << " observers in the list.\n";
    }

    /**
     * 通常，订阅逻辑只是主题真正能做的事情的一小部分。
     * 主题通常拥有一些重要的业务逻辑，当重要的事情即将发生(或发生之后)时，这些逻辑就会触发通知方法。
     */
    void someImportantBusiness()
    {
        this->m_message = "change important part";
        notify();
        cout << "Some important happens\n";
    }

private:
    list<IObserver *> m_listObserver;
    string m_message;
};

class Observer : public IObserver
{
public:
    Observer(Subject &subject) : m_subject(subject)
    {
        this->m_subject.attach(this);
        cout << "Hey, I'm the Observer \"" << ++Observer::m_static_number << "\".\n";
        this->m_number = Observer::m_static_number;
    }

    virtual ~Observer()
    {
        cout << "Goodbye, Observer \"" << this->m_number << "\" is gone.\n";
    }

    void update(const string &msg) override
    {
        m_message = msg;
        printInfo();
    }

    void removeObserver()
    {
        m_subject.detach(this);
        cout << "Observer \"" << m_number << "\" was removed from the list.\n";
    }

    void printInfo()
    {
        cout << "Observer \"" << this->m_number << "\": a new message is available --> " << this->m_message << endl;
    }

private:
    Subject &m_subject;
    static int m_static_number;
    int m_number;
    string m_message;
};

int Observer::m_static_number = 0;

void clientCode()
{
    Subject *subject = new Subject;
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->createMessage("Hello world! :)");
    observer3->removeObserver();

    subject->createMessage("What a cool day! :P");
    observer4 = new Observer(*subject);

    observer2->removeObserver();
    observer5 = new Observer(*subject);

    subject->createMessage("I like the design! :)");
    observer5->removeObserver();
    observer4->removeObserver();
    observer1->removeObserver();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    clientCode();
    return 0;
}