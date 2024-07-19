#include<iostream>
using namespace std;
#define bool int
#define true 1
#define True 1
#define TRUE 1
#define false 0
#define False 0
#define FALSE 0
class TMList
{
public:
virtual void add(int data,bool *success)=0;
virtual int get(int index,int *success)const=0;
virtual int getSize()const=0;
virtual void InsertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual void update(int index,int data,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
};
class TMArrayList : public TMList
{
int **ptr;
char allocationFlag;
int capacity;
int size;
bool addrow();
public:
TMArrayList();
TMArrayList(int buffersize);
TMArrayList(const TMArrayList &other);
TMArrayList & operator=(const TMArrayList &other);
void operator+=(const TMArrayList &other);
TMArrayList operator+(const TMArrayList &other);
void add(int data,bool *success);
int get(int index,int *success) const;
int getSize()const;
void InsertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
void update(int index,int data,int *success);
void removeAll();
void clear();
~TMArrayList();
};
bool TMArrayList::addrow()
{
if(capacity%100==0)
{
int numberofpointer;
numberofpointer=this->capacity/10;
int **tmp=new int *[numberofpointer+10];
if(tmp==NULL) return false;
for(int e=0;e<numberofpointer;e++)
tmp[e]=this->ptr[e];
delete [] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
this->ptr[i]=new int[10];
if(this->ptr[i]==NULL) return false;
this->capacity=this->capacity+10;
return true;
}
TMArrayList::TMArrayList()
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
}
TMArrayList::TMArrayList(int buffersize)
{

if(buffersize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointer;
rows=buffersize/10;
if(buffersize%10!=0) rows++;
numberOfPointer=rows+(10-(rows%10));
this->ptr=new int *[numberOfPointer];
for(int e=0;e<=rows;e++)
{
this->ptr[e]=new int [10];
}
this->capacity=rows*10;
this->size=0;
}
}
void TMArrayList::add(int data,bool *success)
{
if(success) *success=false;
if(this->size==this->capacity)
{
if(!addrow()) return;
}
int rowIndex,columnIndex;
rowIndex=this->size/10;
columnIndex=this->size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success) *success=true;
}
int TMArrayList::get(int index,int *success) const
{
if(success) *success=false;
if(index<0 || index>=size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
if(success) *success=true;
return this->ptr[rowIndex][columnIndex];
}
int TMArrayList::getSize()const
{
return this->size;
}
TMArrayList::TMArrayList(const TMArrayList &other)
{
this->allocationFlag=0;
int buffersize=other.size;
if(buffersize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberofpointers;
rows=buffersize/10;
if(buffersize%10!=0) rows++;
numberofpointers=rows+(10-(rows%10));
this->ptr=new int *[numberofpointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int [10];
}
this->capacity=rows*10;
this->size=0;
}
int succ;
for(int i=0;i<=other.size;i++)
{
this->add(other.get(i,&succ),&succ);
}
} 
TMArrayList & TMArrayList::operator=(const TMArrayList &other)
{
if(other.allocationFlag==0)
{
this->size=0;
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
this->size=other.size;
}
return *this;
}
void TMArrayList::operator+=(const TMArrayList &other)
{
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
TMArrayList TMArrayList::operator+(const TMArrayList &other)
{
TMArrayList k;
int succ;
for(int e=0;e<other.size;e++)
k.add(this->get(e,&succ),&succ);
for(int i=0;i<other.size;i++)
k.add(other.get(i,&succ),&succ);
return k;
}
TMArrayList::~TMArrayList()
{
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
}
}
void TMArrayList::InsertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{
this->add(data,success);
return ;
}
bool succ;
int k=this->get(size-1,&succ);
this->add(k,&succ);
if(succ==false) return;
int j;
j=this->size-3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success) *success=true;
}

