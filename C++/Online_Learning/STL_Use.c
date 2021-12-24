clips-187   vector存放自定义容器
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


clips-188  vector容器嵌套
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



clips-189   string容器，构造函数、
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


clips-190   string赋值操作


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




clips-191  string 拼接
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


clips-192   string查找和替换
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





clips-193   字符串比较
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


clips-194   字符存取
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



clips-195   string插入和删除
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



clips-196   string 字串获取
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

clips-197    vector 构造函数



