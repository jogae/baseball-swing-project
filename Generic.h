#ifndef GENERIC_H
#define GENERIC_H

// 제너릭 클래스을 통하여 두 값을 비교
template <typename T>
class Generic {
public:
    static T getMax(const T& a, const T& b) {
        return (a > b) ? a : b;
    }
};

#endif
