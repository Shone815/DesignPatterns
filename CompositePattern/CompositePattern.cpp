#include <iostream>
#include <list>
using namespace std;

/**
 * Component基类为Composite的简单和复杂对象声明了常用操作。
 */
class Component
{
public:
    /**
     * Component基类还可以声明一个接口，用于在树形结构中设置和访问组件的父组件。它还可以为这些方法提供一些默认实现。
     */
    virtual ~Component() {}
    void setParent(Component *parent)
    {
        this->m_parent = parent;
    }

    Component *getParent() const
    {
        return this->m_parent;
    }

    /**
     * 在某些情况下，在Component基类中定义子类的管理操作是有益的。
     * 这样，不需要向客户机代码公开任何具体的Component类，即使是在对象树程序集期间。
     * 缺点是这些方法对于叶级子Component来说是空的，目前没有很好的方法避免这个问题。
     */
    virtual void add(Component *component) {}
    virtual void remove(Component *component) {}

    /**
     * 你可以提供一个方法，让客户端代码判断一个Component是否可以生育Component子类。
     */
    virtual bool isComposite() const
    {
        return false;
    }

    virtual string doTask() const = 0;

protected:
    Component *m_parent;
};

/**
 * Leaf类表示Component的结束对象。一片叶子是不能有孩子的。
 * 通常，Leaf子对象做实际的工作，而Composite对象只委托给它们的Component子类。
 */
class Leaf : public Component
{
public:
    string doTask() const override
    {
        return "Leaf";
    }
};

/**
 * Composite类表示可能有子组件的复杂组件。通常，Composite对象将实际工作委托给它们的子对象，然后“总结”结果。
 */
class Composite : public Component
{
public:
    void add(Component *component) override
    {
        this->m_children.push_back(component);
        component->setParent(this);
    }

    /**
     * 请记住，这个方法删除了指向列表的指针，但并没有释放内存，您应该手动执行，或者更好地使用智能指针。
     */
    void remove(Component *component) override
    {
        m_children.remove(component);
        component->setParent(nullptr);
    }
    bool isComposite() const override
    {
        return true;
    }

    /**
     * 该Composite以特定的方式执行其主要逻辑。它递归地遍历所有子节点，收集并汇总它们的结果。
     * 由于Composite的子对象将这些调用传递给它们的子对象等等，因此将遍历整个对象树。
     */
    string doTask() const override
    {
        string result;
        for (const Component *c : m_children)
        {
            if (c == m_children.back())
            {
                result += c->doTask();
            }
            else
            {
                result += c->doTask() + "+";
            }
        }

        return "Branch (" + result + ")";
    }

protected:
    list<Component *> m_children;
};

void clientCode()
{
    Component *simple = new Leaf();
    cout << "Simple result: " << simple->doTask() << endl;

    Component *tree = new Composite();
    Component *branch = new Composite();

    Component *leaf1 = new Leaf();
    Component *leaf2 = new Leaf();
    Component *leaf3 = new Leaf();

    branch->add(leaf1);
    branch->add(leaf2);

    Component *branch2 = new Composite();
    branch2->add(leaf3);

    tree->add(branch);
    tree->add(branch2);

    cout << "Tree result: " << tree->doTask() << endl;
    tree->add(simple);
    cout << "Tree added simple result: " << tree->doTask() << endl;

    delete simple;
    delete tree;
    delete branch;
    delete branch2;
    delete leaf1;
    delete leaf2;
    delete leaf3;
}

int main(void)
{
    clientCode();
    return 0;
}