/*———————————————————————————————————————————————//
usr:LiuJiahuan
time:2021-12-26
Editon:beta
goal:练习stl使用
issue:只限2个以上的评委(采取排除最高和最低)
//————————————————————————————————————————————————*/
#include <iostream>         
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
using namespace std;
class Player{
public:
    Player(string name,int score){
        this->Name = name;
        this->Score = score;
    }
    string Name;
    int Score;
};

void setScore(vector<Player>&v,int judge){
    for(vector<Player>::iterator it = v.begin();it!=v.end();it++){
        //放入评委评分
        deque<int>d;
        for(int i = 0 ; i < judge; i++){
            int score;
            cout<<"请输入第"<<i+1<<"名评委的得分"<<endl;
            cin>>score;
            d.push_back(score);
        }
        //test打分
        cout<<it -> Name <<"打分"<<endl;
        for(deque<int>::iterator dit = d.begin();dit!=d.end();dit++){
            cout<<*dit<< ' ';
        }
        cout<<endl;
        
        //排序
        sort(d.begin(),d.end());
        d.pop_back();
        d.pop_front();
        //取平均分
        int sum = 0 ;
        for(deque<int>::iterator dit = d.begin();dit!=d.end();dit++){
            sum+=*dit;
        }
        int avg = sum/d.size();
        it -> Score = avg;
    }
}
void creatPlayer(vector<Player>&v,int player){//只有以引用方式传入才能改实参
    for(int i = 0 ; i < player ; i++){
        string name;
        cout<<"请输入第"<<i+1<<"名选手的名字："<<endl;
        cin>>name;
        int score = 0;
        Player p(name,score);
        //放入容器
        v.push_back(p);
    }

}
void showScore(vector<Player>&v){
    for(vector<Player>::iterator it = v.begin();it!=v.end();it++){
        cout<<(*it).Name<<"avg is ="<<(*it).Score<<endl;
    }
}
int main(){
    //pre:加入随机数种子
    //srand((size_t)time(NULL));

    int judge,player;
    cout<<"请输入一共多少名裁判"<<endl;
    cin>>judge;
    cout<<"请输入一共多少名选手"<<endl;
    cin>>player;

    //1.创建选手
    vector<Player>v;
    creatPlayer(v,player);
    /*创建测试
    for(vector<Player>::iterator it = v.begin();it!=v.end();it++){
        cout<<(*it).Name<<" "<<(*it).Score<<endl;
    }
    */

    //2.打分
    setScore(v,judge);

    //3.显示最后得分
    showScore(v);
}
