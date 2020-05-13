#pragma once

template <typename T>
class Array_List{
private:
    typedef T element_type;
    int* array_; // Динамический массив, в  котором хранятся все данные
    int last_index_; // Последний занятый индекс в массиве
    int capacity_; // Ёмкость списка: реальный размер массива
    int size_; // Кол-во элементов в массиве
public:
    explicit Array_List(int capacity=2) : capacity_(capacity), size_(0), last_index_(-1){
        if (capacity<2){
            capacity_=2;
        }
        array_=new T[capacity_];
    }

};