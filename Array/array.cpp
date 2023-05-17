#include <iostream>
using namespace std;

class Array
{ int *a, n;

    public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10); // видимо, конструктор по умолчанию

    Array(int *, int); // конструктор 2: по массиву
    Array(Array &); // конструктор копирования
    ~Array(); // деструктор
    Array& operator = (Array &);
    int &operator [](int);

    bool Test(); // проверка на упорядоченность по неубыванию
    bool operator == (Array); // равенство элементов массивов (но не порядка)

    void Shell_sort();
    void Heapsort();
    void Hoar_sort();
    void Bit_sort();
    friend istream & operator >> (istream &, Array &);
    friend ostream & operator << (ostream &, Array &);
};

Array::Array(int len = 1, int t = 1, int d = 10) 
    {

    }