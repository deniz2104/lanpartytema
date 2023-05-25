#include "my_library.h"
#define NUMBER_OF_TASKS 5

int main(int argc,char *argv[])  {
    if(argc<4)  {
        exit ( 1 ); 
    }
    int nr_echipe,iteratie_echipe_lista=0,task;
    char *inputfile=argv[1],*datafile=argv[2],*outfile=argv[3];
    FILE *inputFile,*dataFile,*outFile;
    inputFile = fopen(inputfile, "r"),dataFile = fopen(datafile, "r"),outFile = fopen(outfile, "w");
    if (inputFile == NULL || dataFile == NULL || outFile == NULL) {
        return 1; 
    }
    fscanf(dataFile,"%d",&nr_echipe);
    Node *head_lista_jucatori=NULL;
    head_lista_jucatori=(Node*) malloc(sizeof(Node));
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            completare_lista(&head_lista_jucatori,iteratie_echipe_lista,nr_echipe,dataFile);
            printfile(&head_lista_jucatori,outFile,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            modificare_lista(&head_lista_jucatori,&nr_echipe);
            printfile(&head_lista_jucatori,outFile,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            Queue* coada_matchuri=creare_coada();
            S* winners=creare_stiva();
            S* losers=creare_stiva();
            printfile(&head_lista_jucatori,outFile,outfile);
            afisare_rezultate_meciuri(&head_lista_jucatori,coada_matchuri,winners,losers,nr_echipe,outFile,outfile);
    }
    return 0;   
}