#pragma once

template <typename T>
class Array_List{
private:
    typedef T element_type;
    int capacity_; // Ёмкость списка: реальный размер массива
    int size_; // Кол-во элементов в массиве
    int last_index_; // Последний занятый индекс в массиве
    T* array_; // Динамический массив, в  котором хранятся все данные
    void MemoryUp(){ // Метод увеличения памяти для массива
        capacity_*=2;
        T* new_array;
        new_array=new T[capacity_];
        for (int i=0; i<size_; i++){
            new_array[i]=array_[i];
        }
        delete array_;
        array_=new_array;
    }
    void MemoryDown(){ // Метод сокращения памяти для массива
        capacity_/=2;
        T* new_array;
        new_array=new T[capacity_];
        for (int i=0; i<size_; i++){
            new_array[i]=array_[i];
        }
        delete array_;
        array_=new_array;
    }
public:
    explicit Array_List(int capacity=2) : capacity_(capacity), size_(0), last_index_(-1){ // Конструктор
        array_=new T[capacity];
    }
    Array_List(const Array_List &ArrayList){ // Конструктор копирования
        capacity_=ArrayList.capacity_;
        size_=ArrayList.size_;
        last_index_=ArrayList.last_index_;
        array_=new T[capacity_];
        for (int i=0; i<size_; i++){
            array_[i]=ArrayList.array_[i];
        }
    }
    void Append(T value){
        size_++;
        last_index_++;
        if (capacity_==size_) {
            MemoryUp();
        }
        array_[last_index_]=value;
    }
    void Prepend(T value){
        size_++;
        last_index_++;
        if (capacity_==size_){
            MemoryUp();
        }
        for (int i=0; i<(size_-1); i++){
            array_[i+1]=array_[i];
        }
        array_[0]=value;
    }
};