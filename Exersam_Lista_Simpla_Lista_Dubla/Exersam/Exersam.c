#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)

//structura cu care vom lucra
typedef struct sticla
{
	char* material;
	int volum;
	int cost;
}sticla;
sticla initializare(const char* material,
	int volum,
	int cost)
{
	struct sticla s;
	s.material = malloc(sizeof(char) * (strlen(material) + 1));
	strcpy(s.material, material);
	s.volum = volum;
	s.cost = cost;
	return s;
}
sticla copiere(sticla s)
{
	return initializare(s.material, s.volum, s.cost);
}
void afisareSticla(sticla s)
{
	printf("%s\n", s.material);
	printf("%d\n", s.volum);
	printf("%d\n", s.cost);
	printf("\n");
}
//structura necesara pentru o lista simpla inalantuita
 struct Nod {
	sticla info;
	struct Nod* next;
};
 typedef struct Nod Nod;
Nod* adaugareListaSimplaInceput(Nod** nod, sticla s)
{
	Nod* n = malloc(sizeof(Nod));
	n->info = copiere(s);
	n->next = (*nod);

	return n;
}
void adaugareListaSimplaLaFinal(Nod** nod, sticla s)
{
	Nod* n = malloc(sizeof(Nod));
	n->info = copiere(s);
	n->next = NULL;
	if ((*nod) != NULL)
	{
		Nod* aux = (*nod);
		while (aux->next)
		{
			aux = aux -> next;
		}

		aux->next = n;
	}
	else
	{
		(*nod) = n;
	}
}
void afisareListaSimpla(Nod* nod)
{
	Nod* aux = nod;
	while (aux != NULL)
	{
		afisareSticla(aux->info);
		aux = aux->next;
	}
}
//structurile necesare pentru crearea unei liste dublu inlantuite
typedef struct nodLdi {

	sticla info;
	struct nodLdi* prev;
	struct nodLdi* next;

}nodLdi;

typedef struct ListaDubla
{
	nodLdi* first;
	nodLdi* last;
}ListaDubla;

void push_front(ListaDubla* ldi, sticla s)
{
	nodLdi* parcurgere = malloc(sizeof(nodLdi));
	parcurgere->prev = NULL;
	parcurgere->info = copiere(s);
	parcurgere->next = ldi->first;
	if (ldi->first != NULL)
	{
		ldi->first->prev = parcurgere;
		ldi->first = parcurgere;
	}
	else
	{
		ldi->first = parcurgere;
		ldi->last = parcurgere;
	}
}
void push_back(ListaDubla* lista, sticla s)
{
	nodLdi* aux = malloc(sizeof(nodLdi));
	aux ->next = NULL;
	aux->info = copiere(s);
	aux->prev = lista->last;
	if (lista->last != NULL)
	{
		lista->last->next = aux;
		lista ->last = aux;
	}
	else
	{
		lista->first = aux;
		lista->last = aux;
	}
}
void stergereListaDubla(ListaDubla* lista)
{
	nodLdi* aux = lista->first;
	while (aux != NULL)
	{
		free(aux->info.material);
		aux = aux->next;
		if (aux != NULL)
			free(aux->prev);
	}
	lista->first = NULL;
	lista->last = NULL;
	free(lista->first);
	free(lista->last);
}
void afisareInceput(ListaDubla lista)
{
	nodLdi* aux = lista.first;
	while (aux != NULL)
	{
		afisareSticla(aux->info);
		aux = aux->next;
	}
}
void afisareFinal(ListaDubla lista)
{
	nodLdi* aux = lista.last;
	while (aux != NULL)
	{
		afisareSticla(aux->info);
		aux = aux->prev;
	}
}
void stergereNod(ListaDubla* lista, const char* material)
{
	nodLdi* aux = lista->first;
	while (aux != NULL && strcmp(aux->info.material, material) != 0)
	{
		aux = aux->next;
	}
	if (aux != NULL)
	{
		if (aux->prev != NULL)
		{
			aux->prev->next = aux->next;
		}
		else
			lista->first = aux->next;
		if (aux->next != NULL)
			aux->next->prev = aux->prev;
		else
			lista->last = aux->prev;
	}
}
void main()
{
	printf("Acuma ne ocupam de lista dublu inalantuita:\n");
	sticla s1 = initializare("plastic", 500, 2);
	sticla s2 = initializare("plastic", 250, 1);
	sticla s3 = initializare("sticla", 500, 4);
	sticla s4 = initializare("plastic", 500, 3);

	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	push_front(&lista, s1);
	push_front(&lista, s2);
	push_front(&lista, s3);
	push_back(&lista, s4);

	afisareInceput(lista);

	stergereNod(&lista, "sticla");
	afisareFinal(lista);
	stergereListaDubla(&lista);
	printf("Acuma ne ocupam de lista simplu inalantuita:\n");
	Nod* nod = NULL;
	nod=adaugareListaSimplaInceput(&nod, s1);
	nod=adaugareListaSimplaInceput(&nod, s2);
	adaugareListaSimplaLaFinal(&nod, s3);
	adaugareListaSimplaLaFinal(&nod, s4);
	afisareListaSimpla(nod);

	while (nod)
	{
		free(nod->info.material);
		Nod* n = nod->next;
		free(nod);
		nod = n;
	}
}