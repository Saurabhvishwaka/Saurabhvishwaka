using namespace std;
template<class T>
#define bool int
#define true 1
#define True 1
#define TRUE 1
#define false 0
#define False 0
#define FALSE 0
template<T>
class Iterator
{
private:
int releaseIteratorAfterIteration;
Iterator *iterator;
public:
Iterator()
{
this->releaseIteratorAfterIteration=1;
this->iterator=NULL;
}
Iterator(Iterator *iterator)
{
this->releaseIteratorAfterIteration=1;
this->iterator=iterator;
}
Iterator(const Iterator &other)
{
this->releaseIteratorAfterIteration=1;
this->iterator=other.iterator;
}
virtual ~Iterator()
{
if(releaseIteratorAfterIteration==1) delete this->iterator;
}
void SetReleaseIteratorAfterIteration(int releaseIteratorAfterIteration)
{
this->releaseIteratorAfterIteration=releaseIteratorAfterIteration;
}
Iterator & operator=(const Iterator &other)
{
this->iterator=other.iterator;
}
virtual int hasMoreElements()
{
if(iterator!=NULL) return this->iterator->hasMoreElements();
return 0;
}
virtual int next()
{
if(iterator!=NULL) return this->iterator->next();
return 0;
}
};
template<class T>
class Iterable
{
public:
virtual Iterator<T> getIterator()=0;
};
template<class T>
class TMList:public Iterable<T>
{
public:
virtual void add(T data,bool *success)=0;
virtual T get(int index,int *success)const=0;
virtual int getSize()const=0;
virtual void InsertAt(int index,T data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual void update(int index,T data,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
};
tamplate<class T>
class TMArrayList : public TMList<T>
{
T **ptr;
char allocationFlag;
int capacity;
int size;
bool addrow();
public:
class TMArrayListIterator:public Iterator<T>
{
int index;
int size;
int **ptr;
public:
TMArrayListIterator(T **ptr,int size)
{
this->index=0;
this->size=size;
this->ptr=ptr;
}
TMArrayListIterator(const TMArrayListIterator &other)
{
this->index=other.index;
}
TMArrayListIterator & operator=(const TMArrayListIterator &other)
{
this->index=other.index;
return *this;
}
int hasMoreElements()
{
return index<size;
}
int next()
{
if(index==size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
T data=this->ptr[rowIndex][columnIndex];
index++;
return data;
}
};
Iterator<T> getIterator()
{
TMArrayListIterator *tmArrayListIterator;
tmArrayListIterator=new TMArrayListIterator(this->ptr,this->size);
Iterator<T> k(tmArrayListIterator);
k.SetReleaseIteratorAfterIteration(0);
return k;
}
TMArrayList();
TMArrayList(int buffersize);
TMArrayList(const TMList &other);
TMArrayList(const TMArrayList &other);
TMArrayList & operator=(const TMArrayList &other);

void operator+=(const TMArrayList &other);
TMArrayList & operator=(const TMList &other);
void operator+=(const TMList &other);
TMArrayList operator+(const TMList &other);
TMArrayList operator+(const TMArrayList &other);

void add(T data,bool *success);
T get(int index,int *success) const;
int getSize()const;
void InsertAt(int index,T data,bool *success);
T removeAt(int index,int *success);
void update(int index,T data,int *success);
void removeAll();
void clear();
~TMArrayList();
};
temlpate<class T>
bool TMArrayList<T>::addrow()
{
if(capacity%100==0)
{
int numberofpointer;
numberofpointer=this->capacity/10;
T **tmp=new T *[numberofpointer+10];
if(tmp==NULL) return false;
for(int e=0;e<numberofpointer;e++)
tmp[e]=this->ptr[e];
delete [] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
this->ptr[i]=new T[10];
if(this->ptr[i]==NULL) return false;
this->capacity=this->capacity+10;
return true;
}
temlpate<class T>
TMArrayList<T>::TMArrayList()
{
this->ptr=new T *[10];
this->ptr[0]=new T [10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
}
temlpate<class T>
TMArrayList<T>::TMArrayList(int buffersize)
{
this->allocationFlag=0;
if(buffersize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new T[10];
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
this->ptr=new T *[numberOfPointer];
for(int e=0;e<=rows;e++)
{
this->ptr[e]=new T [10];
}
this->capacity=rows*10;
this->size=0;
}
}
temlpate<class T>
TMArrayList<T>::TMArrayList(const TMArrayList<T> &other)
{
this->allocationFlag=0;
int buffersize=other.size;
if(buffersize<=0)
{
this->ptr=new T *[10];
this->ptr[0]=new T[10];
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
this->ptr=new T *[numberofpointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new T [10];
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
temlpate<class T>
TMArrayList<T>::TMArrayList(const TMList<T> &other)
{
this->ptr=new T *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->allocationFlag=0;
int e;
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
temlpate<class T> 
TMArrayList<T> & TMArrayList<T>::operator=(const TMArrayList<T> &other)
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
temlpate<class T>
void TMArrayList<T>::operator+=(const TMArrayList<T> &other)
{
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
temlpate<class T>
TMArrayList<T> TMArrayList<T>::operator+(const TMArrayList<T> &other)
{
TMArrayList k;
int succ;
for(int e=0;e<other.size;e++)
k.add(this->get(e,&succ),&succ);
for(int i=0;i<other.size;i++)
k.add(other.get(i,&succ),&succ);
return k;
}
temlpate<class T>
TMArrayList<T>::~TMArrayList()
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
temlpate<class T>
TMArrayList<T> & TMArrayList<T>::operator=(const TMList<T> &other)
{
this->size=0;
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}
temlpate<class T>
void TMArrayList<T>::operator+=(const TMList<T> &other)
{
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
temlpate<class T>
TMArrayList<T> TMArrayList<T>::operator+(const TMList<T> &other)
{
TMArrayList k;
int succ;
for(int e=0;e<this->size;e++)
k.add(this->get(e,&succ),&succ);
for(int s=0;s<getSize();s++)
k.add(other.get(s,&succ),&succ);
return k;
}
temlpate<class T>
void TMArrayList<T>::add(int data,bool *success)
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
if(index<0 || index>=this->size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
if(success) *success=true;
return this->ptr[rowIndex][columnIndex];
}
temlpate<class T>
void TMArrayList<T>::InsertAt(int index,int data,bool *success)
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
temlpate<class T>
int TMArrayList<T>::removeAt(int index,int *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
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
temlpate<class T>
void TMArrayList<T>::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return;
int rowIndex=size/10;
int columnIndex=size%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
template<class T>
int TMArrayList<T>::getSize()const
{
return this->size;
}
template<class T>
void TMArrayList<T>::removeAll()
{
 this->size=0;
}
void TMArrayList::clear()
{
this->size=0;
}
//TMFowardList Implementation start here
template<class T>
class TMForwardList:public TMList<T>
{
class TMNode
{
public:
T data;
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
template<class T>
class TMForwardListIterator:public Iterator<T>
{
TMNode *ptr;
public:
template<class T>
TMForwardListIterator<T>()
{
this->ptr=NULL;
}
template<class T>
TMForwardListIterator<T>(TMNode *ptr)
{
this->ptr=ptr;
}
template<class T>
TMForwardListIterator<T>(const TMForwardListIterator &other)
{
this->ptr=other.ptr;
}
template<class T>
TMForwardListIterator<T> & operator=(const TMForwardListIterator &other)
{
this->ptr=other.ptr;
return *this;
}
template<class T>
int hasMoreElements<T>()
{
return this->ptr!=NULL;
}
template<class T>
int next<T>()
{
if(this->ptr==NULL) return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};
template<class T>
Iterator<T> getIterator()
{
TMForwardListIterator *tmForwardListIterator;
tmForwardListIterator=new TMForwardListIterator(this->start);
Iterator k(tmForwardListIterator);
k.SetReleaseIteratorAfterIteration(0);
return k;
}
TMForwardList();
TMForwardList(int buffersize);
TMForwardList(const TMForwardList<T> &other);
TMForwardList(const TMList &other);
virtual ~ TMForwardList();
TMForwardList & operator=(const TMForwardList<T> &other);
void operator+=(const TMForwardList<T> &other);
TMForwardList  operator+(const TMForwardList<T> &other);
void add(T data,bool *success);
T get(int index,int *success) const;
int getSize()const;
void InsertAt(T data,int index,bool *success);
T removeAt(int index,int *success);
void update(int index,T data,int *success);
TMForwardList & operator=(const TMList &other);
void operator+=(const TMList &other);
TMForwardList operator+(const TMList &other);
void removeAll();
void clear();
};
template<class T>
void TMForwardList<T>::add(T data,bool *success)
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
template<class T>
T TMForwardList<T>::get(int index,int *success) const
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
template<class T>
int TMForwardList<T>::getSize()const
{
return this->size;
}
tanplate<class T>
void TMForwardList<T>::InsertAt(T data,int index,bool *success)
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
//this->start=t;
this->start=gg;
}
else
{
gg->next=t;
j->next=gg;
}
this->size++;
if(success) *success=true;
}
template<class T>
int TMForwardList<T>::removeAt(int index,int *success)
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
template<class T>
void TMForwardList<T>::update(int index,T data,int *success)
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
template<class T>
void TMForwardList<T>::removeAll()
{
clear();
}
template<class T>
void TMForwardList<T>::clear()
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
template<class T>
TMForwardList<T>::TMForwardList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
template<class T>
TMForwardList<T>::TMForwardList(int buffersize)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
template<class T>
TMForwardList<T>::TMForwardList(const TMList<T> &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
int succ;
for(int e=0;e<getSize();e++)
this->add(other.get(e,&succ),&succ);
}
template<class T>
TMForwardList<T>::TMForwardList(const TMForwardList<T> &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<getSize();e++)
this->add(other.get(e,&succ),&succ);
}
temlpate<class T>
TMForwardList<T>::~TMForwardList()
{
if(allocationFlag==0)
{
this->clear();
}
}
temlpate<class T>
TMForwardList<T> & TMForwardList<T>::operator=(const TMList<T> &other)
{
this->clear();
int succ;
for(int x=0;x<other.getSize();x++)
{
this->add(other.get(x,&succ),&succ);
}
return *this;
}
temlpate<class T>
TMForwardList<T> & TMForwardList<T>::operator=(const TMForwardList<T> &other)
{
this->clear();
int succ;
for(int x=0;x<other.getSize();x++)
{
this->add(other.get(x,&succ),&succ);
}
return *this;
}
temlpate<class T>
void TMForwardList<T>::operator+=(const TMList<T> &other)
{
int k;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&k),&k);
}
}
temlpate<class T>
void TMForwardList<T>::operator+=(const TMForwardList<T> &other)
{
int k;
for(int e=0;e<other.getSize();e++)
this->add(other.get(e,&k),&k);
}
temlpate<class T>
TMForwardList<T> TMForwardList<T>::operator+(const TMList<T> &other)
{
TMForwardList<T> k;
k+=(*this);
k+=other;
return k;
}
temlpate<class T>
TMForwardList<T> TMForwardList<T>::operator+(const TMForwardList<T> &other)
{
TMForwardList<T> k;
k+=(*this);
k+=other;
return k;
}
int main()
{
cout<<"Now iterating on TMFowardList"<<endl;
TMForwardList<char> list1;
int s;
list1.add('A',&s);
list1.add('B',&s);
list1.add('C',&s);
list1.add(543,&s);
list1.add(423,&s);
list1.add(4234,&s);
list1.add(232,&s);
Iterator<char> iterator1=list1.getIterator();
Iterator<char> iterator2=list1.getIterator();
Iterator<int> iterator3=list1.getIterator();
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"***********************"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"************************"<<endl;
cout<<"Now iterating on TMArrayList"<<endl;
TMArrayList list2;
list2.add(1100,&s);
list2.add(201,&s);
list2.add(3047,&s);
list2.add(5431,&s);
list2.add(423,&s);
list2.add(4234,&s);
list2.add(232,&s);
iterator1=list2.getIterator();
iterator2=list2.getIterator();
iterator3=list2.getIterator();
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"***********************"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"***********************"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
return 0;
}