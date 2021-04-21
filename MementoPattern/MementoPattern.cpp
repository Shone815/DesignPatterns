#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

/**
 * Memento接口提供了一种方法来检索Memento的元数据，例如创建日期或名称。
 * 然而，它并没有暴露Originator的状态。
 */
class Memento
{
public:
    virtual string getState() const = 0;
    virtual string getDate() const = 0;
    virtual string getName() const = 0;
};

/**
 * ConcreteMemento包含了保存Originator状态的基本实现。
 */
class ConcreteMemento : public Memento
{
public:
    ConcreteMemento(string state) : m_state(state)
    {
        this->m_state = state;
        time_t now = time(0);
        this->m_date = ctime(&now);
    }

    /**
     * Originator在恢复其状态时使用此方法。
     */
    string getState() const override
    {
        return this->m_state;
    }
    string getDate() const override
    {
        return this->m_date;
    }
    string getName() const override
    {
        return "date: " + this->m_date + "; state: " + this->m_state.substr(0, 9) + "...";
    }

private:
    string m_state;
    string m_date;
};

/**
 * Originator持有一些可能随时间而改变的重要状态。
 * 它还定义了保存Memento中的状态的方法和从Memento中恢复状态的方法。
 */
class Originator
{
public:
    Originator(string state) : m_state(state)
    {
        cout << "Originator: initial state is: " << this->m_state << endl;
    }

    /**
     * Originator的业务逻辑可能会影响其内部状态。
     * 因此，客户端应该在通过save()方法启动业务逻辑方法之前备份状态。
     */
    void doTask()
    {
        cout << "Originator: I'm doing business for bunch of money!\n";
        this->m_state = this->generateRandomString(30);
        cout << "Originator: then my state changed to: " << this->m_state << endl;
    }

    Memento *save()
    {
        return new ConcreteMemento(this->m_state);
    }

    void restore(Memento *memento)
    {
        this->m_state = memento->getState();
        cout << "Originator: my state has restored to: " << this->m_state << endl;
    }

    string getState()
    {
        return this->m_state;
    }

private:
    string m_state;

    string generateRandomString(int length = 10)
    {
        const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnoppqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        string randomString;
        for (int i = 0; i < length; i++)
        {
            randomString += alphanum[rand() % stringLength];
        }
        return randomString;
    }
};

/**
 * Caretaker并不依赖于具体的Memento类别。因此，它不能访问Originator的状态，储存在Memento里。
 * 它通过基本的Memento接口与所有的Memento工作。
 */
class Caretaker
{
public:
    Caretaker(Originator *originator) : m_originator(originator) {}

    void backup()
    {
        cout << "Caretaker: Saving Originator's state: " << m_originator->getState() << "...\n";
        this->m_mementos.push_back(this->m_originator->save());
    }

    void undo()
    {
        if (!this->m_mementos.size())
        {
            return;
        }
        Memento *memento = this->m_mementos.back();
        this->m_mementos.pop_back();
        cout << "Caretaker: Restoring state to: " << memento->getName() << endl;
        try
        {
            this->m_originator->restore(memento);
        }
        catch (...)
        {
            this->undo();
        }
    }

    void showHistory() const
    {
        cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->m_mementos)
        {
            cout << memento->getName() << endl;
        }
    }

private:
    vector<Memento *> m_mementos;
    Originator *m_originator;
};

void clientCode()
{
    Originator *originator = new Originator("abs");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->backup();
    originator->doTask();
    caretaker->backup();
    originator->doTask();
    caretaker->backup();
    originator->doTask();
    caretaker->backup();
    originator->doTask();
    caretaker->showHistory();
    caretaker->undo();
    caretaker->undo();
    caretaker->showHistory();

    delete originator;
    delete caretaker;
}

int main(void)
{
    clientCode();
    return 0;
}