#include "stdlib.h"
#include "stdio.h"

struct ListElem {
    float value;
    struct ListElem* next;
};
typedef struct ListElem ListElem;

struct LinkedList {
    ListElem sentinel_start;  // Sentinelle de début
    ListElem sentinel_end;    // Sentinelle de fin
};
typedef struct LinkedList LinkedList;

// Fonction pour créer une nouvelle liste
LinkedList* linked_list_new() {
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    // Initialisation des sentinelles
    l->sentinel_start.next = &(l->sentinel_end);
    l->sentinel_end.next = &(l->sentinel_end); // la sentinelle de fin pointe vers elle-même
    return l;
}

// Fonction pour afficher le contenu de la liste
void linked_list_print(LinkedList* list) {
    ListElem* elem = list->sentinel_start.next;  // On commence par le premier élément
    while (elem != &(list->sentinel_end)) {      // On s'arrête à la sentinelle de fin
        printf("%f ", elem->value);
        elem = elem->next;
    }
    printf("\n");
}

// Fonction pour libérer toute la mémoire allouée pour la liste
void linked_list_free(LinkedList* list) {
    ListElem* current = list->sentinel_start.next;
    while (current != &(list->sentinel_end)) {  // Tant qu'on n'atteint pas la sentinelle de fin
        ListElem* toDelete = current;
        current = current->next;  // On passe à l'élément suivant
        free(toDelete);  // Libère l'élément actuel
    }
    free(list);  // Libère la structure de la liste elle-même
}

// Fonction pour insérer un élément après un élément donné
void linked_list_insert_after(ListElem* elem, float toInsert) {
    ListElem* newElem = (ListElem*)malloc(sizeof(ListElem));
    newElem->value = toInsert;
    newElem->next = elem->next;
    elem->next = newElem;
}

// Fonction pour supprimer l'élément suivant un noeud donné
void list_elem_delete_after(ListElem* elem) {
    if (elem == NULL || elem->next == NULL) {
        return;
    }
    ListElem* toDelete = elem->next;
    elem->next = toDelete->next;
    free(toDelete);
}

// Fonction pour chercher un noeud contenant une valeur donnée
ListElem* linked_list_search(LinkedList* list, float toSearch) {
    ListElem* current = list->sentinel_start.next;
    while (current != &(list->sentinel_end)) {
        if (current->value == toSearch) {
            return current;  // Retourne l'élément trouvé
        }
        current = current->next;
    }
    return NULL;  // Retourne NULL si la valeur n'est pas trouvée
}

int main() {
    LinkedList* list = linked_list_new();  // On crée une liste chaînée
    ListElem* elem = &(list->sentinel_start);  // On prend l'élément de départ (sentinelle)
    
    // Insertion de quelques éléments après la sentinelle de début
    for (int i = 0; i < 4; i++) {
        linked_list_insert_after(elem, (float)i);  // Insertion de i
        elem = elem->next;  // On passe à l'élément suivant
    }
    
    // Affichage de la liste
    linked_list_print(list);  // Affiche 0 1 2 3
    
    // Insertion de nouveaux éléments après le deuxième élément
    elem = list->sentinel_start.next->next;  // On prend le 3e élément de la liste
    for (int i = 10; i < 14; i++) {
        linked_list_insert_after(elem, (float)i);  // Insertion de i
        elem = elem->next;  // On passe à l'élément suivant
    }
    
    // Affichage de la liste après les nouvelles insertions
    linked_list_print(list);  // Affiche 0 1 2 3 10 11 12 13
    
    // Libération de la mémoire allouée
    linked_list_free(list);
}
