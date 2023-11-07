#pragma once

#include <cstdint>
#include <initializer_list>
#include <map>
#include <sstream>
#include <tuple>

namespace Project {

    class Poly {
    public:
        Poly() = default;

        Poly(std::initializer_list <int64_t> coefs);

        Poly(std::initializer_list <std::pair<int64_t, int64_t>> deg_coef);

        int64_t operator()(int64_t x) const;

        const bool operator==(const Poly &poly1) const;

        const bool operator!=(const Poly &poly1) const;

        Poly operator+(const Poly &poly1) const;

        Poly operator-() const;

        Poly operator-(const Poly &poly1) const;

        Poly operator+=(const Poly &poly1);

        Poly operator-=(const Poly &poly1);

        Poly operator*(const Poly &poly1) const;

        Poly operator*=(const Poly &poly1);

        friend std::ostream &operator<<(std::ostream &stream, const Poly &poly);

    private:
        std::map <size_t, int64_t, std::greater<size_t>> polynomial_;

        void RemoveZeros(Poly &poly) const;

        int64_t FastPow(int64_t x, int64_t deg) const;
    };
}
