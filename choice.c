//
// Created by hugol on 22/11/2024.
//

#include "choice.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loc.h"
#include <time.h>

int valeurAleatoire(int x) {
    // Générer une valeur aléatoire entre 0 et x
    return rand() % (x + 1);
}

Possible_Node_Move* selectMoves(Possible_Node_Move* move) {

    Move moves[7] = {
            {"Avancer de 10 m", 22},
            {"Avancer de 20 m", 15},
            {"Avancer de 30 m", 7},
            {"Reculer de 10 m", 7},
            {"Tourner d un quart de tour a gauche", 21},
            {"Tourner d un quart de tour a droite", 21},
            {"Faire demi-tour", 7}
    };

    int totalChances = 0;
    Possible_Node_Move *current = move;

    // Calculer le total des chances
    for (int j = 0; j < 7; j++) {
        totalChances += moves[j].probability;
    }
    while (current != NULL) {
        int randomValue = valeurAleatoire(totalChances);

		int cumulativeProbability = 0;
		for (int j = 0; j < 7; j++) {
			cumulativeProbability += moves[j].probability;
			if (randomValue < cumulativeProbability) {
				current->name = moves[j].name;
				moves[j].probability--; // Décrémenter la probabilité choisie
				totalChances--;
				break;
			}
		}

        current = current->next; // Passer au prochain mouvement
    }

    return move; // Retourner le pointeur vers la liste de mouvements
}

void print_move(Possible_Node_Move *move){
    Possible_Node_Move *current = move;
    while (current != NULL){
        printf("\n%s",current->name);
        current = current->next;
    }
}

t_treeNode* createNode(NodeMoveValue value) {
    t_treeNode* newNode = (t_treeNode*)malloc(sizeof(t_treeNode));
    newNode->value.loc = value.loc;
    newNode->value.cost = value.cost;
    newNode->value.name = value.name;
    for (int i = 0; i < 9; i++) {
        newNode->subBranches[i] = NULL; // Initialiser les sous-branches à NULL
    }
    return newNode;
}

void printTree(t_treeNode* node, int level) {
    if (node == NULL) return;

    // Affichage de la valeur du nœud
    printf("%*s%d\n", level * 4, "", node->value.cost); // Indentation dynamique

    // Affichage des sous-branches
    for (int i = 0; i < 9; i++) {
        if (node->subBranches[i] != NULL) {
            printTree(node->subBranches[i], level + 1);
        }
    }
}

int getCost(t_position pos, t_map map) {
    // Vérifier les limites avant d'accéder à la matrice
    if (pos.x < 0 || pos.x >= map.x_max || pos.y < 0 || pos.y >= map.y_max) {
        //printf("Position hors limites: (%d, %d)\n", pos.x, pos.y);
        return 10000; // Indique un coût invalide
    }

    // Retourner le coût
    return map.costs[pos.x][pos.y];
}

NodeMoveValue setNode_in_Tree(t_localisation loc,t_position pos_Move, Possible_Node_Move move_name, t_map map) {
    char *name = move_name.name;
    Move moves[7] = {
            {"Avancer de 10 m", 22},
            {"Avancer de 20 m", 15},
            {"Avancer de 30 m", 7},
            {"Reculer de 10 m", 7},
            {"Tourner d un quart de tour a gauche", 21},
            {"Tourner d un quart de tour a droite", 21},
            {"Faire demi-tour", 7}
    };

    NodeMoveValue donne;
    donne.name = name; // Correction ici pour assigner la chaîne correctement

    int NewX = loc.pos.x;
    int NewY = loc.pos.y;
    t_orientation NewOri = loc.ori;

    if (move_name.name == moves[0].name){
        switch (loc.ori){
            case NORTH:
                NewY -= 1;
                break;
            case SOUTH:
                NewY += 1;
                break;
            case WEST:
                NewX -= 1;
                break;
            case EAST:
                NewX += 1;
                break;
        }
    }else if (move_name.name == moves[1].name) {
        switch (loc.ori) {
            case NORTH:
                NewY -= 2;
                break;
            case SOUTH:
                NewY += 2;
                break;
            case WEST:
                NewX -= 2;
                break;
            case EAST:
                NewX += 2;
                break;
        }
    }else if (move_name.name == moves[2].name) {
        switch (loc.ori) {
            case NORTH:
                NewY -= 3;
                break;
            case SOUTH:
                NewY += 3;
                break;
            case WEST:
                NewX -= 3;
                break;
            case EAST:
                NewX += 3;
                break;
        }
    }else if (move_name.name == moves[3].name) {
        switch (loc.ori) {
            case NORTH:
                NewY += 1;
                break;
            case SOUTH:
                NewY -= 1;
                break;
            case WEST:
                NewX += 1;
                break;
            case EAST:
                NewX -= 1;
                break;
        }
    }else if (move_name.name == moves[4].name) {
        switch (loc.ori) {
            case NORTH:
                NewOri = WEST;
                break;
            case SOUTH:
                NewOri = EAST;
                break;
            case WEST:
                NewOri = SOUTH;
                break;
            case EAST:
                NewOri = NORTH;
                break;
        }
    }else if (move_name.name == moves[5].name) {
        switch (loc.ori) {
            case NORTH:
                NewOri = EAST;
                break;
            case SOUTH:
                NewOri = WEST;
                break;
            case WEST:
                NewOri = NORTH;
                break;
            case EAST:
                NewOri = SOUTH;
                break;
        }
    }else if (move_name.name == moves[6].name) {
        switch (loc.ori) {
            case NORTH:
                NewOri = SOUTH;
                break;
            case SOUTH:
                NewOri = NORTH;
                break;
            case WEST:
                NewOri = EAST;
                break;
            case EAST:
                NewOri = WEST;
                break;
        }
    }

    t_position pos = {NewY,NewX};
    int cost = getCost(pos, map);
    //printf("%d a %d ",NewX,NewY);

    // Mettre à jour la position
    donne.loc.pos.x = NewX;
    donne.loc.pos.y = NewY;
    donne.loc.ori = NewOri; // Mettre à jour l'orientation
    donne.cost = cost;

    return donne;
}

