#include <iostream>
#include <unordered_map>
using namespace std;

/**
 * 原型模式
 * 目的：可以通过不依赖于类型来copy已存在的对象
 */

enum PrototypeTypeNum
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype
{
protected:
    string m_prototypeName;
    float m_prototypeField;

public:
    Prototype() {}
    Prototype(string name) : m_prototypeName(name) {}

    virtual ~Prototype() {}
    virtual Prototype *clone() const = 0; // 注意这个clone方法是prototype所独有的
    virtual void method(float field)
    {
        this->m_prototypeField = field;
        cout << "Call method from " << m_prototypeName << " with field: " << m_prototypeField << endl;
    }
};

/**
 * ConcretePrototype1是Prototype的子类，并实现了Clone方法。
 * 在这个例子中，Prototype类的所有数据成员都在堆栈中。
 * 如果你在你的属性中有 String* m_name的指针，则需要实现复制构造函数来确保你有一个来自克隆方法的深层拷贝
 * 
 * 如果一个类拥有指针类型的成员变量，那么绝大部分情况下就需要深拷贝。
 * 只有这样，才能将指针指向的内容再复制出一份来，让原有对象和新生对象相互独立，彼此之间不受影响。
 * 如果类的成员变量没有指针，一般浅拷贝足以。
 */
class ConcretePrototype1 : public Prototype
{
private:
    float m_concretePrototypeField1;

public:
    ConcretePrototype1(string name, float field)
        : Prototype(name), m_concretePrototypeField1(field) {}
    /**
     * 请注意，克隆方法返回一个指向新的ConcretePrototype1副本的指针。
     * 因此，clientCode（调用克隆方法)有责任释放内存。
     * 如果你有智能指针的知识，你可能更喜欢在这里使用unique_pointer。
     */
    ConcretePrototype1 *clone() const override
    {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype
{
private:
    float m_concretePrototypeField2;

public:
    ConcretePrototype2(string name, float field)
        : Prototype(name), m_concretePrototypeField2(field) {}
    ConcretePrototype2 *clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

class ProtoFactory
{
private:
    std::unordered_map<PrototypeTypeNum, Prototype *, std::hash<int>> m_prototypes;

public:
    ProtoFactory()
    {
        m_prototypes[PrototypeTypeNum::PROTOTYPE_1] = new ConcretePrototype1("Prototype_1", 50.f);
        m_prototypes[PrototypeTypeNum::PROTOTYPE_2] = new ConcretePrototype2("Prototype_2", 52.f);
    }
    ~ProtoFactory()
    {
        delete m_prototypes[PrototypeTypeNum::PROTOTYPE_1];
        delete m_prototypes[PrototypeTypeNum::PROTOTYPE_2];
    }

    Prototype *createPrototype(PrototypeTypeNum type)
    {
        return m_prototypes[type]->clone();
    }
};

void clientCode()
{
    ProtoFactory *prototypeFac = new ProtoFactory();
    Prototype *prototype = prototypeFac->createPrototype(PrototypeTypeNum::PROTOTYPE_1);
    prototype->method(66.6);
    delete prototype;

    prototype = prototypeFac->createPrototype(PrototypeTypeNum::PROTOTYPE_2);
    prototype->method(77.7);
    delete prototype;
    delete prototypeFac;
}

int main(void)
{
    clientCode();
    return 0;
}