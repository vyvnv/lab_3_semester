#include <iostream>
using namespace std;

class String
{ 
    char *str;
    int len;

    public:
    String(int l = 1); // конструктор по умолчанию +
    String(const char *); //конструктор строки +
    String(String &); // конструктор копирования +
    ~String() { if(str) delete []str; str = NULL; } // деструктор +
    int Len(); //получить размер +
    String & operator = (const String &);//перегруженная операция присваивания
    char &operator [](int);
    bool operator == (String &);
    bool operator != (String &);
    String operator + (const String &);
    String & operator += (const String &);
    friend istream & operator >> (istream &, String &);
    friend ostream & operator << (ostream &, String &);
    int BMH_search(String &);
};

String::String(int l)
{
    str = new char[l];
    len = 0;
    str[0] = '/0';
}

String::String(const char *line) // cпросить про такую реализацию конструктора
{
    str = new char[strlen(line)+1];
    if(str)
    { 
        for (len = 0; len != '/0'; str[len] = line[len], len++);
        str[len] = '/0';
    }
    else delete(str);
}

String::String(String & string_object)
{

    str = new char[string_object.len+1];
    for (len = 0;  len <= string_object.len;  str[len] = string_object.str[len], len++);
    len--;
}

int String::Len()
{
    return len;
}

String& String::operator = (const String &some_obj)
{
    if (this != &some_obj) // если первый операнд не указывает на одну и ту же область памяти, что и второй, то выполняем присвоение
    {
        delete []str; // осв память поля str объекта this
        str = new char[(len=some_obj.len)+1]; //выделяем
        strcpy (str, some_obj.str); // копируем из поля str второго операнда в поле str операнда this
    }
    return *this; // иначе возвращаем первый операнд
}

char & String:: operator [](int i){
    if (i<0 || i>len) {puts("Index outside the row");exit(0);}
    return str[i];
}

bool String:: operator == (String &s){
    if(strcmp(str,s.str)==0) return true;
    return false;
}

bool String:: operator != (String &s){
    if (strcmp(str,s.str)!=0) return true;
    return false;
}

String String:: operator + (const String &s){
    String tmp(len+s.len+1);
    strcpy(tmp.str,str);
    strcat(tmp.str,s.str);
    tmp.len=strlen(tmp.str);
    return tmp;
}

String & String:: operator += (const String &s){
    char *m=new char[len+1];
    strcpy(m,str);
    delete []str;
    len=len+s.len;
    str=new char[len+1];
    strcpy(str,m);
    strcat(str,s.str);
    delete []m;
    return *this;
}

istream & operator >> (istream &r, String &s){
    char m[120];
    cin>>m;
    String tmp(m);
    s=tmp;
    return r;
}

ostream & operator << (ostream &r, String &s){
    r<<s.str<<endl;;
    return r;
}

int String:: BMH_search(String &s)
{
    int i=0,k,j=0,l; 
    char t[255+1];
    if (s.len>len) 
        return -1;
    for (; i< 256; i++)
    {
        t[i]=s.len;
    }
    for (;j<s.len-1;j++) 
    {
        t[s[j]]=s.len-j-1;
    }

    i= j = s.len-1;

    while (i < len && j >= 0) 
    {
        k=i; 
        j=s.len-1;

        while (j >= 0) 
        {
            if (str[k]==s[j])   
            {
                k--;
                j--;
            } 
            else 
            {
                i+=t[str[i]];
                j=s.len-1;
                break;
            }
        }
        } if (j>=0) 
        return -1; 
        else return i+1-s.len;
}

int main() {
    String s1("Michael"); String s2("Afton"); String s3; String s4("Michael"); String s5("Terrence");
    cout<<"Length "<<s2.Len()<<endl;
    s3=s1+s5+s2;
    cout<<s3;
    s2[3]='c'; cout<<s2;
    if (s1==s1) cout<<"Lines are equal"<<endl;
    if (s1!=s1) cout<<"Lines are not equal"<<endl;
    s4+=s5;
    cout<<s4;
    cin>>s3;
    cout<<s3;
    int count=s4.BMH_search(s1);
    if (count==-1) cout<<"No "<<endl; else cout<<"Index= "<<count<<endl;
    String s6("achfakhacfadbcaababcaaa");
    String s7("aac");
  if (s6==s7) cout<<"Lines are equal"<<endl;
  if (s6!=s7) cout<<"Lines are not equal"<<endl;
    count=s6.BMH_search(s7);
    if (count==-1) cout<<"No "<<endl; else cout<<"Index= "<<count<<endl;
return 0;   
}

