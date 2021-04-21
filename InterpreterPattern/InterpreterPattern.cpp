/**
 * 解释器模式
 * 四则运算
 */

#include <iostream>
#include <map>
#include <stack>
using namespace std;

class Expression
{
public:
    virtual int interpreter(map<string, int> &var) = 0;
    virtual ~Expression(){};
};

// 变量解析器（终结符表达式）
class VarExpression : public Expression
{
public:
    VarExpression(string key) : m_key(key) {}
    int interpreter(map<string, int> &var) override
    {
        return var[m_key];
    }
    ~VarExpression()
    {
        cout << "Bye~VarExpression()" << endl;
    }

private:
    string m_key;
};

// 抽象运算符号解析器
class SymbolExpression : public Expression
{
public:
    SymbolExpression(Expression *left, Expression *right) : m_left(left), m_right(right) {}

    Expression *getLeft()
    {
        return m_left;
    }

    Expression *getRight()
    {
        return m_right;
    }

protected:
    Expression *m_left;
    Expression *m_right;
};

// 加法解析器
class AddExpression : public SymbolExpression
{
public:
    AddExpression(Expression *left, Expression *right)
        : SymbolExpression(left, right)
    {
    }

    int interpreter(map<string, int> &var)
    {
        return m_left->interpreter(var) + m_right->interpreter(var);
    }
    ~AddExpression()
    {
        cout << "Bye~AddExpression().\n";
    }
};

// 减法解析器
class SubExpression : public SymbolExpression
{
public:
    SubExpression(Expression *left, Expression *right)
        : SymbolExpression(left, right)
    {
    }

    int interpreter(map<string, int> &var)
    {
        return m_left->interpreter(var) - m_right->interpreter(var);
    }

    ~SubExpression()
    {
        cout << "Bye~SubExpression().\n";
    }
};

/**
 * 解析器封装类
 * 根据迪米特法则进行封装，目的是让client只与直接朋友打交道，相当于Facade。
 */
class Calculator
{
public:
    // 构造函数传参，并解析表达式，构建语法树。
    Calculator(string expStr)
    {
        m_expression = NULL;
        stack<Expression *> stackExp; // 栈，用来暂存中间结果。

        Expression *left = NULL;
        Expression *right = NULL;

        /**
         * 从左向右分析表达式，a+b-c+d，最终语法树如下：
         *                  +
         *                /   \
         *               -     d
         *             /   \
         *            +     c
         *          /   \
         *         a     b
         */
        for (unsigned int i = 0; i < expStr.size(); i++)
        {
            switch (expStr[i])
            {
            case '+':
                /* code */
                left = stackExp.top();
                stackExp.pop();

                right = new VarExpression(expStr.substr(++i, 1));

                stackExp.push(new AddExpression(left, right));
                break;

            case '-':
                /* code */
                left = stackExp.top();
                stackExp.pop();

                right = new VarExpression(expStr.substr(++i, 1));

                stackExp.push(new SubExpression(left, right));
                break;

            default:
                stackExp.push(new VarExpression(expStr.substr(i, 1)));
                break;
            }
        }

        // 栈中保存的就是最终语法树的根节点。
        if (!stackExp.empty())
        {
            m_expression = stackExp.top();
            stackExp.pop();
        }
    }

    void deleteTree(Expression *expression)
    {
        SymbolExpression *branch = dynamic_cast<SymbolExpression *>(expression);
        // 叶子节点。
        if (branch == NULL)
        {
            delete expression;
        }
        else
        {
            deleteTree(branch->getLeft());
            deleteTree(branch->getRight());
            delete expression;
        }
    }

    ~Calculator()
    {
        deleteTree(m_expression);
    }

    int run(map<string, int> &var)
    {
        return (m_expression == NULL) ? 0 : m_expression->interpreter(var);
    }

private:
    Expression *m_expression;
};

void clientCode()
{
    string expStr = "a+b-c+d";
    map<string, int> var;
    var.emplace("a", 100);
    var.emplace("b", 20);
    var.emplace("c", 40);
    var.emplace("d", 50);

    Calculator cal(expStr);

    cout << "Result of " << expStr << ": " << cal.run(var) << endl;
}

int main(void)
{
    clientCode();
    return 0;
}