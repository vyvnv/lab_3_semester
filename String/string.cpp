#include <iostream>
#include <cstring>
//#include <cstdio>

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
    String operator + (const String &); // сложение строк +
    char &operator [](int); //кв скобки +
    bool operator == (String &); // сравнение и равенство +
    bool operator != (String &); // сравнение и неравенство хотя зачем оно надо +
    
    String & operator += (const String &);
    friend istream & operator >> (istream &, String &);
    friend ostream & operator << (ostream &, String &);
    int BMH_search(String &);
};

String::String(int l)
{
    str = new char[l];
    len = 0;
    str[0] = '\0';
}

String::String(const char *line) 
{
    str = new char[strlen(line) + 1 ];
        for (len = 0; line[len] != '\0'; len++)
        {
            str[len] = line[len];       
        }
        //cout << len << endl;
        str[len] = '\0';
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
    if (this != &some_obj) 
    {
        delete []str; // осв память поля str объекта this
        str = new char[(len=some_obj.len)+1]; //выделяем
        strcpy (str, some_obj.str); // копируем из поля str второго операнда в поле str операнда this
    }
    return *this; 
}

char& String:: operator [](int i){
    if (i < 0 || i > len) 
    {
        cout << "index is out of range";
        //return str[len+1];    
    }
    return str[i];
}

bool String:: operator == (String &s)
{
    if (strcmp(str,s.str) == 0) 
        return true;
    return false;
}

bool String:: operator != (String &s)
{
    if (strcmp(str,s.str) !=0 ) 
        return true;
    return false;
}

String String:: operator + (const String &s)
{
    String tmp(len + s.len + 1); //создаем локальный объект
    strcpy(tmp.str, str); 
    strcat(tmp.str, s.str); // конкатенируем
    return tmp;
}

String& String:: operator += (const String &s) // переделать через +
{
   // String tmp = *this;
    *this = *this + s;
    return *this;
}

istream & operator >> (istream &r, String &s)
{
    char m[120];
    cin >> m;
    String tmp(m);
    s = tmp;
    return r;
}

ostream & operator << (ostream &r, String &s)
{
    r << s.str <<endl;;
    return r;
}

int String:: BMH_search(String &s)
{
    int * symTable = new int[256];

    for (int i = 0; i < 256; i++)
    {
        symTable[i] = s.len;
    }
    for (int i = 0; i < (s.len -1); i++)
    {
        symTable[s[i] ] = s.len - 1 - i;

    }
	
	int i = s.len - 1, j = s.len - 1;
	while (true)
	{
		if ((i < len) && (j >= 0))
		{
			int k = i;
			j = s.len - 1;

			bool flag = true;
			while (flag)
			{
				if (j < 0) flag = false;
				else
				{
					if (str[k] == s.str[j]) { j--; k--; }
					else
                    {
						i = i + symTable[str[i]];
						j = s.len - 1;
						flag = false;
					}
				}
				
			}
			
		}
		else
		{
			if (j >= 0)
			{
				cout << "String in text not found.\n";
				return -1;
			}
			else
			{
				return (i + 1 - s.len);
			}
		}
		
	}

}

int main() {
    //СОЗДАДИМ СТРОКИ ДЛЯ ТЕСТОВ
    String s1("ban"); //тут сработал конструктор
    String s2 = s1;  // тут к. копирования
    String s3; // тут к. по умолчанию
    String s4("plates"); 
    String s5("banana");
    //проверим работу конструкторов
    cout << "String 1 = " << s1 << endl;
    cout << "String 2 = " << s2 << endl;
    cout << "String 3 = " << s3 << endl;

    //ОПЕРАТОР СЛОЖЕНИЯ
    s3 = s1 + s5; 
    cout << s3 << endl;

    //КВАДРАТНЫЕ СКОБКИ
    cout << "First letter of the string:" << s1[0] << endl;
    cout << "Last letter of the string:" << s1[5] << endl;
    // тут я попробовала ввести индекс за пределами длины 
    cout << s1[7] << endl;
    
    //СРАВНЕНИЕ СТРОК
    if (s1 == s2) // сравним заведомо одинаковые
    {
        cout << "Strings 1 and 2 are equal" << endl;
    }

    else cout << "Strings 1 and 2 are different" << endl;

    if (s1 == s3) // сравним заведомо разные
    {
       cout << "Strings 1 and 3 are equal" << endl;
    }

    else cout << "Strings 1 and 3 are different" << endl;

    cout << endl << endl;

    //ОПЕРАТОР +=
    cout <<  "String 4 = " << s4 << endl;
    s4 += s5;
    cout << "Now string 4  = " << s4 << endl;

    //ПРОВЕРИМ РАБОТУ БМ ПОИСКА

    String s6; //= "bbcabcabcabc";
    String s7; // = "abc";
    cout << "Enter the string :" ;
    cin >> s6;
    cout << "Enter the substring :";
    cin >> s7;

    int index = s6.BMH_search(s7);

    if (index == -1) cout << "No such substrings" << endl; 
    else cout << "Index = " << index  << endl;


return 0;   
}