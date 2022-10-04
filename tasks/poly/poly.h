#pragma once

#include <cstdint>
#include <map>
#include <sstream>

class Poly {
public:
    Poly();
    Poly(const std::initializer_list<int>& initializer_list);
    Poly(const std::initializer_list<std::pair<int, int>>& initializer_pair_list);

    int64_t operator()(int x) const;

    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;

    Poly operator-(const Poly& other) const;
    const Poly& operator-=(const Poly& other);

    Poly operator+(const Poly& other) const;
    const Poly& operator+=(const Poly& other);

    Poly operator-() const;

    Poly operator*(const Poly& other) const;
    const Poly& operator*=(const Poly& other);

    friend std::ostream& operator<<(std::ostream& os, const Poly& poly);

private:
    std::map<size_t, int> poly_;

    void Normalize();
};