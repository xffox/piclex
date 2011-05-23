#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <vector>

#include "BaseExceptions.h"

namespace search
{
template<class T>
class Matrix3d
{
public:
    Matrix3d();
    Matrix3d(size_t pages, size_t rows, size_t columns, const T &initValue = T());
    ~Matrix3d();

    void resize(size_t pages, size_t rows, size_t columns,
            const T &initValue = T());

    void set(size_t i, size_t j, size_t k, const T &value);
    const T get(size_t i, size_t j, size_t k) const;

    size_t getPages() const;
    size_t getRows() const;
    size_t getColumns() const;

private:
    void copy(std::vector<T> &data, size_t pages, size_t rows, size_t columns);

private:
    size_t mPages;
    size_t mRows;
    size_t mColumns;
    
    std::vector<T> mData;
};

template<class T>
Matrix3d<T>::Matrix3d()
    :mPages(0), mRows(0), mColumns(0)
{
}

template<class T>
Matrix3d<T>::Matrix3d(size_t pages, size_t rows, size_t columns,
        const T &initValue)
    :mPages(pages), mRows(rows), mColumns(columns)
{
    mData.resize(pages * rows * columns, initValue);
}

template<class T>
Matrix3d<T>::~Matrix3d()
{
}

template<class T>
void Matrix3d<T>::resize(size_t pages, size_t rows, size_t columns,
        const T &initValue)
{
    if(pages == mPages && rows == mRows && columns == mColumns)
        return;

    std::vector<T> tmpData(pages * rows * columns, initValue);

    copy(tmpData, pages, rows, columns);

    mData = tmpData;

    mPages = pages;
    mRows = rows;
    mColumns = columns;
}

template<class T>
void Matrix3d<T>::set(size_t i, size_t j, size_t k, const T &value)
{
    if(i >= mPages)
        throw base::OutOfBoundError(i, mPages);
    if(j >= mRows)
        throw base::OutOfBoundError(j, mRows);
    if(k >= mColumns)
        throw base::OutOfBoundError(k, mColumns);

    mData[mRows*mColumns * i + mColumns * j + k] = value;
}

template<class T>
const T Matrix3d<T>::get(size_t i, size_t j, size_t k) const
{
    if(i >= mPages)
        throw base::OutOfBoundError(i, mPages);
    if(j >= mRows)
        throw base::OutOfBoundError(j, mRows);
    if(k >= mColumns)
        throw base::OutOfBoundError(k, mColumns);

    return mData[mRows*mColumns * i + mColumns * j + k];
}

template<class T>
size_t Matrix3d<T>::getPages() const
{
    return mPages;
}

template<class T>
size_t Matrix3d<T>::getRows() const
{
    return mRows;
}

template<class T>
size_t Matrix3d<T>::getColumns() const
{
    return mColumns;
}

template<class T>
void Matrix3d<T>::copy(std::vector<T> &data, size_t pages, size_t rows,
        size_t columns)
{
    const size_t minPages = std::min(mPages, pages);
    const size_t minRows = std::min(mRows, rows);
    const size_t minColumns = std::min(mColumns, columns);

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    for(i = 0; i < minPages; ++i)
        for(j = 0; j < minRows; ++j)
            for(k = 0; k < minColumns; ++k)
                data[rows*columns * i + columns * j + k] =
                    mData[mRows*mColumns * i + mColumns * j + k];
}

}

#endif//MATRIX3D_H
