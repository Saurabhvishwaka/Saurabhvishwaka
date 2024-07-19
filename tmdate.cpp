#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;
class TMDate
{
private:
int dayOfMonth;
int month;
int year;
int dayNumber;
int isLeapYear(int);
void toDayNumber();
void FromDayNumber();
void isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y);
public:
//constructor function
int getDayOfWeek();
void getDayOfWeekString(char *dayOfWeekString);
void getDayOfWeekShortString(char *dayOfWeekShortString);
TMDate(const char *dateString);
int isLeapYear();
TMDate(const TMDate &other);
TMDate & operator=(const TMDate &other);
TMDate();
//operator function
void operator+=(int);
void operator-=(int);
TMDate operator+(int);
TMDate operator-(int);
TMDate & operator=(const char *dateString);
int operator<(const TMDate &other);
int operator>(const TMDate &other);
int operator<=(const TMDate &other);
int operator>=(const TMDate &other);
int operator==(const TMDate &other);
int operator!=(const TMDate &other);
void getmonthShortString(char *MonthShortString);
void getmonthString(char *MonthString);
int getDayOfMonth();
int getMonth();
int getYear();
void fromDayNumber();
/*int getDayNumber()
{
return this->dayNumber;
}*/
};
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
dayOfMonth=now->tm_mday;
month=now->tm_mon+1;
year=now->tm_year+1900;
this->toDayNumber();
}
void TMDate::operator+=(int days)
{
if(this->dayNumber==0)return;
this->dayNumber+=days;
this->fromDayNumber();
}
/*TMDate TMDate::operator+(int days)
{
if(this->dayNumber==0) return TMDate("00/00/0000");
TMDate date;
date.dayNumber=this->dayNumber+days;
date.fromDayNumber();
return date;
}*/
TMDate TMDate::operator+(int months)
{
if(this->dayNumber==0) return TMDate("00/00/0000");
TMDate date=(*this);
date.month=this->month+months;
date.year=this->year+months;
date.fromDayNumber();
return date;
}
TMDate TMDate::operator-(int days)
{
if(this->dayNumber==0) return TMDate("00/00/0000");
TMDate date;
date.dayNumber=this->dayNumber-days;
date.fromDayNumber();
return date;
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0)return;
this->dayNumber-=days;
this->fromDayNumber();
}
TMDate & TMDate::operator=(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
return *this;
}
TMDate::TMDate(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
}
int TMDate::operator<(const TMDate &other)
{
return this->dayNumber<other.dayNumber;
}
int TMDate::operator>(const TMDate &other)
{
return this->dayNumber>other.dayNumber;
}
int TMDate::operator>=(const TMDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int TMDate::operator<=(const TMDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int TMDate::operator==(const TMDate &other)
{
return this->dayNumber==other.dayNumber;
}
int TMDate::operator!=(const TMDate &other)
{
return this->dayNumber!=other.dayNumber;
}
int TMDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0)return 1;
else return 0;
}
void TMDate::toDayNumber()
{
int x=0;
int y=1901;
int m;
while(y<this->year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
int ep=this->month-2;
m=0;
while(m<=ep)
{
x=x+mth[m];
m++;
}
m++;
x=x+this->dayOfMonth;
this->dayNumber=x;
}
void TMDate::fromDayNumber()
{
if(this->dayNumber==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int x=this->dayNumber;
int d,m,y;
int daysInyear;
int daysInmonth;
y=1901;
while(1)
{ 
if(isLeapYear(y)) daysInyear=366;
else daysInyear=365;
if(x<=daysInyear) break;
x=x-daysInyear;
y=y+1;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y))mth[1]=29;
m=0;
while(1)
{
daysInmonth=mth[m];
if(x<=daysInmonth) break;
x=x-daysInmonth;
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
TMDate::TMDate(const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
}
TMDate & TMDate::operator=(const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
return *this;
}
void TMDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy;
char sep;
int sepIndex1,sepIndex2,i,r;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
*isValid=0;
if(dateString==NULL) return;
int x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-')
sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep))
return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepIndex2==i+2 && (dateString[i+1]<48 || dateString[i+1]>57))
return;
if(sepIndex2==i+1)
{
mm=dateString[i]-48;
}
else
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return;
i=sepIndex2+1;
yy=0;
r=0;
while(r<=3)
{
if(dateString[i+r]<48 || dateString[i+r]>57) return;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400==0) mth[1]=29;
else if(yy%100==0) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1 || dd>mth[mm-1]) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}
int TMDate::isLeapYear()
{
if(this->dayNumber==0) return 0;
if(this->year%400==0) return 1;
if(this->year%100==0) return 0;
if(this->year%4==0) return 1;
}
void TMDate::getmonthString(char *MonthString)
{
if(this->dayNumber==0)
{
*MonthString='\0';
return;
}
if(month==1) strcpy(MonthString,"January");
if(month==2) strcpy(MonthString,"February");
if(month==3) strcpy(MonthString,"March");
if(month==4) strcpy(MonthString,"April");
if(month==5) strcpy(MonthString,"may");
if(month==6) strcpy(MonthString,"June");
if(month==7) strcpy(MonthString,"July");
if(month==8) strcpy(MonthString,"August");
if(month==9) strcpy(MonthString,"September");
if(month==10) strcpy(MonthString,"October");
if(month==11) strcpy(MonthString,"November");
if(month==12) strcpy(MonthString,"December");
}
void TMDate::getmonthShortString(char *MonthShortString)
{
if(this->dayNumber==0)
{
*MonthShortString='\0';
return;
}
if(month==1) strcpy(MonthShortString,"Jan");
if(month==2) strcpy(MonthShortString,"Feb");
if(month==3) strcpy(MonthShortString,"Mar");
if(month==4) strcpy(MonthShortString,"Apr");
if(month==5) strcpy(MonthShortString,"may");
if(month==6) strcpy(MonthShortString,"Jun");
if(month==7) strcpy(MonthShortString,"Jul");
if(month==8) strcpy(MonthShortString,"Aug");
if(month==9) strcpy(MonthShortString,"Sep");
if(month==10) strcpy(MonthShortString,"Oct");
if(month==11) strcpy(MonthShortString,"Nov");
if(month==12) strcpy(MonthShortString,"Dec");
}
int TMDate::getDayOfWeek()
{
if(dayNumber==0) return 0;
int leftDays=this->dayNumber%7;
int dow=2+leftDays;
if(dow>7) dow=dow%7;
return dow;
}
void TMDate::getDayOfWeekString(char *dayOfWeekString)
{
if(dayNumber==0)
{
*dayOfWeekString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekString,"Sunday");
if(dow==2) strcpy(dayOfWeekString,"Monday");
if(dow==3) strcpy(dayOfWeekString,"Tuesday");
if(dow==4) strcpy(dayOfWeekString,"Wednesday");
if(dow==5) strcpy(dayOfWeekString,"Thursday");
if(dow==6) strcpy(dayOfWeekString,"Friday");
if(dow==7) strcpy(dayOfWeekString,"Saturday");
}
void TMDate::getDayOfWeekShortString(char *dayOfWeekShortString)
{
if(dayNumber==0)
{
*dayOfWeekShortString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekShortString,"Sun");
if(dow==2) strcpy(dayOfWeekShortString,"Mon");
if(dow==3) strcpy(dayOfWeekShortString,"Tue");
if(dow==4) strcpy(dayOfWeekShortString,"Wed");
if(dow==5) strcpy(dayOfWeekShortString,"Thu");
if(dow==6) strcpy(dayOfWeekShortString,"Fri");
if(dow==7) strcpy(dayOfWeekShortString,"Sat");
}
int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
ostream & operator<<(ostream &oo,TMDate &tmdate)
{
oo<<tmdate.getDayOfMonth()<<"/"<<tmdate.getMonth()<<"/"<<tmdate.getYear();
return oo;
}
int main()
{
TMDate date="28/01/2024";
date=date+10; // Adding 10 months using operator+ 
cout<<date<<endl;
return 0;
}