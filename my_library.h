#include <stdio.h>
#include <stdlib.h>

typedef float Data;
typedef int Data_int;
typedef char string;


struct Player {
    char* firstName;
    char* secondName;
    int points;
};

struct lista {
    int nr_jucatori;
    float score;
    char *nume_echipa;
    struct Player* jucator;
    struct lista* next;
};

typedef struct lista Node;

struct Match    {
    char *team1,*team2;
    float score1,score2;
};

struct elem_queue   {
    struct Match match;
    struct elem_queue* next;
};

typedef struct elem_queue node;

struct Q {
    node *front,*rear;
};

typedef struct Q Queue;
typedef struct Match match;

struct stackNode    {
    char *team;
    float score;
    struct stackNode* next;
};
typedef struct stackNode S;

void add_at_beginning (Node **head,FILE* filename);
void printfile (Node** head,FILE* filename,const char* file);
void completare_lista (Node** head,int index,Data_int numar_echipe,FILE *filename);
void stergere_element_lista (Node** head,string nume_echipa);
void min (Node** head);
void functie_pentru_score_in_lista(Node** head);
void modificare_lista (Node** head,Data_int *numar_echipe);
Data media_aritmetica (Node* head,Data_int nr_jucatori);
Data_int multiplu_de_2 (Data_int numar_echipe);
Data_int isEmpty_stack(S* stack);
Data_int isEmpty_coada(Queue* q);
Queue* creare_coada();
S* creare_stiva();
void creare_queue_echipe(Queue* q,string* team_front,string* team_rear,Data score_front,Data score_rear);
void creare_din_lista(Node** head,Queue* q);
void printfile_queue(Queue* q,FILE* filename,const char* file);
void printfile_stack(S* stack,FILE* filename,const char* file);
void stergere_queue(Queue* q);
void stergere_lista(Node** head);
void push(S** stack,string* nume_echipa,Data score);
void pop(S** stack);
void delete_stack(S** stack);
void comparare_rezultate_echipe_coada(Queue* q,S** winners,S** losers);
void afisare_rezultate_meciuri(Node** head,Queue* q,S* winners,S* losers,Data_int nr_echipe,FILE* filename,const char* file);
void creare_din_lista_stack(S** stack,Queue* q);