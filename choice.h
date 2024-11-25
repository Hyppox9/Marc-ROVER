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

typedef struct NodeMoveValue{
    int cost;
    char *name;
    t_localisation loc;
}NodeMoveValue;

typedef struct s_treeNode {
    NodeMoveValue value;
    struct s_treeNode* subBranches[9];
} t_treeNode;

Possible_Node_Move * selectMoves(Possible_Node_Move*);
int valeurAleatoire(int);
void print_move(Possible_Node_Move *);
t_treeNode* createNode(NodeMoveValue);
void printTree(t_treeNode* , int );
NodeMoveValue setNode_in_Tree(t_localisation, t_position , Possible_Node_Move, t_map );
int getCost(t_position, t_map );
t_treeNode *set_arbre_choix(t_localisation , Possible_Node_Move *,t_map );
#endif //UNTITLED1_CHOICE_H
