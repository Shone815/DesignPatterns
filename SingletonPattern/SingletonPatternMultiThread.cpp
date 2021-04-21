#include <iostream>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds
#include <mutex>
#include <atomic>
using namespace std;

/**
 * Singleton类定义了`getInstance`方法，作为构造函数的替代方法，
 * 允许客户端一次又一次地访问该类的同一个实例。
 * 最复杂的地方就是线程安全问题，网上有好多讨论，也有相关论文。
 */
class Singleton
{
public:
    /**
     * Singleton 不允许有拷贝构造
     */
    Singleton(Singleton &) = delete;

    /**
     * Singleton 不允许有赋值操作
     */
    void operator=(const Singleton &) = delete;

    /**
     * 这是控制对Singleton实例访问的静态方法。在第一次运行时，它创建了一个singleton对象
     * 并将其放入静态字段中。在后续运行时，它返回存储在静态字段中的客户端现有对象。
     */
    static Singleton *getInstance(const string &);

    /**
     * 最后，任何Singleton都应该定义一些业务逻辑，这些逻辑可以在其实例上执行。
     */
    void process() const
    {
        cout << "m_singleton->m_value: " << m_value << endl;
    }

    string getValue() const
    {
        return m_value;
    }

protected:
    /**
     * Singleton的构造函数应该始终是私有的，以防止直接使用'new'操作符进行构造调用。
     */
    Singleton(const string value) : m_value(value) {}
    ~Singleton() {}

    static std::atomic<Singleton *> m_singleton;
    string m_value;

private:
    static std::mutex m_mutex;
};

// 初始化
std::atomic<Singleton *> Singleton::m_singleton;
std::mutex Singleton::m_mutex;
// 静态方法必须在类外部定义
Singleton *Singleton::getInstance(const string &value)
{
    Singleton *tmp = m_singleton.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire); // 获取内存fence
    if (tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_singleton.load(std::memory_order_relaxed);
        if (tmp == nullptr)
        {
            // 加锁到内部，而不用每次都先加锁再判断，避免锁占用后期资源。
            tmp = new Singleton(value);
            std::atomic_thread_fence(std::memory_order_release); // 释放内存fence
            m_singleton.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}

void threadFoo()
{
    // 下面的代码模拟缓慢的初始化，可以更好的体现两个进程之间的交叉关系
    // 单个进程sleep 1000ms，其他进程不受影响。
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::getInstance("FOO");
    cout << singleton->getValue() << endl;
    singleton->process();
}

void threadBar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::getInstance("BAR");
    cout << singleton->getValue() << endl;
    singleton->process();
}

void clientCode()
{
    // cout << "Here is an example of single thread." << endl;
    // Singleton *singleton = Singleton::getInstance("Example");
    // cout << singleton->getValue() << endl;
    // singleton->process();

    /**
     * 注意：一下代码可能发生不按顺序的输出，因为t1和t2是并行运行的。
     * 可能输出都是FOO，也可能都是BAR。
     */
    cout << "Here is an example of safe multi threads." << endl;
    std::thread t1(threadFoo);
    std::thread t2(threadBar);
    t1.join();
    t2.join();
}

int main(void)
{
    cout << "start" << endl;
    clientCode();
    return 0;
}