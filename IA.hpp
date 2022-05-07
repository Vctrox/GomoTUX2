#include <iostream>
#include <unordered_map>
#include <vector>

#include "Board.hpp"

using namespace std;

class IA {
    private:
        unordered_map<string, int> hashMap;

    public:
        int evaluation(Board & board, bool isMax);
};