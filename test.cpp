// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
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

namespace lect_7_2_1 {
    struct Base {
        Base() { std::cout << "Base : created \n"; }
        void method() const { std::cout << "Base : method \n"; }
        virtual void virtual_method() const { std::cout << "Base : virtual_method \n"; }
    };

    struct D1 : Base {
        D1() { std::cout << "D1 : created \n"; }
        void method() const { std::cout << "D1 : metod  \n"; }
        void virtual_method() const { std::cout << "D1 : virtual_method \n"; }
    };

    struct D2 : Base {
        D2() { std::cout << "D2 : created \n"; }
        void method() const { std::cout << "D2 : metod  \n"; }
        void virtual_method() const { std::cout << "D2 : virtual_method \n"; }
    };

    struct D3 : D1, D2 {
        D3() { std::cout << "D3 : created \n"; }
    };

    Base const* D1BaseToD2Base(Base const* base)
    {
        return dynamic_cast<const D2*>(dynamic_cast<const D3*>(base));
    }

    Base const* static_D1BaseToD2Base(Base const* base) // withot virtual methods
    {
        const D1* d1 = static_cast<const D1*>(base);
        const D3* d3 = static_cast<const D3*>(d1);
        return static_cast<const D2*>(d3);
    }
}

namespace lect_7_2_2 {
    struct Unit
    {
        explicit Unit(size_t id)
            : id_(id)
        {}

        size_t id() const { return id_; }

    private:
        size_t id_;
    };

    // базовый класс для животных
    struct Animal : virtual Unit
    {
        // name хранит название животного
        // "bear" для медведя
        // "pig" для свиньи
        Animal(std::string const& name, size_t id) : Unit(id), name_(name) {}

        std::string const& name() const { return name_; }
    private:
        std::string name_;
    };

    // класс для человека
    struct Man : virtual Unit
    {
        explicit Man(size_t id) : Unit(id) {}
        // ...
    };

    // класс для медведя
    struct Bear : Animal
    {
        explicit Bear(size_t id) : Unit(id), Animal("bear", id) {}
    };

    // класс для свиньи
    struct Pig : Animal
    {
        explicit Pig(size_t id) : Unit(id), Animal("pig", id) {}
    };

    // класс для челмедведосвина
    struct ManBearPig : Man, Bear, Pig
    {
        ManBearPig(size_t id) : Unit(id), Man(id), Bear(id), Pig(id) {}
    };
}

namespace lect_7_5_1 {
    /*
        declare ComplexFunction as function
        (int, pointer to function (double) returning int)
        returning pointer to function (pointer to const char) returning pointer to int
    */
    typedef int* (*ComplexFunction1(int, int (*)(double)))(const char*);
    // same
    typedef int (*func1)(double);
    typedef int* (*ComplexFunction2(int, func1))(const char*);
    

    /*
        declare ComplexFunction as pointer to function
        (int, pointer to function (double) returning int)
        returning pointer to function (pointer to const char) returning pointer to int
    */
    typedef int* (*f)(const char*);
    typedef f(*ComplexFunctionPtr1)(int, int (*)(double));
    // same
    typedef int* (*(*ComplexFunctionPtr2)(int, int (*) (double)))(const char*);
}

namespace lect_7_6_1 {
    template<class T, class V>
    bool compare(const T& a, const T& b, V (T::* mptr)() const)
    {
        return (a.*mptr)() < (b.*mptr)();
    }
}

namespace lect_8_1_1 {
    void print_values(std::ostream& os) {}

    template <class T, class... Args>
    void print_values(std::ostream& os, const T& value, Args... args)
    {
        os << typeid(value).name() << ": " << value;
        print_values(os, args...);
    }
}

