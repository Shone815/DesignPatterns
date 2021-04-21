#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 策略模式
 * Strategy接口声明了一些算法的所有支持版本的通用操作。
 * Context使用这个接口去调用由Strategy子类实现的具体算法。
 */

/**
 * Strategy 基类，这里只提供接口，没有具体的实现。
 */
class Strategy
{
public:
    virtual ~Strategy() {}
    virtual string doAlgorithm(const vector<string> &data) const = 0;
};

/**
 * Context定义与Client相关的操作。
 */
class Context
{
public:
    /**
     * 通常，Context通过构造函数接受一个Strategy类，同时也提供一个setter方法，使得运行时能够改变它。
     */
    Context(Strategy *strategy = nullptr) : p_strategy(strategy)
    {
    }
    ~Context()
    {
        delete this->p_strategy;
    }

    /**
     * 通常，Context类允许在运行时切换Strategy对象。
     */
    void setStrategy(Strategy *strategy)
    {
        delete this->p_strategy;
        this->p_strategy = strategy;
    }

    /**
     * Context将一些工作委托给Strategy对象，而不是自己实现多个版本的算法。
     */
    void doBusiness() const
    {
        // ...
        cout << "Context: sorting data using strategy(not sure how to do it yet) \n";
        string result = this->p_strategy->doAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
        cout << result << endl;
        // ...
    }

private:
    /**
     * Context维护一个Strategy对象的引用。Context不知道Strategy的具体实现类。
     * 它应该通过Strategy接口与所有Strategy一起工作。
     */
    Strategy *p_strategy;
};

/**
 * 具体Strategy A和B在遵循基类Strategy接口的同时实现算法。
 */
class ConcreteStrategyA : public Strategy
{
public:
    string doAlgorithm(const vector<string> &data) const override
    {
        string result;
        for_each(data.begin(), data.end(), [&result](const string &letter) {
            result += letter;
        });
        sort(result.begin(), result.end());

        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
    string doAlgorithm(const vector<string> &data) const override
    {
        string result;
        for_each(data.begin(), data.end(), [&result](const string &letter) {
            result += letter;
        });
        sort(result.begin(), result.end());
        for (int i = 0; i < result.size() / 2; i++)
        {
            swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};

/**
 * clientCode选择一个具体的Strategy并将其传递给Context。为了做出正确的选择，client应该了解不同Strategy之间的差异。
 */
void clientCode()
{
    Context *context = new Context(new ConcreteStrategyA);
    cout << "Client: Strategy is set to do normal sorting.\n";
    context->doBusiness();
    cout << endl;
    cout << "Client: Strategy is set to do reverse sorting.\n";
    context->setStrategy(new ConcreteStrategyB);
    context->doBusiness();
    delete context;
}

int main()
{
    clientCode();
    return 0;
}