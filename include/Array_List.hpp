#pragma once

#include <cstdlib>

template <typename T>
class Array_List{
private:
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
    void Append(T value){ // Метод добавления элемента в конец массива
        size_++;
        last_index_++;
        if (capacity_==size_) {
            MemoryUp();
        }
        array_[last_index_]=value;
    }
    void Prepend(T value){ // Метод добавления элемента в начало массива
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
    void AppendAll(const Array_List<T> that){ // Метод добавления всех элементов одного списка в конец другого
        if (that.size_==0) {
            return exit(1);
        }
        int size_all=size_+that.size_;
        if (capacity_ == size_all) {
            while (capacity_<=size_all) {
                MemoryUp();
            }
        }
        for (int i = 0; i < that.size_; i++) {
            Append(that.array_[i]);
        }
        size_=size_all;
        if (capacity_ / 4 >= size_all) {
            MemoryDown();
        }
    }
    void InsertAt(int index, T value) { // Вставка элемента после индекса
        if ((index >= 0) && (index <= last_index_)) {
            size_++;
            last_index_++;
            if (capacity_ == size_) {
                MemoryUp();
            }
            for (int i = last_index_; i > (index+1); i--){
                array_[i]=array_[i-1];
            }
            array_[index+1]=value;
        }
    }
    void RemoveAt(int index) { // Удаление элемента по индексу
        if (index >=0 && index <= last_index_){
            size_--;
            last_index_--;
            for (int i = index; i < size_ ; i++) {
                array_[i] = array_[i + 1];
            }
            if (capacity_ / 4 >= size_){
                MemoryDown();
            }
        }
    }
    void RemoveAll() { // Удаление всех элементов из списка
        last_index_=-1;
        capacity_=2;
        size_=0;
        delete array_;
        array_=new T[capacity_];
    }
    T Pop(){ // Удаление и возвращение последнего элемента
        if (size_ == 0) {
            exit(1);
        }
        T value=array_[last_index_];
        size_--;
        last_index_--;
        if (capacity_/4 >= size_){
            MemoryDown();
        }
        return value;
    }
    T Dequeue() { // Удаление и возвращение 1-ого элемента
        if (size_ == 0){
            exit(1);
        }
        T value=array_[0];
        size_--;
        last_index_--;
        for (int i=0; i < size_; i++){
            array_[i]=array_[i+1];
        }
        if (capacity_/4 == size_){
            MemoryDown();
        }
        return value;
        }
    int Length() const{ // Нахождение длины списка
        return size_;
    }
    T GetAt(int index) { // Взятие элемента по индексу
        if (size_ <= 0 || index < 0 || index > last_index_) {
            exit(-1);
        }
        return array_[index];
    }
};