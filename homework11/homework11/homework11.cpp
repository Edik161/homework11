// homework11.cpp: определяет точку входа для приложения.
//

#include "homework11.h"
#include <gsl/gsl>
#include <iostream>
using namespace std;
using namespace gsl;
// Удаление первого элемента
double* popFront(not_null<double*> arr, int* size) 
{
    if (*size <= 0) return nullptr;

    double* newArr = new double[*size - 1];
    for (int i = 1; i < *size; ++i) 
    {
        newArr[i-1] = arr.get()[i];
    }
    
    (*size)--;
    delete[] arr.get();
    return newArr;
}

// Удаление последнего элемента
double* popBack(not_null<double*> arr, int* size) 
{
    if (*size <= 0) return nullptr;

    double* newArr = new double[*size - 1];
    for (int i = 0; i < *size - 1; ++i) 
    {
        newArr[i] = arr.get()[i];
    }
    
    (*size)--;
    delete[] arr.get();
    return newArr;
}

// Удаление элемента по позиции
double* removeAt(not_null<double*> arr, int* size, int index) 
{
    if (index < 0 || index >= *size) return nullptr;

    double* newArr = new double[*size - 1];
    
    for (int i = 0; i < index; ++i) 
    {
        newArr[i] = arr.get()[i];
    }
    
    for (int i = index+1; i < *size; ++i) 
    {
        newArr[i-1] = arr.get()[i];
    }
    
    (*size)--;
    delete[] arr.get();
    return newArr;
}

// Проверка наличия элемента в массиве
bool contains(not_null<const double*> arr, int size, double value) 
{
    for (int i = 0; i < size; ++i) 
    {
        if (arr.get()[i] == value) 
        {
            return true;
        }
    }
    return false;
}

// Пересечение массивов
double* arrayIntersection(not_null<double*> arr1, int size1, 
                         not_null<double*> arr2, int size2, 
                         int* resultSize) 
{
    int maxSize = std::min(size1, size2);
    double* tempResult = new double[maxSize];
    int count = 0;
    
    for (int i = 0; i < size1; ++i) 
    {
        double current = arr1.get()[i];
        if (contains(arr2, size2, current))
        {
            bool duplicate = false;
            for (int j = 0; j < count; ++j) 
            {
                if (tempResult[j] == current) 
                {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                tempResult[count++] = current;
            }
        }
    }
    
    double* result = new double[count];
    for (int i = 0; i < count; ++i) 
    {
        result[i] = tempResult[i];
    }
    
    *resultSize = count;
    delete[] tempResult;
    return result;
}

// массив из всех элементов, не принадлежащие ни одному из массивов;
double* arraySymmetricDifference(not_null<double*> arr1, int size1,
                                not_null<double*> arr2, int size2,
                                int* resultSize) 
{
    int maxSize = size1 + size2;
    double* tempResult = new double[maxSize];
    int count = 0;
    
    for (int i = 0; i < size1; ++i) 
    {
        double current = arr1.get()[i];
        if (!contains(arr2, size2, current)) 
        {
            tempResult[count++] = current;
        }
    }
    
    for (int i = 0; i < size2; ++i) 
    {
        double current = arr2.get()[i];
        if (!contains(arr1, size1, current)) 
        {
            tempResult[count++] = current;
        }
    }
    
    double* result = new double[count];
    for (int i = 0; i < count; ++i) 
    {
        result[i] = tempResult[i];
    }
    
    *resultSize = count;
    delete[] tempResult;
    return result;
}

void printArray(not_null<const double*> arr, int size) 
{
    for (int i = 0; i < size; ++i) {
        cout << arr.get()[i] << " ";
    }
    cout << "\n";
}

int main() 
{
    int size1 = 5, size2 = 7;
    double* arr1 = new double[size1]{1.1, 2.2, 3.3, 4.4, 5.5};
    double* arr2 = new double[size2]{4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0};
    
    cout << "Original array 1: ";
    printArray(make_not_null(arr1), size1);
    
    arr1 = popFront(make_not_null(arr1), &size1);
    cout << "After popFront: ";
    printArray(make_not_null(arr1), size1);
    
    arr1 = removeAt(make_not_null(arr1), &size1, 1);
    cout << "After removeAt(1): ";
    printArray(make_not_null(arr1), size1);
    
    int interSize;
    double* intersection = arrayIntersection(
        make_not_null(arr1), size1,
        make_not_null(arr2), size2,
        &interSize);
    cout << "Intersection: ";
    printArray(make_not_null(intersection), interSize);
    
    int diffSize;
    double* difference = arraySymmetricDifference(
        make_not_null(arr1), size1,
        make_not_null(arr2), size2,
        &diffSize);
    cout << "Symmetric difference: ";
    printArray(make_not_null(difference), diffSize);
    
    delete[] arr1;
    delete[] arr2;
    delete[] intersection;
    delete[] difference;
    
    return 0;
}