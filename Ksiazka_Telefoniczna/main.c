#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



struct Element {
    char imie[20];
    char nazwisko[50];
    int nr_tel;
    struct Element* previous;
    struct Element* next;
};
struct Element* create_list()
{
    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element));
    if (NULL == new_node)
    {
        printf("blad przydzialu pamieci");
        return 0;
    }

    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;

}
struct Element* insert_before(struct Element** head, char imie[], char nazwisko[], int nr_tel)//dodaje element po lewej stronie od ,,glowy"
{
    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element));
    if (NULL == new_node)
    {
        printf("blad przydzialu pamieci");
        return 0;
    }
    strcpy_s(new_node->imie, sizeof(new_node->imie), imie);
    strcpy_s(new_node->nazwisko, sizeof(new_node->nazwisko), nazwisko);
    new_node->nr_tel = nr_tel;

    
    new_node->next = *head;
    new_node->previous = NULL;
    (*head)->previous = new_node;
    *head = new_node;
    
    /*
    new_node->next = (*head)->next;
    new_node->previous = *head;
    if ((*head)->next != NULL)
    {
        (*head)->next->previous = new_node;
    }
    (*head)->next = new_node;
    *head = new_node;
    */

    return new_node;


}

struct Element* insert_after(struct Element** head, char imie[], char nazwisko[], int nr_tel)//dodaje element po prawej stronie od ,,glowy" do poprawki
{

    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element));
    if (NULL == new_node)
    {
        printf("blad przydzialu pamieci");
        return 0;
    }
    strcpy_s(new_node->imie, sizeof(new_node->imie), imie);
    strcpy_s(new_node->nazwisko, sizeof(new_node->nazwisko), nazwisko);
    new_node->nr_tel = nr_tel;


    /*
    new_node->next = NULL;
    new_node->previous = *head;
    (*head)->next = new_node;
    *head = new_node;
    */


    new_node->next = (*head)->next;
    new_node->previous = *head;

    if ((*head)->next != NULL)
    {
        (*head)->next->previous = new_node;
    }

    (*head)->next = new_node;
    if (new_node->next != NULL) 
    {
        new_node->next->previous = new_node;
    }

    *head = new_node;
    

    return new_node;
}
void print_list(struct Element** head)//wyswietla cala liste
{
    //struct Element* current = (*head)->next;
    while (NULL != (*head)->next)
    {
        printf("Imie: %s\n", (*head)->imie);
        printf("Nazwisko: %s\n", (*head)->nazwisko);
        printf("Numer telefonu: %d\n\n", (*head)->nr_tel);
        *head = (*head)->next;
        //current = current->next;
    }

}
void print_values(struct Element** head)//wyswietla dane elementu w liscie
{
    printf("Imie: %s\nNazwisko: %s\nNumer telefonu: %d\n", (*head)->imie, (*head)->nazwisko, (*head)->nr_tel);
}

void set_head_front(struct Element** head)//przesuwa ,,glowe" czyli glowny wskaznik na poczatek listy
{
    while ((*head)->previous != NULL)
    {
        *head = (*head)->previous;
    }
}

struct Element* search_by_imie(struct Element** head, char imie_s[20])//wyszukuje po imieniu
{
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;
    while ((*head)->next != NULL)
    {
        //printf("%s\n", (*head)->imie);
        if (strcmp(imie_s, (*head)->imie) == 0)
        {	//je¿eli beda miely takie same wartosci kilka razy to trzeba wyswietlac do ostatniego
            found++;
            print_values(head);

        }

        if (strcmp(imie_s, (*head)->imie) != 0);
        {
            *head = (*head)->next;
        }

    }

    if (!found)
    {
        printf("Nie znaleziono osoby o imieniu %s \n", imie_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d", found);
    }

    return 0;//zwraca 0 jezeli nic nie znajdzie
}

struct Element* search_by_nazwisko(struct Element** head, char nazwisko_s[50])
{
    set_head_front(head);
    // Mozna dodac zabezpieczenie przez utworzenie tymczasowej 'glowy' struct Element *temp = *head;
    int found = 0;

