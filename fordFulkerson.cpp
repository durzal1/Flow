//
// Created by zacky on 8/1/2021.
//
#include "fordFulkerson.h"
#include "random.h"
#include <bits/stdc++.h>
// randomly sets the neighbors of the students
fordFulkerson::fordFulkerson(int students, int schools) {
    this->students = students;
    this->schools = schools;


    // sets the rest to 0
    for (int i = 1; i < MAX; i++){
        flow[i] = 0;
        curFlow[i] = 0;
    }
    // sets first node to infinite
    flow[0] = 999999999;
    flow[students+schools+1] = 999999999;
    curFlow[0] = 9999999;

    for (int i = 1 ;i <= students; i++){
        // for each student(i) they get a random amount of connections
        int conns = randomint(0,schools);

        // sets each student to have 1 flow
        flow[i] = 1;

        // sets each student to a neighbor of first node(source)
        Edge edge = Edge(0,i, 1);
        neighbors[0].push_back(edge);

        // ranks each connection
        std::vector<int> ranks;
        for (int j = 0; j < conns; j++){
            int num = randomint(1,conns);
            bool subtract = true;
            while (std::find(ranks.begin(), ranks.end(), num) != ranks.end()){
                if (num > 1 && subtract){
                    num--;
                }else if (num == 1 && subtract) subtract = false;
                if (!subtract){
                    num++;
                }
            }
            ranks.push_back(num);
        }
        // for each connection randomly assign it to a school
        for (int j = 0; j < conns; j++){
            // runs loop until it adds the connection
            bool run = true;
            while (run){
                // add students to it to get the correct index
                int index = randomint(1,schools) + students;

                int size = neighborsInd[i].size();
                neighborsInd[i].insert(index);
                if (neighborsInd[i].size() > size){
                    // edge we are checking for
                    Edge look = Edge(i,index,1,ranks[j]);

                    // unique connection
                    neighbors[i].push_back(look);

                    // add where it came from
                    cameFrom[index].push_back(neighbors[i][j]);

                    // adds one flow to neighbors
                    // this will be used to see how many nodes are connected to it
                    flow[index] ++;
                    break;
                }
            }
        }
    }
    // sets the neighbors of the schools
    for (int i = 1; i <= schools; i++){
        // amount of students the school will hold
        int num = randomint(1,abs(students - schools) + 1);

        Edge edge = Edge(i+students, schools+students+1, num);
        neighbors[i+students].push_back(edge);

        // sets how many students each school can hold to
        // formula is -> amount of connections to it / 2
        flow[i+students] = ceil((flow[i+students]+0.0f) / 2);
    }

    // creates random rgb values for all the students
    for (int i = 0; i < students; i++){
        red.push_back(randomint(0,255));
        green.push_back(randomint(0,255));
        blue.push_back(randomint(0,255));
    }
}

