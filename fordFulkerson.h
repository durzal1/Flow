//
// Created by zacky on 8/1/2021.
//

#ifndef FLOW_FORDFULKERSON_H
#define FLOW_FORDFULKERSON_H
#include <bits/stdc++.h>
#include "Edge.h"
class fordFulkerson{
public:
    // max amount of nodes
    static const int MAX = 202;

    // neighbors of each node
    std::vector<Edge> neighbors[MAX];

    // neighbors of each node by index
    std::set<int> neighborsInd[MAX];

    // where the nodes came from
    std::vector<Edge> cameFrom[MAX];

    // map of edges that connect to the point
    // school, (rank, student)
    std::multimap<int,std::pair<int,int>> edgesConnect;

    // vector for all rgb values
    std::vector<int> red;
    std::vector<int> green;
    std::vector<int> blue;

    // school each student goes to and their ranking (found after findMaxFlow)
    // map<indexOfStudent, pair<indexOfSchool, ranking>>
    std::map<int,std::pair<int,int>> school;

    // max flow each node can hold
    int flow[MAX];

    // current flow of each node
    int curFlow[MAX];

    // amount of students
    int students;

    // for the loop
    int visitedToken = 1;
    int visited[MAX];

    // amount of schools
    int schools;

    // max flow in the system
    int maxFlow = 0;

    // constructor
    fordFulkerson(int students, int schools);

    // gets max flow
    int findMaxFlow(int cur, int flow);

    // fix the rankings of the choices
    void rankings();
};
#endif //FLOW_FORDFULKERSON_H
