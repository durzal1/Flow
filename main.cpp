#include <bits/stdc++.h>
#include <ctime>
#include "fordFulkerson.h"
#include "draw.h"
int main(int argc, char* argv[]) {
    // for random
    srand(time(NULL));

    fordFulkerson graph(100,100); // for it to look good the students and schools have to be >= 9

    for (int f = graph.findMaxFlow(0,99999); f!= 0; f = graph.findMaxFlow(0,99999)){
        graph.visitedToken++;
        graph.maxFlow += f;
    }
    graph.rankings();
    std::vector<std::vector<int>> neighborsInd;
    neighborsInd.resize(202);
    for (int i = 0; i < 202; i++){
        for (int val:graph.neighborsInd[i]){
            neighborsInd[i].push_back(val);
        }
    }
    draw(graph.students, graph.schools, graph.school, graph.red, graph.green, graph.blue, neighborsInd);

    return 0;
}