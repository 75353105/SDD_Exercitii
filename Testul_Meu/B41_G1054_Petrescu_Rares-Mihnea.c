#include<stdio.h>
#include<malloc.h>
typedef struct Pacient Pacient;
typedef struct Nod Nod;
struct Pacient {
	char* numePacient;
	char sex;
	float nrZileSpitlizare;
};
struct Nod {
	Pacient info;
	struct Nod* next;
};

Pacient initializare(const char* numePacient, int cod,
	float nrZileSpitlizare)
{
	 Pacient p;
	p.numePacient = malloc(sizeof(char) * (strlen(numePacient)+1));
	strcpy(p.numePacient, numePacient);
	p.nrZileSpitlizare = nrZileSpitlizare;
	if (cod == 0)
		p.sex = 'f';
	else
		if(cod==1)
		p.sex = 'm';
	//strcpy(p.sex, sex);
	return p;
}
Pacient copiere(Pacient p)
{
	Pacient nou;
	nou.nrZileSpitlizare = p.nrZileSpitlizare;
	nou.numePacient = malloc(sizeof(char) * (strlen(p.numePacient) + 1));
	strcpy(nou.numePacient, p.numePacient);
	if (p.sex == 'm')
		nou.sex = 'm';
	if (p.sex == 'f');
	nou.sex = 'f';
	return nou;

}
void afisarePacient(Pacient p)
{
	printf("Numele: %s\n",p.numePacient);
	printf("Sexul pacientului:%c\n", p.sex);
	printf("Nr de zile:%5.2f\n", p.nrZileSpitlizare);
}

//Lista simpla
Nod* inserareLaInceput(Nod* nod, Pacient p)
{
	Nod* aux = malloc(sizeof(Nod));
	aux->info = p;
	aux->next = nod;

	return aux;
}

Nod* inserareLaInceputDeep(Nod* nod, Pacient p)
{
	Nod* aux = malloc(sizeof(Nod));
	aux->info = copiere(p);
	aux->next = nod;

	return aux;
}


void afisareListaSimpluInalantuita(Nod* nod)
{
	Nod* aux = nod;
	while (aux->next != NULL)
	{
		afisarePacient(aux->info);
		aux = aux->next;
	}
}
Nod* parcurgereListaSimpla(Nod* nod)
{
	nod = nod->next;
	return nod;
}
void stergereListaSimpla(Nod** nod)
{
	Nod* aux = (*nod);
	while (aux->next != NULL)
	{
		free(aux->info.numePacient);
		Nod* m = aux->next;
		free(aux);
		aux = m;
	}
}
void parcurgereListaPanaLaCapat(Nod* nod)
{
	Nod* aux = nod;
	while (aux->next != NULL)
	{
		aux = aux->next;
	}
}

float numarMediuDeZileDeSpitalizare(Nod* nod)
{
	float mean = 0;
	int i = 1;
	Nod* aux = nod;
	mean = mean + aux->info.nrZileSpitlizare;
	while (aux->next != NULL)
	{
		aux = parcurgereListaSimpla(aux);
		i++;
		mean = mean + aux->info.nrZileSpitlizare;
	}
	mean = mean / i;
	return mean;
}
Pacient cautarePacient(Nod* nod, const char* nume)
{
	Nod* aux = nod;

	while (aux->next != NULL)
	{
		if (strcmp(nume, aux->info.numePacient) == 0)
		{
			Pacient p = copiere(aux->info);
			return p;
		}
		else
			aux = aux->next;
	}
}
void main()
{
	Pacient p1;
	p1=initializare ("Ionescu Cristian",1, 5.0);
	Pacient p2=initializare("Amalia Ioana",0,6);
	Pacient p3=initializare("Elena Ionela",0,7);
	Pacient p4=initializare("Armand Hagiu",1,6);
	Pacient p5=initializare("Iulius Bega",1,5);

	Nod* nod = NULL;
	nod = inserareLaInceputDeep(nod, p1);
	nod = inserareLaInceputDeep(nod, p2);
	nod = inserareLaInceputDeep(nod, p3);
	nod = inserareLaInceputDeep(nod, p4);
	nod = inserareLaInceputDeep(nod, p5);
	afisareListaSimpluInalantuita(nod);

	Pacient p6 = cautarePacient(nod, "Ionescu Cristian");
	afisarePacient(p6);

	float medie = 0;
	medie = numarMediuDeZileDeSpitalizare(nod);
	printf("\n %5.2f", medie);
	printf("\n");
	afisarePacient(p1);

	stergereListaSimpla(&nod);
	free(p1.numePacient);
	free(p2.numePacient);
	free(p3.numePacient);
	free(p4.numePacient);
	free(p5.numePacient);
	free(p6.numePacient);
}