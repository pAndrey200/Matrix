#if !defined(MATRIX)
#define MATRIX
#include <iostream>

template <typename dataType>
class matrix
{
private:
    dataType** arr; // матрица
    int row;        // количество строк
    int col;        // количество столбцов

public:
    matrix()
    {
        col = row = 0;
        arr = nullptr;
    }
    matrix(int _m, int _n)
    {
        row = _m;
        col = _n;

        arr = new dataType * [row];

        for (int i = 0; i < row; i++)
            arr[i] = (dataType*)new dataType[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = 0;
    }

    matrix(const matrix& _M)
    {
        row = _M.row;
        col = _M.col;

        arr = new dataType * [row];

        for (int i = 0; i < row; i++)
            arr[i] = (dataType*)new dataType[col];

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

    friend std::istream& operator>>(std::istream& istr, matrix& ma)
    {
        for (int i = 0; i < ma.row; i++)
            for (int j = 0; j < ma.col; j++)
                istr >> ma.arr[i][j];
        return (istr);
    }

    friend std::ostream& operator<<(std::ostream& ostr, matrix<dataType>& ma)
    {
        ostr << "---------------------" << std::endl;
        for (int i = 0; i < ma.row; i++)
        {
            for (int j = 0; j < ma.col; j++)
                ostr << ma.arr[i][j] << "\t";
            ostr << std::endl;
        }
        ostr << "---------------------" << std::endl
            << std::endl;
        return (ostr);
    }
    matrix operator*(const matrix& ma)
    {
        if (col != ma.row)
        {
            std::cout << "Умножение невозможно!";
            return matrix();
        }
        matrix c(row, ma.col);
        for (int i = 0; i < row; i++)
        {
            c.arr[i] = new dataType[ma.col];
            for (int j = 0; j < ma.col; j++)
            {
                c.arr[i][j] = 0;
                for (int k = 0; k < col; k++)
                    c.arr[i][j] += arr[i][k] * ma.arr[k][j];
            }
        }
        return c;
    }
    matrix makeM()
    {
        if (col != row)
        {
            std::cout << "ERROR!";
            return matrix();
        }
        matrix<double> y(col, 1);
        y.arr[0][0] = 1.;

        matrix<double> rez(col, col + 1);
        for (size_t i = 1; i < col + 1; i++)
        {
            matrix<double> y1 = *this * y;
            for (size_t j = 0; j < row; j++)
            {
                rez.arr[j][i] = y1.arr[j][0];
            }
            y = y1;
            
        }
        rez.arr[0][0] = 1;
        return rez;
    }

    matrix operator=(const matrix& _M)
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
        arr = (dataType**)new dataType * [row]; // количество строк, количество указателей
        for (int i = 0; i < row; i++)
            arr[i] = (dataType*)new dataType[col];

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
