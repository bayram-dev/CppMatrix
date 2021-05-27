#include "matrix.h"
using namespace std;

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

    return 0;
}
