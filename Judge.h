#ifndef JUDGE_H
#define JUDGE_H

#include "Data.h"
#include <string>
using namespace std;

// 추상 클래스, 다형성, 가상함수
class Judge {
public:
    virtual ~Judge() {}
    virtual string judge(const Data& swing) const = 0;
};

class AngleJudge : public Judge {
public:
    string judge(const Data& swing) const override;
};

class ZoneJudge : public Judge {
public:
    string judge(const Data& swing) const override;
};

#endif
