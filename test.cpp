// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include "stepik_csc_1.h"
#include "stepik_csc_2.h"
#include "some_test_code.h"
using namespace std;

int main() {
    //B* b = new B();
    //A* a = b;
    //delete b;
    //delete a;
    using namespace leetcode::task_6;
    Solution k;
    cout << k.convert("a", 1);

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

#pragma region part2

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

#pragma endregion

    return 0;
}

