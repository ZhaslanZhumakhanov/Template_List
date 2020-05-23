#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../Include/Linked_List.hpp"

static void Test_LinkedList(){
    Linked_List<int> list;
    assert(0 == list.Length());
    list.Append(42); // ([42]) - список
    assert(1 == list.Length());
    assert(42 == list[0]);
    list.Prepend(1); // ([1] [42])
    assert(1 == list[0]);
    assert(42 == list[1]);
    list.RemoveAll(); // ()
    list.Prepend(2); // ([2])
    assert(2 == list[0]);
    list.RemoveAll(); // ()
    assert(0 == list.Length());
    list.Append(1); // ([1])
    list.InsertAt(0,2); // ([1] [2])
    assert(2 == list[1]);
    assert(1 == list[0]);
    // list.InsertAt(2,3);
    // assert(1 == list[0]); Выход за границы списка
    Linked_List<int> list2;
    list2.AppendAll(list); // ([1] [2])
    assert(2 == list[1]);
    list.AppendAll(list2); // ([1] [2] [1] [2])
    assert(2 == list[3]);
    Linked_List<int> list3;
    list.AppendAll(list3); // ([1] [2] [1] [2])
    // assert(2 == list[4]); Выход за границы списка
    // assert(0 == list2.Length()); Нахождение длины несуществующего списка
    list.RemoveAt(3); // ([1] [2] [1])
    assert(3 == list.Length());
    list.RemoveAt(0); // ([2] [1])
    assert(2 == list[0]);
    //list.RemoveAt(2); //Выход за границы списка
    int value=list.Pop(); // ([2])
    assert(1 == value);
    value=list.Dequeue();
    assert(2 == value);
    Linked_List<int> list4;
    list4.Append(1);
    assert(1 == list4[0]);
    list4[0]=10;
    assert(10 == list4[0]);
    Linked_List<int> vector = {1,2,3,4,5};
    assert(3 == vector[2]);
    Linked_List<int> vector_copy=vector;
    assert(3 == vector_copy[2]);
    vector_copy[2]=10;
    assert(10 == vector_copy[2]);
    assert(3 == vector[2]);
    for (auto &element: vector){
        std::cout << element << " ";
    }
}