    while (NULL != (*head)->next)
    {
        //printf("%s\n", (*head)->nazwisko);
        if (strcmp(nazwisko_s, (*head)->nazwisko) == 0)
        {
            found++;
            print_values(head);
            *head = (*head)->next;
        }
        else
        {
            *head = (*head)->next;
        }

    }
    if (!found)
    {
        printf("Nie znaleziono osoby o nazwisku %s \n", nazwisko_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d", found);
    }

    return 0;

};

struct Element* search_by_nrtel(struct Element** head, int nrtel_s)
{
    set_head_front(head);

    int found = 0;
    while (NULL != (*head)->next)
    {
        if (nrtel_s == (*head)->nr_tel)
        {
            found++;
            print_values(head);
            *head = (*head)->next;
        }
        else
        {
            *head = (*head)->next;
        }

    }
    if (!found)
    {
        printf("Nie znaleziono osoby o numerze telefonu %d \n", nrtel_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d", found);
    }

    return 0;

};

struct Element* search_by_imie_naziwsko(struct Element** head, char imie_s[20], char nazwisko_s[50])
{
    set_head_front(head);
    // Mozna dodac zabezpieczenie przez utworzenie tymczasowej 'glowy' struct Element *temp = *head;
    int found = 0;

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0))
        {
            found++;
            print_values(head);

            *head = (*head)->next;
        }
        else
        {
            *head = (*head)->next;
        }

    }
    if (!found)
    {
        printf("Nie znaleziono osoby  %s %s \n", imie_s, nazwisko_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d", found);
    }

    return 0;

};

struct Element* search_by_imie_naziwsko_nrtel(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s)
{
    set_head_front(head);
    // Mozna dodac zabezpieczenie przez utworzenie tymczasowej 'glowy' struct Element *temp = *head;
    int found = 0;

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0) && nrtel_s == (*head)->nr_tel)
        {
            found++;
            print_values(head);

            *head = (*head)->next;
        }
        else
        {
            *head = (*head)->next;
        }

    }
    if (!found)
    {
        printf("Nie znaleziono osoby  %s %s o numerze telefonu: %d\n", imie_s, nazwisko_s, nrtel_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d", found);
    }

    return 0;

};


int main()
{
    
    //TEST CZY DZIALA ALLEGRO 
    /*
    ALLEGRO_DISPLAY* display = NULL;

    al_init(); // inicjalizacja biblioteki Allegro
    display = al_create_display(640, 480); // utworzenie okna

    al_rest(5.0); // poczekaj 5 sekund

    al_destroy_display(display); // usunięcie okna
    //TEST ALLEGRO KONIEC
    */
    struct Element* head = create_list();

    //print_values(&head);
    insert_before(&head, "Kacper", "PierwszyDodanyPrzed", 222222222);
    //insert_before(&head, "Jan","Adamczyk", 333333333);
    //insert_before(&head, "Piotr", "Adamowicz", 111111111);
    //print_values(&head);

    insert_after(&head, "Dawid", "DrugiDodanyZa",333333333);
    insert_after(&head, "Kamil", "TrzeciDodanyZa", 333333333);
    insert_after(&head, "Kamil", "CzwartyDodanyZa", 333333333);
    //insert_before(&head, "Piotr", "CzwartyDodanyPrzed", 222222222);
    //print_values(&head);
    set_head_front(&head);
    print_list(&head);
    printf("\n\n\n");


    //search_by_imie(&head, "Piotr");
    //search_by_nazwisko(&head, "Adamczyk");
    //search_by_nrtel(&head, 222222222);
    //search_by_imie_naziwsko(&head, "Jan", "Adamczyk");
    //search_by_imie_naziwsko_nrtel(&head, "Kamil", "CzwartyDodanyZa", 333333333);
    
    return 0;
}