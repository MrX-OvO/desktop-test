#include <iostream>
template <typename T>
class Array2D
{
public:
    Array2D(size_t dim1 = 1, size_t dim2 = 0);
    Array2D(const Array2D &);
    Array2D &operator=(const Array2D &) &;
    ~Array2D();

    class Array1D
    {
    public:
        Array1D(size_t dim = 1) : arr1(new T[dim]), size(dim)
        {
            if (dim == 0)
            {
                arr1 = new T[1];
                size = 1;
            }
        }
        Array1D(T *ptr, size_t dim = 1) : arr1(new T[dim]), size(dim)
        {
            for (size_t i = 0; i < dim; i++)
                arr1[i] = *(ptr + i);
        }
        Array1D(const Array1D &arr1d)
        {
            auto arr1dSize = arr1d.getSize();
            if (getSize() < arr1dSize)
            {
                delete arr1;
                arr1 = new T[arr1dSize];
                setSize(arr1dSize);
            }
            for (size_t i = 0; i < arr1dSize; ++i)
                arr1[i] = arr1d[i];
        }
        Array1D &operator=(const Array1D &rhs) &
        {
            auto arr1dSize = rhs.getSize();
            if (this != &rhs)
            {
                delete arr1;
                arr1 = new T[arr1dSize];
                for (size_t i = 0; i < arr1dSize; ++i)
                    arr1[i] = rhs[i];
            }
            return *this;
        }
        ~Array1D() { delete arr1; }

        const T &operator[](size_t index) const & { return *(arr1 + index); }
        T &operator[](size_t index) & { return const_cast<T &>(static_cast<const Array1D &>(*this)[index]); }

        size_t getSize() const { return size; }
        void setSize(size_t size) { this->size = size; }

    private:
        T *arr1;
        size_t size;
    };

    const Array1D operator[](size_t) const &;
    Array1D operator[](size_t) &;

    size_t getRowSize() const { return row; }
    void setRowSize(size_t size) { row = size; }
    size_t getColSize() const { return col; }
    void setColSize(size_t size) { col = size; }

private:
    T **arr2;
    size_t row;
    size_t col;
};

template <typename T>
Array2D<T>::Array2D(size_t dim1, size_t dim2) : row(dim1), col(dim2)
{
    arr2 = new T *[dim1];
    for (size_t i = 0; i < dim1; ++i)
        arr2[i] = new T[dim2];
    if (dim1 == 0)
    {
        arr2 = new T *[1];
        arr2[0] = new T[1];
        row = 1;
        col = 1;
    }
}

template <typename T>
Array2D<T>::Array2D(const Array2D &arr2d)
{
    auto arr2dRowSize = arr2d.getRowSize();
    auto arr2dColSize = arr2d.getColSize();
    if (getRowSize() < arr2dRowSize && getColSize() < arr2dColSize)
    {
        ~Array2D();
        arr2 = new T *[arr2dRowSize];
        setRowSize(arr2dRowSize);
        for (size_t i = 0; i < arr2dRowSize; ++i)
            arr2[i] = new T[arr2dColSize];
        setColSize(arr2dColSize);
    }
    for (size_t i = 0; i < arr2dRowSize; ++i)
    {
        for (size_t j = 0; j < arr2dColSize; ++i)
            arr2[i][j] = arr2d[i][j];
    }
}

template <typename T>
Array2D<T> &Array2D<T>::operator=(const Array2D &rhs) &
{
    auto arr2dRowSize = rhs.getRowSize();
    auto arr2dColSize = rhs.getColSize();
    if (this != &rhs)
    {
        ~Array2D();
        arr2 = new T *[arr2dRowSize];
        setRowSize(arr2dRowSize);
        for (size_t i = 0; i < arr2dRowSize; ++i)
            arr2[i] = new T[arr2dColSize];
        setColSize(arr2dColSize);
        for (size_t i = 0; i < arr2dRowSize; ++i)
        {
            for (size_t j = 0; j < arr2dColSize; ++i)
                arr2[i][j] = rhs[i][j];
        }
    }
    return *this;
}

template <typename T>
Array2D<T>::~Array2D()
{
    for (size_t i = 0; i < getRowSize(); ++i)
        delete[] arr2[i];
    delete[] arr2;
}

template <typename T>
const typename Array2D<T>::Array1D Array2D<T>::operator[](size_t index) const &
{
    auto ptr = arr2[index];
    auto size = getColSize();
    return Array1D(ptr, size);
}

template <typename T>
typename Array2D<T>::Array1D Array2D<T>::operator[](size_t index) & { return static_cast<const Array2D &>(*this)[index]; }

int main(int argc, char const *argv[])
{
    Array2D<size_t> arr2d(2, 3);
    std::cout << arr2d[0][0] << std::endl;

    return 0;
}
