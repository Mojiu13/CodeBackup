# threadpool
based on C++11 , a mini `threadpool` , accept variable number of parameters.
基于C++11的线程池,简洁且可以带任意多的参数

管理一个任务队列，一个线程队列，然后每次取一个任务分配给一个线程去做，循环往复。
有意思的是,限制只创建一个线程,这样就是一个完全的任务队列了。

线程池,可以提交变参函数或拉姆达表达式的匿名函数执行,可以获取执行返回值

*为了避嫌，先进行一下版权说明：代码是 me “写”的，但是思路来自 Internet， 特别是[这个线程池实现](https://github.com/progschj/ThreadPool)(基本 copy 了这个实现,加上[这位同学的实现](http://blog.csdn.net/zdarks/article/details/46994607)和解释，好东西值得 copy ! * 
**然后综合更改了下,更加简洁**
*)。*

#