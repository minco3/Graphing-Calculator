#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using namespace std;

int random(int x, int y) { // generates a random int between x and y
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(x,y);
    return dist(mt);
}

int fastrand(int x) { 
        return rand()%x;
} 

#endif //RANDOM_H