#include "vector.h"
Vector::Vector(): size_(0u), capacity_(0u), data_(NULL) {
}
Vector::Vector(size_t size): size_(size), capacity_(size_) {
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < size; ++i) {
        data_[i] = 0;
    }
}
Vector::Vector(std::initializer_list<ValueType> list): size_(list.size()), capacity_(list.size()) {
    data_ = new ValueType[capacity_];
    size_t i = 0;
    for (ValueType value : list) {
        data_[i++] = value;
    }
}
Vector::Vector(const Vector& other): size_(other.size_), capacity_(other.capacity_) {
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}
Vector& Vector::operator=(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    if (data_) {
        delete[] data_;
    }
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}
Vector::~Vector() {
    size_ = 0;
    capacity_ = 0;

    if (data_) {
        delete[] data_;
        data_ = NULL;
    }
}
Vector::SizeType Vector::Size() const {
    return size_;
}
Vector::SizeType Vector::Capacity() const {
    return capacity_;
}
const Vector::ValueType* Vector::Data() const {
    return data_;
}
Vector::ValueType& Vector::operator[](size_t position) {
    return data_[position];
}
Vector::ValueType Vector::operator[](size_t position) const {
    return data_[position];
}
bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}
bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}
std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < size_; ++i) {
        if (i == other.size_) { // size_ > other.size_
            return std::strong_ordering::greater;
        }
        if (data_[i] < other.data_[i]) {
            return std::strong_ordering::less;
        } else if (data_[i] > other.data_[i]) {
            return std::strong_ordering::greater;
        }
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    }
    return std::strong_ordering::equal;
}
void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    capacity_ = new_capacity;

    if (data_) {
        delete[] data_;
    }
    data_ = new ValueType[capacity_];
}
void Vector::Clear() {
    size_ = 0;
}
void Vector::PushBack(const Vector::ValueType& new_element) {
    if (capacity_ == 0) {
        ++capacity_;
        data_ = new ValueType[capacity_];
    } else if (size_ == capacity_) {
        capacity_ *= 2;
        ValueType* new_data = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    data_[size_] = new_element;
    ++size_;
}
void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}
void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    ValueType* temp = data_;
    data_ = other.data_;
    other.data_ = temp;
}
Vector::Iterator Vector::Begin() {
    return Vector::Iterator(&data_[0u]);
}
Vector::Iterator Vector::End() {
    return Vector::Iterator(&data_[size_]);
}
Vector::Iterator Vector::begin() {
    return Begin();
}
Vector::Iterator Vector::end() {
    return End();
}
Vector::Iterator::Iterator(Vector::ValueType* pointer): m_ptr_(pointer) {
}
Vector::Iterator::Iterator(): m_ptr_(NULL) {
}
Vector::ValueType& Vector::Iterator::operator*() const {
    return *m_ptr_;
}
Vector::ValueType* Vector::Iterator::operator->() const {
    return m_ptr_;
}
Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    m_ptr_ = other.m_ptr_;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator++() {
    ++m_ptr_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator result = *this;
    ++m_ptr_;
    return result;
}
Vector::Iterator& Vector::Iterator::operator--() {
    --m_ptr_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Vector::Iterator result = *this;
    --m_ptr_;
    return result;
}
Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Iterator result = *this;
    result.m_ptr_ += shift;
    return result;
}
Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return m_ptr_ - other.m_ptr_;
}
Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    m_ptr_ += shift;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    m_ptr_ -= shift;
    return *this;
}
bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return m_ptr_ == other.m_ptr_;
}
bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return m_ptr_ != other.m_ptr_;
}
std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    return m_ptr_ <=> other.m_ptr_;
}
