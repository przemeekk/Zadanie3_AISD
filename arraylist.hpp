#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>

template <typename T>
class ArrayList {
    T* tab;
    std::size_t msize;
    std::size_t last;
public:
    ArrayList(std::size_t s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    }
    ~ArrayList() { delete [] tab; }

    ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) {
        tab = new T[msize];
        assert( tab != nullptr );
        for (std::size_t i = 0; i < last; ++i) {
            tab[i] = other.tab[i];
        }
    }

    ArrayList(ArrayList&& other) noexcept : tab(other.tab), msize(other.msize), last(other.last) {
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    }

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            T* new_tab = new T[other.msize];
            assert(new_tab != nullptr);
            for (std::size_t i = 0; i < other.last; ++i) {
                new_tab[i] = other.tab[i];
            }
            delete [] tab;
            tab = new_tab;
            msize = other.msize;
            last = other.last;
        }
        return *this;
    }

    ArrayList& operator=(ArrayList&& other) noexcept {
        if (this != &other) {
            delete [] tab;
            tab = other.tab;
            msize = other.msize;
            last = other.last;
            other.tab = nullptr;
            other.msize = 0;
            other.last = 0;
        }
        return *this;
    }

    bool empty() const { return last == 0; }
    bool full() const { return last == msize; }
    std::size_t size() const { return last; }
    std::size_t max_size() const { return msize; }

    void push_front(const T& item) {
        assert(!full());
        std::copy_backward(tab, tab + last, tab + last + 1);
        tab[0] = item;
        ++last;
    }

    void push_front(T&& item) {
        assert(!full());
        std::copy_backward(tab, tab + last, tab + last + 1);
        tab[0] = std::move(item);
        ++last;
    }

    void push_back(const T& item) {
        assert(!full());
        tab[last++] = item;
    }

    void push_back(T&& item) {
        assert(!full());
        tab[last++] = std::move(item);
    }

    T& front() {
        assert(!empty());
        return tab[0];
    }

    const T& front() const {
        assert(!empty());
        return tab[0];
    }

    T& back() {
        assert(!empty());
        return tab[last - 1];
    }

    const T& back() const {
        assert(!empty());
        return tab[last - 1];
    }

    void pop_front() {
        assert(!empty());
        std::copy(tab + 1, tab + last, tab);
        --last;
    }

    void pop_back() {
        assert(!empty());
        --last;
    }

    void clear() {
        last = 0;
    }

    void display() const {
        for (std::size_t i = 0; i < last; ++i) {
            std::cout << tab[i] << (i + 1 == last ? "" : " ");
        }
        std::cout << std::endl;
    }

    void display_reversed() const {
        for (std::size_t i = last; i > 0; --i) {
            std::cout << tab[i - 1] << (i == 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    void reverse() {
        for (std::size_t i = 0; i < last / 2; ++i) {
            T temp = std::move(tab[i]);
            tab[i] = std::move(tab[last - 1 - i]);
            tab[last - 1 - i] = std::move(temp);
        }
    }

    void sort() {
        std::sort(tab, tab + last);
    }

    void merge(ArrayList& other) {
        assert(last + other.last <= msize);
        T* temp = new T[last + other.last];
        std::merge(tab, tab + last, other.tab, other.tab + other.last, temp);
        for (std::size_t i = 0; i < last + other.last; ++i) {
            tab[i] = std::move(temp[i]);
        }
        last += other.last;
        delete [] temp;
        other.clear();
    }

    T& operator[](std::size_t pos) {
        assert(pos < last);
        return tab[pos];
    }

    const T& operator[](std::size_t pos) const {
        assert(pos < last);
        return tab[pos];
    }

    void erase(std::size_t pos) {
        assert(pos < last);
        std::copy(tab + pos + 1, tab + last, tab + pos);
        --last;
    }

    int index(const T& item) const {
        for (std::size_t i = 0; i < last; ++i) {
            if (tab[i] == item) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void insert(std::size_t pos, const T& item) {
        assert(pos <= last && !full());
        std::copy_backward(tab + pos, tab + last, tab + last + 1);
        tab[pos] = item;
        ++last;
    }

    void insert(std::size_t pos, T&& item) {
        assert(pos <= last && !full());
        std::copy_backward(tab + pos, tab + last, tab + last + 1);
        tab[pos] = std::move(item);
        ++last;
    }

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i = 0; i < L.last; ++i) {
            os << L.tab[i] << (i + 1 == L.last ? "" : " ");
        }
        return os;
    }
};

#endif