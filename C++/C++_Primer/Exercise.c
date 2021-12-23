Ex7.11_____________________________________________________________________________________
struct Sales_data{
	//新增的构造函数
	Sales_data() = default;  								 //用默认构造器
	Sales_data(const std::string& s) :bookNo(s){}			//隐式构造另外两个参数
	Sales_data(const std::string& s, unsigned n, double p)	//显式构造所有参数
		:bookNo(s), units_sold(n), revenue( n * p ){}
	Sales_data(std::istream& is);							//读取交易信息的构造函数
	//以前已经有的成员
	std::string isbn() const{return bookNo};
	Sales_data& combine(const Sales_data&);

	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
}
//非成员函数暂时不写
//调用构造函数
int main(){
	Sales_data item1;//利用默认构造函数
	printf(std::cout,item1) << std::endl;

	Sales_data item2("0-xxx-xxx-xx")//利用了一个参数的构造函数
	printf(std::cout,item1) << std::endl;

	Sales_data item4("0-xxx-xxx-x",10,10.00);//利用了三个参数的构造函数
	printf(std::cout,item1) << std::endl;
}



Ex9.4_____________________________________________________________________________________
bool find(vector<int>::iterator start,vector<int>::iterator end,int val){
	for(auto iter = start;iter != end; ++iter){
		if(*iter == val){
			return true;
		}
	}
	return false;
}



Ex9.5_____________________________________________________________________________________
vector<int>::iterator find(vector<int>::iterator start,vector<int>::iterator end,int val){
	for(auto iter = start;iter != end; ++iter){
		if(*iter == val){
			return iter;
		}bool find(vector<int>::iterator start,vector<int>::iterator end,int val){
	for(auto iter = start;iter != end; ++iter){
		if(*iter == val){
			return true;
		}
	}
	return false;
}
	}
	return end;
}
Ex9.11_____________________________________________________________________________________
vector<int> vec;//0
vector<int> vec(10);//0
vector<int> vec(10,1)//10 个 1
vector<int> vec{1,2,3,4,5}//1,2,3,4,5
vector<int>	vec(其他的vector)//复制过来
vector<int> vec(othervec.begin(),othervec.end())//两个迭代器之间的内容

Ex9.12_____________________________________________________________________________________
1.容器作为参数
默认"假定两个容器的容器类型和元素类型相同。"
接收到的所有元素复制到新容器中：
list< int > numbers = { 1 , 2 , 3 , 4 , 5 };
list< int > numbers2（数字）；        //好的， numbers2 与 numbers 具有相同的元素
vector< int > numbers3 (numbers);      //错误：没有匹配的调用函数... 
list< double > numbers4 (numbers);     //错误：没有匹配的调用函数...
2.迭代器作为参数
"不需要容器类型相同。"
可以不同,只要内部的逻辑可以转换(如本身可以互相强制类型转换)
它还将仅复制由接收到的迭代器分隔的对象。
list< int > numbers = { 1 , 2 , 3 , 4 , 5 };
list< int > numbers2 (numbers.begin(), numbers.end);        //好的， numbers2 与 numbers 具有相同的元素
vector< int > numbers3 (numbers.begin(), --numbers.end());  //好的， numbers3 是 {1, 2, 3, 4} 
list< double > numbers4 (++numbers.beg(), --numbers.end());        //好的， numbers4 是 {2, 3, 4} 
forward_list< float > numbers5 (numbers.begin(), numbers.end());   //好的，number5 是 {1, 2, 3, 4, 5}

Ex9.13_____________________________________________________________________________________
#include<bits/stdc++.h>
using std::list;
using std::vector;
using std::cout;
using std::endl;

int main()
{
    list<int> ilst(5, 4);//初始化list<int>容器
    vector<int> ivc(5, 5);//初始化vector<int>容器

    //! from list<int> to vector<double>
    vector<double> dvc(ilst.begin(), ilst.end());
    for (auto i : ilst) cout << i;
    cout << endl;
    for (auto t : dvc) cout << t;
    cout << endl;

    //! from vector<int> to vector<double>
    vector<double> dvc2(ivc.begin(), ivc.end());
    for (auto i : ivc) cout << i;
    cout << endl;
    for (auto t : dvc2) cout << t;

    return 0; 
}



Ex9.14_____________________________________________________________________________________
/*
将一个list中的char*指针(指向c风格字符串)的元素赋值给vector的string
*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(){
	std::list<const char*> l{"AAAAA","BBBBBB","CCCCCCCC"};
	std::vector<std::string> v;
	v.assign(l.cbegin(),l.cend());//目的已达到

	//验证
	for(const auto& ch : v) std::cout<< ch <<std::endl;
	//这个for循环很重要,就是输出v所有的内容
	//const auto& ch:v;就是便利读取v中的内容,而且是之读,不拷贝,不修改;	
	return 0; 
}
//知识点:1.容器赋值,替换 2.for中的auto


Ex9.15_____________________________________________________________________________________
/*判定两个vector<int> 是否相等*/
#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<int> vec1{1,2,3,4,5};
	vector<int> vec2{1,2,3,4,5};
	vector<int> vec3{1,2,3,4};

	cout<<boolalpha<<(vec1 == vec2) <<endl;
	//当使用boolalpha后，以后的bool类型结果都将以true或false形式输出，
	//除非使用noboolalpha取消 boolalpha流的格式标志。
	cout<<boolalpha<<(vec1 == vec3) << endl;

	return 0;
}
//知识点:1.容器-关系运算符,2.boolalpha处理函数



Ex9.16_____________________________________________________________________________________
/*重写9.15,比较list-int和vector-int中的元素*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(){
    vector<int> vec{1,2,3,4,5};
    list<int> l{1,2,3,4,5};
    cout<<boolalpha << (vector<int>(l.begin(),l.end()) == vec)<<endl;
    //(xxxxxxxxxxx)括号里面是比较的运算过程
    //因为比较运算符只对同类型适用,所以要准换成vector-int再比较
}
//知识点:1.容器-关系运算符
