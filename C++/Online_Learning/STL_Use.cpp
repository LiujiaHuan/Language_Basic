clips-187   vector存放自定义容器__________________________________________________________________________________________________________________________________
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person{
public:
    Person(string name,int age){
        this->Name = name;
        this->Age = age;
    }
    string Name;
    int Age;
};
int main() {
    vector<Person>v;
    Person p1("小刘",18);
    Person p2("小周",18);
    Person p3("小张",18);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    for(vector<Person>::iterator it = v.begin();it!=v.end();it++){
        //这里的it是指针类型
        cout<<it->Name<<endl;//写法一
        cout<<(*it)->Name<<endl//写法二，先解引用然后再直接对对象的实体属性进行访问
    }

}


clips-188  vector容器嵌套__________________________________________________________________________________________________________________________________
#include <iostream>
#include <vector>
using namespace std;

int main(){
    //容器嵌套第一个尖括号后要留空格，这是c++98规定
    vector<vector<int> > v;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for(int i = 0 ;i < 4; i++){
        v1.push_back(i);
        v2.push_back(i+1);
        v3.push_back(i+2);
        v4.push_back(i+3);
    }

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for(vector<vector<int> >::iterator it = v.begin();it!=v.end();it++){
        //此处*it是子vector本身，it是子vctor的地址
        for(vector<int>::iterator vit = (*it).begin();vit!=(*it).end();vit++){
            cout<<*vit;
        }
        cout<<endl;
    }
}



clips-189   string容器，构造函数__________________________________________________________________________________________________________________________________
/*string本质是个类，封装了很多成员方法，封装了char*管理字符串，不用管理内存分配

构造函数
string()
string(const string& str) 拷贝构造
...etc
*/
#include <iostream>
#include <string>
using namespace std;
int main(){
    //默认构造
    string s1;
    //使用字符串初始化
    const char * str = "helllo world";
    string s2(str);
    //拷贝构造
    string s3(s2);
    //n个x
    string s4(10,'a');

}


clips-190   string赋值操作__________________________________________________________________________________________________________________________________


#include <iostream>
#include <string>
using namespace std;
int main(){
    string str1;
    //等号赋值
    str1 = "hello world";
    //类拷贝构造
    string str2
    str2  =  str1;
    //成员函数构造assign
    string str3;
    str3.assign("hello world");//func1

    string str5;
    str5.assign("hello world",5);//func2 截取前n个

    string str6;
    str6.assign(str5);//func3 类拷贝构造

    string str7;
    str6.assign(10,‘w’);//func4  几个x
}//一般用等号就好了




clips-191  string 拼接__________________________________________________________________________________________________________________________________
/*
    1.重载+=操作符
    2.append成员函数
*/
#include <iostream>
#include <iostream>
using namespace std;
int main(){
    //string + char+字符串
    string str1 = "i";
    str1+="love games";
    str1+=':';
    cout <<str1;
    //双string
    string str2 = "LOL DNF";
    str1+=str2;
    //append拼接
    string str3 = "I";
    str3.append("love");
    cout << str3<<endl;
    //append截取拼接
    str3.append("game abcd ",4);
    //append拼接另一个string
    str3.append(str2);//str3.append(str2,0,3),只截取从0开始往后三个
    cout<<str3<<endl;
}//重载版本很多，不用记太多


