#include <iostream>
using namespace std;

/**
 * State基类声明了所有具体状态都应该实现的方法，还提供了与状态相关联的Context对象的反向引用。
 * State可以使用这个反向引用将Context转换到另一个状态。
 */
class Context;
class State
{
public:
    virtual ~State() {}
    virtual void handle1() const = 0;
    virtual void handle2() const = 0;
    void setContext(Context *context)
    {
        this->m_context = context;
    }

protected:
    Context *m_context;
};

/**
 * Context定义了客户所感兴趣的接口。它还维护对State子类实例的引用，该实例表示Context的当前状态。
 */
class Context
{
public:
    Context(State *state) : m_state(nullptr)
    {
        this->transferStateTo(state);
    }

    /**
     * transferStateTo允许State对象在运行是可以切换Context的状态
     */
    void transferStateTo(State *state)
    {
        if (m_state != nullptr)
        {
            delete m_state;
        }
        this->m_state = state;
        this->m_state->setContext(this);
    }

    /**
     * Context将其部分行为委托给当前State对象。
     */
    void request1()
    {
        this->m_state->handle1();
    }
    void request2()
    {
        this->m_state->handle2();
    }

private:
    /**
     * m_state保存了Context当前状态
     */
    State *m_state;
};

/**
 * ConcreteState实现与Context相关联的各种行为。
 */
class ConcreteState1 : public State
{
public:
    void handle1() const override
    {
        cout << "ConcreteState1 handle1...\n";
    }
    void handle2() const override;
};
class ConcreteState2 : public State
{
public:
    void handle1() const override
    {
        cout << "ConcreteState2 handle1...\n";
    }
    void handle2() const override
    {
        cout << "ConcreteState2 handle2...\n";
        this->m_context->transferStateTo(new ConcreteState1);
    }
};

void ConcreteState1::handle2() const
{
    cout << "ConcreteState1 handle2...\n";
    this->m_context->transferStateTo(new ConcreteState2);
}

void clientCode()
{
    Context *context = new Context(new ConcreteState1);
    context->request1();
    context->request2(); // 切换状态
    context->request1();
    context->request2();

    delete context;
}

int main(void)
{
    clientCode();
    return 0;
}