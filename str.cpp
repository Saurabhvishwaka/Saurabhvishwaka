#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
class TMString
{
private:
char *ptr;
int size;
public:
TMString();
virtual~TMString();
TMString(const char *ptr);
TMString & operator=(const TMString &other);
TMString & operator=(const char *ptr);
void operator+=(const TMString &other);
TMString operator+(const TMString &other);
int operator<(const TMString &other);
int operator>(const TMString &other);
int operator<=(const TMString &other);
int operator>=(const TMString &other);
int operator==(const TMString &other);
int operator!=(const TMString &other);
friend ostream &operator<<(ostream &out,const TMString &tmSting);
};
TMString::TMString()
{
this->ptr=NULL;
this->size=0;
}
TMString::TMString(const char *ptr)
{
this->ptr=NULL;
if(ptr==NULL) return;
this->size=strlen(ptr);
this->ptr=new char[this->size+1];
strcpy(this->ptr,ptr);
}
TMString & TMString::operator=(const TMString &other)
{
if(this->ptr) delete[] this->ptr;
this->ptr=NULL;
this->size=0;
if(other.ptr==NULL) return *this;
this->size=strlen(other.ptr);
this->ptr=new char[size+1];
strcpy(this->ptr,other.ptr);
return *this;
}
TMString & TMString::operator=(const char *ptr)
{
if(this->ptr) delete[] this->ptr;
this->ptr=NULL;
this->size=0;
if(ptr==NULL) return *this;
this->size=strlen(ptr);
this->ptr=new char[size+1];
strcpy(this->ptr,ptr);
return *this;
}
TMString::~TMString()
{
if(this->ptr) delete [] this->ptr;
}
ostream & operator<<(ostream &out,const TMString &tmString)
{
if(tmString.ptr==NULL) return out;
out<<tmString.ptr;
return out;
}
int TMString::operator<(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL) return 1;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr,other.ptr)<0;
}
int TMString::operator>(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL) return 0;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr)>0;
}
int TMString::operator<=(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 1;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr,other.ptr)<=0;
}
int TMString::operator>=(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr)>=0;
}
int TMString::operator==(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr,other.ptr)==0;
}
int TMString::operator!=(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL) return 1;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr)!=0;
}
void TMString::operator+=(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return;
if(other.ptr==NULL) return;
if(this->ptr==NULL)
{
(*this)=other;
return;
}
char *tmp=new char[this->size+other.size+1];
strcpy(tmp,this->ptr);
strcat(tmp,other.ptr);
delete [] this->ptr;
this->ptr=tmp;
this->size=this->size+other.size;
}
TMString TMString::operator+(const TMString &other)
{
TMString k;
if(this->ptr==NULL && other.ptr) return k;
if(this->ptr==NULL)  k=other;
else if(other.ptr==NULL)  k=(*this);
else
k=(*this);
k+=other;
return k;
}
istream & operator>>(istream &in, TMString &tmString) {
    char buffer[1024]; // Assuming maximum input size is 1024 characters
    in >> buffer;
    tmString = buffer;
    return in;
}
int main()
{
/*TMString a="Gao";
TMString b="Ahmedabad";
cout<<(a<b)<<endl;
cout<<(a>b)<<endl;
cout<<(a<=b)<<endl;
cout<<(a>=b)<<endl;
cout<<(a==b)<<endl;
cout<<(a!=b)<<endl;
a+=b;
TMString g;
TMString h;
TMString i;
g="katni";
h="jabalpur";
i=g+h;
cout<<i<<endl;
cout<<"********************"<<endl;
cout<<a<<endl;
*/
/*TMString str[10];
str[0]="saurabh";
str[1]="kanak";
str[2]="supriya";
str[3]="tanu";
str[4]="suresh";
str[5]="rounak";
str[6]="amit";
str[7]="akash";
str[8]="ravi";
str[9]="akhilesh";
int e,f,m;
TMString g;
m=8;
while(m>=0)
{
e=0;
f=1;
while(e<=m)
{
if(str[f]<str[e])
{
g=str[e];
str[e]=str[f];
str[f]=g;
}
e++;
f++;
}
m--;
}
for(int i=0;i<=9;i++)
cout<<str[i]<<endl;*/
cout<<"check your code"<<endl;
TMString str[1024];
cout<<"Enter a string: ";
fgets(str,1024,stdin);
fflush(stdin);
cout<<str<<endl;
return 0;
}