int TMArrayList::removeAt(int index,int *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return 0;
bool succ;
int data=this->get(index,&succ);
int j;
int ep=this->size-2;
j=index;
while(j<=ep)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success) *success=true;
return data;
}
void TMArrayList::update(int index,int data,int *success)
{
if(success==NULL) *success=false;
if(index<0 || index>=this->size) return;
int rowIndex=size/10;
int columnIndex=size%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
void TMArrayList::removeAll()
{
 this->size=0;
}
void TMArrayList::clear()
{
this->size=0;
}
//TMFowardList Implementation start here
class TMForwardList:public TMList
{
class TMNode
{
public:
int data;
TMNode *next;
TMNode()
{
this->next=NULL;
}
};
private:
char allocationFlag;
TMNode *start,*end;
int size;
public:
TMForwardList();
TMForwardList(int buffersize);
TMForwardList(const TMForwardList &other);
virtual ~ TMForwardList();
TMForwardList & operator=(const TMForwardList &other);
void operator+=(const TMForwardList &other);
TMForwardList  operator+(const TMForwardList &other);
void add(int data,bool *success);
int get(int index,int *success) const;
int getSize()const;
void InsertAt(int data,int index,bool *success);
int removeAt(int index,int *success);
void update(int index,int data,int *success);
void removeAll();
void clear();
};
TMForwardList::TMForwardList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
TMForwardList::TMForwardList(int buffersize)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
TMForwardList::TMForwardList(const TMForwardList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<getSize();e++)
this->add(other.get(e,&succ),&succ);
}
TMForwardList::~TMForwardList()
{
if(allocationFlag==0)
{
this->clear();
}
}
TMForwardList & TMForwardList::operator=(const TMForwardList &other)
{
this->clear();
if(allocationFlag==1)
{
this->size=other.size;
this->start=other.start;
this->end=other.end;
}
else
{
int succ;
for(int x=0;x<other.getSize();x++)
{
this->add(other.get(x,&succ),&succ);
}
}
return *this;
}
void TMForwardList::operator+=(const TMForwardList &other)
{
int k;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&k),&k);
}
}
TMForwardList TMForwardList::operator+(const TMForwardList &other)
{
TMForwardList k;
k+=(*this);
k+=other;
return k;
}
void TMForwardList::add(int data,bool *success)
{
if(success) *success=false;
TMNode *t;
t=new TMNode;
if(t==NULL) return;
t->data=data;
if(this->start==NULL)
{
this->start=this->end=t;
}
else
{
this->end->next=t;
this->end=t;
}
this->size++;
if(success) *success=true;
}
int TMForwardList::get(int index,int *success) const
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
TMNode *t;
int x;
t=this->start;
for(x=0;x<index;x++) t=t->next;
if(success) *success=true;
return t->data;
}
int TMForwardList::getSize()const
{
return this->size;
}
void TMForwardList::InsertAt(int data,int index,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
TMNode *gg;
gg=new TMNode;
if(gg==NULL) return;
gg->data=data;
int x;
TMNode *j,*t;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}
if(t==this->start)
{
gg->next=this->start;
this->start=t;
}
else
{
gg->next=t;
j->next=gg;
}
this->size++;
if(success) *success=true;
}
int TMForwardList::removeAt(int index,int *success)
{
int data=0;
if(success) *success=false;
if(index<0 || index>=this->size) return data;
TMNode *t,*j;
int x;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}
data=t->data;
if(t==this->start && t==this->end)//only one node
{
this->start=this->end=NULL;
}else if(t==this->start)// many but delete firts
{
this->start=this->start->next;
}else if(t==end)// many but delete last
{
j->next=NULL;
this->end=j;
}
else// many but not first, nor last
{
j->next=t->next;
}
this->size--;
delete t;
if(success) *success=true;
return data;
}
void TMForwardList::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0|| index>=this->size) return;
TMNode *t;
int x;
for(t=this->start,x=0,x<index;x++;t=t->next);
{
t->data=data;
if(success) *success=true;
}
}
void TMForwardList::removeAll()
{
clear();
}
void TMForwardList::clear()
{
TMNode *t;
while(this->start!=NULL)
{
t=this->start;
this->start=this->start->next;
delete t;
}
this->end=NULL;
this->size=0;
}
int mainTMArrayList()
{
TMArrayList list1;
bool k;
for(int x=80;x<=123;x++)
{
list1.add(x,&k);
}
cout<<"size is"<<list1.getSize()<<endl;
for(int e=0;e<list1.getSize();e++)
cout<<list1.get(e,&k)<<" ";
cout<<"***************"<<endl;
TMArrayList list2;
for(int x=100;x<=123;x++)
{
list1.add(x,&k);
}
cout<<"size is"<<list2.getSize()<<endl;
for(int e=0;e<list2.getSize();e++)
cout<<list2.get(e,&k)<<" ";
TMArrayList list3;
for(int x=100;x<=123;x++)
{
list1.add(x,&k);
}
cout<<"size is"<<list3.getSize()<<endl;
for(int e=0;e<list3.getSize();e++)
cout<<list3.get(e,&k)<<" ";
for(int x=80;x<=120;x++) list2.add(x,&k);
for(int e=0;e<list2.getSize();e++)
cout<<list2.get(e,&k)<<" ";
cout<<"size is: "<<list2.getSize()<<endl;
list2=list1;
cout<<"After assigning list1 to list2"<<endl;
for(int x=0;x<list2.getSize();x++)
cout<<list2.get(x,&k)<<" ";
cout<<endl <<"size is: "<<list2.getSize()<<endl;
list2+=list1;
cout<<"After += "<<endl;
for(int e=0;e<list2.getSize();e++)
cout<<list2.get(e,&k)<<" ";
cout<<endl<<"size is: "<<list2.getSize()<<endl;
return 0;
}
int main()
{
TMForwardList list1;
bool s;
cout<<"size is :"<<list1.getSize()<<endl;
for(int e=0;e<=10;e++)
{
list1.add(e,&s);
}
cout<<list1.getSize()<<endl;
for(int x=0;x<=list1.getSize();x++)
{
cout<<list1.get(x,&s)<<endl;
}
/*TMArrayList list2(list1);
for(int x=0;x<=list2.getSize();x++)
{
cout<<"*******************************"<<endl;
cout<<"content of list2"<<endl;
cout<<list2.get(x,&s)<<endl;
}*/
return 0;
}