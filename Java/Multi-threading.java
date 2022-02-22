//-----------------------------RunnableDemo.java-----------------------------------------------------------------Runnable接口实现多线程----------------------
class RunnableDemo implements Runnable{
    private Thread t;
    private String threadName;

    RunnableDemo(String name){//构造器
        threadName = name;
        System.out.println("Created " + threadName);
    }

    public void run(){//调用链是start()--> JVM_StartThread --> thread_entry --> run()
        System.out.println("Running " + threadName);
        try {//异常捕获
            for (int i = 4; i > 0; i--) {
                System.out.println("Thread: " + threadName +","+ i);
                Thread.sleep(100);
            }
        }catch(InterruptedException e){
            System.out.println("Thread" + threadName + "interrupted");
        }
        System.out.println("Thread " + threadName + "exiting.");
    }

    public void start(){//要调用start(),而不是run()
        System.out.println("starting"+threadName);
        if(t == null){
            t = new Thread(this,threadName);//创建对象
            t.start();//启动
        }
    }
}

public class TestThread{
    public static void main(String args[]){
        RunnableDemo R1 = new RunnableDemo("Thread-1");//构造器传入变量
        R1.start();//创建+启动

        RunnableDemo R2 = new RunnableDemo("thread-2");
        R2.start();
    }
}
//注意，为什么没有显式调用run()  查资料显示，整个调用链是start() --> JVM_StartThread --> thread_entry --> run()
//详细分析   https://wuchengwei.blog.csdn.net/article/details/103428493