int fordFulkerson::findMaxFlow(int cur, int flow) {
    // if its at the sink
    if (cur == schools+1+students){
        return flow;
    }

    // mark the current node as visited
    visited[cur] = visitedToken;

    for (Edge &edge:neighbors[cur]){
        if (edge.remainingCapacity() > 0 && visited[edge.to] != visitedToken){
            int bottleNeck = findMaxFlow(edge.to, std::min(flow, edge.remainingCapacity()));

            // if we made it to the end then we augment flow
            if (bottleNeck > 0){
                edge.augment(bottleNeck);
                for (int i = 0; i < cameFrom[edge.to].size(); i++){
                    Edge &edge2 = cameFrom[edge.to][i];
                    if (edge2.to == edge.to && edge2.from == edge.from){
                        // same edge
                        edge2.flow = edge.flow;
                    }
                }
                // makes sure its from the beginning or to the sink
                if (edge.to != students + schools + 1 && edge.from != 0){
                    // adds the edge to edgesConnect
                    edgesConnect.emplace(edge.to, std::make_pair(edge.rank, edge.from));
                }

                return bottleNeck;
            }
        }
    }
    return 0;
}
void fordFulkerson::rankings() {
    // iterates through all the winners to get the initial values
    for (std::map<int, std::pair<int,int>>::iterator it = edgesConnect.begin();
             it != edgesConnect.end();++it){
        school.emplace(it->second.second, std::make_pair(it->first, it->second.first));
    }
    // iterate through each school and add the winner to the map
    for (int i = 1; i < schools; i++){
        int ind = schools + i;

        // current node's ranking
        int curRank;

        bool breakT = false;

        int lastSchoolInd = 99999;
        // iterates through all the "winners"
        // A winner is somebody who got accepted to a school
        if (edgesConnect.find(ind) != edgesConnect.end()){
            for (std::map<int, std::pair<int,int>>::iterator it = edgesConnect.begin();
                 it != edgesConnect.end();++it){
                if (breakT) break;
                bool foundMatch = false;
                bool fakeFoundMatch = false;
                if (it->first == ind){
                    // if the school is the one we're looking for

                    // student1 index
                    int s1 = it->second.second;

                    std::vector<Edge> Edges = cameFrom[ind];
                    curRank = it->second.first;

                    // iterates through all the possibilities and puts them all in a vector
                    std::vector<std::pair<int,int>> first;
                    std::vector<std::pair<int,int>> second;

                    // what the ith s2 index is
                    std::vector<int> s2Vals;

                    // looks at the other students who could have gone to that school
                    for (Edge edge:Edges){
                        if (foundMatch) break;
                        if (edge.flow == 0){
                            // students also cant be part of this school
                            for (std::map<int, std::pair<int,int>>::iterator it2 = edgesConnect.begin();
                                 it2 != edgesConnect.end();++it2){
                                if (it2->first == lastSchoolInd){
                                    // might be going through an infinite loop so we break it.
                                    foundMatch = true;
                                    break;
                                }
                                if (foundMatch || fakeFoundMatch){
                                    fakeFoundMatch = false;
                                    break;
                                }
                                int s2 = it2->second.second;
                                // if they're part of another school
                                if (it2->second.second == edge.from){
                                    // check if student1 is interested in this school
                                    auto thing = std::find(neighborsInd[s1].begin(), neighborsInd[s1].end(), it2->first);

                                    if (thing != neighborsInd[s1].end()){
                                        // student1 has a link that reaches this school therefore he is interested in it

                                        for (int IT = 0; IT < neighbors[s1].size(); IT++) {
                                            Edge F = neighbors[s1][IT];
                                            // if new school has a higher rank
                                            if (F.to != it2->first) continue;
                                            if (curRank > neighbors[s1][IT].rank){

                                                // check if it has an open spot
                                                if (neighbors[it2->first][0].remainingCapacity() != 0){
                                                    // switch it with the other spot
                                                    neighbors[it2->first][0].flow++;
                                                    school[s1] = std::make_pair(F.to,neighbors[s1][IT].rank);
                                                    foundMatch = true;
                                                    it--;
                                                }
                                                else{
                                                    // add the two potential values to a vector
                                                    first.emplace_back(F.to,neighbors[s1][IT].rank);
                                                    second.emplace_back(ind,edge.rank);
                                                    s2Vals.push_back(s2);
                                                    fakeFoundMatch = true;
                                                }
                                                break;
                                            }

                                        }

                                    }
                                }
                            }
                        }
                    }
                    if (!foundMatch && !first.empty()){
                        int min = 999999;
                        for (auto & C : first){
                            min = std::min(C.second, min);
                        }
                        for (int C = 0; C < first.size(); C++){
                            if (first[C].second == min){
                                school[s1] = first[C];
                                school[s2Vals[C]] = second[C];

                                // update edgeconnect
                                // iterate through edge connect till it finds the values
                                for (std::map<int, std::pair<int,int>>::iterator iterator = edgesConnect.begin();
                                     iterator != edgesConnect.end();++iterator){
                                    if (iterator->first == ind && iterator->second.second == s1){
                                        // found s1
                                        iterator->second.second = s2Vals[C];
                                        iterator->second.first = second[C].second;
                                    }
                                    if (iterator->first == first[C].first && iterator->second.second == s2Vals[C]){
                                        iterator->second.second = s1;
                                        iterator->second.first = first[C].second;
                                    }
                                }
                                s1 = s2Vals[C];
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