namespace lect_8_3_1 {
    template<int i1, int i2, class... Types>
    auto to_pair_cpp_11(std::tuple<Types...> t) -> decltype(std::make_pair(std::get<i1>(t), std::get<i2>(t)))
    {
        return std::make_pair(std::get<i1>(t), std::get<i2>(t));
    }
    // c++ 11
    // or
    // c++ 14
    template<int i1, int i2, class... Types>
    auto to_pair_cpp_14(std::tuple<Types...> t)
    {
        return std::make_pair(std::get<i1>(t), std::get<i2>(t));
    }
    // or
   // c++ 14
    template<int i1, int i2, class... Types>
    auto to_pair_cpp_14_for_ref(std::tuple<Types...> t) -> decltype(auto)
    {
        return std::make_pair(std::get<i1>(t), std::get<i2>(t));
    }
    
}

namespace lect_8_3_3 {
    template<class F>
    void for_each_int(int* p, int* q, F f)
    {
        for (; p != q; ++p)
            f(*p);
    }

    auto square_fun = [](int& x) { x *= x; };
}

namespace lect_8_3_4 {
    template<class F>
    int* find_if(int* p, int* q, F f)
    {
        for (; p != q; ++p)
            if (f(*p))
                return p;
        return q;
    }

    // определение переменной
    auto gen_finder = [](int* p, int* q) {
        return [p, q](int value) {
            for (int* i = p; i != q; ++i)
                if (*i == value)
                    return true;
            return false;
        };
    };

}

namespace lect_8_4_q1 {
    class String {
    public:
        String() {
            cout << "constructor ";
        }
        String(const String& str) {
            cout << "copy constructor ";
        }
        String(String&& str) {
            cout << "move constructor ";
        }

        String& operator=(const String& str) {
            cout << "copy operator = ";
            return *this;
        }
        String& operator=(String&& str) {
            cout << "move operator = ";
            return *this;
        }
    };

    String& fun1(String& s)
    {
        return s;
    }

    String&& fun2(String& s)
    {
        return std::move(s);
    }

    String fun3(String& s)
    {
        return std::move(s);
    }

    String fun4(String s)
    {
        return std::move(s);
    }

    String fun5(String s)
    {
        return std::forward<String>(s);
    }

    String&& fun6(String&& s)
    {
        return std::move(s);
    }

    String fun7(String&& s)
    {
        return s;
    }
    /*
    1. Ничего не создается, потому что везде фигурируют ссылки. Ссылка прокидывается через возвращаемое значение.
    2. Аналогично 1. move меняет тип ссылки, ничего не создается.
    3. Создается объект в возвращаемое значение.
    4. Аналогично 3.
    5. Аналогично 4.
    6. Аналогично 1, только с другим типом ссылок.
    7. Используем Hint из условия, s внутри имеет тип S&. Поэтому вызовется обычный S(S&).
    */
}

namespace lect_8_4_1 {
    template<class F, class... Args>
    auto apply(const F& f, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
    {
        return f(std::forward<Args>(args)...);
    }

    // or c++ 14
    template<class F, class... Args>
    auto apply_cpp_14(const F& f, Args&&... args)
    {
        return f(std::forward<Args>(args)...);
    }
}

namespace lect_9_2_1 {
    template<class It>
    size_t max_increasing_len(It p, It q)
    {
        if (p == q)
            return 0;
        size_t len = 1;
        size_t max_len = 1;
        auto prev = p++;
        for (; p != q; ++p, ++prev) {
            if (*prev < *p)
                ++len;
            else
            {
                if (max_len < len)
                    max_len = len;
                len = 1;
            }
        }
        if (max_len < len)
            max_len = len;
        return max_len;
    }
}

namespace lect_9_3_1 {
    // базовый класс фигуры (полиморфный)
    struct Shape {
        virtual string intersect() = 0;
    };

    // прямоугольник
    struct Rectangle : Shape {
        string intersect() override {
            return "Rectangle ";
        }
    };

    // треугольник
    struct Triangle : Shape {
        string intersect() override {
            return "Triangle ";
        }
    };

    // функция для проверки пересечения двух прямоугольников
    string is_intersect_r_r(Shape* a, Shape* b) {
        return "is_intersect_r_r: " + a->intersect() + "and " + b->intersect();
    }

    // функция для проверки пересечения прямоугольника и треугольника
    string is_intersect_r_t(Shape* a, Shape* b) {
        return "is_intersect_r_t: " + a->intersect() + "and " + b->intersect();
    }