clips-192   string查找和替换__________________________________________________________________________________________________________________________________
#include <iostream>
#include <string>
using namespace std;
/*
    find
    rfind
    replace
*/
/*
    int find(const string& str, int pos = 0) const;
    //查找str第一次出现位置,从pos开始查找
    int find(const char* s, int pos = 0) const;
    //查找s第一次出现位置,从pos开始查找
    int find( const char* s, int pos， int n) const;
    ll从pos位置查找s的前n个字符第一次位置
    int find(const char c, int pos = 0) const;
    /查找字符c第一次出现位置
    int rfind(const string& str, int pos = npos ) const;
    //查找str最后一次位置,从pos开始查找//查找s最后一次出现位置,从pos开始查找
    int rfind(const char* s, int pos = npos) const;
    ll从pos查找s的前n个字符最后一次位置
    int rfind(const char* s, int pos, int n) const;
    int rfind(const char c, int pos = e) const;
    //查找字符c最后一次出现位置
    string& replace(int pos, int n, const string& str);
    //替换从pos开始n个字符为字符串str//替换从pos开始的n个字符为字符串s
    string& replace(int pos, int n,const char* s ) ;
*/
int main(){
    //1.查找
    string str1 = "abcdefg";
    int pos = str1.find("de");//从0开始给，返回下标，没有返回-1
    cout << "it is here"<<pos<<endl;
    /* if(pos = -1){
         ...
        }*/
    pos = str1.rfind("de");
    //rfind从右往左查找


    //2.替换
    string str1 = "abcdefg";
    str1.replace(1,3,"1111");//从第1个位置替换3个原内容为1111
}





clips-193   字符串比较__________________________________________________________________________________________________________________________________
//compare函数，挨个比较ascii
#include <iostream>
using namespace std;
#include <string>
int main(){
    string str1 = "hello";
    string str2 = "hello";
    if(str1.compare(str2)==0){
        //相等
        cout<<1<<endl;
    }
    else if(str1.compare(str2)>0){
        //str1第一个不相同的ascii大于str2的
    }    
    else if(str1.compare(str2)<0){
        //str1第一个不相同的ascii小于str2的
    }
}


clips-194   字符存取__________________________________________________________________________________________________________________________________
/*
    1.[]
    2.str.at()
*/
#include <iostream>
using namespace std;
#include <string>
int main(){
    string str1 = "hello";
    //1.通过中括号访问单个字符
    for(int i = 0 ; i < str1.size();i++){
        cout << str[i]<<' '; 
    }
    cout<<endl;
    //2.通过at方式访问单个字符    
    for(int i = 0 ; i < str1.size();i++){
        cout << str.at(i)<<' '; 
    }
    cout<< endl;
    //3.修改
    //略
}



clips-195   string插入和删除__________________________________________________________________________________________________________________________________
/*
    insert
    erase
*/
#include <iostream>
using namespace std;
#include <string>
int main(){
    string str1 = "hello";
    //1.插入
    str1.insert(1,"111")//从下标1插入一个111字符串  
    //2.删除
    str1.erase(1,3)//从第一个位置删除三个
}



clips-196   string 字串获取__________________________________________________________________________________________________________________________________
/*
  substr  
*/
#include <iostream>
using namespace std;
#include <string>
int main(){
    string str1 = "abcdef";
    string substr = str1.substr(1,3);//截取下标1-3的串   
    //小实例
    string email = "cheayuki13@gamil.com";
    int pos = email.find('@');
    string usrName = email.substr(0,pos);
    cout << usrName << endl;
}

clips-197    vector 构造函数__________________________________________________________________________________________________________________________________
/*
    动态扩容，找更大的空间整体cp过去

    前端封闭，尾部插入

    迭代器begin()第一个元素
    end()最后一个元素
    rbegin()最后一个内容
    rend()第一个内容之前的
    迭代器支持随机访问
*/

    
#include <iostream>
using namespace std;
#include <vector>
void printVector(vector<int>& v){
    for(vector<int>::iterator it = v.begin();it!=v.end();it++){
        cout<<*it<<endl;
    }
}
int main(){
    //构造函数
    //默认构造，无参构造
    vector<int> v1;
    for(int i = 0 ; i < 10 ; i++){
        v1.push_back(i);
    }
    printVector(v1);
    //区间构造
    vector<int> v2(v1.begin(),v1.end());

    //n个xx构造
    vector<int> v3(10,100);
    printVector(v3);

    //拷贝构造
    vector<int> v4(v3);
    printVector(v4);

}