t_treeNode *set_arbre_choix(t_localisation loc, Possible_Node_Move *move,t_map map) {
    t_position posValue = {loc.pos.x,loc.pos.y};
    t_treeNode * root;
    NodeMoveValue t_root_value;
    t_root_value.loc = loc;
    t_root_value.cost = getCost(loc.pos,map);
    t_root_value.name = "Robot pos";

    root = createNode(t_root_value);
    int i = 0;
    Possible_Node_Move *current = move;
    while (current != NULL) {
        Possible_Node_Move moov_choose;
        moov_choose.name = current->name;
        root->subBranches[i] = createNode(setNode_in_Tree(loc, posValue, moov_choose, map));
        int k = 0;
        for (int j = 0;j<9;j++){
            loc = root->subBranches[i]->value.loc;
            posValue.x = loc.pos.x;
            posValue.y = loc.pos.y;
            if (j != i){
                if (root->subBranches[i]->value.cost > 1000) break;
                moov_choose.name = root->subBranches[i]->value.name;
                root->subBranches[i]->subBranches[k] = createNode(setNode_in_Tree(loc, posValue, moov_choose, map));
                int m = 0;
                for(int l = 0;l<9;l++){
                    loc = root->subBranches[i]->subBranches[k]->value.loc;
                    posValue.x = loc.pos.x;
                    posValue.y = loc.pos.y;
                    if(l != i && l != j){
                        if (root->subBranches[i]->subBranches[k]->value.cost > 1000) break;
                        moov_choose.name = root->subBranches[i]->subBranches[k]->value.name;
                        root->subBranches[i]->subBranches[k]->subBranches[m] = createNode(setNode_in_Tree(loc, posValue, moov_choose, map));
                        int n = 0;
                        for(int o = 0;o<9;o++){
                            loc = root->subBranches[i]->subBranches[k]->subBranches[m]->value.loc;
                            posValue.x = loc.pos.x;
                            posValue.y = loc.pos.y;
                            if(o != i && o != j){
                                if (root->subBranches[i]->subBranches[k]->subBranches[m]->value.cost > 1000) break;
                                moov_choose.name = root->subBranches[i]->subBranches[k]->subBranches[m]->value.name;
                                root->subBranches[i]->subBranches[k]->subBranches[m]->subBranches[n] = createNode(setNode_in_Tree(loc, posValue, moov_choose, map));
                                int p = 0;
                                for(int q = 0;q<9;q++){
                                    loc = root->subBranches[i]->subBranches[k]->subBranches[m]->subBranches[n]->value.loc;
                                    posValue.x = loc.pos.x;
                                    posValue.y = loc.pos.y;
                                    if(q != i && q != j && q != l && q != o){
                                        if (root->subBranches[i]->subBranches[k]->subBranches[m]->subBranches[n]->value.cost > 1000) break;
                                        moov_choose.name = root->subBranches[i]->subBranches[k]->subBranches[m]->subBranches[n]->value.name;
                                        root->subBranches[i]->subBranches[k]->subBranches[m]->subBranches[n]->subBranches[p] = createNode(setNode_in_Tree(loc, posValue, moov_choose, map));
                                        p++;
                                    }
                                }
                                n++;
                            }
                        }
                        m++;
                    }
                }
                k++;
            }
        }
        current = current->next;
        //printf("\n%d",i);
        i++;
    }
    return root;
}

BetterChoice calculatebetter(t_treeNode* node) {
    int test =0;
    int min = 1000;
    BetterChoice better;better.cost = 0;better.loc.pos.x = 0;better.loc.pos.y = 0;better.loc.ori = NORTH;
    int a,b,c,d,e,f =0;
    if (node != NULL){
        a = node->value.cost;
        for (int i=0;i<9;i++){
            if (node->subBranches[i] != NULL) {
                b = node->subBranches[i]->value.cost + a;
                for (int j=0;j<9;j++){
                    if (node->subBranches[i]->subBranches[j] != NULL){
                        c = node->subBranches[i]->subBranches[j]->value.cost + b;
                        for (int k=0;k<9;k++){
                            if (node->subBranches[i]->subBranches[j]->subBranches[k] != NULL){
                                d = node->subBranches[i]->subBranches[j]->subBranches[k]->value.cost + c;
                                for (int l=0;l<9;l++){
                                    if (node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l] != NULL){
                                        e = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->value.cost + d;
                                        for (int m=0;m<9;m++){
                                            if (node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m] != NULL){
                                                f = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.cost + e;
                                                if (node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.cost < min && e<1000){
                                                    better.cost = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.cost;
                                                    better.loc.pos.x = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.loc.pos.x;
                                                    better.loc.pos.y = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.loc.pos.y;
                                                    better.loc.ori = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.loc.ori;
                                                    min = node->subBranches[i]->subBranches[j]->subBranches[k]->subBranches[l]->subBranches[m]->value.cost;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return better;
}