#include "Data.h"

Data::Data(double angle, bool inStrikeZone)
    : angle(angle), inStrikeZone(inStrikeZone) {}

double Data::getAngle() const {
    return angle;
}

bool Data::isInStrikeZone() const {
    return inStrikeZone;
}

// 연산자 중복을 사용했다.
bool Data::operator==(const Data& other) const {
    return angle == other.angle && inStrikeZone == other.inStrikeZone;
}
