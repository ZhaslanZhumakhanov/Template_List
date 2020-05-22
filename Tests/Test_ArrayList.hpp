#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../Include/Array_List.hpp"


static void Test_ArrayList() {
    Array_List<int> list;
    Array_List<int> b;
    b.Append(5);
    b.Append(10);
    b.Append(11);
    assert(0 == list.Length());
    list.Append(42);
    assert(1 == list.Length());
    assert(42 == list[0]);
    list.Prepend(1);
    assert(1 == list[0]);
    list.AppendAll(b);
    assert(11 == list[4]);
    assert(10 == list[3]);
    assert(42 == list[1]);
    list.InsertAt(1, 123);
    assert(123 == list[2]);
    assert(5 == list[3]);
    assert(42 == list[1]);
    list.RemoveAt(2);
    assert(11 == list[4]);
    assert(10 == list[3]);
    assert(42 == list[1]);
    b.RemoveAll();
    b.Append(10);
    b.Append(11);
    b.Append(12);
    assert(10 == b[0]);
    assert(11 == b[1]);
    assert(12 == b[2]);
    assert(12 == b.Pop());
    assert(10 == b.Dequeue());
    assert(1 == b.Length());
    assert(11 == b[0]);
    Array_List<int> arr = {1, 2, 3, 4, 5};
    Array_List<int> arr2 = arr;
    assert(3 == arr2[2]);
    arr2[2]=10;
    assert(3 == arr[2]);
    for (auto el = arr.begin(); el != arr.end(); el++) {
        std::cout << *el << " ";
    }
}
