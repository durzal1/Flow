//
// Created by zacky on 7/14/2021.
//

#ifndef FLOW_MAZE_RANDOM_H
#define FLOW_MAZE_RANDOM_H
#include <random>
#include <iostream>
#include "time.h"


double randomfloat(float min, float max){
    float a = static_cast<float>(rand()) / RAND_MAX * (max - min) + min;
    return a;

}
int randomint(int min, int max){
    // sets another time to add more rng
    int b = rand()%(max-min+1)+min;
    return b;

}

#endif //FLOW_MAZE_RANDOM_H
