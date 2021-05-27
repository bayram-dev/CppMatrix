#include <iostream>
#include <string>
#include <fstream>
// using namespace std;

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


Matrix::Matrix()
{
    std::cout<<"Default constructor is called\n";
    width = 0;
    height = 0;
    data = nullptr;
}

Matrix::Matrix(unsigned int w, unsigned int h)
{
    std::cout<<"Constructor is called\n";
    height = h;
    width = w;
    createMatrix();
}

Matrix::Matrix(const Matrix &other)
{
    std::cout<<"Copy constructor is called\n";
    width = other.width;
    height = other.height;
    createMatrix();
    for(unsigned int i = 0; i < height; i++)
        for(unsigned int j = 0; j < width; j++)
            data[i][j] = other.data[i][j];
}

Matrix::~Matrix()
{
    deleteMatrix();
}

void Matrix::createMatrix()
{
    data = new double*[height];
    for(unsigned int i=0; i < height; i++)
    {
        data[i] = new double[width];
        for(unsigned int j = 0; j < width; j++)
            data[i][j] = 0;
    }
}

void Matrix::deleteMatrix()
{
    for(unsigned int i=0; i < height; i++)
        delete[] data[i];
    delete[] data;
}

void Matrix::print() const
{
    if(height != 0 && width != 0)
        for(unsigned int i=0; i < height; i++)
        {
            for(unsigned int j=0; j < width; j++)
                std::cout<<data[i][j]<<" ";
            std::cout<<std::endl;
        }
}

void Matrix::setWidth(unsigned int w)
{
    if(height != 0 && width != 0)
        deleteMatrix();
    width = w;
    if(height != 0 && width != 0)
        createMatrix();
}

unsigned int Matrix::getWidth() const{
    return width;
}

void Matrix::setHeight(unsigned int h)
{
    if(height != 0 && width != 0)
        deleteMatrix();
    height = h;
    if(height != 0 && width != 0)
        createMatrix();
}

unsigned int Matrix::getHeight() const{
    return height;
}

void Matrix::setWidthHeight(unsigned int w, unsigned int h)
{
    if(height != 0 && width != 0)
        deleteMatrix();
    width = w;
    height = h;
    if(height != 0 && width != 0)
        createMatrix();
}

void Matrix::setElement(unsigned int i, unsigned int j, double value)
{
    if(i >= height  || j >= width){
        throw "\n\e[1m \033[31m * OutOfRangeException\033[0m \e[0m: You got out of matrix \n";
    }
        data[i][j] = value;
}

double Matrix::getElement(unsigned int i, unsigned int j){
    if(i >= height  || j >= width){
        throw "\n\e[1m \033[31m * OutOfRangeException\033[0m \e[0m: You got out of matrix \n";
    }
    return data[i][j];
}

void Matrix::getMatrixFromFile(std::string file_name)
{
    std::ifstream input;
    input.open(file_name);
    if(input.is_open())
    {
        input>>height;
        input>>width;
        createMatrix();
        for(unsigned int i=0; i < height; i++)
            for(unsigned int j=0; j < width; j++)
            {
                if(input.eof())
                {
                    std::cout<<"Error! Reached EOF!\n";
                    input.close();
                    return;
                }
                input>>data[i][j];
            }
        if(!input.eof())
            std::cout<<"Error! All data was loaded, but EOF has not been reached!\n";

    }
    else
    {
        std::cout<<"Error! File is not open!\n";
        return;
    }
    input.close();
}

Matrix Matrix::operator +(const Matrix& other)
{
    std::cout<<"Operator + is called\n";
    Matrix result(width, height);
    for(unsigned int i=0; i < height; i++)
        for(unsigned int j=0; j < width; j++)
            result.setElement(i, j, data[i][j]+other.data[i][j]);
    return result;
}

Matrix Matrix::operator =(const Matrix& other)
{
    std::cout<<"Operator = is called\n";
    width = other.width;
    height = other.height;
    createMatrix();
    for(unsigned int i=0; i < height; i++)
        for(unsigned int j=0; j < width; j++)
            data[i][j] = other.data[i][j];
    return *this;
}

Matrix Matrix::operator -(const Matrix &other) {
    std::cout<<"Operator - is called\n";
    Matrix result(width, height);
    for(unsigned int i=0; i < height; i++)
        for(unsigned int j=0; j < width; j++)
            result.setElement(i, j, data[i][j]-other.data[i][j]);
    return result;
}

Matrix Matrix::operator *(double value) {
    std::cout<<"Operator * to double is called\n";
    Matrix result(width, height);
    for(unsigned int i=0; i < height; i++)
        for(unsigned int j=0; j < width; j++)
            result.setElement(i, j, data[i][j]*value);
    return result;
}

Matrix Matrix::operator *(const Matrix &other) {
    std::cout << "Operator * is called\n";
    Matrix result(other.width, height);
    if (width != other.height) {
        throw "\n\e[1m \033[31m * MatrixMultiplyException\033[0m \e[0m: Can't multiply this matrices \n";
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < other.width; j++) {
            for (unsigned int k = 0; k < other.height; k++) {
                    result.setElement(i, j, result.data[i][j] + data[i][k] * other.data[k][j]);
            }
        }
    }
    return result;
}

int main()
{
    Matrix matrixA;
    matrixA.getMatrixFromFile("/home/bayram/Рабочий стол/c++/lab02/input.txt");
    Matrix matrixB;
    matrixB.getMatrixFromFile("/home/bayram/Рабочий стол/c++/lab02/input2.txt");
    matrixA.print();
    std::cout<<"_________\n";
    matrixB.print();
    Matrix matrixC;
    try {
        matrixC = matrixA * matrixB;
        std::cout<<"_________\n";
        matrixC.print();
    }catch(const char* error){
        // catching multiplication error
        std::cout<<error;
    }
    try
    {
        std::cout<<matrixC.getHeight()<<std::endl<<matrixC.getWidth()<<std::endl;
        std::cout<<matrixC.getElement(0, 3)<<std::endl;
        matrixC.setElement(0, 3, 25);
        std::cout<<"_________\n";
        std::cout<<matrixC.getElement(0, 3)<<std::endl;
    }
    catch(const char* error)
    {
        std::cout<<error;
    }
    

    return 0;
}