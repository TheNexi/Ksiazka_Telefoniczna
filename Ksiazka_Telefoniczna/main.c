#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "main.h"


struct Element // Struktura bazowa
{
    char imie[30];
    char nazwisko[50];
    int nr_tel;
    struct Element* previous; // wskaznik na poprzedni element w liscie
    struct Element* next; // wskaznik na nastepny element
};
struct Element* create_list() //tworzenie nowego węzła
{
    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element)); // dynamiczna alokacja pamięci dla nowego węzła
    if (NULL == new_node) // sprawdzanie czy alokacja sie powiodła
    {
        printf("blad przydzialu pamieci");
        return 0;
    }

    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node; // zwracanie wskaznika, ktory bedzie poczatkiem listy

}
struct Element* insert_before(struct Element** head, char imie[], char nazwisko[], int nr_tel)//dodaje element po lewej stronie od ,,glowy"
{
    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element)); // dynamiczna alokacja pamięci
    if (NULL == new_node) // sprawdzanie czy alokacja sie powiodła
    {
        printf("blad przydzialu pamieci");
        return 0;
    }
    strcpy_s(new_node->imie, sizeof(new_node->imie), imie); // kopiowanie imienia z parametru funkcji do pola bazowego funkcji
    strcpy_s(new_node->nazwisko, sizeof(new_node->nazwisko), nazwisko); // kopiowanie nazwiska z parametru funkcji do pola bazowego funkcji
    new_node->nr_tel = nr_tel; // kopiowanie nr telefonu z parametru funkcji do pola bazowego funkcji

    
    new_node->next = *head; // ustawienie wskaźnika następnego elementu na węzeł głowy listy
    new_node->previous = NULL; // ustawienie wskaźnika poprzedniego elementu na NULL
    (*head)->previous = new_node; // ustawienie wskaźnika poprzedniego elementu w głowie listy na nowy węzeł
    *head = new_node; // ustawienie wskaźnika na początek listy na nowy węzeł
  
    return new_node; // zwrócenie wskaźnika na nowy węzeł

}

/*
Funkcja do poprawienia 
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
*/

void print_list(struct Element** head)//wyswietla cala liste
{
    

    while (NULL != (*head)->next) // wykonywanie pętli do momentu osiągniecia ostatniego elementu listy
    {
        printf("Imie: %s\n", (*head)->imie); // wyswietlenie imienia osoby obecnie wskazywanej przez głowę listy
        printf("Nazwisko: %s\n", (*head)->nazwisko); // wyswietlenie nazwiska osoby obecnie wskazywanej przez głowę listy
        printf("Numer telefonu: %d\n\n", (*head)->nr_tel); // wyświetlenie numeru telefonu osoby obecnie wskazywanej przez głowę listy
        *head = (*head)->next; // przesuniecie wskaźnika na następny element listy
    }
    

}
void print_values(struct Element** head)//wyswietla dane elementu w liscie
{
    printf("Imie: %s\nNazwisko: %s\nNumer telefonu: %d\n", (*head)->imie, (*head)->nazwisko, (*head)->nr_tel);
}

void set_head_front(struct Element** head)//przesuwa ,,glowe" czyli glowny wskaznik na poczatek listy
{
    while ((*head)->previous != NULL) // sprawdza czy aktualna głowa nie jest początkiem listy
    {
        *head = (*head)->previous; // przesuwa wskaźnik na poprzedni element listy
    }
}

