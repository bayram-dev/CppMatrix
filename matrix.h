#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <fstream>

class Matrix
{
private:
    unsigned int width;
    unsigned int height;
    double** data;
public:
    Matrix();
    Matrix(unsigned int w, unsigned int h);
    Matrix(const Matrix& other);
    void createMatrix();
    void deleteMatrix();
    void setWidth(unsigned int w);
    unsigned int getWidth() const;
    void setHeight(unsigned int h);
    unsigned int getHeight() const;
    void setWidthHeight(unsigned int w, unsigned int h);
    void getMatrixFromFile(std::string file_name);
    void setElement(unsigned int i, unsigned int j, double value);
    double getElement(unsigned int i, unsigned int j);
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator*(const Matrix &other);
    Matrix operator*(double value);
    Matrix operator=(const Matrix &other);
    void print() const;
    ~Matrix();
};

#endif // MATRIX_H
