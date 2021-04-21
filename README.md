

# 一、面向对象八大设计原则
 ## 1. 依赖倒置原则（DIP，Dependence Inversion Principle） -> 隔离变化
> ### (1) 高层模块(稳定)不应该依赖于低层模块(变化)，二者都应该依赖于抽象(稳定) 。
> ### (2) 抽象(稳定)不应该依赖于实现细节(变化) ，实现细节应该依赖于抽象(稳定)。
 ## 2. 开放封闭原则（OCP，Open Closed Principle）
> ### (1) 对扩展开放，对更改关闭。
> ### (2) 类模块应该是可扩展的，但是不可修改。
 ## 3. 单一职责原则（SRP，Single Responsibility Principle）
> ### (1) 一个类应该仅有一个引起它变化的原因。
> ### (2) 变化的方向隐含着类的责任。
 ## 4. Liskov替换原则（LSP，Liskov Substitution Principle）
> ### (1) 子类必须能够替换它们的基类（is-a）。
> ### (2) 继承表达类型抽象。
 ## 5. 接口隔离原则（ISP，Interface Segregation Principle）
> ### (1) 不应该强迫客户程序依赖它们不用的方法。（不要无节制使用public）
> ### (2) 接口应该小而完备
 ## 6. 优先使用对象组合，而不是继承（Composite Reuse Principle）
> ### (1) 类继承通常为“白箱复用”，对象组合通常为“黑箱复用”。
> ### (2) 继承在某种程度上破坏了封装性，子类父类耦合度高。
> ### (3) 而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低。
 ## 7. 封装变化点
> ### (1) 使用封装来创建对象之间的分界层，让设计者可以在分界层的一侧进行修改，而不会对另一侧产生不良的影响，从而实现层次间的松耦合。
 ## 8. 针对接口编程，而不是针对实现编程
> ### (1) 不将变量类型声明为某个特定的具体类，而是声明为某个接口。
> ### (2) 客户程序无需获知对象的具体类型，只需要知道对象所具有的接口。
> ### (3) 减少系统中各部分的依赖关系，从而实现“高内聚、松耦合”的类型设计方案。

&emsp;
# 二、C++23种设计模式 - 从目的来看
## 1. 创建型模式（5种）：将对象的部分创建工作延迟到子类或者其他对象，从而应对需求变化为对象创建时具体类型实现引来的冲击。<font color=red>（抽单 建工原）</font>
    (1) Factory Method工厂方法模式
<div align=center><img src=".\pic\FactoryMethod.png"></div>

    (2) Abstract Factory抽象工厂模式
<div align=center><img src=".\pic\AbstractFactory.png"></div>

    (3) Singleton单例模式
<div align=center><img src=".\pic\SingletonPattern.png"></div>

    (4) Builder建造者模式
<div align=center><img src=".\pic\BuilderPattern.png"></div>

    (5) Prototype原型模式
<div align=center><img src=".\pic\PrototypePattern.png"></div>

## 2. 结构型模式（7种）：通过类继承或者对象组合获得更灵活的结构，从而应对需求变化为对象的结构带来的冲击。<font color=red>（适代组外装享桥）</font>
    (1) Adapter适配器模式
<div align=center><img src=".\pic\AdapterPattern.png"></div>

    (2) Decorator装饰器模式
<div align=center><img src=".\pic\DecoratorPattern_2.png"></div>
<div align=center><img src=".\pic\DecoratorPattern.png"></div>

    (3) Proxy代理模式
<div align=center><img src=".\pic\ProxyPattern.png"></div>

    (4) Facade外观模式
<div align=center><img src=".\pic\FacadePattern.png"></div>

    (5) Bridge桥接模式
<div align=center><img src=".\pic\BridgePattern.png"></div>

    (6) Composite组合模式
<div align=center><img src=".\pic\CompositePattern.png"></div>

    (7) Flyweight享元模式
<div align=center><img src=".\pic\FlyweightPattern.png"></div>

## 3. 行为型模式（11种）：通过类继承或者对象组合来划分类与对象间的职责，从而应对需求变化为多个交互的对象带来的冲击。<font color=red>（责备中模访，状观迭 解命策）</font>
    (1) Strategy策略模式
<div align=center><img src=".\pic\Strategy.png"></div>

    (2) Template Method模板方法模式
<div align=center><img src=".\pic\TemplateMethod.png"></div>

    (3) Observer/Event观察者模式
<div align=center><img src=".\pic\Observer.png"></div>

    (4) Iterator迭代子模式
<div align=center><img src=".\pic\IteratorPattern.png"></div>

    (5) Chain of Resposibility责任链模式
<div align=center><img src=".\pic\ResponsibilityPattern.png"></div>

    (6) Command命令模式
<div align=center><img src=".\pic\CommandPattern.png"></div>

    (7) Memento备忘录模式
<div align=center><img src=".\pic\MementoPattern.png"></div>

    (8) State状态模式
<div align=center><img src=".\pic\StatePattern.png"></div>

    (9) Visitor访问者模式
<div align=center><img src=".\pic\VisitorPattern.png"></div>

    (10) Mediator中介者模式
<div align=center><img src=".\pic\MediatorPattern.png"></div>

    (11) Interpreter解释器模式
<div align=center><img src=".\pic\InterpreterPattern.gif"></div>
&emsp;
<div align=center><img src=".\pic\relationships.jpg"></div>
&emsp;

# 三、C++23种设计模式 - 从范围来看
&emsp;

# 四、C++23种设计模式 - 从封装变化角度来看
## 1. 组件协作
    (1) Template Method模板方法模式
    (2) Observer/Event观察者模式
    (3) Strategy策略模式
## 2. 单一职责
    (1) Decorator装饰器模式
    (2) Bridge桥接模式
## 3. 对象创建
    (1) Factory Method工厂方法模式
    (2) Abstract Factory抽象工厂模式
    (3) Prototype原型模式
    (4) Builder建造者模式
## 4. 对象性能
    (1) Singleton单例模式
    (2) Flyweight享元模式
## 5. 接口隔离
    (1) Facade外观模式
    (2) Proxy代理模式
    (3) Mediator中介者模式
    (4) Adapter适配器模式
## 6. 状态变化
    (1) Memento备忘录模式
    (2) State状态模式
## 7. 数据结构
    (1) Composite组合模式
    (2) Iterator迭代子模式
    (3) Chain of Resposibility责任链模式
## 8. 行为变化
    (1) Command命令模式
    (2) Visitor访问者模式
## 9. 领域问题
    (1)Interpreter解释器模式
&emsp;