struct Element* search_by_imie(struct Element** head, char imie_s[20])//wyszukuje po imieniu
{
    printf("\nSzukane imie: %s \n", imie_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;
    while ((*head)->next != NULL)
    {
        if (strcmp(imie_s, (*head)->imie) == 0)
        {	//jezeli beda miely takie same wartosci kilka razy to trzeba wyswietlac do ostatniego
            found++; // zmienna zliczajaca wystapienia
            print_values(head);

        }

        if (strcmp(imie_s, (*head)->imie) != 0);
        {
            *head = (*head)->next; //przesuwa wskaznik na nastepny element jesli szukane imie nie pasuje
        }

    }

    if (!found)
    {
        printf("\nNie znaleziono osoby o imieniu %s \n\n", imie_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
    }

    return 0;//zwraca 0 jezeli nic nie znajdzie
}

struct Element* search_by_nazwisko(struct Element** head, char nazwisko_s[50])//wyszukuje po nazwisku
{
    printf("\nSzukane nazwisko: %s \n", nazwisko_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;

    while (NULL != (*head)->next)
    {
        if (strcmp(nazwisko_s, (*head)->nazwisko) == 0)
        {
            found++;
            print_values(head);
            *head = (*head)->next;
        }
        else
        {
            *head = (*head)->next;// przesuwa wskaznik na nastepny element jesli szukane nazwisko nie pasuje
        }

    }
    if (!found)
    {
        printf("\nNie znaleziono osoby o nazwisku %s \n\n", nazwisko_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
    }

    return 0;
};

struct Element* search_by_nrtel(struct Element** head, int nrtel_s)//wyszukuje po numerze telfonu
{
    printf("\nSzukany nr telefonu: %d \n", nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy

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
            *head = (*head)->next;//przesuwa wskaznik na nastepny element jesli szukany nr telefonu nie pasuje do obecnego elementu
        }

    }
    if (!found)
    {
        printf("\nNie znaleziono osoby o numerze telefonu %d \n\n", nrtel_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
    }

    return 0;

};

struct Element* search_by_imie_naziwsko(struct Element** head, char imie_s[20], char nazwisko_s[50])//wyszukuje po imieniu i nazwisku
{
    printf("\nSzukana osoba: %s %s \n", imie_s, nazwisko_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0))
        {
            found++;
            print_values(head);

            *head = (*head)->next;//przesuwa wskaznik na nastepny element po wyswietleniu pasujacej osoby
        }
        else
        {
            *head = (*head)->next;//przesuwa wskaznik na nastepny element jesli szukana osoba nie pasuje do obecnego elementu
        }

    }
    if (!found)
    {
        printf("\nNie znaleziono osoby %s %s \n\n", imie_s, nazwisko_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
    }

    return 0;

};

struct Element* search_by_imie_naziwsko_nrtel(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s)//wyszukuje po imieniu, nazwisku i numerze telefonu
{
    printf("\nSzukana osoba: %s %s %d \n", imie_s, nazwisko_s, nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0) && nrtel_s == (*head)->nr_tel)
        {
            found++;
            print_values(head);

            *head = (*head)->next;//przesuwa wskaznik na nastepny element po wyswietleniu pasującej osoby
        }
        else
        {
            *head = (*head)->next; //przesuwa wskaznik na nastepny element jesli szukana osoba nie pasuje do obecnego elementu
        }

    }
    if (!found)
    {
        printf("\nNie znaleziono osoby %s %s o numerze telefonu: %d\n\n", imie_s, nazwisko_s, nrtel_s);
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
    }

    return 0;

};

struct Element* edit_contact(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s, char imie_ed[20], char nazwisko_ed[50], int nrtel_ed)//wyszukuje po imieniu, nazwisku i numerze telefonu
{
    printf("\nSzukana osoba: %s %s %d \n", imie_s, nazwisko_s, nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0;

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0) && nrtel_s == (*head)->nr_tel)
        {
            found++;

            strcpy_s((*head)->imie, sizeof((*head)->imie), imie_ed); // edycja imienia z parametru funkcji do pola bazowego funkcji
            strcpy_s((*head)->nazwisko, sizeof((*head)->nazwisko), nazwisko_ed); // kopiowanie nazwiska z parametru funkcji do pola bazowego funkcji
            (*head)->nr_tel = nrtel_ed; // kopiowanie nr telefonu z parametru funkcji do pola bazowego funkcji

            *head = (*head)->next;//przesuwa wskaznik na nastepny element po edytowaniu pasujacej osoby
        }
        else
        {
            *head = (*head)->next; //przesuwa wskaznik na nastepny element jesli szukana osoba nie pasuje do obecnego elementu
        }

    }
    if (!found)
    {
        printf("\nNie znaleziono osoby %s %s o numerze telefonu: %d\n\n", imie_s, nazwisko_s, nrtel_s);
    }
    else
    {
        printf("\nZnaleziono osobe %s %s o numerze telefonu %d i zmieniono jej dane\n\n", imie_s, nazwisko_s, nrtel_s);

    }

    return 0;

};
void delete_element(struct Element** head)
{
    if (*head == NULL)
    {
        // Lista jest pusta
        return;
    }
    struct Element* temp = *head;
    if ((*head)->next == NULL)
    {
        (*head)->previous->next = NULL;
        (*head) = (*head)->previous;
        free(temp);
    }
    else if ((*head)->previous == NULL)
    {
        (*head)->next->previous = NULL;
        (*head) = (*head)->next;
        free(temp);
    }
    else
    {
        (*head)->previous->next = (*head)->next;
        (*head)->next->previous = (*head)->previous;
        (*head) = (*head)->next;
        free(temp);
    }

}

