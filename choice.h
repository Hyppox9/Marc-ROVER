//
// Created by hugol on 22/11/2024.
//

#ifndef UNTITLED1_CHOICE_H
#define UNTITLED1_CHOICE_H
#include "map.h"
#include "loc.h"

typedef struct Move {
    char *name;
    int probability;
} Move;

typedef struct Possible_Node_Move {
    char *name;
    struct Possible_Node_Move *next;
} Possible_Node_Move;

typedef struct Possible_Move {
    Possible_Node_Move *root;
} Possible_Move;


typedef struct s_treeNode {
    int value;
    struct Node* subBranches[8];
} t_treeNode;

void selectMoves(Possible_Move*);
int getCostAtPosition(t_map, t_position);
#endif //UNTITLED1_CHOICE_H
