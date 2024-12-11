#include "Save.h"
#include <iostream>
#include <fstream>

using namespace std;

void Save::log(const string& result) const {
    cout << result << endl; 
}

void Save::save(const string& filename, const vector<Data>& swings) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "파일 저장 중 오류가 발생했습니다: " << filename << endl;
        return;
    }

    for (const auto& swing : swings) {
        outFile << "각도: " << swing.getAngle() << " / 스트라이크 존 여부: " 
                << (swing.isInStrikeZone() ? "예" : "아니오") << endl;
    }
    outFile.close();
    cout << "결과가 파일에 저장되었습니다: " << filename << endl;
}
