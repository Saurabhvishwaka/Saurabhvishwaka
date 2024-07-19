#include<iostream>
#include<forward_list>
using namespace std;
class myComparator
{
public:
bool operator()(int a,int b)
{
cout<<"operator got called  with"<<" " <<a<<","<<b<<endl;
return a>b;
}
};
int main()
{
forward_list<int> list;
forward_list<int>::iterator i;
i=list.before_begin();
i=list.insert_after(i,90);
i=list.insert_after(i,0);
i=list.insert_after(i,190);
i=list.insert_after(i,-120);
i=list.insert_after(i,-90);
i=list.insert_after(i,20);
i=list.insert_after(i,9120);
myComparator m;
list.sort(m);
for(i=list.begin();i!=list.end();++i)
{
cout<<*i<<endl;
}
return 0;
}