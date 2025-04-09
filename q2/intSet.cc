#include "intSet.h"
#include <iostream>

intSet::intSet() {
    capacity = 4;
    size = 0;
    data = new int[capacity];
}

intSet::intSet(const intSet& is) { //copy constructor, why dont we need delete? bc the object has not alr been created
    capacity = is.capacity;
    size = is.size;

    data = new int[capacity];
    for(int i = 0; i < size; ++i) {
        data[i] = is.data[i];
    }
}

intSet::intSet(intSet &&is) { //move
    size = is.size;
    capacity = is.capacity;
    data = is.data;
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}

intSet& intSet::operator=(const intSet& is) { //copy
    if (this == &is) {
        return *this;
    }
    delete[] data;

    capacity = is.capacity;
    size = is.size;
    data = new int[capacity];

    for(int i = 0; i < size; ++i) {
        data[i] = is.data[i];
    }
    return *this;
}

intSet& intSet::operator=(intSet &&is) { //move
    if (this == &is) {
        return *this;
    }
    delete[] data;

    capacity = is.capacity;
    size = is.size;
    data = is.data;

    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;

    return *this;
}

intSet::~intSet() {
    delete[] data;
    data = nullptr; //good practice
    capacity = 0;
    size = 0;
}

intSet intSet::operator|(const intSet &other) const {
    // Set union
    intSet unionSet;
    for(int i = 0; i < size; ++i) {
        unionSet.add(data[i]);
    }
    for(int i = 0; i < other.size; ++i) {
        unionSet.add(other.data[i]);
    }
    return unionSet; //return by value
}

intSet intSet::operator&(const intSet &other) const {
    // Set intersection.
    intSet intersectSet;
    intSet smallerSet = size >= other.size ? *this : other;
    intSet largerSet = size > other.size ? *this : other;
    for(int i = 0; i < smallerSet.size; ++i) {
        if(largerSet.contains(smallerSet.data[i])) {
            intersectSet.add(smallerSet.data[i]);
        }
    }
    return intersectSet;
}

bool intSet::operator==(const intSet &other) const {
    if(isSubset(other) && other.isSubset(*this)) {
        return true;
    }
    return false;
}

bool intSet::isSubset(const intSet &s) const {
    for(int i = 0; i < size; ++i) {
        if(!s.contains(data[i])) return false;
    }
    return true;
}

bool intSet::contains(int e) const { // garbage bin search
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) /2;
        if(data[mid] == e) {
            return true;
        }
        else if (data[mid] < e) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

void intSet::add(int e) {
    if(!contains(e)) {
        if(capacity == size) { //looks like we need to double here...
            int *new_data = new int[capacity*2]; //why did it complain when using []
            for(int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity *= 2;
        }
        int i = size-1;
        while(i >= 0 && data[i] > e) {
            data[i+1] = data[i];
            --i;
        }
        data[i+1] = e;
        ++size;
    }
}

void intSet::remove(int e) {
    if (!contains(e)) return;
    int i = 0;
    while(i < size && data[i] != e) {
        ++i;
    }
    if(i < size) {
        // Shift elements to the left to remove the element
        for (int j = i ; j < size - 1; ++j) {
            data[j] = data[j+1];
        }
        --size;
    }
}

std::ostream& operator<<(std::ostream& out, const intSet& is) { // output operator for intSet
    //why is this a friend? review what that means
    out << '(';
    for(int i = 0; i < is.size; ++i) {
        out << is.data[i];
        if(!(i == is.size-1)) {
            out << ", ";
        }
    }
    out << ')';
    return out; //this will allow for chaining!
}
