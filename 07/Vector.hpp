#pragma once

#include <iostream>

template <class T> class Vector
{
    size_t size_;
    T* mas_;
    size_t cap_;
public:
    class iter
    {
        T* pointer;
    public:
        iter();
        iter(T*);
        iter &operator++();
        T operator*() const;
        bool operator==(const iter &) const;
        bool operator!=(const iter &) const;
    };
    class reverse_iter
    {
        T* pointer;
    public:
        reverse_iter();
        reverse_iter(T*);
        reverse_iter &operator++();
        T operator*() const;
        bool operator==(const reverse_iter &) const;
        bool operator!=(const reverse_iter &) const;
    };

    Vector();
    Vector(size_t n);
    Vector(const Vector &);
    ~Vector();

    Vector &operator = (const Vector &);
    template <class N> Vector &operator = (const Vector<N> &);

    T &operator [] (size_t);
    T &operator [] (size_t) const;

    void push_back(const T&);
    T pop_back();
    void emplace_back(const T&);

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    void reserve(size_t);

    void resize(size_t new_size, T val = T())
    {
        T* tmp = new T[size_];
        for (size_t i = 0; i < size_; i++)
            tmp[i] = mas_[i];

        size_t old_size = size_;
        clear();
        if (new_size < old_size) {
            for (size_t i = 0; i < new_size; i++)
                push_back(tmp[i]);
        } else {
            for (size_t i = 0; i < old_size; i++)
                push_back(tmp[i]);
            for (size_t i = old_size; i < new_size; i++)
                push_back(val);
        }
        delete [] tmp;
    }

    iter begin();
    iter end();
    reverse_iter rbegin();
    reverse_iter rend();

    void print();
};

/*--------------------- Vector<T>::iter ---------------*/

template <class T>
Vector<T>::iter::iter() : pointer(NULL) {}

template <class T>
Vector<T>::iter::iter(T* i) : pointer(i) {}

template <class T>
typename Vector<T>::iter &Vector<T>::iter::operator ++()
{
    ++pointer;
    return *this;
}

template <class T>
T Vector<T>::iter::operator * () const
{
    return *pointer;
}

template <class T>
bool Vector<T>::iter::operator == (const iter & it) const
{
    return pointer == it.pointer;
}

template <class T>
bool Vector<T>::iter::operator != (const iter & it) const
{
    return pointer != it.pointer;
}
/*--------------------- Vector<T>::reverse_iter ---------------*/
template <class T>
Vector<T>::reverse_iter::reverse_iter() : pointer(NULL) {}

template <class T>
Vector<T>::reverse_iter::reverse_iter(T* i) : pointer(i) {}

template <class T>
typename Vector<T>::reverse_iter &Vector<T>::reverse_iter::operator++()
{
    --pointer;
    return *this;
}

template <class T>
T Vector<T>::reverse_iter::operator*() const
{
    return *pointer;
}

template <class T>
bool Vector<T>::reverse_iter::operator==(const reverse_iter & it) const
{
    return pointer == it.pointer;
}

template <class T>
bool Vector<T>::reverse_iter::operator!=(const reverse_iter & it) const
{
    return pointer != it.pointer;
}

/*--------------------- Vector<T> ---------------*/

template <class T>
Vector<T>::Vector() : size_(0), cap_(2)
{
    mas_ = new T[cap_];
}

template <class T>
Vector<T>::Vector(size_t cap) : size_(0), cap_(cap)
{
    mas_ = new T[cap_];
}

template <class T>
Vector<T>::Vector(const Vector<T> & vec)
{
    clear();
    for (size_t i = 0; i < vec.size(); i++) {
        push_back(vec[i]);
    };
    size_ = vec.size();
    cap_ = vec.capacity();
}

template <class T>
Vector<T> & Vector<T>::operator =
(const Vector<T> & vec)
{
    clear();
    for (size_t i = 0; i < vec.size(); i++) {
        push_back(vec[i]);
    };
    size_ = vec.size();
    cap_ = vec.capacity();
    return *this;
}

template <class T>
template <class N>
Vector<T> & Vector<T>::operator =
(const Vector<N> & vec)
{
    clear();
    for (size_t i = 0; i < vec.size(); i++) {
        push_back(vec[i]);
    };
    size_ = vec.size();
    cap_ = vec.capacity();
    return *this;
}

template <class T>
void Vector<T>::push_back(const T& elem)
{
    if (size_ < cap_) {
        mas_[size_] = elem;
        ++size_;
    } else {
        T* mas__tmp = new T[cap_];
        for (size_t i = 0; i < cap_; i++) {
            mas__tmp[i] = mas_[i];
        };
        cap_ *= 2;
        delete [] mas_;
        mas_ = new T[cap_];
        for (size_t i = 0; i < size_; i++) {
            mas_[i] = mas__tmp[i];
        }
        mas_[size_++] = elem;
        delete [] mas__tmp;
    }
}

template <class T>
T Vector<T>::pop_back()
{
    if (size_ == 0) {
        throw "Empty vector";
    };
    return mas_[--size_];
}

template <class T>
void Vector<T>::emplace_back(const T& elem)
{
    if (size_ == 0) {
        throw "Empty vector";
    };
    mas_[size_ - 1] = elem;
}

template <class T>
bool Vector<T>::empty() const
{
    return size_ == 0;
}

template <class T>
void Vector<T>::reserve(size_t new_cap)
{
    if (new_cap > cap_) {
        T* mas__tmp = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            mas__tmp[i] = mas_[i];
        }
        delete [] mas_;
        mas_ = new T[new_cap];
        for (size_t i = 0; i < size_; i++) {
            mas_[i] = mas__tmp[i];
        }
        delete [] mas__tmp;
        cap_ = new_cap;
    }
}

template <class T>
T & Vector<T>::operator[](size_t i)
{
    if (i >= size_) {
        throw "Wrong index";
    };
    return *(mas_ + i);
}

template <class T>
T & Vector<T>::operator[](size_t i) const
{
    if (i >= size_) {
        throw "Wrong index";
    };
    return *(mas_ + i);
}

template <class T>
typename Vector<T>::iter Vector<T>::begin()
{
    return iter(mas_);
}

template <class T>
typename Vector<T>::reverse_iter Vector<T>::rbegin()
{
    return reverse_iter(mas_ + size_ - 1);
}

template <class T>
typename Vector<T>::iter Vector<T>::end()
{
    return iter(mas_ + size_);
}

template <class T>
typename Vector<T>::reverse_iter Vector<T>::rend()
{
    return reverse_iter(mas_ - 1);
}

template <class T>
size_t Vector<T>::size() const
{
    return size_;
}

template <class T>
size_t Vector<T>::capacity() const
{
    return cap_;
}

template <class T>
void Vector<T>::print()
{
    for (size_t i = 0; i < size_; i++) {
        std::cout << mas_[i] << " ";
    };
    std::cout << std::endl;
}

template <class T>
void Vector<T>::clear()
{
    delete [] mas_;
    size_ = 0;
    mas_ = new T[cap_];
}

template <class T>
Vector<T>::~Vector()
{
    delete [] mas_;
}
