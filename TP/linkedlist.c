#include "stdlib.h"
#include "stdio.h"

struct ListElem{
    float value;
    struct ListElem* next;
};
typedef struct ListElem ListElem ;

struct LinkedList{
    ListElem sentinel_start;
    ListElem sentinel_end;
};
typedef struct LinkedList LinkedList;


//////// FONCTIONS DEJA IMPLEMENTEES PLUS BAS
// crée une nouvelle liste
LinkedList* linked_list_new();

// affiche le contenu de la liste dans le terminal
void linked_list_print(LinkedList* list);




//////// FONCTIONS A IMPLEMENTER EX 1

// libère toute la mémoire allouée pour la liste
void linked_list_free(LinkedList* list);

// insère un element à la suite de l'élément donné
void linked_list_insert_after(ListElem* elem, float toInsert);



//////// FONCTIONS A IMPLEMENTER EX 2

// enlève l'élément suivant le noeud donné dans la liste
void list_elem_delete_after(ListElem* elem);

// cherche un noeud contenant la valeur donnée
ListElem* linked_list_search(LinkedList* list, float toSearch);



int main(){
    LinkedList* list = linked_list_new(); // on crée une liste chainée
    ListElem* elem = &(list->sentinel_start); // on prend le premier element
    for (int i = 0; i < 4; i++){ 
        linked_list_insert_after(elem, (float)i);
    }
    linked_list_print(list); // affiche 3 2 1 0
    elem = (list->sentinel_start).next->next;
    for (int i = 10; i < 14; i++){
        linked_list_insert_after(elem, (float)i);
    }
    linked_list_print(list); // affiche 3 2 13 12 11 10 1 0
    linked_list_free(list);
}


LinkedList* linked_list_new(){
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    l->sentinel_start.next = &(l->sentinel_end);
    l->sentinel_end.next = &(l->sentinel_end); // la sentinelle de fin pointe vers elle même
    return l;
}

void linked_list_print(LinkedList* list){
    for (ListElem* elem = list->sentinel_start.next; // on commence par le premier element
         elem->next != elem; // on ira jusqu'a la sentinelle de fin (qui pointe vers elle même)
         elem = elem->next){ // on avance d'un element a chaque iteration 
        printf("%f ", elem->value);
    }
    printf("\n");
}
