#include <iostream>
using namespace std;

class String
{ 
    char *str;
    int len;
    public:
    String(int l = 0);
    String(const char *);
    String(String &);
    ~String() { if(str) delete []str; str = NULL; }
    int Len();
    String & operator = (const String &);
    char &operator [](int);
    bool operator == (String &);
    bool operator != (String &);
    String operator + (const String &);
    String & operator += (const String &);
    friend istream & operator >> (istream &, String &);
    friend ostream & operator << (ostream &, String &);
    int BMH_search(String &);
};
