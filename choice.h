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
    struct s_treeNode* subBranches[9];
} t_treeNode;

void selectMoves(Possible_Move*);
int getCostAtPosition(t_map, t_position);
t_treeNode* createNode(int);
void printTree(t_treeNode*, int);
#endif //UNTITLED1_CHOICE_H