    template<class Base, class Result, bool Commutative>
    struct Multimethod2
    {
        using Func = std::function<Result(Base*, Base*)>;
        // устанавливает реализацию мультиметода
        // для типов t1 и t2 заданных через typeid 
        // f - это функция или функциональный объект
        // принимающий два указателя на Base 
        // и возвращающий значение типа Result
        void addImpl(const type_info& t1, const type_info& t2, const Func f)
        {
            auto i1 = type_index(t1);
            auto i2 = type_index(t2);

            methods[make_pair(i1, i2)] = f;
        }

        // проверяет, есть ли реализация мультиметода
        // для типов объектов a и b
        bool hasImpl(const Base* a, const Base* b) const
        {
            auto i1 = type_index(typeid(*a));
            auto i2 = type_index(typeid(*b));

            return methods.find(make_pair(i1, i2)) != methods.end() ||
                Commutative && methods.find(make_pair(i2, i1)) != methods.end();
        }

        // Применяет мультиметод к объектам
        // по указателям a и b
        Result call(Base* a, Base* b) const
        {
            auto i1 = type_index(typeid(*a));
            auto i2 = type_index(typeid(*b));
            
            auto it12 = methods.find(make_pair(i1, i2));
            if (it12 != methods.end())
                return it12->second(a, b);

            auto it21 = methods.find(make_pair(i2, i1));
            if (Commutative)
                if (it21 != methods.end())
                    return it21->second(b, a);
        }
    private:
        map<pair<type_index, type_index>, Func> methods;
    };
}

namespace lect_9_4_1 {
    template<class T>
    class VectorList
    {
    private:
        using VectT = std::vector<T>;
        using ListT = std::list<VectT>;

    public:
        using value_type = T;

        VectorList() = default;
        VectorList(VectorList const&) = default;
        VectorList(VectorList&&) = default;

        VectorList& operator=(VectorList&&) = default;
        VectorList& operator=(VectorList const&) = default;

        class const_iterator : public std::iterator<std::bidirectional_iterator_tag,
                                                    const value_type> {
        public:
            const_iterator() = default;
            const_iterator(const_iterator const&) = default;
            const_iterator& operator=(const_iterator const&) = default;

            const_iterator operator+(int shift) const {
                if (shift < 0)
                    return operator-(-shift);
                auto it = const_iterator(*this);
                for (int i = 0; i < shift; ++i)
                    it++;
                return it;
            }
            const_iterator& operator++() {
                itv++;
                if (itv == itl->end()) {
                    itl++;
                    if (itl != data->end())
                        itv = itl->begin();
                }

                return *this;
            }
            const_iterator operator++(int v) {
                const_iterator it(*this);
                operator++();
                return it;
            }
            const_iterator operator-(int shift) const {
                if (shift < 0)
                    return operator+(-shift);
                auto it = const_iterator(*this);
                for (int i = 0; i < shift; ++i)
                    it--;
                return it;
            }
            const_iterator& operator--() {
                if (itl == data->end() ||
                    itv == itl->begin()) {
                    --itl;
                    itv = --itl->end();
                    return *this;
                }
                else
                    --itv;

                return *this;
            }
            const_iterator operator--(int v) {
                const_iterator it(*this);
                operator--();
                return it;
            }
            bool operator!= (const const_iterator& it) const {
                return !(*this == it);
            }
            bool operator== (const const_iterator& it) const {
                return itl == it.itl && (itl == data->end() || itv == it.itv);
            }
            value_type& operator*() {
                return const_cast<value_type&>(*itv);
            }
            const value_type* operator->() {
                return itv.operator->();
            }

            typename ListT::const_iterator itl;
            typename VectT::const_iterator itv;
            ListT const* data;
        };

        // метод, который будет использоваться для заполнения VectorList
        // гарантирует, что в списке не будет пустых массивов
        template<class It>
        void append(It p, It q) // определена снаружи
        {
            if (p != q)
                data_.push_back(VectT(p, q));
        }
        

