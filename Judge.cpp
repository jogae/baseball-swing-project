#include "Judge.h"

string AngleJudge::judge(const Data& swing) const {
    return (swing.getAngle() >= 45.0) ? "각도 기반: 스트라이크" : "각도 기반: 볼";
}

string ZoneJudge::judge(const Data& swing) const {
    return swing.isInStrikeZone() ? "존 기반: 스트라이크" : "존 기반: 볼";
}
