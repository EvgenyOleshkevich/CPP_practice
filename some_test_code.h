#pragma once

#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <functional>
using namespace std;

class A {
public:
    A() {}
    virtual ~A() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    B() {}
    ~B() {
        std::cout << "B" << std::endl;
    }
};