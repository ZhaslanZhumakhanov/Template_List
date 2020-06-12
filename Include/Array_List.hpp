#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>

template <typename T>
class Array_List{
private:
    int capacity_; // Ёмкость списка: реальный размер массива
    int size_; // Кол-во элементов в массиве
    int last_index_; // Последний занятый индекс в массиве
    T* array_; // Динамический массив, в  котором хранятся все данные
    // Метод увеличения памяти для массива
    void MemoryUp(){
        capacity_ *= 2;
        T* new_array = static_cast<T*>(::operator new(sizeof(T)*capacity_));
        for (int i=0; i < size_; i++){
            ::new(new_array+i) T(std::move(array_[i]));
        }
        delete array_;
        array_ = new_array;
    }
    // Метод сокращения памяти для массива
    void MemoryDown(){
        capacity_ /= 2;
        T* new_array = static_cast<T*>(::operator new(sizeof(T)*capacity_));
        for (int i=0; i<size_; i++){
            ::new(new_array+i) T(std::move(array_[i]));
        }
        delete array_;
        array_ = new_array;
    }
public:
    // Конструктор
    explicit Array_List(int capacity=2) : capacity_(capacity), size_(0), last_index_(-1){
        if (capacity < 2){
            capacity_ = 2;
        }
        array_ = static_cast<T*>(::operator new(sizeof(T)*capacity_));
    }

    // Конструктор инициализации
    Array_List(std::initializer_list<T> elements) {
        capacity_ = elements.size() * 2;
        size_ = elements.size();
        last_index_ = elements.size() - 1;
        array_ = static_cast<T*>(::operator new(sizeof(T)*capacity_));
        int i = 0;
        for (auto &element : elements) {
            ::new(array_+i) T(element);
            i++;
        }
    }

    // Конструктор копирования
    Array_List(const Array_List<T> &that){
        capacity_=that.capacity_;
        size_=that.size_;
        last_index_=that.last_index_;
        array_=static_cast<T*>(::operator new(sizeof(T)*capacity_));
        for (int i=0; i<size_; i++){
            ::new(array_+i) T(that.array_[i]);
        }
    }

    // Оператор присваивания копированием
    Array_List<T>& operator = (const Array_List<T> &that){
        if (this != &that){
            for (int i=0; i < this->size_; i++) {
                array_[i].~T();
            }
            ::operator delete(array_);
            capacity_=that.capacity_;
            size_=that.size_;
            last_index_=that.last_index_;
            array_=static_cast<T*>(::operator new(sizeof(T)*capacity_));
            for (int i=0; i<size_; i++){
                ::new(array_+i) T(that.array_[i]);
            }
        }
        return *this;
    }

    // Конструктор перемещения
    Array_List(Array_List<T>&& that) noexcept{
        capacity_ = that.capacity_;
        size_ = that.size_;
        last_index_ = that.last_index_;
        array_ = std::move(that.array_);
        that.capacity_ = 2;
        that.size_ = 0;
        that.last_index_ = -1;
        that.array_ = static_cast<T*>(::operator new(sizeof(T)*that.capacity_));
    }

    // Оператор присваивания перемещением
    Array_List<T>& operator = (Array_List<T> &&that) noexcept{
        if (this != &that){
            for (int i=0; i < this->size_; i++) {
                array_[i].~T();
            }
            ::operator delete(array_);
            capacity_=that.capacity_;
            size_=that.size_;
            last_index_=that.last_index_;
            array_=std::move(that.array_);
            that.capacity_ = 2;
            that.size_ = 0;
            that.last_index_ = -1;
            that.array_ = static_cast<T*>(::operator new(sizeof(T)*that.capacity_));
        }
        return *this;
    }

    // Метод добавления элемента в конец массива
    void Append(const T& value){
        size_++;
        last_index_++;
        if (capacity_==size_) {
            MemoryUp();
        }
        ::new(array_+last_index_) T(value);
    }
    void Append(T&& value){
        size_++;
        last_index_++;
        if (capacity_==size_) {
            MemoryUp();
        }
        ::new(array_+last_index_) T(std::move(value));
    }

    // Метод добавления элемента в начало массива
    void Prepend(const T& value){
        size_++;
        last_index_++;
        if (capacity_==size_){
            MemoryUp();
        }
        for (int i=0; i<(size_-1); i++){
            ::new(array_+i+1) T(array_[i]);
        }
        ::new(array_) T(value);
    }
    void Prepend(T&& value){
        size_++;
        last_index_++;
        if (capacity_==size_){
            MemoryUp();
        }
        for (int i=0; i<(size_-1); i++){
            ::new(array_+i+1) T(std::move(array_[i]));
        }
        ::new(array_) T(std::move(value));
    }

    // Метод добавления всех элементов одного списка в конец другого
    void AppendAll(const Array_List<T>& that){
        for (int i=0; i < that.size_; i++){
            Append(that.array_[i]);
        }
    }
    void AppendAll(Array_List<T>&& that) = delete;

    // Вставка элемента после индекса
    void InsertAt(int index,const T& value) {
        assert(index >= 0 && index <= last_index_);
        size_++;
        last_index_++;
        if (capacity_ == size_) {
            MemoryUp();
        }
        for (int i = last_index_; i > (index+1); i--){
            ::new(array_+i) T(array_[i-1]);
        }
        ::new(array_+index+1) T(value);
    }
    void InsertAt(int index,T&& value) {
        assert(index >= 0 && index <= last_index_);
        size_++;
        last_index_++;
        if (capacity_ == size_) {
            MemoryUp();
        }
        for (int i = last_index_; i > (index+1); i--){
            ::new(array_+i) T(std::move(array_[i-1]));
        }
        ::new(array_+index+1) T(std::move(value));
    }

    // Удаление элемента по индексу
    void RemoveAt(int index) {
        assert(index >=0 && index <= last_index_);
        size_--;
        last_index_--;
        array_[index].~T();
        for (int i = index; i < size_ ; i++) {
            ::new(array_+i) T(std::move(array_[i+1]));
        }
        if (capacity_ / 4 >= size_){
            MemoryDown();
        }
    }

    // Удаление всех элементов из списка
    void RemoveAll() {
        for (int i=0; i < size_; i++){
            array_[i].~T();
        }
        ::operator delete(array_);
        last_index_=-1;
        capacity_=2;
        size_=0;
        array_=static_cast<T*>(::operator new(sizeof(T)*capacity_));
    }

    // Удаление и возвращение последнего элемента
    T Pop(){
        assert(size_ != 0);
        T value=std::move(array_[last_index_]);
        size_--;
        last_index_--;
        if (capacity_/4 >= size_){
            MemoryDown();
        }
        return value;
    }

    // Удаление и возвращение 1-ого элемента
    T Dequeue() {
        assert(size_ != 0);
        T value = std::move(array_[0]);
        size_--;
        last_index_--;
        for (int i = 0; i < size_; i++) {
            ::new(array_+i) T(std::move(array_[i + 1]));
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
    const T& operator [](int index) const{
        assert(size_>0 && index>=0 && index<=last_index_);
        return array_[index];
    }
    T& operator [](int index){
        assert(size_>0 && index>=0 && index<=last_index_);
        return array_[index];
    }

    // Возвращает итератор, указывающий на начало списка
    T* begin() const {
        return array_;
    }

    // Возвращает итератор, указывающий на конец списка
    T* end() const {
        return array_+size_;
    }

    // Деструктор
    ~Array_List(){
        for (int i=0; i<size_; i++){
            array_[i].~T();
        }
        ::operator delete(array_);
        std::cout << "~Array_List" << std::endl;
    }
};