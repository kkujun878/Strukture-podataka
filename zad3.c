#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 50 // maksimalna duljina imena i prezimena

// Struktura koja opisuje osobu u vezanoj listi
typedef struct Person
{
	char name[NAMESIZE];
	char surname[NAMESIZE];
	int age;
	struct Person* next; // pokaziva� na sljede�i element
} Person;

// Prototipovi funkcija
int IspisClana(Person* head);
int Ispisliste(Person* head);
int UpisiUlistu(Person* head);
Person* UnosElementa();
Person* DodajNaPocetak(Person* head);
Person* DodajNaKraj(Person* head);
int PronadiPoPrezimenu(Person* head);
Person* IzbrisiListu(Person* head);
Person* DodajNakon(Person* head);
Person* DodajIspred(Person* head);
Person* UcitajizDatoteke(Person* head);
int PocetniMenu(int* odabir);

int main()
{
	int odabir = 0;          // izbor korisnika iz menija
	Person* head = NULL;     // po�etak liste (prazna lista)

	PocetniMenu(&odabir);    // ispis po�etnog menija

	while (odabir >= 1 && odabir <= 9) // glavni meni petlja
	{
		switch (odabir)
		{
		case 1: Ispisliste(head); break;               // ispis liste
		case 2: head = DodajNaPocetak(head); break;    // dodaj novi na po�etak
		case 3: head = DodajNaKraj(head); break;       // dodaj novi na kraj
		case 4: PronadiPoPrezimenu(head); break;       // tra�i po prezimenu
		case 5: head = IzbrisiListu(head); break;      // izbri�i cijelu listu
		case 6: head = DodajNakon(head); break;        // dodaj iza odre�enog
		case 7: head = DodajIspred(head); break;       // dodaj ispred odre�enog
		case 8: UpisiUlistu(head); break;              // spremi u datoteku
		case 9: head = UcitajizDatoteke(head); break;  // u�itaj iz datoteke
		default:
			puts("Opcija nije u izboru");
			break;
		}

		puts("\nUnesite novi broj za izvrsenje odredene radnje (ili bilo koji drugi broj za izlaz):");
		scanf("%d", &odabir); // ponovno pitaj korisnika
	}
	return 0;
}

// Funkcija ispisuje jednog �lana liste
int IspisClana(Person* head)
{
	printf("%s %s %d\n", head->name, head->surname, head->age);
	return 0;
}

// Ispis cijele liste
int Ispisliste(Person* head)
{
	if (head == NULL) { // ako je lista prazna
		puts("Lista je prazna!");
		return 0;
	}
	while (head != NULL) // prolazak kroz cijelu listu
	{
		IspisClana(head);
		head = head->next;
	}
	return 0;
}

// Upisuje cijelu listu u datoteku
int UpisiUlistu(Person* head)
{
	FILE* FilePointer = fopen("popis.txt", "w"); // otvori datoteku za pisanje
	if (FilePointer == NULL)
	{
		puts("Nemoguce otvoriti datoteku.");
		return 1;
	}

	while (head != NULL)
	{
		fprintf(FilePointer, "%s %s %d\n", head->name, head->surname, head->age); // upis u datoteku
		head = head->next;
	}

	fclose(FilePointer); // zatvori datoteku
	puts("Upis obavljen!");
	return 0;
}

// Funkcija za unos novog �lana
Person* UnosElementa()
{
	Person* novaosoba = (Person*)malloc(sizeof(Person)); // alokacija memorije
	if (novaosoba == NULL)
		return NULL;

	printf("Unesi ime: ");
	scanf("%s", novaosoba->name);
	printf("Unesi prezime: ");
	scanf("%s", novaosoba->surname);
	printf("Unesi godine: ");
	scanf("%d", &novaosoba->age);

	novaosoba->next = NULL; // novi element jo� nije povezan
	return novaosoba;
}

// Dodaje novi element na po�etak liste
Person* DodajNaPocetak(Person* head)
{
	Person* novaosoba = UnosElementa(); // kreiraj novi �vor
	if (novaosoba == NULL) return head;
	novaosoba->next = head; // pove�i novi element s postoje�im
	head = novaosoba;       // pomakni pokaziva� na po�etak
	return head;
}

// Dodaje novi element na kraj liste
Person* DodajNaKraj(Person* head)
{
	Person* novaosoba = UnosElementa();
	if (novaosoba == NULL) return head;

	if (head == NULL) // ako je lista prazna
		return novaosoba;

	Person* current = head;
	while (current->next != NULL) // idi do kraja liste
		current = current->next;

	current->next = novaosoba; // pove�i zadnji element s novim
	return head;
}

