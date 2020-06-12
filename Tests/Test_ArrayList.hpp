#pragma once

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <memory>

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

static void Test_HardArrayList(){
    Array_List<std::unique_ptr<int>> arr1;
    assert(arr1.Length() == 0);
    arr1.Append(std::make_unique<int>(1));
    assert(arr1.Length() == 1);
    assert(*arr1[0].get() == 1);
    arr1.Prepend(std::make_unique<int>(2));
    assert(*arr1[0].get() == 2);
    assert(*arr1[1].get() == 1);
    arr1.InsertAt(0, std::make_unique<int>(3));
    assert(*arr1[1].get() == 3);
    assert(2 == *arr1.Dequeue().get());
    assert(1 == *arr1.Pop().get());
    arr1.InsertAt(0, std::make_unique<int>(4));
    assert(*arr1[1].get() == 4);
    arr1.Append(std::make_unique<int>(5));
    arr1.RemoveAt(1);
    assert(*arr1[1].get() == 5);
    for (auto& el: arr1) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;
    for (auto el = arr1.begin(); el != arr1.end(); el++) {
        std::cout << **el << " ";
    }
    std::cout << std::endl;
    Array_List<std::unique_ptr<int >> arr2(std::move(arr1));
    assert(*arr2[1].get() == 5);
    Array_List<std::unique_ptr<int >> arr3;
    arr3 = std::move(arr2);
    assert(*arr3[0].get() == 3);
}