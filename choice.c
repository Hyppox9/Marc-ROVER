//
// Created by hugol on 22/11/2024.
//

#include "choice.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loc.h"


void selectMoves(Possible_Move *move) {
    move->root = NULL; // Initialiser la racine de la liste chaînée

    Move moves[8] = {
            {"Avancer de 10 m", 22},
            {"Avancer de 20 m", 15},
            {"Avancer de 30 m", 7},
            {"Reculer de 10 m en marche arriere", 7},
            {"Tourner d un quart de tour a gauche", 21},
            {"Tourner d un quart de tour a droite", 21},
            {"Faire demi-tour", 7},
            {"Faire rien", 0}
    };

    int numSelections = 9;
    for (int i = 0; i < numSelections; i++) {
        int totalProbability = 0;

        // Calculer la somme des probabilités
        for (int j = 0; j < 8; j++) {
            totalProbability += moves[j].probability;
        }

        // Tirage aléatoire
        int randValue = rand() % totalProbability;
        int cumulativeProbability = 0;
        int selectedIndex = -1;

        // Sélectionner le mouvement
        for (int j = 0; j < 8; j++) {
            cumulativeProbability += moves[j].probability;
            if (randValue < cumulativeProbability) {
                selectedIndex = j;
                break;
            }
        }

        // Afficher le mouvement sélectionné
        //printf("Mouvement selectionne: %s\n", moves[selectedIndex].name);

        // Créer un nouveau nœud pour le mouvement sélectionné
        Possible_Node_Move *newNode = (Possible_Node_Move *)malloc(sizeof(Possible_Node_Move));
        newNode->name = moves[selectedIndex].name; // Assigner le nom du mouvement
        newNode->next = NULL;

        // Ajouter le nouveau nœud à la liste chaînée
        if (move->root == NULL) {
            move->root = newNode; // Si la liste est vide, le nouveau nœud devient la racine
        } else {
            Possible_Node_Move *current = move->root;
            while (current->next != NULL) {
                current = current->next; // Parcourir jusqu'à la fin de la liste
            }
            current->next = newNode; // Ajouter le nouveau nœud à la fin
        }

        // Réduire la probabilité du mouvement sélectionné de 1%
        moves[selectedIndex].probability = (moves[selectedIndex].probability > 0) ? moves[selectedIndex].probability - 1 : 0;
    }
}

int getCostAtPosition(t_map map, t_position pos) {
    // Vérifier si la position est valide
    if (pos.x < 0 || pos.x >= map.x_max || pos.y < 0 || pos.y >= map.y_max) {
        fprintf(stderr, "Error: Invalid position (%d, %d)\n", pos.x, pos.y);
        return -1; // Indiquer une position invalide
    }
    // Retourner le coût à la position spécifiée
    return map.costs[pos.y][pos.x];
}
