#pragma once

#include <cstdlib>
#include <iostream>

// В узле списка хранится само значение value и указатель на следующий узел.
// Эту структуру пользователи списка не должны видеть, так как она относится к внутренней реализации.
template<typename T>
struct Node {
    T value_; // само значение, которое хранит узел
    struct Node<T> *next_; // указатель на следующий узел
};

namespace Linked {
    template<typename T>
    class Linked_List {
    private:
        Node<T> *head_ = nullptr;
        Node<T> *tail_ = nullptr;
    public:
        // Метод добавления элемента в конец списка
        void Append(T value) {
            Node<T> *tmp = new Node<T>;
            tmp->next_ = nullptr;
            tmp->value_ = value;
            if (head_ == nullptr) {
                head_ = tmp;
                tail_ = tmp;
            } else {
                tail_->next_ = tmp;
                tail_ = tmp;
            }
        }

        // Метод добавления элемента в начало списка
        void Prepend(T value) {
            Node<T> *tmp = new Node<T>;
            tmp->value_ = value;
            tmp->next_ = nullptr;
            if (head_ == nullptr) {
                head_ = tmp;
                tail_ = tmp;
            } else {
                tmp->next_ = head_;
                head_ = tmp;
            }
        }

        // Метод добавления одного списка в конец другого
        void AppendAll(const Linked_List<T> &that) {
            for (int i = 0; i < that.Length(); i++) {
                Append(that[i]);
            }
        }

        // Метод добавления элемента после индекса
        void InsertAt(int index,T value) {
            if (index < 0 || index >= Length()) {
                exit(-1);
            }
            Node<T> *tmp = head_;
            for (int i = 0; i < index; i++) {
                tmp = tmp->next_;
            }
            Node<T> *that = new Node<T>;
            that->value_ = value;
            that->next_ = tmp->next_;
            tmp->next_ = that;
            if (index == (Length() - 2)) {
                tail_ = that;
            }
        }

        // Метод удаления элемента по индексу
        void RemoveAt(int index) {
            Node<T> *tmp = head_;
            if (index == 0) {
                head_ = head_->next_;
                tmp->next_ = nullptr;
                delete tmp;
                return;
            }
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next_;
            }
            Node<T> *tmp2 = tmp->next_;
            tmp->next_ = tmp2->next_;
            delete tmp2;
            if (index == Length()) {
                tail_ = tmp;
            }
        }

        // Метод удаления всех элементов
        void RemoveAll() {
            Node<T> *tmp = head_;
            for (int i = 0; i < Length() - 1; i++) {
                tmp = tmp->next_;
                delete head_;
                head_ = tmp;
            }
            tail_ = nullptr;
            head_ = nullptr;
            delete tmp;
        }

        // Метод удаления элемента с конца списка, возвращает значение этого элемента
        T Pop() {
            if (Length() == 0) {
                exit(-1);
            }
            T value = tail_->value_;
            Node<T> *tmp = head_;
            for (int i = 0; i < Length() - 2; i++) {
                tmp = tmp->next_;
            }
            delete tail_;
            tmp->next_ = nullptr;
            tail_ = tmp;
            return value;
        }

        // Метод удаления элемента с начала списка, возвращает значение этого элемента
        T Dequeue() {
            if (head_ == nullptr) {
                exit(-1);
            }
            T value = head_->value_;
            Node<T> *tmp = head_->next_;
            delete head_;
            head_ = tmp;
            if (Length() == 1) {
                tail_ = tmp;
            }
            return value;
        }

        // Метод определения длины списка
        int Length() const{
            if (head_ == nullptr) {
                return 0;
            }
            Node<T> *tmp = head_;
            int count = 0;
            while (tmp != nullptr) {
                count++;
                tmp = tmp->next_;
            }
            return count;
        }

        // Метод взятия значения по индексу
        T& operator[](int index) const{
            if (head_ == nullptr || index >= Length()) {
                exit(-1);
            }
            Node<T> *tmp = head_;
            for (int i = 0; i < index; i++) {
                tmp = tmp->next_;
            }
            return tmp->value_;
        }
    };
}