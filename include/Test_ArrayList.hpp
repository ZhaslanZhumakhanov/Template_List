#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "Array_List.hpp"


static void Test_ArrayList() {
    Array_List<int> list;
    Array_List<int> b;
    b.Append(5);
    b.Append(10);
    b.Append(11);
    assert(0 == list.Length());
    list.Append(42);
    assert(1 == list.Length());
    assert(42 == list.GetAt(0));
    list.Prepend(1);
    assert(1 == list.GetAt(0));
    list.AppendAll(b);
    assert(11 == list.GetAt(4));
    assert(10 == list.GetAt(3));
    assert(42 == list.GetAt(1));
    list.InsertAt(1, 123);
    assert(123 == list.GetAt(2));
    assert(5 == list.GetAt(3));
    assert(42 == list.GetAt(1));
    list.RemoveAt(2);
    assert(11 == list.GetAt(4));
    assert(10 == list.GetAt(3));
    assert(42 == list.GetAt(1));
    b.RemoveAll();
    b.Append(10);
    b.Append(11);
    b.Append(12);
    assert(10 == b.GetAt(0));
    assert(11 == b.GetAt(1));
    assert(12 == b.GetAt(2));
    assert(12 == b.Pop());
    assert(10 == b.Dequeue());
    assert(1 == b.Length());
    assert(11 == b.GetAt(0));
}
