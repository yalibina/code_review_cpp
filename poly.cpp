#include "poly.h"
#include <cmath>

Poly::Poly(std::initializer_list<int64_t> coefs) {
    size_t i = 0;
    for (auto it = coefs.begin(); it < coefs.end(); ++it) {
        if (*it != 0) {
            polynomial_[i] = *it;
        }
        ++i;
    }
}

Poly::Poly(std::initializer_list<std::pair<int64_t, int64_t>> deg_coef) {
    for (auto it = deg_coef.begin(); it < deg_coef.end(); ++it) {
        if (it->second != 0) {
            polynomial_[it->first] = it->second;
        }
    }
}

void Poly::RemoveZeros(Poly& poly) const {
    for (auto it = poly.polynomial_.begin(); it != poly.polynomial_.end();) {
        if (it->second == 0) {
            it = poly.polynomial_.erase(it);
        } else {
            ++it;
        }
    }
}

int64_t Poly::operator()(int64_t x) const {
    int64_t val = 0;
    for (auto mon : this->polynomial_) {
        val += static_cast<int64_t>(std::pow(x, mon.first)) * mon.second;
    }
    return val;
}

const bool Poly::operator==(const Poly& poly1) const {

    if (this->polynomial_.size() != poly1.polynomial_.size()) {
        return false;
    }

    for (auto mon : this->polynomial_) {
        if (poly1.polynomial_.at(mon.first) != mon.second) {
            return false;
        }
    }
    return true;
}

const bool Poly::operator!=(const Poly& poly1) const {
    return (!(*this == poly1));
}

Poly Poly::operator+(const Poly& poly1) const {
    Poly poly = *this;

    for (auto mon : poly1.polynomial_) {
        poly.polynomial_[mon.first] += mon.second;
    }
    RemoveZeros(poly);

    return poly;
}

Poly Poly::operator-() const {
    Poly poly = *this;
    for (auto mon : this->polynomial_) {
        poly.polynomial_[mon.first] = -mon.second;
    }
    return poly;
}

Poly Poly::operator-(const Poly& poly1) const {
    return *this + (-poly1);
}

Poly Poly::operator+=(const Poly& poly1) {
    *this = *this + poly1;
    return *this;
}

Poly Poly::operator-=(const Poly& poly1) {
    return *this += (-poly1);
}

Poly Poly::operator*(const Poly& poly1) const {
    Poly poly;

    for (auto mon : this->polynomial_) {
        for (auto mon1 : poly1.polynomial_) {
            poly.polynomial_[mon.first + mon1.first] += mon.second * mon1.second;
        }
    }
    RemoveZeros(poly);

    return poly;
}

Poly Poly::operator*=(const Poly& poly1) {
    *this = *this * poly1;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    size_t i = 0;
    stream << "y = ";
    if (poly.polynomial_.empty()) {
        stream << 0;
    } else {
        for (auto mon : poly.polynomial_) {
            if (i != 0) {
                stream << (mon.second > 0 ? " + " : " - ");
            } else if (mon.second < 0) {
                stream << "-";
            }
            stream << std::abs(mon.second);
            if (mon.first != 0) {
                stream << "x";
                if (mon.first != 1) {
                    stream << "^" << mon.first;
                }
            }
            ++i;
        }
    }

    return stream;
}
