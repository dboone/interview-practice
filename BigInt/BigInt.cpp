#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

class BigInt {
public:
    BigInt() = delete;
    BigInt(int x);
    BigInt(const std::vector< int >& value);
    BigInt(const std::initializer_list< int >& list);
    std::vector< int > getVector() const {
        return value_;
    }

private:
    std::vector< int > value_;
};

BigInt::BigInt(int x) {
    bool isNegative = false;

    if (x < 0) {
        isNegative = true;
        x *= -1;
    }

    while (x) {
        value_.push_back( x % 10 );
        x /= 10;
    }

    std::reverse(value_.begin(), value_.end());

    if (isNegative) {
        *value_.begin() *= -1;
    }
}

BigInt::BigInt(const std::vector< int >& value) : value_(value) {
}

BigInt::BigInt(const std::initializer_list<int>& list) : value_(list) {
}


BigInt multiply(const BigInt& left, const BigInt& right) {
    std::vector< int > l = left.getVector();
    std::vector< int > r = right.getVector();

    if (l.size() > r.size())
        std::swap(l, r);

    int sign = (l.front() * r.front() < 0)? -1 : 1;

    if (l.front() < 0)
        l.front() *= -1;

    if (r.front() < 0)
       r.front() *= -1;

    std::vector< int > result(l.size() + r.size(), 0);
    auto k = result.begin();
    int offset = 0;
    for (auto i = l.rbegin(); i != l.rend(); ++i) {
        for (auto j = r.rbegin(); j != r.rend(); ++j) {
            int product = (*i) * (*j);
            int carry = (*k + product) / 10;
            *(k + 1) += carry;
            *k = (*k + product) % 10;
            ++k;
        }
        ++offset;
        k = result.begin() + offset;
    }

    // remove leading zeros
    while(result.size() != 1 && result.back() == 0)
        result.pop_back();

    std::reverse(result.begin(), result.end());

    // apply the sign
    result.front() *= sign;
    return BigInt(result);
}

std::ostream& operator<<(std::ostream& out,
    const std::vector< int >& vec ) {
    std::for_each(
        vec.cbegin(), vec.cend(),
        [&out](int x) { out << x << ", "; });
    out << std::endl;
    return out;
}

void test(const std::vector< int >& actual,
          const std::vector< int >& expected) {
    if (actual == expected) {
        std::cout << "Passed" << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;
        std::cout << "Actual:   " << actual
                  << "Expected: " << expected;
    }
}

void bigIntBookTest() {
    BigInt m = multiply(
        { 1,9,3,7,0,7,7,2,1 },
        { -7,6,1,8,3,8,2,5,7,2,8,7 });               // implicit type conversion
    auto actualResult = m.getVector();

    std::vector< int > expectedResult { -1,4,7,5,7,3,9,5,2,5,8,9,6,7,6,4,1,2,9,2,7 };

    test(actualResult, expectedResult);
}

void bigIntSimpleTest() {
    BigInt b0(123);
    BigInt b1(1234);

    BigInt m = multiply(b0, b1);
    auto actualResult = m.getVector();

    std::vector< int > expectedResult { 1,5,1,7,8,2 };

    test(actualResult, expectedResult);
}

int main(int argc, char* argv[]) {
    bigIntSimpleTest();
    bigIntBookTest();

    return 0;
}