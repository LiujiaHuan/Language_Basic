# 是什么？

 __thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。

__thread变量**每一个线程有一份独立实体**，各个线程的值互不干扰

# 为什么？

可以用来修饰那些带有全局性且值可能变，但是又**不值得用全局变量保护的变量**。

# 来自于:Thread Local Storage（TLS）

https://stackoverflow.com/questions/35692188/what-is-thread-local-storage-why-we-need-it
