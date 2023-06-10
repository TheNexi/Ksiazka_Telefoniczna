#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro5.h>



/**
* @brief zmienna przechowująca aktualnie największe ID
*/

int max_id;
/**
*
* @brief Struktura bazowa zawierająca wskazniki na poprzedni i nastepny element wraz z niezbednymi polami typu string tj. imie, nazwisko, nr _tel
*/
struct Element
{
    char imie[20];
    char nazwisko[50];
    int nr_tel;
    int ID;
    struct Element* previous; // wskaznik na poprzedni element w liscie
    struct Element* next; // wskaznik na nastepny element
};

/** 
*
* @brief funkcja tworząca liste
* @return zwraca wskaznik na nowy wezel
*/
struct Element* create_list() 
{
    struct Element* new_node = (struct Element*)malloc(sizeof(struct Element)); // dynamiczna alokacja pamięci dla nowego węzła
    if (NULL == new_node) // sprawdzanie czy alokacja sie powiodła
    {
        printf("blad przydzialu pamieci");
        return 0;
    }
    max_id = 0;
    new_node->ID = 0;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node; // zwracanie wskaznika, ktory bedzie poczatkiem listy

}
/**  
* 
* @brief dodaje nowy element do listy, przypisując kolejno podane w parametrze listy
* @param **head to podwójny wskaznik na ,,głowę" listy
* @param imie[] to ciag znakow bedacy składową nowego elementu
* @param nazwisko[] to ciag znakow bedacy składową nowego elementu
* @param nr_tel to ciag znakow bedacy składową nowego elementu
* @return zwraca ten element
*/
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
    max_id += 1;
    new_node->ID = max_id;
    
    new_node->next = *head; // ustawienie wskaźnika następnego elementu na węzeł głowy listy
    
    new_node->previous = NULL; // ustawienie wskaźnika poprzedniego elementu na NULL
    (*head)->previous = new_node; // ustawienie wskaźnika poprzedniego elementu w głowie listy na nowy węzeł
    *head = new_node; // ustawienie wskaźnika na początek listy na nowy węzeł
  
    return new_node; // zwrócenie wskaźnika na nowy węzeł
}
/**
*
*@brief
*funkcja sluzaca do wyswietlania calej zawartosci listy
*@param **head to podwójny wskaźnik na ,,głowę" listy
*/
void print_list(struct Element** head)//wyswietla cala liste
{

    while (NULL != (*head)->next) // wykonywanie pętli do momentu osiągniecia ostatniego elementu listy
    {
        if ((*head)->ID != NULL)
        {
            printf("ID:%d\nImie: %s\n", (*head)->ID, (*head)->imie); // wyswietlenie imienia osoby obecnie wskazywanej przez głowę listy
            printf("Nazwisko: %s\n", (*head)->nazwisko); // wyswietlenie nazwiska osoby obecnie wskazywanej przez głowę listy
            printf("Numer telefonu: %d\n", (*head)->nr_tel); // wyświetlenie numeru telefonu osoby obecnie wskazywanej przez głowę listy
            printf("__________________________\n");
        }
        *head = (*head)->next; // przesuniecie wskaźnika na następny element listy
    }
    if ((*head)->ID != 0)
    {
        printf("ID:%d\nImie: %s\n", (*head)->ID, (*head)->imie); // wyswietlenie imienia osoby obecnie wskazywanej przez głowę listy
        printf("Nazwisko: %s\n", (*head)->nazwisko); // wyswietlenie nazwiska osoby obecnie wskazywanej przez głowę listy
        printf("Numer telefonu: %d\n", (*head)->nr_tel); // wyświetlenie numeru telefonu osoby obecnie wskazywanej przez głowę listy
        printf("__________________________\n");
    }
}
/**  
* @brief
* funkcja sluzaca do wyswietlania zawartosci pojedynczego elementu listy
*/
void print_values(struct Element** head)//wyswietla dane elementu w liscie
{
    printf("Imie: %s\nNazwisko: %s\nNumer telefonu: %d\n", (*head)->imie, (*head)->nazwisko, (*head)->nr_tel);
}
/**
* @brief
* funkcja slużąca do ustawiania ,,głowy" listy na jej początku
*/
void set_head_front(struct Element** head)//przesuwa ,,glowe" czyli glowny wskaznik na poczatek listy
{
    while ((*head)->previous != NULL) // sprawdza czy aktualna głowa nie jest początkiem listy
    {
        *head = (*head)->previous; // przesuwa wskaźnik na poprzedni element listy
    }
    
}
/**
* @brief funkcja slużąca do ustawiania ,,głowy" listy na jej końcu
*/
void set_head_back(struct Element** head)//przesuwa ,,glowe" czyli glowny wskaznik na poczatek listy
{
    while ((*head)->next != NULL) // sprawdza czy aktualna głowa nie jest początkiem listy
    {
        *head = (*head)->next; // przesuwa wskaźnik na poprzedni element listy
    }
}
/**
* @brief funkcja slużąca do wyszukiwania w liście elementów po imieniu
* @return zwraca 0 jezeli nie znaleziono 
*/
struct Element* search_by_imie(struct Element** head, char imie_s[20])//wyszukuje po imieniu
{
    printf("\nSzukane imie: %s \n", imie_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji
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

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
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
/**
* @brief funkcja slużąca do wyszukiwania w liście elementów po nazwisku
* @return zwraca 0 jezeli nie znaleziono
*/
struct Element* search_by_nazwisko(struct Element** head, char nazwisko_s[50])//wyszukuje po nazwisku
{
    printf("\nSzukane nazwisko: %s \n", nazwisko_s);
    set_head_front(*head);//ustawia wskaznik na poczatek listy
    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji

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

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
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
/**
* @brief funkcja slużąca do wyszukiwania w liście elementów po numerze telefonu
* @return zwraca 0 jezeli nie znaleziono
*/
struct Element* search_by_nrtel(struct Element** head, int nrtel_s)//wyszukuje po numerze telfonu
{
    printf("\nSzukany nr telefonu: %d \n", nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy

    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji
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

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
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
/**
* @brief funkcja slużąca do wyszukiwania w liście elementów po imieniu i nazwisku
* @return zwraca 0 jezeli nie znaleziono
*/
struct Element* search_by_imie_naziwsko(struct Element** head, char imie_s[20], char nazwisko_s[50])//wyszukuje po imieniu i nazwisku
{
    printf("\nSzukana osoba: %s %s \n", imie_s, nazwisko_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji

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

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
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
/**
* @brief funkcja slużąca do wyszukiwania w liście elementów po imieniu, nazwisku i numerze telefonu
* @return zwraca 0 jezeli nie znaleziono
*/
bool search_by_imie_naziwsko_nrtel(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s)//wyszukuje po imieniu, nazwisku i numerze telefonu
{
    printf("\nSzukana osoba: %s %s %d \n", imie_s, nazwisko_s, nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji

    while (NULL != (*head)->next)
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0) && nrtel_s == (*head)->nr_tel)
        {
            found++;
            //print_values(head);

            *head = (*head)->next;//przesuwa wskaznik na nastepny element po wyswietleniu pasującej osoby
        }
        else
        {
            *head = (*head)->next; //przesuwa wskaznik na nastepny element jesli szukana osoba nie pasuje do obecnego elementu
        }

    }

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
    if (!found)
    {
        printf("\nNie znaleziono osoby %s %s o numerze telefonu: %d\n\n", imie_s, nazwisko_s, nrtel_s);
        return false;
    }
    else
    {
        printf("\nZnaleziono pasujace osoby w liczbie: %d\n\n", found);
        return true;
    }


};
/**
* @brief funkcja slużąca do edytowania kontaktu
* @return zwraca 0 jezeli nie znaleziono
*/
struct Element* edit_contact(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s, char imie_ed[20], char nazwisko_ed[50], int nrtel_ed)//wyszukuje po imieniu, nazwisku i numerze telefonu
{
    printf("\nSzukana osoba: %s %s %d \n", imie_s, nazwisko_s, nrtel_s);
    set_head_front(head);//ustawia wskaznik na poczatek listy
    int found = 0; //Zmienna pomocznicza do wyświetlenia informacji o powodzeniu operacji

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

    //Wyswietlanie informacji o powodzeniu operacji bądź nie
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
/**
* @brief funkcja slużąca do usuwania elementow z listy
*/
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
/**
* @brief Funkcja szukająca elementu o podanym imieniu, nazwisku i nr tel
*/
bool search_and_set(struct Element** head, char imie_s[20], char nazwisko_s[50], int nrtel_s)//Funckja szukająca elementu o podanym imieniu, nazwisku i nr tel
{
    if (*head == NULL) //Sprawdzenie czy lista jest pusta
    {
        printf("Lista jest pusta.\n");
        return false;
    }

    set_head_front(head); // Ustawienie głowy na początek listy
    while (NULL != (*head)->next) // Warunek przejścia do ostatniego elementu
    {
        if ((strcmp(imie_s, (*head)->imie) == 0) && (strcmp(nazwisko_s, (*head)->nazwisko) == 0) && nrtel_s == (*head)->nr_tel) //Warunek znalezienia odpowiedniego elementu
        {
            return true; //Zwrócenie wartości true jeżeli uda się znaleźć element
            break;
        }
        else
        {
            *head = (*head)->next; //Przesuwanie sie po liscie
        }
    }

    return false; //Zwrócenie false jeżeli nie uda się znaleźć elementu o podanych parametrach
    // Jeżeli nie znaleziono elementu, wyświetl komunikat
    printf("Nie znaleziono osoby %s %s %d.\n", imie_s, nazwisko_s, nrtel_s);
}
/**
* @brief Funkcja szukająca elementu o podanym ID i ustawiająca na nim ,,głowę" listy
*/
bool search_id_and_set(struct Element** head, int id)//Funckja szukająca elementu o podanym imieniu, nazwisku i nr tel
{
    if (*head == NULL) //Sprawdzenie czy lista jest pusta
    {
        printf("Lista jest pusta.\n");
        return false;
    }

    set_head_front(head); // Ustawienie głowy na początek listy
    while (NULL != (*head)->next) // Warunek przejścia do ostatniego elementu
    {
        if  (id == (*head)->ID) //Warunek znalezienia odpowiedniego elementu
        {
            return true; //Zwrócenie wartości true jeżeli uda się znaleźć element
            break;
        }
        else
        {
            *head = (*head)->next; //Przesuwanie sie po liscie
        }
    }

    return false; //Zwrócenie false jeżeli nie uda się znaleźć elementu o podanych parametrach
    // Jeżeli nie znaleziono elementu, wyświetl komunikat
    printf("Nie znaleziono osoby o id %d\n", id);
}


/**
* @brief Funkcja zamieniająca dwa elementy w liscie
* @param **a podwojny wskaznik na pierwszy z zamienianych elementow
* @param **a podwojny wskaznik na drugi z zamienianych elementow
*/
void swap(struct Element** a, struct Element** b) 
{
    //Zmienna tymczasowa struktury bazowej do przechowywania wartosci pól podczas zamiany miejscami
    struct Element temp = **b;

    //Zamiana nr tel
    temp.nr_tel = (*b)->nr_tel;
    //printf("\n------------------- temporary zmienna %d\n", nr_tel);
    //printf("\n------------------- a zmienna %d\n", (*a)->nr_tel);
    (*b)->nr_tel = (*a)->nr_tel;
    //printf("\n------------------- temporary zmienna %d\n", nr_tel);
    (*a)->nr_tel = temp.nr_tel;
    //printf("\n\npo  zamianie a: %d  i b:%d\n ", (*a)->nr_tel, (*b)->nr_tel);

    temp.ID = (*b)->ID;
    (*b)->ID = (*a)->ID;
    (*a)->ID = temp.ID;

    //Zamiana imion, ograniczając kopie do rozmiaru tablicy -1 znak dla znaku końca ciągu
    strncpy_s(temp.imie, sizeof(temp.imie), (*b)->imie, sizeof(temp.imie) - 1);
    strncpy_s((*b)->imie, sizeof((*b)->imie), (*a)->imie, sizeof((*b)->imie) - 1);
    strncpy_s((*a)->imie, sizeof((*a)->imie), temp.imie, sizeof((*a)->imie) - 1);

    //Zamiana nazwisk, z ograniczeniem -1 znak jak wyżej
    strncpy_s(temp.nazwisko, sizeof(temp.nazwisko), (*b)->nazwisko, sizeof(temp.nazwisko) - 1);
    strncpy_s((*b)->nazwisko, sizeof((*b)->nazwisko), (*a)->nazwisko, sizeof((*b)->nazwisko) - 1);
    strncpy_s((*a)->nazwisko, sizeof((*a)->nazwisko), temp.nazwisko, sizeof((*a)->nazwisko) - 1);
}

/**
* @brief Funkcja sortująca liste po numerze telefonu
* @param **head zawiera podwojny wskaznik na glowe listy
*/
void sortList(struct Element** head) //Funkcja sortująca po nr telefonu malejąco
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

}
/**
* @brief Funkcja sortująca liste po numerze telefonu rosnaco
* @param **head zawiera podwojny wskaznik na glowe listy
*/
void sortListNrTelRos(struct Element** head)
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
            if (current->nr_tel > current->next->nr_tel)
            {
                swap(&current->next, &current);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}
/**
* @brief Funkcja eksportująca elementy listy do pliku
* @param *head zawiera wskaznik na glowe listy
*/
void export_phonebook_to_file(char* file_name, struct Element* head) //Funkcja do eksportu elementów listy do pliku
{
    FILE *file; //Utworzenie zmiennej do operacji na pliku
    if (fopen_s(&file, file_name, "w") != 0) //Otworzenie pliku o nazwie z parametru w trybie zapisu oraz sprawdzenie czy sprawdzenie czy się powiodło
    {
        printf("Błąd podczas otwierania pliku.\n"); //Komunikat o błędzie
        return; //Zakończenie pętli jeżeli plik nie zostanie otwarty
    }

    set_head_front(&head); //Ustawienie głowy na początek listy

    while (NULL != head->next) // Warunek przejścia do ostatniego elementu
    {
        //Zapis danych do pliku
        fprintf(file, "%s\n", head->imie); 
        fprintf(file, "%s\n", head->nazwisko);
        fprintf(file, "%d\n", head->nr_tel);
        head = head->next; //Przesuwanie się po liście
    }

    //Zamkniecie pliku po eksporcie kontakow oraz wyświetlenie komunikatu
    fclose(file); 
    printf("Dane zostaly zapisane do pliku.\n");

}
/**
* @brief Funkcja importująca elementy listy z pliku
* @param **head zawiera podwojny wskaznik na glowe listy
* @param *file_name ciag znakow zawierajacy nazwe pliku 
*/
void import_phonebook_from_file(char* file_name, struct Element** head) //Funkcja do importu kontaktow z pliku do listy
{
    FILE* file; //Utworzenie zmiennej do operacji na pliku
    if (fopen_s(&file, file_name, "r") != 0) //Otworzenie pliku o nazwie z parametru w trybie odczytu oraz sprawdzenie czy się powiodło
    {
        //Wyświetelnie komunikatu błędu oraz zakończenie funkcji
        printf("Błąd podczas otwierania pliku.\n");
        return;
    }
    set_head_front(head);
    //Zmienne tymczasowe do przechowywania wczytywanego kontaktu
    char imie[20];
    char nazwisko[50];
    int nr_tel;

    //Wczytywanie kolejnych lini pliku oraz przypisywanie wczytanych wartości do zmiennych tymczasowych
    while (fscanf_s(file, "%19s\n%49s\n%d\n", imie, sizeof(imie), nazwisko, sizeof(nazwisko), &nr_tel) == 3) //Warunek == 3 sprawdza czy zostały wczytane dokładnie trzy wartości odpowiadające za informacje o kontakcie
    {
        insert_before(head, imie, nazwisko, nr_tel); //Dodawanie nowych elementów do listy
    }

    //Zamknięcie pliku po imporcie kontaktow oraz wyświetlenie komunikatu
    fclose(file); 
    printf("Dane zostaly wczytane z pliku.\n");
}
/**
* @brief Funkcja sortująca elementy listy po imieniu
* @param **head zawiera podwojny wskaznik na glowe listy
* @param dir parametr informujacy o tym czy wartosci maja byc sortowane rosnaco czy malejaco
*/
void sortListByString(struct Element** head,bool dir)
{
    //set_head_front(head);
    int swapped;
    struct Element* ptr1;
    struct Element* lptr = NULL;

    if (*head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (compareStrings(ptr1->imie, ptr1->next->imie,dir) > 0) {
                swap_string(ptr1, ptr1->next);
                printf("dziala");
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
/**
* @brief Funkcja sortująca elementy listy po nazwisku
* @param **head zawiera podwojny wskaznik na glowe listy
* @param dir parametr informujacy o tym czy wartosci maja byc sortowane rosnaco czy malejaco
*/
void sortListByString_surname(struct Element** head, bool dir)
{
    //set_head_front(head);
    int swapped;
    struct Element* ptr1;
    struct Element* lptr = NULL;

    if (*head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (compareStrings(ptr1->nazwisko, ptr1->next->nazwisko, dir) > 0) {
                swap_string(ptr1, ptr1->next);
                printf("dziala");
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
/**
* @brief funkcja zamieniająca ze soba dwa elementy listy jednak po lancuchach
* @param *a wskaznik na pierwszy element
* @param *b wskaznik na drugi element
*/
int swap_string(struct Element* a, struct Element* b) 
{
    //Zmienne tymczasowe do przechowywania wartosci pól podczas zamiany miejscami
    char temp_imie[20];
    char temp_nazwisko[50];

    //Zamiana nr tel
    int nr_tel=a->nr_tel;
    a->nr_tel = b->nr_tel;
    b->nr_tel = nr_tel;
 
    int temp = a->ID;
    temp = b->ID;
    b->ID = a->ID;
    a->ID = temp;

    //Zamiana imion, ograniczając kopie do rozmiaru tablicy -1 znak dla znaku końca ciągu
    strncpy_s(temp_imie, sizeof(temp_imie), a->imie, sizeof(temp_imie) - 1);
    strncpy_s(a->imie, sizeof(a->imie), b->imie, sizeof(a->imie) - 1);
    strncpy_s(b->imie, sizeof(b->imie), temp_imie, sizeof(b->imie) - 1);

    //Zamiana nazwisk, z ograniczeniem -1 znak jak wyżej
    strncpy_s(temp_nazwisko, sizeof(temp_nazwisko), a->nazwisko, sizeof(temp_nazwisko) - 1);
    strncpy_s(a->nazwisko, sizeof(a->nazwisko), b->nazwisko, sizeof(a->nazwisko) - 1);
    strncpy_s(b->nazwisko, sizeof(b->nazwisko), temp_nazwisko, sizeof(b->nazwisko) - 1);
}
/** 
* @brief funkcja porownujaca dwa ciagi znakow ze soba
* @param *a wskaznik na pierwszy element
* @param *b wskaznik na drugi element
* @param dir parametr informujący o tym w którą strone ma porównywać
*/
int compareStrings(const char* a, const char* b,bool dir) 
{
    if (dir==1)
    return strcmp(a, b);
    else 
    return strcmp(b, a);
}

/** 
* 
*@brief funkcja porownujaca dwa ciagi znakow ze soba bez wybory kierunku
* @param *a wskaznik na pierwszy element
* @param *b wskaznik na drugi element
*/
int compare(const char* a, const char* b)
{
    
        return strcmp(b, a); // Porównanie w odwrotnej kolejności (malejąco)
  
}
/**
* 
*@brief Funkcja sortująca listę malejąco alfabetycznie według nazwiska
* @param **lista wskaznik zawierajacy adres poczatku listy
*/
void sortuj(struct Element** lista) {
    struct Element* current;
    struct Element* next;
    int swapped;

    // Sprawdź, czy lista jest pusta lub zawiera tylko jeden element
    if (*lista == NULL || (*lista)->next == NULL)
        return;

    do {
        
        swapped = 0;
        current = *lista;

        while (current->next != NULL) {
            
            next = current->next;
            if ((*lista)->nazwisko==NULL||next==NULL||(*lista)==NULL)
            {
                printf("\n-------------------KONIEC");
                swapped = 0;
                break;
            }
           printf("\naktualne nazwisko: %s\n",current->nazwisko);
            // Porównaj nazwiska
            if (compare(current->nazwisko, next->nazwisko) > 0) {
                // Zamień kolejność elementów
                if (current->previous != NULL)
                    current->previous->next = next;
                else
                    *lista = next;

                next->previous = current->previous;
                current->previous = next;
                current->next = next->next;

                if (next->next != NULL)
                    next->next->previous = current;

                next->next = current;
                swapped = 1;
                
            }
            else {
                current = current->next;
            }
        }
        if (swapped == 0)
        {
            printf("\n-------------------KONIEC");
            swapped = 0;
            break;
        }
    } while (swapped);
}

/**
* 
 * @brief główna funkcja zawierająca menu, mozliwosc wyboru funkcji, pobieranie danych od uzytkownika..
*/
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

    struct Element* head = create_list(); // utworzenie listy 

    //TEST
    //Dodanie elementów do listy
    /*
    insert_before(&head, "kacper", "kowalski", 111111111);
    insert_before(&head, "jan", "adamczyk", 222222222);
    insert_before(&head, "piotr", "adamowicz", 333333333);
    insert_before(&head, "filip", "krawczyk", 987654321);
    insert_before(&head, "tomasz", "gracz", 123456789);


    insert_before(&head, "Kacper\n", "Kowals\n", 111111111);
    insert_before(&head, "Jan\n", "Adamcz\n", 222222222);
    insert_before(&head, "Piotr\n", "Adamow\n", 333333333);
    insert_before(&head, "Filip\n", "Krawczyk\n", 987654321);
    insert_before(&head, "Tomasz\n", "Gracz\n", 123456789);

    */

    //print_list(&head);
    //printf("po sortowaniu:\n\n\n");
    //print_list(&head);


    //Interfejs konsolowy start
    printf("Oto program ksiazki telefonicznej\n");

    //Zmienne potrzebne do menu
    int wybor = 0;
    int wybor_sortowania = 0;
    int wybor_ros_mal = 0;

    //Zmienne do dodawania kontatku
    char imie[30];
    char nazwisko[50];
    char nr_tel_temp[30];
    int nr_tel = 0;

    //Zmienne do edycji kontaktu
    char imie_edycja[30];
    char nazwisko_edycja[50];
    int nr_tel_edycja = 0;
    int nr_tel_temp_edycja = 0;


    while (wybor != 8) //Pętla główna menu
    {
        //Menu podstawowe
        printf("\nWybierz opcje dzialania:\n");
        printf("1. Wyswietl ksiazke telefoniczna\n2. Dodaj osobe do ksiazki telefonicznej\n3. Edytuj osobe w ksiazce telefonicznej\n4. Usun osobe z ksiazki telefonicznej\n5. Sortuj liste\n6. Import kontakow z pliku\n7. Eksport kontaktow do pliku\n8. Zakoncz program\nWybrana opcja: ");
        scanf_s("%d", &wybor);
        switch (wybor)
        {
        case 1:
        {
            //Wyswietlanie listy
            set_head_front(&head);
            print_list(&head);
           
            break;
        }
        case 2:
        {
            //Dodawanie osoby       
            while (getchar() != "\n")
            {
                printf("Podaj imie: ");
                fgets(imie, sizeof(imie), stdin);
                break;
            }


            printf("Podaj nazwisko: ");
            fgets(nazwisko, sizeof(nazwisko), stdin);



            printf("Podaj nr tel: ");
            fgets(nr_tel_temp, sizeof(nr_tel_temp), stdin);
            nr_tel = atoi(nr_tel_temp); //Konwersja string to int
            set_head_front(&head);
            //set_head_back(&head);
            insert_before(&head, imie, nazwisko, nr_tel);

            break;

        }
        case 3:
        {
            //Edytowanie osoby
            while (getchar() != "\n")
            {
                printf("Podaj imie osoby do edycji: ");
                fgets(imie, sizeof(imie), stdin);
                break;
            }


            printf("Podaj nazwisko osoby do edycji: ");
            fgets(nazwisko, sizeof(nazwisko), stdin);



            printf("Podaj nr tel osoby do edycji: ");
            fgets(nr_tel_temp, sizeof(nr_tel_temp), stdin);
            nr_tel = atoi(nr_tel_temp);

            if (search_by_imie_naziwsko_nrtel(&head, imie, nazwisko, nr_tel))
            {
                printf("Podaj imie na jakie chcesz zmienic: ");
                fgets(imie_edycja, sizeof(imie_edycja), stdin);

                printf("Podaj nazwisko na jakie chcesz zmienic: ");
                fgets(nazwisko_edycja, sizeof(nazwisko_edycja), stdin);


                printf("Podaj nr tel na jakie chcesz zmienic: ");
                fgets(nr_tel_temp_edycja, sizeof(nr_tel_temp_edycja), stdin);
                nr_tel_edycja = atoi(nr_tel_temp_edycja);
                edit_contact(&head, imie, nazwisko, nr_tel, imie_edycja, nazwisko_edycja, nr_tel_edycja);

            }
            else
            {
                printf("\nNie znaleziono osoby %s %s o numerze telefonu: %d\nPrzerwano edycje!\n", imie, nazwisko, nr_tel);
            }

            break;

        }
        case 4:
        {
            printf("1.Po imieniu, nazwisku numerze telefonu.\n2. po ID\n");
            int wybor;
            wybor = 0;
            scanf_s("%d", &wybor);
            if (wybor == 1)
            {
                //Usuwanie osoby z listy
                {
                    while (getchar() != "\n")
                    {
                        printf("Podaj imie: ");
                        fgets(imie, sizeof(imie), stdin);
                        break;
                    }

                    printf("Podaj nazwisko: ");
                    fgets(nazwisko, sizeof(nazwisko), stdin);

                    printf("Podaj nr tel: ");
                    fgets(nr_tel_temp, sizeof(nr_tel_temp), stdin);
                    nr_tel = atoi(nr_tel_temp); //Konwersja string to int

                    if (search_and_set(&head, imie, nazwisko, nr_tel)) //Ustawienie głowy na osobie do usuniecia
                    {
                        delete_element(&head);
                        printf("\nUsunieto osobe %s %s %d\n", imie, nazwisko, nr_tel);
                    }
                    else
                    {
                        printf("\nNie znaleziono takiej osoby\n");
                    }

                    break;
                }
            }
            if (wybor == 2)
            {
                //Usuwanie osoby z listy
                {


                    int id;
                    printf("Podaj ID : ");
                    scanf_s("%d", &id);

                    if (search_id_and_set(&head, id)) //Ustawienie głowy na osobie do usuniecia
                    {
                        delete_element(&head);
                        printf("\nUsunieto osobe");
                    }
                    else
                    {
                        printf("\nNie znaleziono takiej osoby\n");
                    }

                    break;

                }
            }
        }
        case 5:
        {
            //Sortowanie
            set_head_front(&head);

            while (getchar() != "\n")
            {
                printf("\n1. Sortowanie po nr telefonu\n2. Sortowanie po imieniu\n3. Sortowanie po nazwisku\n4. Powrot do menu\nWybrana opcja: ");
                scanf_s("%d", &wybor_sortowania);
                break;
            }
            if (wybor_sortowania == 1)
            {
                printf("\n1. Sortowanie rosnaco\n2. Sortowanie malejaco\n3. Powrot do menu\nWybrana opcja: ");
                scanf_s("%d", &wybor_ros_mal);

                if (wybor_ros_mal == 1)
                {
                    //Sortowanie rosnaco po nr telefonu
                    sortListNrTelRos(&head);
                    print_values(&head);
                    printf("\nSortowanie po numerze telefonu rosnaco wykonane.\n");
                    break;
                }
                else if (wybor_ros_mal == 2)
                {
                    //Sortowanie malejaco po nr telefonu
                    sortList(&head);
                    printf("\nSortowanie po numerze telefonu malejaco wykonane.\n");
                    break;
                }
                else
                {
                    //Obsluga blednego wyboru
                    printf("\nBledny wybor sortowania! Powrot do menu.\n");
                    break;
                }

            }
            else if (wybor_sortowania == 2)
            {
                printf("\n1. Sortowanie rosnaco\n2. Sortowanie malejaco\n3. Powrot do menu\nWybrana opcja: ");
                scanf_s("%d", &wybor_ros_mal);

                if (wybor_ros_mal == 1)
                {
                    //Sortowanie rosnaco po imieniu
                    sortListByString(&head, 1);
                    printf("\nSortowanie po imieniu rosnaco wykonane.\n");
                    break;
                }
                else if (wybor_ros_mal == 2)
                {
                    //Sortowanie malejaco po imieniu
                    sortListByString(&head, 0);
                    printf("\nSortowanie po imieniu malejaco wykonane.\n");
                    break;
                }
                else
                {
                    //Obsluga błędnego wyboru
                    printf("\nBledny wybor sortowania! Powrot do menu.\n");
                    break;
                }

                break;
            }
            else if (wybor_sortowania == 3)
            {
                printf("\n1. Sortowanie rosnaco\n2. Sortowanie malejaco\n3. Powrot do menu\nWybrana opcja: ");
                scanf_s("%d", &wybor_ros_mal);

                if (wybor_ros_mal == 1)
                {
                    //Sortowanie rosnąco po nazwisku
                    set_head_front(&head);

                    sortListByString_surname(&head, 1);
                    break;
                }
                else if (wybor_ros_mal == 2)
                {
                    //Sortowanie malejąco po nazwisku
                    sortListByString_surname(&head, 0);
                    break;
                }
                else
                {
                    //Obsługa błędnego wyboru
                    printf("\nBledny wybor sortowania! Powrot do menu.\n");
                    break;
                }

                break;
            }
            else if (wybor_sortowania == 4)
            {
                //Powrot do menu
                break;
            }
            else
            {
                //Obsługa błędnego wyboru
                printf("\nBledny wybor! Powrot do menu.\n");
                break;
            }

        }
        case 6:
        {
            //Import z pliku
            import_phonebook_from_file("kontakty_eksport.txt", &head);

            break;
        }
        case 7:
        {
            //Eksport do pliku
            export_phonebook_to_file("kontakty_eksport.txt", head);

            break;
        }
        case 8:
        {
            //Zakończ program
            break;


        }
        default:
        {
            //Obsluga blednego wyboru
            printf("ERROR! Wybierz opcje od 1 do 5");
            break;
        }
            }


        }


        //Interfejs konsolowy koniec

        return 0;
    }