clips-198   vector 赋值操作__________________________________________________________________________________________________________________________________
/*
    1.等号赋值
    2.assign成员函数
*/
#include <iostream>
using namespace std;
#include <vector>
int main(){
    vector<int> v1;
    for(int i = 0 ; i < 10 ;i++){
        v1.push_back(i);
    }   
    printVector(v1);

    //等号赋值
    vector<int> v2;
    v2 = v1;
    //assign成员函数
    vector<int> v3;
    v3.assign(v1.begin(),v1.end());
    printVector(v3);

    std::vector<int> v4;
    v4.assign(10,100);
    printVector(v4);
}



clips-199   vector容量和大小__________________________________________________________________________________________________________________________________
/*
    empty()
    capacity()
    size()
    resize()重载版本，可非0填充
*/
#include <iostream>
using namespace std;
#include <vector>
int main(){
    vector<int> v1;
    for(int i =  0 ;i < 10 ; i++){
        v1.push_back(i);
    }
    printVector(v1);
    //empty(),size()
    if(v1.empty())//true则为空
    {
        ...
    }
    else{
        cout<<"vector all capacity is"<<v1.capacity()<<endl;
        cout<<"v1 ' s size is"<<v1.size();
    }
    //resize()
    v1.resize(15);//如果比原来长默认0填充,如果比原来短超出部分被删掉
    printVector(v1);
    v1.resize(15,100);//重载版本改变填充默认值

}



clips-200   vector 插入和删除__________________________________________________________________________________________________________________________________
/*  
    push_back
    pop_back
    insert
    erase
    clear
*/
#include <iostream>
using namespace std;
#include <vector>
int main(){
    vector<int> v1;
    //尾插
    v1.push_back(10);    
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    //尾删
    v1.pop_back();
    //插入
    v1.insert(v1.begin(),100);//给头部位置插入100

    v1.insert(v1.begin(),2,100)//重载，插n个数据在指定位置
    //删除
    v1.erase(v1.begin());
    v1.erase(v1.begin(),v1.end());//重载，给定范围
}



clips-201      vector数据存取__________________________________________________________________________________________________________________________________
#include <iostream>
using namespace std;
#include <vector>
/*
    at
    []
    front
    back
*/
int main(){
    vector<int> v1;
    v1.push_back(1);    
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(1);
    //[]访问
    cout<<v1[2]<<endl;
    //成员函数at
    cout<<v1.at(1)<<endl;
    //最后一个元素,第一个元素
    cout<<v1.back()<<" "<<v1.front();

}

clips-202   vector 互换容器__________________________________________________________________________________________________________________________________
#include <iostream>
using namespace std;
#include <vector>
int main(){
    vector<int> v1;
    for(int i = 0 ; i < 10 ; i++){
        v1.push_back(i);
    }
    vector<int> v2;
    for (int i = 10; i > 0; i--)
    {
            v2.push_back(i);
    }  
    //swap
    v1.swap(v2);
    //用途        巧用swap收缩多余的容量
    vector<int> v2;
    for(int i = 0 ; i < 100000;i++){
        v2.push_back(i);
    }
    v2.resize(3);
    vector<int>(v2).swap(v2)
/*分析
    vector<int>(v2)是匿名对象，利用v2进行初始化
    .swap()后匿名对象指向原先占用很多空间的内存，
    当前行执行完，系统发现是个匿名对象就自动回收
*/
}

clips-203   vector 预留空间__________________________________________________________________________________________________________________________________
/*
    reserver    减少vector在动态扩展容量时扩展的次数，
    但是预留空间没有初始化不可访问
*/
#include <iostream>
using namespace std;
#include <vector>
int main(){
    //查看重新开辟了多少次内存
    vector<int> v1;
    int num = 0;//计数器
    int *p = NULL;//利用每次重开地址都会不同的特性
    for(int i = 0 ; i < 100000;i++){
        v1.push_back(i);
        if(p!=&v[0]){
            p = &v[0];
            num++;
        }
    }
    //用reserve
    v1.reserve(100000)
    int num = 0;//计数器
    int *p = NULL;//利用每次重开地址都会不同的特性
    for(int i = 0 ; i < 100000;i++){
        v1.push_back(i);
        if(p!=&v[0]){
            p = &v[0];
            num++;
        }
    }
}



