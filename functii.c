#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#define Nr_Max 100
#define epsilon 0.000001

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

//functie pentru adaugare in lista
void add_at_beginning(Node** head, FILE *filename)      {
    int nr_jucatori, puncte_jucator, i;
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->nume_echipa = (char*)malloc(Nr_Max * sizeof(char));
    fscanf(filename, "%d", &nr_jucatori);
    fgets(newnode->nume_echipa, Nr_Max, filename);
    (newnode->nume_echipa)++; //incrementez ca sa nu mai am spatiu la inceput
    newnode->nume_echipa[strcspn(newnode->nume_echipa, "\n")] = '\0';
    newnode->nr_jucatori = nr_jucatori;
    newnode->jucator=(struct Player*)malloc(newnode->nr_jucatori*sizeof(struct Player));
    for (i = 0; i < newnode->nr_jucatori; i++) {
        newnode->jucator[i].firstName = (char*)malloc(Nr_Max * sizeof(char));
        newnode->jucator[i].secondName = (char*)malloc(Nr_Max * sizeof(char));
        fscanf(filename, "%s", newnode->jucator[i].firstName);
        fscanf(filename, "%s", newnode->jucator[i].secondName);
        fscanf(filename, "%d", &puncte_jucator);
        newnode->jucator[i].points = puncte_jucator;
    }
newnode->next=*head;
*head=newnode;
}

void completare_lista(Node** head,int index,int numar_echipe,FILE* filename)    {
    while(index<numar_echipe)
            {
            add_at_beginning(&(*head),filename);
            index++;
            }
}

//functie pentru punerea in fisier a numelor echipelor
void printfile(Node** head,FILE* filename,const char* file)     {
    filename=fopen(file,"w");
    Node *iter=*head;
    while(iter->next!=NULL)
        {   
            fprintf(filename,"%s",iter->nume_echipa);
            fprintf(filename,"\n");
            iter=iter->next;
        }
        fclose(filename);
}

//functie pentru calcularea mediei aritmetice
float media_aritmetica(Node* head,int nr_jucatori)      {
int s=0,i;
for(i=0; i<nr_jucatori; i++)
{
    s+=head->jucator[i].points;
}
return (float)s/nr_jucatori;
}

//functie pentru initializarea scorurilor in cadrul fiecarei echipe pentru a fi mai usor de comparat apoi
void functie_pentru_score_in_lista(Node** head)     {
    Node *current=*head;
    while(current->next!=NULL)
    {
        current->score=media_aritmetica(current,current->nr_jucatori);
        current=current->next;
    }
}

//functie pentru a verifica daca un numar este multiplu de 2
int multiplu_de_2(int numar_echipe)     {
    while(numar_echipe>1 && numar_echipe%2==0 )
    {
        numar_echipe/=2;
    }
    if(numar_echipe!=1)
    {
        return 0;
    }
    else    {return 1;}
}

//functie pentru stergerea unui nod
void stergere_element_lista(Node** head, char* nume_echipa)     {
    if (*head == NULL) {
        return;
    }

    Node* headcopy = *head;
    Node* prev = NULL;

    if (strcmp(headcopy->nume_echipa, nume_echipa) == 0) {
        *head = headcopy->next;
        free(headcopy);
        return;
    }

    while (headcopy != NULL && strcmp(headcopy->nume_echipa, nume_echipa) != 0) {
        prev = headcopy;
        headcopy = headcopy->next;
    }

    if (headcopy == NULL) {
        return;
    }

    prev->next = headcopy->next;
    free(headcopy);
}

//functie care calculeaza care e echipa cu media minima din lista
void min(Node** head) {
    
    float min = INT_MAX;
    Node* min_node = NULL;

    Node* iter_gasire_minim = *head;
    while (iter_gasire_minim != NULL) {
        float avg = media_aritmetica(iter_gasire_minim, iter_gasire_minim->nr_jucatori);
        if (avg < min && fabs(min-avg)>epsilon) {
            min = avg;
            min_node = iter_gasire_minim;
        }
        iter_gasire_minim = iter_gasire_minim->next;
    }

        if (min_node != NULL) {
            stergere_element_lista(&(*head),min_node->nume_echipa);
        }
}

//functie pentru modificarea listei pana la 2^n
void modificare_lista(Node **head,int *numar_echipe)    {
while(multiplu_de_2(*numar_echipe)!=1)
    {
        min(&(*head));
        (*numar_echipe)--;
    }
}

//functie pentru crearea cozii
Queue* creare_coada()     {
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->front=q->rear=NULL;
    return q;
}

//functie pentru crearea stivei
S* creare_stiva()   {
    S* stacktop=NULL;
    return stacktop;
}

