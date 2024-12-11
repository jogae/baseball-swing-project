#ifndef Save_H
#define Save_H

#include <string>
#include <vector>
#include "Data.h"
using namespace std;

class Save {
public:
    void log(const string& result) const;                 
    void save(const string& filename, const vector<Data>& swings) const; 
};

#endif
