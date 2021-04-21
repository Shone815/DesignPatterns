#include <iostream>
using namespace std;

/**
 * Command接口声明了一个用于执行命令的方法。
 */
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

/**
 * 有些命令可以自己执行简单的操作。
 */
class SimpleCommand : public Command
{
public:
    explicit SimpleCommand(string pay_load) : m_pay_load(pay_load) {}
    void execute() const override
    {
        cout << "SimpleCommand: this task is too simple and give it to me.\n";
    }

private:
    string m_pay_load;
};

/**
 * Receiver类包含一些重要的业务逻辑。他们知道如何执行与执行请求相关的各种操作。事实上，任何类都可以作为接收者。
 */
class Receiver
{
public:
    void doTask(const string str)
    {
        cout << "Receiver: Working on " << str << ".\n";
    }
    void doExtraTask(const string str)
    {
        cout << "Receiver: Working on extra task: " << str << ".\n";
    }
};

/**
 * 然而，有些命令可以将更复杂的操作委托给其他对象，称为“接收者”。
 */
class ComplexCommand : public Command
{
public:
    /**
     * ComplexCommand可以通过构造函数接受一个或多个receiver对象以及任何上下文数据。
     */
    ComplexCommand(Receiver *receiver, string str1, string str2)
        : m_receiver(receiver), m_str1(str1), m_str2(str2)
    {
    }

    /**
     * ComplexCommand可以委托给Receiver的任何方法。
     */
    void execute() const override
    {
        cout << "ComplexCommand: Complex stuff should be done by a receiver.\n";
        this->m_receiver->doTask(this->m_str1);
        this->m_receiver->doExtraTask(this->m_str2);
    }

private:
    Receiver *m_receiver;
    string m_str1;
    string m_str2;
};

class Invoker
{
public:
    ~Invoker()
    {
        delete m_start;
        delete m_end;
    }
    void setStart(Command *cmd)
    {
        this->m_start = cmd;
    }
    void setFinish(Command *cmd)
    {
        this->m_end = cmd;
    }

    /**
     * Invoker不依赖于具体的命令或接收方类。调用方通过执行命令间接地将请求传递给接收方。
     */
    void doSomethingImportant()
    {
        cout << "Invoker: start something...\n";
        if (this->m_start)
        {
            this->m_start->execute();
        }
        cout << "Invoker: Important ongoing...\n";
        if (this->m_end)
        {
            this->m_end->execute();
        }
    }

private:
    Command *m_start;
    Command *m_end;
};

void clientCode()
{
    Invoker *invoker = new Invoker;
    invoker->setStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->setFinish(new ComplexCommand(receiver, "Send Email", "Save report"));
    invoker->doSomethingImportant();

    delete invoker, receiver;
}

int main(void)
{
    clientCode();
    return 0;
}