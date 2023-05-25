# Checker Tema 1 - 2021
Checker-ul este o aplicație de testare automată a temelor. Este un produs open-source realizat de către și pentru studenții din Facultatea de Automatică și Calculatoare - UPB, și este menit atât să usureze munca asistenților de a corecta teme cât și sa ofere studenților o evaluare cât mai obiectivă.

## Rularea checker-ului
Pentru a verifica functionarea checker-ului va trebui sa descarcati tot depozitul de mai sus, dupa aceasta deschideti un terminal in folderul in care se afla depozitul descarcat si scrieti urmatoarea comanda:
```shell
./checker.sh
```
In primul rand se vor creea mai multe structuri aferente:
- o structura Player in care se va retine numele prenumele si punctele
- o structura lista in care vom tine evidenta numarului de jucatori,score-ul,numelui echipei,un pointer pentru elem urmator
- o structura match in care se vor gasi detaliile legate despre coada de match-uri
- o structura pentru memorarea informatiilor despre stiva

Task1:
Functia add_at_beginning(Node** head,FILE* filename):
-vom creea un nod nou de tip Node* in care vom stoca informatiile pe care le vom citi din fisierul pe care il deschidem
-vom adauga elementele la inceput conform cerintei

Functia completare_lista(Node** head,int numar_echipe,FILE* filename):
-va completa lista in functie de numarul de echipe care este transmis ca parametru

Functia printfile(Node** head,FILE* filename,const char* file)
-deschide fisierul de out si se pun in fisier numele din echipe din lista conform cerintei
-se inchide fisierul

Task2:
Functia media_aritmetica(Node *head,int nr_jucatori):
-calculeaza score-ul initial pentru fiecare echipa

Functia stergere_element_lista(Node** headm,char* nume_echipa):
-va elimina echipa aferenta cerintei si sunt incluse toate cazurile:
cazul in care capul de lista este gol
cazul in care este primul element
cazul in care se afla oriunde altundeva 
vom sterge elementul cu ajutorul functiei free si vom realiza legaturile intre nodul de dinainte si nodul de dupa nodul sters
-va fi apelata (&(*head),....) in functia min care gaseste echipa cu score ul cel mai mic iar fabs(min-avg)>epsilon,unde epsilon=0.000001 acopera cazul in care trebuie sa fie eliminata prima echipa si nu mai trebuie o a doua parcurgere

Functia modificare_lista(Node** head,int *numar_echipe)
-va apela cele doua functii:multiplu_de_2 prin care se verifica daca numarul de echipe este multiplu de 2(conditie de stop)
si functia min prin care se va elimina echipa cu score ul minim 
-numar_echipe este transmis prin referinta deoareece i se va modifica valoarea




