#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ZADATAK:
Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste (u mom sluèaju briše cijelu listu)
U zadatku se ne smiju koristiti globalne varijable
*/

#define NAMESIZE 50

// struktura osoba koja sadrži osnovne podatke i pokazivaè na sljedeæu osobu
typedef struct Person
{
	char name[NAMESIZE];
	char surname[NAMESIZE];
	int age;
	struct Person* next;
} Person;

// funkcija koja ispisuje podatke jedne osobe
void IspisClana(Person* head)
{
	printf("%s %s %d\n", head->name, head->surname, head->age);
}

// funkcija za ispis cijele liste
void Ispisliste(Person* head)
{
	if (head == NULL) {
		printf("Lista je prazna.\n");
		return;
	}

	while (head != NULL)
	{
		IspisClana(head);
		head = head->next;
	}
}

// funkcija za unos podataka o osobi
Person* UnosElementa()
{
	Person* novaosoba = (Person*)malloc(sizeof(Person));
	if (novaosoba == NULL)
		return NULL;

	printf("Unesi ime: ");
	scanf("%s", novaosoba->name);
	printf("Unesi prezime: ");
	scanf("%s", novaosoba->surname);
	printf("Unesi godine: ");
	scanf("%d", &novaosoba->age);

	novaosoba->next = NULL;
	return novaosoba;
}

// funkcija za dodavanje elementa na poèetak liste
Person* DodajNaPocetak(Person* head)
{
	Person* novaosoba = UnosElementa();
	if (novaosoba == NULL) return head;

	novaosoba->next = head; // nova osoba pokazuje na staru glavu
	return novaosoba;       // nova osoba postaje glava liste
}

// funkcija za dodavanje elementa na kraj liste
Person* DodajNaKraj(Person* head)
{
	Person* novaosoba = UnosElementa();
	if (novaosoba == NULL) return head;

	if (head == NULL) {
		// ako je lista prazna, nova osoba postaje glava
		return novaosoba;
	}

	Person* current = head;
	while (current->next != NULL) {
		current = current->next; // prolazimo do zadnjeg èlana
	}
	current->next = novaosoba; // spajamo novi element na kraj
	return head;
}

// funkcija za pronalazak osobe po prezimenu
void PronadiPoPrezimenu(Person* head)
{
	char wantedSurname[NAMESIZE];
	printf("Unesi prezime zeljenog clana: ");
	scanf("%s", wantedSurname);

	while (head != NULL)
	{
		if (strcmp(wantedSurname, head->surname) == 0)
		{
			IspisClana(head);
			return;
		}
		head = head->next;
	}
	puts("Clan nije pronaden na listi.");
}

// funkcija koja briše cijelu listu 
Person* IzbrisiListu(Person* head)
{
	while (head != NULL)
	{
		Person* temp = head;
		head = head->next;
		free(temp);
	}
	printf("Lista je izbrisana.\n");
	return NULL;
}

int main()
{
	int odabir = 0;
	Person* head = NULL; 

	do {
		puts("\nOdaberi radnju:");
		puts("1. Ispisi listu");
		puts("2. Dodaj element na pocetak liste");
		puts("3. Dodaj element na kraj liste");
		puts("4. Pretrazi listu po prezimenu");
		puts("5. Izbrisi cijelu listu");
		puts("Drugi broj za izlaz.");
		scanf("%d", &odabir);

		switch (odabir)
		{
		case 1: Ispisliste(head); break;           // ispis svih èlanova
		case 2: head = DodajNaPocetak(head); break; // dodavanje na poèetak
		case 3: head = DodajNaKraj(head); break;    // dodavanje na kraj
		case 4: PronadiPoPrezimenu(head); break;    // traženje po prezimenu
		case 5: head = IzbrisiListu(head); break;   // brisanje cijele liste
		default:
			if (odabir >= 1 && odabir <= 5)
				puts("Nepoznata opcija!");
			break;
		}
	} while (odabir >= 1 && odabir <= 5);

	// na kraju brisem listu ako je jos ostala u memoriji
	head = IzbrisiListu(head);
	return 0;
}
