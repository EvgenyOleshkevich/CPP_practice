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
namespace test {

    class Test {
    public:
        int* value;
        Test() {
            cout << "constructor" << endl;
            value = new int(0);
        }
        ~Test() {
            cout << "destructor" << endl;
            if (value)
                cout << "value was: " << *value;
            else
                cout << "value was nullptr";
            delete value;
        }

        Test(const Test& test) {
            cout << "copy constructor" << endl;
            value = new int(*test.value);
        }
        Test(Test&& test) noexcept {
            cout << "move constructor" << endl;
            value = test.value;
            test.value = nullptr;
        }

        Test operator=(const Test& test) {
            cout << "copy operator=" << endl;
            if (value == test.value)
                return *this;

            delete value;
            value = new int(*test.value);
        }
        Test operator=(Test&& test) noexcept {
            cout << "move operator=" << endl;
            if (value == test.value)
                return *this;

            value = test.value;
            test.value = nullptr;
        }
    };

    Test get_test(int value) {
        Test t;
        *t.value = value;
        return t;
    }

    Test send_value_test(Test t, int value) {
        *t.value = value;
        return t;
    }

    void send_const_test(const Test& t, int value) {
        *t.value = value;
    }

    void send_ref_test(Test& t, int value) {
        *t.value = value;
    }
}

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