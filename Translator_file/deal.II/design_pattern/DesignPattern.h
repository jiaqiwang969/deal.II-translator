
/**
 * 参考：李建忠老师C++设计模式教程
 * 
 * # 基本原则 -> 面对变化，提高复用 -> 寻找并划分变化点，在合适的时机使用设计模式 -> 重构到模式
 * - 原则1: 依赖倒置 (DIP)
 *   -# 高层模块(稳定)不应该依赖于低层模块(变化)，二者都应该依赖 于抽象(稳定)。
 *   -# 抽象(稳定)不应该依赖于实现细节(变化)，实现细节应该依赖于 抽象(稳定)。
 * 
 * - 原则2: 开放封闭原则 (OCP) 
 *   -# 对扩展开放，对更改封闭。
 *   -# 类模块应该是可扩展的，但是不可修改。
 * 
 * - 原则3: 单一职责原则 (SRP)
 *   -# 一个类应该仅有一个引起它变化的原因。
 *   -# 变化的方向隐含着类的责任。
 * 
 * - 原则4: Liskov 替换原则 (LSP)
 *   -# 子类必须能够替换它们的基类(IS-A)。
 *   -# 继承表达类型抽象。
 * 
 * - 原则5: 接口隔离原则 (ISP)
 *   -# 不应该强迫客户程序依赖它们不用的方法。
 *   -# 接口应该小而完备。
 * 
 * - 原则6: 优先使用对象组合，而不是类继承
 *   -# 类继承通常为 "白箱复用" ，对象组合通常为 "黑箱复用" 。
 *   -# 继承在某种程度上破坏了封装性，子类父类耦合度高。
 *   -# 而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低。
 */

/**
 * - 原则7: 封装变化点
 *   -# 使用封装来创建对象之间的分界层，让设计者可以在分界层的一侧进行修改，而不会对另一侧产生不良的影响，从而实现层次间的松耦合。
 *   -# 使用封装来创建对象之间的分界层，让设计者可以在分界层的一侧进行修改，而不会对另一侧产生不良的影响，从而实现层次间的松耦合。
 */

/**
 * - 原则8: 针对接口编程，而不是针对实现编程
 *   -# 不将变量类型声明为某个特定的具体类，而是声明为某个接口。
 *   -# 客户程序无需获知对象的具体类型，只需要知道对象所具有的接口。
 *   -# 减少系统中各部分的依赖关系，从而实现 "高内聚、松耦合" 的类型设计方案。
 */

/**
 * # 分类
 * 
 * 从目的来看: 
 *   - 创建型 ( Creational ) 模式 ：将对象的部分创建工作延迟到子类或者其他对象，从市应对需求变化为对象仓建时具体类型实现引来的冲击。
 * 
 *   - 结构型 ( Structural ) 模式 ：通过类继承或者对象组合获得更灵活的结构，从而应对需求变化为对象的结构带来的冲击。
 * 
 *   - 行为型 ( Behavioral ) 模式 ：通过类继承或者对象组合来划分类与对象间的职责，从而应对需求变化为多个交互的对象带来的冲击。
 * 
 * 
 * 从范围来看 : 
 *   - 类模式：处理类与子类的静态关系。
 * 
 *   - 对象模式：处理对象的动态关系。
 */

/**
 * # 从封装变化角度对模式分类
 * - 组件协作: 晚期绑定
 * Template Method
 * Observer / Event
 * Strategy
 * 
 * - 对象性能:
 * Singleton
 * Flyweight
 * 
 * - 数据结构:
 * Composite 
 * Iterator 
 * Chain of Resposibility
 * 
 * - 单一职责:
 * Decorator
 * Bridge
 * 
 * - 接口隔离:
 * Facade 
 * Proxy 
 * Mediator
 * Adapter
 * 
 * - 行为变化:
 * Command 
 * Visitor
 * 
 * - 对象创建:
 * Factory 
 * Method 
 * Abstract 
 * Factory 
 * Prototype 
 * Builder
 * 
 * - 状态变化:
 * Memento
 * State
 * 
 * - 领域问题:
 * Interpreter
 */

/**
 * # 重构关键技法：
 * - 静态 -> 动态
 * - 早绑定 -> 晚绑定
 * - 继承 -> 组合
 * - 编译时依赖 -> 运行时依赖
 * - 紧耦合 -> 松耦合
 * 

namespace DesignPattern
{

    /**
     * 创建型 ( Creational ) 模式 ：
     * 将对象的部分创建工作延迟到子类或者其他对象，从市应对需求变化为对象仓建时具体类型实现引来的冲击。
     */
namespace CreationalDesign
{
}

/**

     *  
     */

namespace StructuralDesign
{
}

/**
     * 行为型 ( Behavioral ) 模式 ：
     * 通过类继承或者对象组合来划分类与对象间的职责，从而应对需求变化为多个交互的对象带来的冲击。
     */
namespace BehavioralDesign
{
}
}