clips-204   deque容器__________________________________________________________________________________________________________________________________
/*
    双端数组，可对头端进行插入删除

    而对于vector，头部插入数据会导致全部移动
    
    内部工作原理：
        deque内部有个中控器，维护每段缓冲区的内容，缓
        冲区中放着真实数据

        中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间
        这样也就导致访问元素不是很快了

*/
#include <iostream>
using namespace std;
#include <deque>
void printDeque(const deque<int>& d){//创建只读迭代器
    for(deque<int>::const_iterator it = d.begin();it != d.end();it++){
        cout<<*it<<' ';
    }
    //只读迭代器必须要const_iterator
}
int main(){
    //构造函数
    deque<int>d1;
    for(int i = 0 ; i < 10 ; i++){
        d1.push_back(i);
    }
    printDeque(d1);

    //区间构造
    deque<int>d2(d1.begin(),d1.end());

    //n个x
    deque<int>d3(10,100);

    //拷贝构造
    deque<int>d4(d3);
}//构造方式基本与vector一样




clips-205   deque赋值--与vector基本一样，略；__________________________________________________________________________________________________________________________________



clips-206   deque大小操作__________________________________________________________________________________________________________________________________
/*
    empty
    size    ps没有获取容量
    resize 
    resize重载
*/
#include <iostream>
using namespace std;
#include <deque>
int main(){
    //大小操作
    deque<int> d1;
    for(int i = 0; i < 10 ; i++){
        d1.push_back(i);
    }
    printDeque(d1);
    if(d1.empty()){
        cout<<"empty";
    }
    else{
        cout<<"not empty"<<endl;
        cout<<d1.size()<<endl;
    }
    d1.resize(15);//大了缺省0填充,断了删
    printDeque(d1);
    //重载版本略，指定用谁填充(15，1)
}



clips-207   deque删除__________________________________________________________________________________________________________________________________
/*
    pushback
    pushfront
    popback
    popfront

    insert、
    clear
    erase
*/
#include <iostream>
using namespace std;
#include <deque>
int main(){
    //两端
    deque<int> d1;//插
    d1.push_back(10);
    d1.push_back(20);

    d1.push_front(10);
    d1.push_front(10);//200 100 10 20
                    //删
    d1.pop_back();//200 100 10
    d1.pop_front();//100 10
    //指定位置
    deque<int> d2;
    d2.push_back(10);
    d2.push_back(20);
    d2.push_back(30);
    d2.push_back(40);//10 20 30 40

    d2.insert(d2.begin(),1000);//1000 10 20 30 40
    d2.insert(d2.begin,2,10000);//10000 10000 1000 10 20 30 40
    //指定区间
    deque<int> d2;
    d2.push_back(1);
    d2.push_back(2);
    d2.push_back(3);
    d1.insert(d1.begin(),d2.begin(),d2.end());//在d1开头插入d2的区间
    //删除
    deque<int>::iterator it = d1.begin();//指定
    it++;
    d1.erase(it);

    //区间删除
    d1.clear()  or  d1.erase(d1.begin(), d1.end());
}//注意，参数必须提供迭代器，直接给索引值时不行的！


clips-208      deque数据存取__________________________________________________________________________________________________________________________________
/*
跟vector一样
比它多一个front() 和back()
*/


clips-209   deque排序__________________________________________________________________________________________________________________________________
/*
sort(迭代器，迭代器)//默认升序，从小到大
算法头 #include <algorithm>
sort，只要能随机访问的迭代器都可以用sort如vector
*/