void swap(struct Element** a, struct Element** b)
{
    struct Element temp = **b;
    printf("\n------------------- temporary zmienna %d\n", temp.nr_tel);
    printf("\n------------------- a zmienna %d\n", (*a)->nr_tel);
    (*b)->nr_tel = (*a)->nr_tel;
    printf("\n------------------- temporary zmienna %d\n", temp.nr_tel);
    (*a)->nr_tel = temp.nr_tel;
    printf("\n\npo  zamianie a: %d  i b:%d\n ", (*a)->nr_tel, (*b)->nr_tel);
    
}

void sortList(struct Element** head) 
{
    if (*head == NULL || (*head)->next == NULL)
    {
        // Lista jest pusta lub zawiera tylko jeden element
        return;
    }

    int swapped;
    struct Element* current;
    struct Element* last = NULL;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != last)
        {
            if (current->nr_tel < current->next->nr_tel)
            {
                swap(&current->next, &current);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}/* {
    int i = 0; 
    struct Element temp = **head;
    for (i=0;i < 5;i++)
    {
        set_head_front(head);
        while ((*head)->next != NULL)
        {
            // printf("start petli");
            if ((*head)->next->nr_tel > (*head)->nr_tel)
            {
                swap(&(*head)->next, &(*head));

            }
            (*head) = (*head)->next;
        }
    }
}*/

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
    
    /*
    //Dodanie elementów do listy
    insert_before(&head, "Jan", "Adamczyk", 222222222);
    insert_before(&head, "Kacper", "Kowalski", 111111111);
    
    insert_before(&head, "Piotr", "Adamowicz", 333333333);
    insert_before(&head, "Filip", "Krawczyk", 987654321);
    insert_before(&head, "Tomasz", "Gracz", 123456789);

    //Ustawienie wskaznika na początek oraz wyświetlenie listy
    set_head_front(&head);
    print_list(&head);
    printf("\n\n\n");

    //Wyszukiwanie osob w liscie
    /*
    search_by_imie(&head, "Piotr");
    search_by_nazwisko(&head, "Adamczyk");
    search_by_nrtel(&head, 222222222);
    search_by_imie_naziwsko(&head, "Jan", "Kowalski");
    search_by_imie_naziwsko_nrtel(&head, "Kamil", "Adamczyk", 123456789);
    */

    search_by_imie(&head, "Kacper");
    printf("imie: %s", head->imie);
    //search_by_imie_naziwsko_nrtel(&head, "Kacper", "Kowalski", 111111111);
    printf("\nZamiana imienia na Piotrek i nr telefonu na 999999999\n");
    set_head_front(&head);
   // printf("head====%s\n nastepny=%s\n", head->imie,head->next->imie);
    sortList(&head);
    set_head_front(&head);
    print_list(&head);
    
    return 0;
}