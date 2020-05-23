#pragma once

#include <cstdlib>
#include <iostream>

template <typename T>
class Array_List{
private:
    int capacity_; // Ёмкость списка: реальный размер массива
    int size_; // Кол-во элементов в массиве
    int last_index_; // Последний занятый индекс в массиве
    T* array_; // Динамический массив, в  котором хранятся все данные
    // Метод увеличения памяти для массива
    void MemoryUp(){
        capacity_*=2;
        T* new_array;
        new_array=new T[capacity_];
        for (int i=0; i<size_; i++){
            new_array[i]=array_[i];
        }
        delete array_;
        array_=new_array;
    }
    // Метод сокращения памяти для массива
    void MemoryDown(){
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
    // Конструктор
    explicit Array_List(int capacity=2) : capacity_(capacity), size_(0), last_index_(-1){
        array_=new T[capacity];
    }

    // Конструктор инициализации
    Array_List(std::initializer_list<T> elements) {
        capacity_ = elements.size() * 2;
        size_ = elements.size();
        last_index_ = elements.size() - 1;
        array_ = static_cast<T*>(new T[capacity_]);
        int i = 0;
        for (auto &element : elements) {
            array_[i]=element;
            i++;
        }
    }

    // Конструктор копирования
    Array_List(const Array_List<T> &that){
        capacity_=that.capacity_;
        size_=that.size_;
        last_index_=that.last_index_;
        array_=new T[capacity_];
        for (int i=0; i<size_; i++){
            array_[i]=that.array_[i];
        }
    }


    // Метод добавления элемента в конец массива
    void Append(T value){
        size_++;
        last_index_++;
        if (capacity_==size_) {
            MemoryUp();
        }
        array_[last_index_]=value;
    }

    // Метод добавления элемента в начало массива
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

    // Метод добавления всех элементов одного списка в конец другого
    void AppendAll(const Array_List<T> that){
        if (that.size_==0) {
            exit(1);
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

    // Вставка элемента после индекса
    void InsertAt(int index, T value) {
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

    // Удаление элемента по индексу
    void RemoveAt(int index) {
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

    // Удаление всех элементов из списка
    void RemoveAll() {
        last_index_=-1;
        capacity_=2;
        size_=0;
        delete array_;
        array_=new T[capacity_];
    }

    // Удаление и возвращение последнего элемента
    T Pop(){
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

    // Удаление и возвращение 1-ого элемента
    T Dequeue() {
        if (size_ == 0) {
            exit(1);
        }
        T value = array_[0];
        size_--;
        last_index_--;
        for (int i = 0; i < size_; i++) {
            array_[i] = array_[i + 1];
        }
        if (capacity_ / 4 == size_) {
            MemoryDown();
        }
        return value;
    }

    // Нахождение длины списка
    int Length() const{
        return size_;
    }

    // Взятие элемента по индексу
    T& operator [](int index) const{
        if (size_ <= 0 || index < 0 || index > last_index_) {
            exit(-1);
        }
        return array_[index];
    }

    // Возвращает итератор, указывающий на начало списка
    T *begin() const {
        return array_;
    }

    // Возвращает итератор, указывающий на конец списка
    T *end() const {
        return array_+size_;
    }

    // Деструктор
    ~Array_List(){
        capacity_=0;
        size_=0;
        last_index_=-1;
        delete array_;
        std::cout << "~Array_List" << std::endl;
    }
};