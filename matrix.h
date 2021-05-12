#if !defined(MATRIX)
#define MATRIX

template <typename dataType>
class matrix
{
private:
    dataType **arr;
    size_t row, col;
public:
    matrix(size_t row, size_t  col, dataType a = 0){
        
    }
    ~matrix();
};



#endif // MATRIX