// Tra�i osobu po prezimenu
int PronadiPoPrezimenu(Person* head)
{
	char wantedSurname[NAMESIZE];
	puts("Unesi prezime zeljenog clana:");
	scanf("%s", wantedSurname);

	while (head != NULL)
	{
		if (strcmp(wantedSurname, head->surname) == 0) // usporedi prezimena
		{
			IspisClana(head);
			return 0;
		}
		head = head->next;
	}
	puts("�lan nije prona�en na listi.");
	return 1;
}

// Bri�e cijelu listu iz memorije
Person* IzbrisiListu(Person* head)
{
	while (head != NULL)
	{
		Person* temp = head;  // privremeni pokaziva�
		head = head->next;    // pomakni pokaziva� na sljede�i element
		free(temp);           // oslobodi trenutni
	}
	puts("Lista obrisana!");
	return NULL; // vra�a praznu listu
}

// Dodaje novi element nakon odre�enog �lana
Person* DodajNakon(Person* head)
{
	if (head == NULL)
	{
		puts("Lista je prazna, dodajte prvi clan.");
		return head;
	}

	int clanprije;
	puts("Nakon kojeg clana (po rednom broju) zelite dodati novi clan?");
	scanf("%d", &clanprije);

	Person* novaOsoba = UnosElementa(); // unos novog
	if (novaOsoba == NULL) return head;

	Person* current = head;
	for (int i = 1; i < clanprije; i++) // prona�i poziciju
	{
		current = current->next;
		if (current == NULL)
		{
			puts("Uneseno mjesto je izvan ranga liste.");
			free(novaOsoba);
			return head;
		}
	}

	novaOsoba->next = current->next; // pove�i novi �vor
	current->next = novaOsoba;
	return head;
}

// Dodaje novi element ispred odre�enog �lana
Person* DodajIspred(Person* head)
{
	if (head == NULL)
	{
		puts("Lista je prazna.");
		return head;
	}

	int clan;
	puts("Prije kojeg clana (po rednom broju) zelite dodati novog clana?");
	scanf("%d", &clan);

	if (clan == 1) // ako je prvi, pozovi funkciju za dodavanje na po�etak
		return DodajNaPocetak(head);

	Person* novaosoba = UnosElementa(); // novi �vor
	if (novaosoba == NULL) return head;

	Person* current = head;
	for (int i = 1; i < clan - 1; i++) // idi do �lana ispred �eljenog
	{
		if (current->next == NULL)
		{
			puts("Ne postoji taj clan u listi.");
			free(novaosoba);
			return head;
		}
		current = current->next;
	}

	novaosoba->next = current->next; // pove�i pokaziva�e
	current->next = novaosoba;
	return head;
}

// U�itava listu iz datoteke
Person* UcitajizDatoteke(Person* head)
{
	FILE* FilePointer = fopen("popis.txt", "r"); // otvori za �itanje
	if (FilePointer == NULL)
	{
		puts("Datoteka nije uspjesno otvorena.");
		return head;
	}

	char name[NAMESIZE];
	char surname[NAMESIZE];
	int age;
	Person* kraj = NULL;

	while (fscanf(FilePointer, "%s %s %d", name, surname, &age) == 3) // �itaj dok ima podataka
	{
		Person* NovaOsoba = (Person*)malloc(sizeof(Person)); // novi �vor
		if (NovaOsoba == NULL)
		{
			puts("Greska pri stvaranju osobe.");
			fclose(FilePointer);
			return head;
		}
		strcpy(NovaOsoba->name, name);
		strcpy(NovaOsoba->surname, surname);
		NovaOsoba->age = age;
		NovaOsoba->next = NULL;

		if (head == NULL) // ako je lista prazna
		{
			head = NovaOsoba;
			kraj = NovaOsoba;
		}
		else // dodaj na kraj
		{
			kraj->next = NovaOsoba;
			kraj = NovaOsoba;
		}
	}
	fclose(FilePointer);
	puts("Ucitavanje iz datoteke zavrseno!");
	return head;
}

// Prikazuje po�etni meni i prima odabir
int PocetniMenu(int* odabir)
{
	puts("Unesi broj kojim zelis izvrsiti radnju:");
	puts("1. Ispisi listu");
	puts("2. Dodaj element na pocetak liste");
	puts("3. Dodaj element na kraj liste");
	puts("4. Pretrazi listu po prezimenu");
	puts("5. Izbrisi cijelu listu");
	puts("6. Dodaj clana nakon odredenog");
	puts("7. Dodaj ispred odredenog clana");
	puts("8. Upisi listu u datoteku");
	puts("9. Ucitaj listu iz datoteke");
	scanf("%d", odabir); // u�itaj odabir korisnika
	return 0;
}
