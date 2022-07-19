## 观察者模式

观察者模式 (Observer Design Pattern) 也被称为发布订阅模式 (Publish Subscribe Design Pattern),
在 GoF 的 《设计模式》一书中，它的定义是这样的:

>Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

翻译成中文就是: 在对象之间定义一个一对多的依赖，当一个对象状态改变的时候，所有依赖的对象都会自动收到通知。

一般情况下，被依赖的对象叫作被观察者，依赖的对象叫作观察者。不过，在实际的项目开发中，这两种对象的称呼是比较灵活的，有各种不同的叫法，比如：Subject-Observer、Publisher-Subcriber、Producer-Consumer、EventEmitter-EventListener、Dispatcher-Listener。不管怎么称呼，只要应用场景符合刚刚给出的定义，都可以看作观察者模式。

总的来说，设计模式要做的事情就是解耦。创建型模式就是讲创建和使用代码解耦，结构型模式是将不同的功能代码解耦，行为型模式是将不同的行为代码解耦，具体到观察者模式，它是将观察者和被观察者解耦。借助设计模式，我们利用更好的代码结构，将一大坨代码拆分成指职责单一的小类，让其满足开闭原则、高内聚松耦合等特性，以此来控制和应对代码的复杂性，提高代码的可扩展性。