        bool empty() const { return size() == 0; }

        // определите метод size
        size_t size() const
        {
            size_t size = 0;
            for (const auto& v : data_)
                size += v.size();
            return size;
        }


        // определите методы begin / end
        const_iterator begin() const {
            const_iterator it;
            it.data = &data_;
            it.itl = data_.begin();
            if (it.itl != data_.end())
                it.itv = it.itl->begin();
            return it; 
        }
        const_iterator end()   const {
            const_iterator it;
            it.data = &data_;
            it.itl = data_.end();
            return it;
        }

        // определите const_reverse_iterator
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            // определите методы rbegin / rend
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend()   const {
            return const_reverse_iterator(begin());
        }


    private:
        ListT data_;
    };
}

namespace lect_9_4_1 {

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

namespace leetcode {
    namespace task_1 {
/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
*/
        class Solution {
        public:
            vector<int> twoSum(vector<int>& nums, int target) {
                for (size_t i = 0; i < nums.size(); i++)
                    for (size_t j = i + 1; j < nums.size(); j++)
                        if (nums[i] + nums[j] == target)
                            return { (int)i, (int)j };
                return { 0, 0 };
            }
        };
    }

    namespace task_2 {
/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

        //Definition for singly - linked list.
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

        };
        class Solution {
        public:
            ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
                auto head = new ListNode(l1->val);
                l1 = l1->next;
                auto current = head;
                while (l1) {
                    current->next = new ListNode(l1->val);
                    current = current->next;
                    l1 = l1->next;
                }
                current = head;
                current->val += + l2->val;
                l2 = l2->next;
                int add_one = current->val / 10;
                current->val %= 10;
                while (l2 || add_one) {
                    if (l2) {
                        add_one += l2->val;
                        l2 = l2->next;
                    }
                    if (!current->next)
                        current->next = new ListNode(0);
                    current = current->next;
                    current->val += add_one;
                    add_one = current->val / 10;
                    current->val %= 10;
                }
                return head;
            }
        };
    }

    namespace task_3 {
/*
Given a string s, find the length of the longest substring without repeating characters.
*/
        class Solution {
        public:
            int lengthOfLongestSubstring(string s) {
                vector<int> set(256, -1);
                int max_size = 0;
                size_t start = 0;
                for (size_t i = 0; i < s.size(); i++) {
                    if (set[s[i]] >= 0) {
                        int size = i - start;
                        if (max_size < size)
                            max_size = size;
                        auto index = set[s[i]];
                        for (size_t j = start; j < index; j++)
                            set[s[j]] = -1;
                        start = index + 1;
                    }
                    set[s[i]] = i;
                }
                int size = s.size() - start;
                if (max_size < size)
                    max_size = size;
                return max_size;
            }
        };
    }
}



