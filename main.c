#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"
#include "choice.h"
#include <time.h>

int main() {
    t_map map;
    srand(time(NULL));
    // type de structure avec le nom du mouvement et sa probabilité:


    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    //Possible_Node_Move *move = malloc(sizeof(Possible_Node_Move));
    Possible_Node_Move *move = malloc(9*sizeof(Possible_Node_Move));
    move = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next->next->next->next->next = (Possible_Node_Move*) malloc(9*sizeof(Possible_Node_Move));
    move->next->next->next->next->next->next->next->next->next = NULL;

    selectMoves(move);
    Possible_Node_Move *current = move;
    print_move(move);

    t_localisation robot_loc;
    robot_loc.ori = NORTH;
    robot_loc.pos.x = 4;
    robot_loc.pos.y = 4;

    t_treeNode* root = set_arbre_choix(robot_loc, move,map);
    //printf("%d",root->value.cost);


    //t_position posValue = {robot_loc.pos.x,robot_loc.pos.y};
    //t_treeNode* root =  createNode(setNode_in_Tree(robot_loc,posValue, *move,map));

    printTree(root, 0);



    return 0;
}
