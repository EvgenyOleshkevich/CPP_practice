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
using namespace std;

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
    bool compare(const T& a, const T& b, V(T::* mptr)() const)
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

#endif // stepik