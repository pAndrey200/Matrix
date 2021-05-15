#if !defined(MATRIX)
#define MATRIX
#include <iostream>
#include <cmath>

class matrix
{
private:
    double **arr; // матрица
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

        arr = new double *[row];

        for (int i = 0; i < row; i++)
            arr[i] = (double *)new double[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = 0;
    }

    matrix(const matrix &_M)
    {
        row = _M.row;
        col = _M.col;

        arr = new double *[row];

        for (int i = 0; i < row; i++)
            arr[i] = (double *)new double[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                arr[i][j] = _M.arr[i][j];
    }

    double GetMij(int i, int j)
    {
        if ((row > 0) && (col > 0))
            return arr[i][j];
        else
            return 0;
    }

    void SetMij(int i, int j, double value)
    {
        if ((i < 0) || (i >= row))
            return;
        if ((j < 0) || (j >= col))
            return;
        arr[i][j] = value;
    }

    friend std::istream &operator>>(std::istream &istr, matrix &ma)
    {
        for (int i = 0; i < ma.row; i++)
            for (int j = 0; j < ma.col; j++)
                istr >> ma.arr[i][j];
        return (istr);
    }

    friend std::ostream &operator<<(std::ostream &ostr, matrix &ma)
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
    matrix operator*(const matrix &ma)
    {
        if (col != ma.row)
        {
            std::cout << "Умножение невозможно!";
            return matrix();
        }
        matrix c(row, ma.col);
        for (int i = 0; i < row; i++)
        {
            c.arr[i] = new double[ma.col];
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
        matrix y(col, 1);
        y.arr[0][0] = 1.;

        matrix rez(col, col + 1);
        for (size_t i = 1; i < col + 1; i++)
        {
            matrix y1 = *this * y;
            for (size_t j = 0; j < row; j++)
            {
                rez.arr[j][i] = y1.arr[j][0];
            }
            y = y1;
        }
        rez.arr[0][0] = 1;
        return rez.gauss();
    }

    matrix gauss()
    {
        using namespace std;
        matrix x(1,col);
        double  max;
        int k, index;
        const double eps = 0.00001; 
        k = 0;
        double *y = new double[row];
        for(int i = 0; i < row; i++){
            y[i] = arr[i][row];
        }

        while (k < row)
        {
            max = abs(arr[k][k]);
            index = k;
            for (int i = k + 1; i < row; i++)
            {
                if (abs(arr[i][k]) > max)
                {
                    max = abs(arr[i][k]);
                    index = i;
                }
            }
            for (int j = 0; j < row; j++)
            {
                double temp = arr[k][j];
                arr[k][j] = arr[index][j];
                arr[index][j] = temp;
            }
            double temp = y[k];
            y[k] = y[index];
            y[index] = temp;
            for (int i = k; i < row; i++)
            {
                double temp = arr[i][k];
                if (abs(temp) < eps)
                    continue; 
                for (int j = 0; j < row; j++)
                    arr[i][j] = arr[i][j] / temp;
                y[i] = y[i] / temp;
                if (i == k)
                    continue; 
                for (int j = 0; j < row; j++)
                    arr[i][j] = arr[i][j] - arr[k][j];
                y[i] = y[i] - y[k];
            }
            k++;
        }
        for (k = row - 1; k >= 0; k--)
        {
            x.arr[0][k] = y[k];
            for (int i = 0; i < k; i++)
                y[i] = y[i] - arr[i][k] * x.arr[0][k];
        }
        x.arr[0][row] = -1;
        for(int i = 0; i <= col/2; i++){
            double temp = x.arr[0][i];
            x.arr[0][i] = -x.arr[0][row-i];
            x.arr[0][row-i] = -temp;
        }
        return x;
    }

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
        arr = (double **)new double *[row]; // количество строк, количество указателей
        for (int i = 0; i < row; i++)
            arr[i] = (double *)new double[col];

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
