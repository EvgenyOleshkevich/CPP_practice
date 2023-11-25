#pragma once
#ifdef stepik
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
#include "leetcode.h"
using namespace std;

namespace part_one {
    struct A {
        virtual ~A() { cout << "A" << endl; }
    };

    struct B : A {
        ~B() { cout << "B" << endl; }
    };

    struct C : B {
        ~C() { cout << "C" << endl; }
    };

    struct Expression {};

    struct SharedPtr
    {
        explicit SharedPtr(Expression* ptr = 0) : ptr_(ptr), count(0) {
            if (ptr_ != nullptr)
                count = new int(1);
        }
        ~SharedPtr() {
            if (count) {
                --* count;
                if (*count == 0) {
                    delete ptr_;
                    delete count;
                }
            }
        }
        SharedPtr(const SharedPtr& shared) : ptr_(shared.ptr_), count(shared.count) {
            if (count != nullptr)
                ++* count;
        }
        SharedPtr& operator=(const SharedPtr& shared) {
            if (count == shared.count)
                return *this;

            if (count != nullptr) {
                --* count;
                if (*count <= 0) {
                    delete ptr_;
                    delete count;
                }
            }

            count = shared.count;
            ptr_ = shared.ptr_;
            if (shared.ptr_ != nullptr)
                ++* count;

            return *this;
        }
        Expression* get() const {
            return ptr_;
        }
        void reset(Expression* ptr = 0) {
            if (ptr == ptr_)
                return;
            if (count != nullptr) {
                --* count;
                if (*count == 0) {
                    delete ptr_;
                    delete count;
                }
            }

            ptr_ = ptr;
            if (ptr_ != nullptr)
                count = new int(1);
            else
                count = nullptr;
        }
        Expression& operator*() const {
            return *ptr_;
        }
        Expression* operator->() const {
            return ptr_;
        }

        Expression* ptr_;
        int* count;
    };

    template <typename T>
    class Array
    {
    public:
        explicit Array(size_t size, const T& value = T()) : size_type(sizeof(T)), size_(size) {
            array = (T*)(new char[size_ * size_type]);
            for (size_t i = 0; i < size_; ++i)
                new (array + i) T(value);
        }
        Array() : size_type(sizeof(T)), size_(0), array(nullptr)
        {}
        Array(const Array& arr) : size_type(sizeof(T)), size_(arr.size_) {
            array = (T*)(new char[size_ * size_type]);
            for (size_t i = 0; i < size_; ++i)
                new (array + i) T(arr.array[i]);
        }

        ~Array() {
            clearMemory();
        }

        Array& operator=(const Array& arr) {
            if (array == arr.array)
                return *this;

            clearMemory();

            size_ = arr.size_;
            array = (T*)(new char[size_ * size_type]);
            for (size_t i = 0; i < size_; ++i)
                new (array + i) T(arr.array[i]);

            return *this;
        }

        size_t size() const {
            return size_;
        }

        T& operator[](size_t i) {
            return array[i];
        }
        const T& operator[](size_t i) const {
            return array[i];
        }
    private:
        size_t size_type;
        size_t size_;
        T* array;

        void clearMemory() {
            for (int i = 0; i < size_; ++i) {
                array[i].~T();
            }
            delete[](char*) array;
        }
    };

    struct ICloneable
    {
        virtual ICloneable* clone() const = 0;
        virtual ~ICloneable() { }
    };

    template <typename T>
    struct ValueHolder : ICloneable {
        explicit ValueHolder(const T& data) : data_(data) {}
        ValueHolder(const ValueHolder& holder) : data_(holder.data_) {}

        ValueHolder& operator=(const ValueHolder& holder) {
            return *this;
        }

        ICloneable* clone() const {
            return new ValueHolder(data_);
        }

        T data_;
    };

    class Any
    {
    public:
        ICloneable* value;

        Any() : value(nullptr) {}
        template <typename T>
        Any(const T& object) : value(new ValueHolder<T>(object)) {}
        Any(const Any& any) : value(nullptr) {
            if (any.value)
                value = any.value->clone();
        }
        ~Any() {
            delete value;
        }

        Any& operator=(const Any& any) {
            if (value == any.value)
                return *this;

            delete value;
            value = nullptr;
            if (any.value)
                value = any.value->clone();
            return *this;
        }


        template <typename T>
        T* cast() {
            auto ret = dynamic_cast<ValueHolder<T>*>(value);
            if (ret)
                return &ret->data_;
            else
                return nullptr;
        }

    };

    template <typename A, typename B>
    struct SameType {
        static const bool value = false;
    };

    template <typename A>
    struct SameType<A, A> {
        static const bool value = true;
    };

    template <typename T, size_t size>
    size_t array_size(const T(&arr)[size]) {
        return size;
    }

}

#endif // stepik