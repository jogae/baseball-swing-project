#ifndef DATA_H
#define DATA_H

class Data {
private:
    double angle; 
    bool inStrikeZone; 

public:
    Data(double angle, bool inStrikeZone); 
    double getAngle() const; 
    bool isInStrikeZone() const; 

    // 연산자 중복을 사용
    bool operator==(const Data& other) const; 
};

#endif

