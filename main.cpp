/*
컴퓨터프로그래밍 및 실습 평가 과제
학과 : 컴퓨터공학부
학번 : 202203316
이름 : 조성경
과제 주제 : 미래의 야구(배트 스윙 판독)에 관한 프로그램 구현
*/

#ifndef NOMINMAX
#define NOMINMAX 
#endif
                                   //byte 문제가 자꾸만 떠서 사용하였다.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#endif

#include "Generic.h"
#include "Judge.h"
#include "Data.h"
#include "Save.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <windows.h>

using namespace std;

// 예외 처리를 위해 try-catch-throw 구조를 사용하였다.
double getInput(const string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        try {
            cout << prompt;
            cin >> value;

            if (cin.fail()) {
                throw invalid_argument("잘못된 입력입니다. 숫자를 입력해주세요.");
            } else if (value < minVal || value > maxVal) {
                throw out_of_range("값은 " + to_string(minVal) + "에서 " + to_string(maxVal) + " 사이여야 합니다.");
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;

        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        }
    }
}

// 파일의 입력을 위해 loadDataFromFile를 사용하였다.
vector<Data> loadDataFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return {};
    }

    vector<Data> swings;
    double angle;
    bool inStrikeZone;

    while (inFile >> angle >> inStrikeZone) {
        if (angle < 0 || angle > 180) {
            cerr << "잘못된 각도 값이 발견되었습니다: " << angle << endl;
            continue;
        }
        swings.emplace_back(angle, inStrikeZone);
    }

    inFile.close();
    return swings;
}

// 파일에 데이터를 저장하고 출력하기 위해 saveDataToFile를 사용하였다.
void saveDataToFile(const string& filename, const vector<Data>& swings) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "파일 저장 중 오류가 발생했습니다: " << filename << endl;
        return;
    }

    for (const auto& swing : swings) {
        outFile << swing.getAngle() << " " << swing.isInStrikeZone() << endl;
    }

    outFile.close();
    cout << "결과가 저장되었습니다: " << filename << endl;
}

// 두 값을 비교하여 큰 값을 반환하기 위해 함수 중복을 사용하였다.
int big(int a, int b) {
    return (a > b) ? a : b;
}

double big(double a, double b) {
    return (a > b) ? a : b;
}

int main() {
    SetConsoleOutputCP(CP_UTF8); //한국어 인식이 되지 않아 사용하였다.

    vector<Data> swings; // 객체 배열을 사용하였다.
    Judge* angleJudge = new AngleJudge(); // 객체 포인터로 생성하였다.
    Judge* zoneJudge = new ZoneJudge();   // 객체 포인터로 생성하였다.

    
    string inputFilename = "input.txt";
    swings = loadDataFromFile(inputFilename);

    if (!swings.empty()) {
        cout << "파일에서 로드한 데이터와 판정 결과:" << endl;
        for (const auto& swing : swings) {
            string angleResult = angleJudge->judge(swing); // 포인터로 접근한다.
            string zoneResult = zoneJudge->judge(swing);   // 포인터로 접근한다.
            string finalResult = (angleResult == "각도 기반: 스트라이크" || zoneResult == "존 기반: 스트라이크")
                                 ? "최종 판정: 스트라이크"
                                 : "최종 판정: 볼";

            cout << "각도: " << swing.getAngle()
                 << ", 스트라이크 존 여부: " << (swing.isInStrikeZone() ? "예" : "아니오")
                 << ", " << angleResult
                 << ", " << zoneResult
                 << ", " << finalResult << endl;
        }

        // 연산자 중복을 위해 ==을 사용하였다.
        if (swings.size() > 1 && swings[0] == swings[1]) {
            cout << "첫 번째와 두 번째 스윙 데이터가 동일합니다." << endl;
        } else {
            cout << "첫 번째와 두 번째 스윙 데이터가 동일하지 않습니다." << endl;
        }
    } else {
        cout << "파일에서 로드할 데이터가 없습니다." << endl;
    }

    while (true) {
        double angle1 = getInput("스윙 각도를 입력하세요 (0~180도): ", 0, 180);
        double angle2 = getInput("비교할 두 번째 스윙 각도를 입력하세요 (0~180도): ", 0, 180);

        // 함수 중복(big) 사용
        double maxAngle = big(angle1, angle2);
        cout << "두 스윙 각도 중 큰 값은: " << maxAngle << "도 입니다." << endl;

        bool isInZone = static_cast<int>(getInput("공이 스트라이크 존에 들어갔습니까? (1: 예, 0: 아니오): ", 0, 1));
        swings.emplace_back(maxAngle, isInZone);

        string angleResult = angleJudge->judge(swings.back());
        string zoneResult = zoneJudge->judge(swings.back());
        string finalResult = (angleResult == "각도 기반: 스트라이크" || zoneResult == "존 기반: 스트라이크")
                             ? "최종 판정: 스트라이크"
                             : "최종 판정: 볼";

        cout << angleResult << ", " << zoneResult << ", " << finalResult << endl;

        char cont;
        while (true) {
            cout << "계속 입력하시겠습니까? (y/n): ";
            cin >> cont;

            if (cont == 'y' || cont == 'Y' || cont == 'n' || cont == 'N') {
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다. y 또는 n만 입력해주세요." << endl;
        }

        if (cont == 'n' || cont == 'N') {
            break;
        }
    }

    saveDataToFile("results.txt", swings);

    // 동적 객체 해제
    delete angleJudge;
    delete zoneJudge;

    cout << "프로그램을 종료하려면 아무 키나 누르세요..." << endl;
    cin.get();
    cin.get();

    return 0;
}
