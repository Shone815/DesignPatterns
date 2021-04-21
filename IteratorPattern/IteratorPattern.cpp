#include <iostream>
#include <vector>
using namespace std;

/**
 * 目的: 让你遍历一个集合的元素而不暴露它的底层表示(列表，堆栈，树，等等)。
 * c++有自己的迭代器实现，它与标准库定义的不同泛型容器一起工作。
 */
template <typename T, typename U>
class Iterator
{
public:
    typedef typename vector<T>::iterator iter_type;

    Iterator(U *p_data, bool reverse = false) : m_p_data(p_data)
    {
        m_it = m_p_data->m_data.begin();
    }

    void first()
    {
        m_it = m_p_data->m_data.begin();
    }

    void next()
    {
        m_it++;
    }

    bool isDone()
    {
        return (m_it == m_p_data->m_data.end());
    }

    iter_type current()
    {
        return m_it;
    }

private:
    U *m_p_data;
    iter_type m_it;
};

/**
 * 泛型集合/容器提供一个或几个方法来检索新的迭代器实例，与集合类兼容。
 */
template <class T>
class Container
{
    friend class Iterator<T, Container>;

public:
    void add(T t)
    {
        m_data.push_back(t);
    }

    Iterator<T, Container> *createContainer()
    {
        return new Iterator<T, Container>(this);
    }

private:
    vector<T> m_data;
};

class Data
{
public:
    Data(int a = 0) : m_data(a) {}
    void setData(int a)
    {
        m_data = a;
    }
    int data()
    {
        return m_data;
    }

private:
    int m_data;
};

void clientCode()
{
    Container<int> cont;
    for (int i = 0; i < 10; i++)
    {
        cont.add(i);
    }

    Iterator<int, Container<int>> *it = cont.createContainer();
    for (it->first(); !it->isDone(); it->next())
    {
        cout << *it->current() << endl;
    }

    Container<Data> cont2;
    Data a(100), b(200), c(3000);
    cont2.add(a);
    cont2.add(b);
    cont2.add(c);

    Iterator<Data, Container<Data>> *it2 = cont2.createContainer();
    for (it2->first(); !it2->isDone(); it2->next())
    {
        cout << it2->current()->data() << endl;
    }

    delete it, it2;
}

int main(void)
{
    clientCode();
    return 0;
}