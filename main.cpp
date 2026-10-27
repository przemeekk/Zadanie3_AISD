#include <iostream>
#include <cassert>
#include "arraylist.hpp"

int main() {
    ArrayList<int> list(5);
    assert(list.empty() == true);
    assert(list.full() == false);
    assert(list.size() == 0);
    assert(list.max_size() == 5);

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    assert(list.size() == 3);
    assert(list.front() == 5);
    assert(list.back() == 20);
    assert(list[0] == 5);
    assert(list[1] == 10);
    assert(list[2] == 20);

    list.insert(1, 7);
    assert(list.size() == 4);
    assert(list[1] == 7);
    assert(list[2] == 10);

    list.erase(1);
    assert(list.size() == 3);
    assert(list[1] == 10);

    assert(list.index(5) == 0);
    assert(list.index(10) == 1);
    assert(list.index(20) == 2);
    assert(list.index(99) == -1);

    list.pop_front();
    assert(list.size() == 2);
    assert(list.front() == 10);

    list.pop_back();
    assert(list.size() == 1);
    assert(list.back() == 10);

    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    assert(list.size() == 4);
    assert(list.full() == false);

    list.push_back(50);
    assert(list.full() == true);

    list.clear();
    assert(list.empty() == true);
    assert(list.size() == 0);

    list.push_back(30);
    list.push_back(10);
    list.push_back(20);
    list.sort();
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);

    list.reverse();
    assert(list[0] == 30);
    assert(list[1] == 20);
    assert(list[2] == 10);

    ArrayList<int> list2(list);
    assert(list2.size() == list.size());
    assert(list2[0] == list[0]);

    ArrayList<int> list3;
    list3 = list2;
    assert(list3.size() == list2.size());
    assert(list3[1] == list2[1]);

    ArrayList<int> sorted1(5);
    sorted1.push_back(1);
    sorted1.push_back(3);
    sorted1.push_back(5);

    ArrayList<int> sorted2(5);
    sorted2.push_back(2);
    sorted2.push_back(4);

    sorted1.merge(sorted2);
    assert(sorted1.size() == 5);
    assert(sorted1[0] == 1);
    assert(sorted1[1] == 2);
    assert(sorted1[2] == 3);
    assert(sorted1[3] == 4);
    assert(sorted1[4] == 5);
    assert(sorted2.empty() == true);

    return 0;
}