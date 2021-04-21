#include <iostream>
#include <unordered_map>
using namespace std;

/**
 * 通过分离多个对象之间共享状态的公共部分，而不是简单地将所有数据保存在每个对象中，这样可以在可用RAM中容纳更多对象。
 * 针对内存需求较大的情况下的考虑。
 */
struct SharedState
{
    string m_brand;
    string m_model;
    string m_color;

    SharedState(const string brand, const string model, string color)
        : m_brand(brand), m_model(model), m_color(color)
    {
    }

    friend ostream &operator<<(ostream &os, const SharedState &ss)
    {
        return os << "[" << ss.m_brand << ", " << ss.m_model << ", " << ss.m_color << "]";
    }
};

struct UniqueState
{
    string m_owner;
    string m_plates;

    UniqueState(const string &owner, const string &plates)
        : m_owner(owner), m_plates(plates)
    {
    }

    friend ostream &operator<<(ostream &os, const UniqueState &us)
    {
        return cout << "[" << us.m_owner << ", " << us.m_plates << "]";
    }
};

/**
 * Flyweight存储属于多个实际业务实体的状态的公共部分(也称为内在状态)。
 * Flyweight通过它的方法参数接受状态的其余部分(外部状态，对每个实体都是唯一的)。
 */
class Flyweight
{
public:
    Flyweight(const SharedState *sharedState) : m_sharedState(new SharedState(*sharedState))
    {
    }
    Flyweight(const Flyweight &flyweight) : m_sharedState(new SharedState(*flyweight.m_sharedState))
    {
    }
    ~Flyweight()
    {
        delete m_sharedState;
    }

    SharedState *sharedState() const
    {
        return m_sharedState;
    }

    void doBusiness(const UniqueState &uniqueState) const
    {
        cout << "FlyweightL Displaying shared(" << *m_sharedState << ") and unique (" << uniqueState << ") state." << endl;
    }

private:
    SharedState *m_sharedState;
};

/**
 * FlyweightFactory创建和管理Flyweight对象。它确保Flyweight被正确地共享。
 * 当客户端请求flyweight时，FlyweightFactory要么返回一个现有的实例，要么创建一个新的(如果它还不存在的话)。
 */
class FlyweightFactory
{
public:
    FlyweightFactory(initializer_list<SharedState> sharedStates)
    {
        for (const SharedState &ss : sharedStates)
        {
            this->m_flyweights.insert(std::make_pair<string, Flyweight>(this->getKey(ss), Flyweight(&ss)));
        }
    }

    /**
     * 返回一个已经存在的Flyweight对象，如果没有这个对象，则创建新的对象并保存。
     */
    Flyweight getFleweight(const SharedState &sharedState)
    {
        string key = this->getKey(sharedState);
        if (this->m_flyweights.find(key) == this->m_flyweights.end())
        {
            cout << "FlyweightFactory: Can't find a flyweight, creating a new one.\n";
            this->m_flyweights.insert(std::make_pair(key, Flyweight(&sharedState)));
        }
        else
        {
            cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return this->m_flyweights.at(key);
    }

    void listFlyweights() const
    {
        size_t count = this->m_flyweights.size();
        cout << "FlyweightFactory: I have " << count << " flyweights.\n";
        for (std::pair<string, Flyweight> pair : this->m_flyweights)
        {
            cout << pair.first << "\n";
        }
    }

private:
    std::unordered_map<string, Flyweight> m_flyweights;
    string getKey(const SharedState &ss) const { return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color; }
};

void addCarToDatabase(FlyweightFactory &ff, const string plates, const string owner,
                      const string brand, const string model, const string color)
{
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.getFleweight({brand, model, color});
    flyweight.doBusiness({plates, owner});
}

void clientCode()
{
    FlyweightFactory *factory = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    factory->listFlyweights();

    addCarToDatabase(*factory, "SH888888", "Shone", "BMW", "M5", "red");
    addCarToDatabase(*factory, "SH888888", "James", "BMW", "X5", "red");

    factory->listFlyweights();

    delete factory;
}

int main(void)
{
    clientCode();
    return 0;
}