//functie pentru formarea cozii de fiecare data
void creare_queue_echipe(Queue* q, char* team_front, char* team_rear,float score_front,float score_rear)   {
    struct Match match;

    match.team1=strdup(team_front);
    match.team2=strdup(team_rear);
    match.score1=score_front;
    match.score2=score_rear;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->match = match;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

//functie pentru parcurgerea listei de inceput pentru a forma coada
void creare_din_lista(Node** head, Queue* q)    {
    Node* current = *head;
    while (current != NULL && current->next != NULL)
    {
        creare_queue_echipe(q, current->nume_echipa, current->next->nume_echipa,current->score,current->next->score);
        current = current->next->next;
    }
}

//functie pentru adaugarea in coada din stiva
void creare_din_lista_stack(S** stack,Queue *q)   {
    S* stacktop=*stack;
    while (stacktop!=NULL && stacktop->next !=NULL)
    {
        creare_queue_echipe(q,stacktop->team,stacktop->next->team,stacktop->score,stacktop->next->score);
        stacktop=stacktop->next->next;
    }
}

//functie pentru afisarea cozii in fisier
void printfile_queue(Queue* q,FILE* filename,const char* file)  {
    filename=fopen(file,"w");
    node *nod_temporar=q->front;
    while (nod_temporar!=NULL)
    {
        fprintf(filename,"%-30s - %-30s\n",nod_temporar->match.team1,nod_temporar->match.team2);
        nod_temporar=nod_temporar->next;
    }
    fclose(filename);
}

//functie pentru verificare daca stiva este goala
int isEmpty_stack(S* stack)   {
    return stack==NULL;
}

//functie pentru eliberarea din stiva, o folosesc in printfilestack
void pop(S** stack)     {
    S* nod_temporar=*stack;
    *stack=(*stack)->next;
    free(nod_temporar);

}

//functie pentru adaugarea in stiva,pt punerea echipelor in cele doua stive
void push(S** stack,char* nume_echipa,float score)    {
    S* newNode=(S*)malloc(sizeof(S));
    newNode->team=(char*)malloc(sizeof(char)*Nr_Max);
    newNode->team=strdup(nume_echipa);
    newNode->team[strcspn(newNode->team, "\n")] = '\0';
    newNode->score=score;
    newNode->next=*stack;
    *stack=newNode;
}

//functie pentru stergerea_elementelor_din stiva
void delete_stack(S** stack)    {
    S* stacktop;
    while((*stack)!=NULL)
    {
        stacktop=*stack;
        *stack=(*stack)->next;
        free(stacktop);
    }
}

//functie pentru afisarea stivei de invingatori
void printfile_stack(S* stack,Queue* q,FILE* filename,const char* file)  {
    filename=fopen(file,"w");
    S* stacktop=stack;
    while(!isEmpty_stack(stacktop))
    {
        fprintf(filename,"%s - %f\n",stacktop->team,stacktop->score);
        creare_din_lista_stack(&stack,q);
        pop(&stacktop);
    }
    fclose(filename);
}

//functie pentru a verifica daca coada este goala
int isEmpty_coada(Queue* q)     {
    return(q->front==NULL);
}

//functie pentru eliberarea cozii ca va trb sa o refacem
void stergere_queue(Queue *q)   {
    node* aux;
    while(!isEmpty_coada(q))
    {
        aux=q->front;
        q->front=q->front->next;
        free(aux);
    }
    free(q);
}

//functie pentru compararea scorurilor dintre cele doua echipe care realizeaza un meci
void comparare_rezultate_echipe_coada(Queue* q,S** winners,S** losers)      {
    node* nod_temporar=q->front;
    while(nod_temporar!=NULL)   {
        if(nod_temporar->match.score1>nod_temporar->match.score2)
        {
            push(winners,nod_temporar->match.team1,nod_temporar->match.score1+1);
            push(losers,nod_temporar->match.team2,nod_temporar->match.score2);
        }
        else {
            push(winners,nod_temporar->match.team2,nod_temporar->match.score2+1);
            push(losers,nod_temporar->match.team1,nod_temporar->match.score1);
        }
        nod_temporar=nod_temporar->next;
    }
}

//functie pentru eliminarea elementelor din lista din moment ce construiesc coada
void stergere_lista(Node** head)   {
    Node *current=*head;
    Node *temporar=NULL;

    while(current!=NULL)
    {
        temporar=current->next;
        free(current);
        current=temporar;
    }
    *head=NULL;
}

//afiseaza atat datele din coada cat si stiva de invingatori pana cand se ajunge la o echipa castigatoare
void afisare_rezultate_meciuri(Node** head,Queue* q,S** winners,S** losers,int nr_echipe,FILE* filename,const char* file)    {
    int runda=1;
    filename=fopen(file,"w");
    if(runda==1)
    {
        fprintf(filename,"--- ROUND NO:%d",runda);
        creare_din_lista(&(*head),q);
        stergere_lista(&(*head));
        printfile_queue(q,filename,file);
        comparare_rezultate_echipe_coada(q,&(*winners),&(*losers));
        stergere_queue(q);
        fprintf(filename,"WINNERS OF ROUND NO:%d",runda);
        printfile_stack((*winners),q,filename,file);
        delete_stack(&(*losers));
        runda++;
    }
    else
    {
        while(runda*2<nr_echipe)
        {
        fprintf(filename,"--- ROUND NO:%d",runda);
        printfile_queue(q,filename,file);
        comparare_rezultate_echipe_coada(q,&(*winners),&(*losers));
        stergere_queue(q);
        fprintf(filename,"WINNERS OF ROUND NO:%d",runda);
        printfile_stack((*winners),q,filename,file);
        delete_stack(&*(losers));
        runda++;
        }
    }
    fclose(filename);
}