#if !defined(MATRIX)
#define MATRIX
#include <iostream>
using namespace std;
template <typename dataType>
class matrix
{
private:
    dataType **arr; // матрица
    int row;        // количество строк
    int col;        // количество столбцов

public:
    // конструкторы
    matrix()
    {
        col = row = 0;
        arr = nullptr; // необязательно
    }

    // конструктор с двумя параметрами
    matrix(int _m, int _n)
    {
        row = _m;
        col = _n;

        // Выделить память для матрицы
        // Выделить пам'ять для массива указателей
        arr = (dataType **)new dataType *[row]; // количество строк, количество указателей

        // Выделить память для каждого указателя
        for (int i = 0; i < row; i++)
            arr[i] = (dataType *)new dataType[col];

        // заполнить массив arr нулями
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = 0;
    }

    // Конструктор копирования - обязательный
    matrix(const matrix &_M)
    {
        // Создается новый объект для которого виделяется память
        // Копирование данных *this <= _M
        row = _M.row;
        col = _M.col;

        // Выделить память для arr
        arr = (dataType **)new dataType *[row]; // количество строк, количество указателей

        for (int i = 0; i < row; i++)
            arr[i] = (dataType *)new dataType[col];

        // заполнить значениями
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = _M.arr[i][j];
    }

    dataType GetMij(int i, int j)
    {
        if ((row > 0) && (col > 0))
            return arr[i][j];
        else
            return 0;
    }

    void SetMij(int i, int j, dataType value)
    {
        if ((i < 0) || (i >= row))
            return;
        if ((j < 0) || (j >= col))
            return;
        arr[i][j] = value;
    }

    // метод, выводящий матрицу
    void Print(const char *ObjName)
    {
        cout << "Object: " << ObjName << endl;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                cout << arr[i][j] << "\t";
            cout << endl;
        }
        cout << "---------------------" << endl
             << endl;
    }

    // оператор копирования - обязательный
    matrix operator=(const matrix &_M)
    {
        if (col > 0)
        {
            // освободить память, выделенную ранее для объекта *this
            for (int i = 0; i < row; i++)
                delete[] arr[i];
        }

        if (row > 0)
        {
            delete[] arr;
        }

        // Копирование данных arr <= _M
        row = _M.row;
        col = _M.col;

        // Выделить память для arr опять
        arr = (dataType **)new dataType *[row]; // количество строк, количество указателей
        for (int i = 0; i < row; i++)
            arr[i] = (dataType *)new dataType[col];

        // заполнить значениями
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = _M.arr[i][j];
        return *this;
    }

    // Деструктор - освобождает память, выделенную для матрицы
    ~matrix()
    {
        if (col > 0)
        {
            // освободить выделенную память для каждой строки
            for (int i = 0; i < row; i++)
                delete[] arr[i];
        }

        if (row > 0)
            delete[] arr;
    }
};

#endif // matrix