int main() {
    B* b = new B();
    A* a = b;
    //delete b;
    delete a;
    using namespace leetcode::task_3;
    Solution k;
    string s("abc");
    cout << k.lengthOfLongestSubstring(s);
#pragma region part1
    /*int* t1 = nullptr;
    int* t2 = nullptr;
    char* t3 = nullptr;
    cout << (t1 == t2) << endl;
    int* y = new int(0);
    C* c1 = new C();
    B* c2 = new C();
    A* c3 = new C();

    delete c1;
    delete c2;
    delete c3;*/
    /*
    int* t2 = new int(0);
    ++*t2;
    cout << *t2 << endl;
    delete t2;
    cout << (nullptr == t2) << endl;
    t2 = 0;
    cout << (nullptr == t2) << endl;
    cout << (nullptr == 0) << endl;
    SharedPtr p1;
    {
        SharedPtr p2(new Expression());
        SharedPtr p3(new Expression());
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p3.reset(NULL);
        p3 = p5;
        p5.reset(NULL);
        SharedPtr p6;
        SharedPtr p7;
        p7 = p7;
        p7.reset(NULL);
        p7.reset(new Expression());
        SharedPtr p8(new Expression());
        p8.reset(NULL);
    }
    p1 = p1;
    */
    /*
    Array<SharedPtr> arr(20, SharedPtr(new Expression()));
    cout << arr[6].get() << endl;
    ICloneable* c = new ValueHolder<Array<SharedPtr>>(arr);

    Any a(arr);
    cout << a.cast<Array<SharedPtr>>()->operator[](6).get() << endl;
    double d = 20;
    Any a2(d);
    cout << *a2.cast<double>() << endl;
    a = a2;
    cout << *a.cast<double>() << endl;
    */
    /*int ints[] = {1, 2, 3, 4};
    int* iptr = ints;
    double doubles[] = { 3.14 };
    cout << *(ints + 0) << endl;
    cout << *(ints + 1) << endl;
    cout << *(ints + 2) << endl;
    cout << *(ints + 3) << endl;
    cout << *(ints + 4) << endl;

    cout << array_size(ints) << endl;
    cout << array_size(doubles) << endl;*/

#pragma endregion

    // lect_7_2_1
    {
        using namespace lect_7_2_1;
        bool launch = false;
        if (launch) {
            D3 const d1;
            std::cout << "______________\n";
            Base const* b;

            b = (D1*)&d1;
            b->virtual_method();    //D1 : virtual_method
            b->method();            //Base: method

            b = D1BaseToD2Base(b);
            b->virtual_method();    //D2 : virtual_method
            b->method();            //Base: method
        }
    }
    // lect_8_3_1
    {
        using namespace lect_8_3_1;
        bool launch = false;
        if (launch) {
            auto pair11 = to_pair_cpp_11<1, 2>(std::make_tuple(10, "Test c++ 11", 3.14));
            cout << pair11.first << endl;
            cout << pair11.second << endl;

            auto pair14 = to_pair_cpp_14<1, 2>(std::make_tuple(10, "Test c++ 11", 3.14));
            cout << pair14.first << endl;
            cout << pair14.second << endl;
        }
    }
    // lect_8_3_3
    {
        using namespace lect_8_3_3;
        bool launch = false;
        if (launch) {
            int m[10] = { 1,2,3,4,5,6,7,8,9,10 };

            for_each_int(m, m + 10, square_fun); // теперь m = {1,4,9,16,25,36,49,64,81,100};
            for (auto x : m)
                cout << x << "; ";
        }
    }
    // lect_8_3_4
    {
        using namespace lect_8_3_4;
        bool launch = false;
        if (launch) {
            int primes[5] = { 2,3,5,7,11 };

            int m[10] = { 0,0,1,1,4,6,7,8,9,10 };

            // first_prime будет указывать на число 7
            int* first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));
            cout << *first_prime;
        }
    }
    // lect_8_4_q1
    {
        using namespace lect_8_4_q1;
        bool launch = false;
        if (launch) {
            String s;
            String s2;

            cout << endl << "fun1 lvalue ";
            fun1(s);
            cout << endl << "fun1 rvalue not compile";
            //fun1(String());

            cout << endl << "fun2 lvalue ";
            fun2(s);
            cout << endl << "fun2 rvalue not compile";
            //fun2(String());

            cout << endl << "fun3 lvalue ";
            fun3(s);
            cout << endl << "fun3 rvalue not compile";
            //fun3(String());

            cout << endl << "fun4 lvalue ";
            fun4(s);
            cout << endl << "fun4 rvalue ";
            fun4(String());

            cout << endl << "fun5 lvalue ";
            fun5(s);
            cout << endl << "fun5 rvalue ";
            fun5(String());

            cout << endl << "fun6 lvalue not compile";
            //fun6(s);
            cout << endl << "fun6 rvalue ";
            fun6(String());

            cout << endl << "fun7 lvalue not compile";
            //fun7(s);
            cout << endl << "fun7 rvalue ";
            fun7(String());
        }
    }
    // lect_8_4_1
    {
        using namespace lect_8_4_1;
        bool launch = false;
        if (launch) {
            auto fun = [](std::string a, std::string const& b) { return a += b; };

            std::string s("world!");

            // s передаётся по lvalue ссылке,
            // а временный объект по rvalue ссылке 
            s = apply(fun, std::string("Hello, "), s);
            cout << s << endl;
        }
    }
    // lect_9_2_1
    {
        using namespace lect_9_2_1;
        bool launch = false;
        if (launch) {
            std::list<int> const l1 = { 7,8,9,4,5,6,1,2,3,4 };
            size_t len1 = max_increasing_len(l1.begin(), l1.end()); // 4, соответствует подотрезку 1,2,3,4
            cout << len1 << endl;
            std::list<int> const l2 = { -3,-2,-1,0,0,1,2,3,4,5 };
            size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
            cout << len2 << endl;
        }
    }
    // lect_9_3_1
    {
        using namespace lect_9_3_1;
        bool launch = false;
        if (launch) {
            // мультиметод для наследников Shape
            // возращающий bool и являющийся коммутативным 
            Multimethod2<Shape, string, true> is_intersect;

            // добавляем реализацию мультиметода для двух прямоугольников
            is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

            // добавляем реализацию мультиметода для прямоугольника и треугольника
            is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

            // создаём две фигуры    
            Shape* s1 = new Triangle();
            Shape* s2 = new Rectangle();

            // проверяем, что реализация для s1 и s2 есть
            if (is_intersect.hasImpl(s1, s2))
            {
                // вызывается функция is_intersect_r_t(s2, s1)
                cout << is_intersect.call(s1, s2);

                // Замечание: is_intersect_r_t ожидает,
                // что первым аргументом будет прямоугольник
                // а вторым треугольник, а здесь аргументы
                // передаются в обратном порядке. 
                // ваша реализация должна самостоятельно 
                // об этом позаботиться
            }
        }
    }
    // lect_9_4_1
    {
        using namespace lect_9_4_1;
        bool launch = false;
        if (launch) {
            VectorList<int> vlist;

            std::vector<int> expectedItems = { 1,2,3,4,5,6,7 };

            std::vector<int> v6;
            v6.push_back(1);
            v6.push_back(2);
            v6.push_back(3);

            std::vector<int> v2;
            v2.push_back(4);
            v2.push_back(5);
            v2.push_back(6);
            v2.push_back(7);
            vlist.append(v6.begin(), v6.end());
            vlist.append(v2.begin(), v2.end());

            //Initial test group
            assert(vlist.size() == 7);
            assert(*vlist.begin() == 1);
            auto dist = std::distance(vlist.begin(), vlist.end());
            assert(std::distance(vlist.begin(), vlist.end()) == 7);

            assert(std::equal(vlist.begin(), vlist.end(), expectedItems.begin()));

            VectorList<int> vlistEmpty;
            assert(std::distance(vlistEmpty.begin(), vlistEmpty.end()) == 0);

            std::cout << "Test i++" << std::endl;
            for (auto i = vlist.begin(); i != vlist.end(); i++)
                std::cout << *i << " ";
            std::cout << std::endl;

            std::cout << "Test ++i" << std::endl;
            for (auto i = vlist.begin(); i != vlist.end(); ++i)
                std::cout << *i << " ";

            std::cout << std::endl;
            std::cout << std::endl;

            std::cout << "Test --i" << std::endl;
            for (auto i = vlist.end(); i != vlist.begin();)
                std::cout << *--i << " ";
            std::cout << std::endl;

            std::cout << "Test i--" << std::endl;
            for (auto i = vlist.end(); i != vlist.begin();) {
                i--;
                std::cout << *i << " ";
            }
            std::cout << std::endl;


            std::cout << std::endl;
            auto j = vlist.rbegin();
            std::cout << "rbegin is " << *j << std::endl;
            j = --vlist.rend();
            std::cout << "--rend is " << *j << std::endl;

            std::cout << "Test reverse_const_iterator ++" << std::endl;
            for (j = vlist.rbegin(); j != vlist.rend(); ++j)
                std::cout << *j << " ";
            std::cout << std::endl;

            auto it1 = vlist.begin();
            for (; it1 != vlist.end(); ++it1)
                std::cout << *it1 << ' ';

            std::cout << std::endl;
            std::cout << *--it1 << ' ';
            std::cout << *--it1 << ' ';
            std::cout << *--it1 << ' ';
            std::cout << *--it1 << ' ';

            std::cout << std::endl;
            std::cout << "One element test" << std::endl;
            VectorList<int> vlistOneElement;
            std::vector<int> vOne;
            vOne.push_back(1);
            vlistOneElement.append(vOne.begin(), vOne.end());

            auto it3 = vlistOneElement.begin();
            for (; it3 != vlistOneElement.end(); ++it3)
                std::cout << *it3 << ' ';

            VectorList<int> vListEmpty;
            auto it4 = vListEmpty.begin();
            for (; it4 != vListEmpty.end(); ++it4)
                std::cout << *it4 << ' ';

            std::cout << std::endl;
            std::cout << std::endl;
            {
                std::cout << "Repeated vector" << std::endl;
                VectorList<int> vListSingleItem;
                std::vector<int> vOneelemtn;
                vOneelemtn.push_back(1);
                vOneelemtn.push_back(2);
                vListSingleItem.append(vOneelemtn.begin(), vOneelemtn.end());
                vListSingleItem.append(vOneelemtn.begin(), vOneelemtn.end());

                auto itcontaint = vListSingleItem.begin();
                for (; itcontaint != vListSingleItem.end(); ++itcontaint)
                    std::cout << *itcontaint << ' ';

                std::cout << std::endl << "Reverse repeated vector" << std::endl;
                --itcontaint;
                std::cout << *itcontaint << ' ';
                --itcontaint;
                std::cout << *itcontaint << ' ';
                --itcontaint;
                std::cout << *itcontaint << ' ';
                --itcontaint;
                std::cout << *itcontaint << ' ';

            }

            std::cout << std::endl;
            std::cout << std::endl;

            {
                std::cout << "Strings" << std::endl;

                std::vector<std::string> v1 = { "one", "two", "three" }; std::vector<std::string> v2 = { "four", "five", "six", "seven", "eight" }; std::vector<std::string> v3 = { "nine", "ten", "eleven", "twelve" }; std::vector<std::string> v4 = {}; for (int k = 13; k <= 30; ++k) { v4.push_back(std::to_string(k) + "-th"); }VectorList<std::string> vl; std::cout << "empty distance = " << std::distance(vl.rbegin(), vl.rend()) << std::endl;


                vl.append(v1.begin(), v1.end());

                vl.append(v2.begin(), v2.end());

                vl.append(v3.begin(), v3.end());

                vl.append(v4.begin(), v4.end());
                VectorList<std::string>::const_iterator it = vl.begin();
                for (; it != vl.end(); ++it) { std::string a = *it;   std::cout << a << " "; }std::cout << std::endl; std::cout << "distance = " << std::distance(vl.begin(), vl.end()) << std::endl;
                VectorList<std::string>::const_iterator eit = vl.end();
                for (; eit != vl.begin();) {
                    std::string a = *(--eit);
                    std::cout << a << " ";
                }std::cout << std::endl;
                VectorList<std::string>::const_reverse_iterator rit = vl.rend();
                for (; rit != vl.rend(); ++rit) {
                    std::string a = *rit;   std::cout << a << " ";
                }std::cout << std::endl; std::cout << "reverse distance = " << std::distance(vl.rbegin(), vl.rend()) << std::endl;
                VectorList<std::string>::const_reverse_iterator erit = vl.rend();
                for (; erit != vl.rbegin();) {
                    std::string a = *(--erit);   std::cout << a << " ";
                }std::cout << std::endl;
                VectorList<std::string>::const_iterator i = vl.rend().base();
                for (; i != vl.end(); ++i) {
                    std::string a = *i;
                    std::cout << a << " ";
                }
                std::cout << std::endl;
            }
        }

    } {}
    // lect_8_3_1
    {
        using namespace lect_8_3_1;
        bool launch = true;
        if (launch) {

        }
    }

    return 0;
}

