//
// Created by zacky on 8/2/2021.
//

#ifndef FLOW_DRAW_H
#define FLOW_DRAW_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>

void draw(int students, int schools, std::map<int,std::pair<int,int>> school, std::vector<int>red, std::vector<int>green, std::vector<int>blue,  std::vector<std::vector<int>> neighborsInd);

#endif //FLOW_DRAW_H
