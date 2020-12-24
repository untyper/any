//          Copyright Jasin Elguemri 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef ANY_HPP
#define ANY_HPP

#include <memory>

class any {
private:
    struct base {
        virtual std::unique_ptr<base> clone() const = 0;
        virtual ~base() {}
    };

    template <typename _t>
    struct container : base {
        _t value;

        std::unique_ptr<base> clone()
        const override {
            return std::unique_ptr<container<_t>>(
                new container<_t>(value)
            );
        }

        container(const _t& lvalue) :
            value(lvalue) {}
    };

    std::unique_ptr<base> ptr;

    template <typename _t>
    container<_t>* get_container() {
        return dynamic_cast<container<_t>*>(
            ptr.get()
        );
    }

    template <typename _t>
    std::unique_ptr<base> make_unique(const _t& lvalue) {
        return std::unique_ptr<base>(
            new container<
                typename std::decay<const _t>::type
            >(lvalue)
        );
    }

public:
    template <typename _t>
    _t as() {
        return get_container<_t>()->value;
    }

    template <typename _t>
    bool is() {
        return get_container<_t>();
    }

    void reset() { 
        ptr.reset(nullptr); 
    }

    template <typename _t>
    any& operator=(const _t& p) {
        ptr = std::move(make_unique(p));
        return *this;
    }

    any& operator=(const any& other) {
        ptr = other.ptr->clone();
        return *this;
    }

    any& operator=(any&& other) {
        ptr = std::move(other.ptr);
        return *this;
    }

    template <typename _t>
    any(const _t& p) :
        ptr(std::move(make_unique(p))) {}

    any(const any& other) :
        ptr(other.ptr->clone()) {}

    any(any&& other) :
        ptr(std::move(other.ptr)) {}

    any() :
        ptr(nullptr) {}
};

#endif // ANY_HPP