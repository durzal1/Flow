//
// Created by zacky on 8/1/2021.
//

#ifndef FLOW_EDGE_H
#define FLOW_EDGE_H
class Edge{
public:
    // where it came from and where it is going
    int from;
    int to;

    // how much flow it currently has
    int flow = 0;

    // how much it it holds
    int capacity;

    // the rank of the connection (how much student wants it)
    int rank;

    Edge(int from, int to, int capacity, int rank = 1){
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->rank = rank;
    }

    int remainingCapacity(){
        return capacity - flow;
    }

    void augment(int bottleNeck){
        flow += bottleNeck;

    }
};
#endif //FLOW_EDGE_H
