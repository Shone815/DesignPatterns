#include <iostream>
#include <string.h> // string.h
#include <vector>
using namespace std;

/**
 * Handler接口声明了一个用于构建处理程序链的方法。它还声明了一个用于执行请求的方法。
 */
class Handler
{
public:
    virtual Handler *setNext(Handler *handler) = 0;
    virtual string handle(string request) = 0;
};

class AbstractHandler : public Handler
{
public:
    AbstractHandler() : m_next_handler(nullptr) {}

    /**
     * 从这里返回一个处理程序将让我们方便地链接处理程序
     */
    Handler *setNext(Handler *handler) override
    {
        this->m_next_handler = handler;
        return handler;
    }

    /**
     * default的链接行为最好在处理程序基类中实现。
     */
    string handle(string request) override
    {
        if (this->m_next_handler)
        {
            return this->m_next_handler->handle(request);
        }

        return {};
    }

private:
    Handler *m_next_handler;
};

/**
 * 所有具体的处理程序要么处理请求，要么将其传递给链中的下一个处理程序。
 */
class MonkeyHandler : public AbstractHandler
{
public:
    string handle(string request) override
    {
        if (!_stricmp(request.c_str(), "Banana"))
        {
            return "Monkey: " + request + "!\n";
            return "Monkey: Banana!\n";
        }
        else
        {
            cout << "->Monkey: no, next!\n";
            return AbstractHandler::handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler
{
public:
    string handle(string request) override
    {
        if (!_stricmp(request.c_str(), "Nut"))
        {
            return "Squirrel: " + request + "!\n";
        }
        else
        {
            cout << "->Squirrel: no, next!\n";
            return AbstractHandler::handle(request);
        }
    }
};
class DogHandler : public AbstractHandler
{
public:
    string handle(string request) override
    {
        if (!_stricmp(request.c_str(), "Bone"))
        {
            return "Dog: " + request + "!\n";
        }
        else
        {
            cout << "->Dog: no, next!\n";
            return AbstractHandler::handle(request);
        }
    }
};

void handle(Handler &handler)
{
    vector<string> food = {"Nut", "Banana", "Bone", "Coffee"};
    for (const string &f : food)
    {
        cout << "Handle: Who wants a " << f << "?\n";
        const string result = handler.handle(f);
        if (!result.empty())
        {
            cout << " " << result << endl;
        }
        else
        {
            cout << "Woops! Nobody wants " << f << ".\n";
        }
    }
}

void clientCode()
{
    MonkeyHandler *monkey = new MonkeyHandler();
    SquirrelHandler *squirrel = new SquirrelHandler();
    DogHandler *dog = new DogHandler();
    monkey->setNext(squirrel)->setNext(dog);

    cout << "Process: monkey -> squirrel -> dog. \n";
    handle(*monkey);

    cout << "Process: squirrel -> dog.\n";
    handle(*squirrel);

    delete monkey, squirrel, dog;
}

int main(void)
{
    clientCode();
    return 0;
}