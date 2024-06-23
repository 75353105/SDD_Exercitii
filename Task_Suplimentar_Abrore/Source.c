//Se considera un arbore binar de cautare.Puteti sa folositi codul de la seminar.
//
//Sa se stearga un nod pentru care se primeste id - ul de cautare.
// Dupa stergere arborele trebuie sa isi pastreze proprietatea de Arbore Binar de Cautare.
//
//Sa se implementeze o functie care pentru o radacina primita ca parametru, 
// returneaza radacina subarborelui stang sau drept care are inaltimea mai mare.
//
//Sa se realizeze o functie care pentru un nod radacina primit, 
// determina numarul de noduri aflate in subordine.
//
//Sa se realizeze o functie care pentru un nod radacina primit ca parametru, 
//returneaza radacina subarborelui stang sau drept care are mai multe noduri in subordine.


#include<stdio.h>
#include<malloc.h>

typedef struct rucsac rucsac;

struct rucsac {

	char* marca;
	float pret;
	int volum;
	int ID;
};

typedef struct NodArbore NodArbore;

struct NodArbore {

	rucsac info;
	NodArbore* stanga;
	NodArbore* dreapta;

};

rucsac initiereRucsac(const char* marca, float pret, int volum, int ID) {
	rucsac r;
	r.pret = pret;
	r.volum = volum;
	r.ID = ID;
	r.marca = malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(r.marca, marca);
	return r;
}

rucsac copiereRucsac(rucsac ru) {
	return initiereRucsac(ru.marca, ru.pret, ru.volum, ru.ID);
}

void afisareRucsac(rucsac r) {
	printf("Cod:%d || Pret:%5.2f || Volum: %d || Marca:%s\n", r.ID, r.pret, r.volum, r.marca);
}

NodArbore* inserareNod(NodArbore* na, rucsac r) {

	if (na) {
		if (na->info.ID > r.ID) {
			na->stanga=inserareNod(na->stanga, r);
		}
		else
			if (na->info.ID < r.ID) {
				na->dreapta=inserareNod(na->dreapta, r);
			}

	}
	else
	{
		na = malloc(sizeof(NodArbore));
		na->info = copiereRucsac(r);
		na->dreapta = NULL;
		na->stanga = NULL;
	}
	return na;
}

void afisareInOrdine(NodArbore* radacina) {
	if (radacina) {
		afisareInOrdine(radacina->stanga);
		afisareRucsac(radacina->info);
		afisareInOrdine(radacina->dreapta);
	}
}
void afisarePreOrdine(NodArbore* radacina) {
	if (radacina) {
		afisareRucsac(radacina->info);
		afisarePreOrdine(radacina->stanga);
		afisarePreOrdine(radacina->dreapta);
	}
}
void parcurgerePreOrdine(NodArbore* radacina) {
	if (radacina) {
		parcurgerePreOrdine(radacina->stanga);
		parcurgerePreOrdine(radacina->dreapta);
	}
}
void parcurgerePreOrdineSubNoduri(NodArbore* radacina,int *nrSubnoduri) {
	if (radacina) {
		(*nrSubnoduri)++;
		parcurgerePreOrdineSubNoduri(radacina->stanga,nrSubnoduri);
		parcurgerePreOrdineSubNoduri(radacina->dreapta,nrSubnoduri);
	}
}

NodArbore* parcurgerePreOrdineptID(NodArbore* radacina, int ID) {

	if (radacina)
	{
		if (radacina->info.ID > ID) {
			return parcurgerePreOrdineptID(radacina->stanga, ID);

		}
		if (radacina->info.ID < ID) {
			return parcurgerePreOrdineptID(radacina->dreapta, ID);
		}
		else
		{
			return radacina;
		}
	}
}

int SubNoduri(NodArbore* radacina, int id, int nrSubNoduri) {
	if (radacina) {


		nrSubNoduri = 0;
		if (id != radacina->info.ID){
			radacina = parcurgerePreOrdineptID(radacina, id);
			nrSubNoduri--;
			parcurgerePreOrdineSubNoduri(radacina, &nrSubNoduri);
		}
		else
		{
			nrSubNoduri--;
			parcurgerePreOrdineSubNoduri(radacina, &nrSubNoduri);
		}
	}
	return nrSubNoduri;
}

//NodArbore* stergereNod(NodArbore* radacina, int id) {
//
//	if (radacina) {
//		radacina = parcurgerePreOrdineptID(radacina, id);
//
//		if (radacina->stanga == NULL && radacina->dreapta == NULL) {
//			free(radacina->info.marca);
//			free(radacina);
//		}
//
//		return radacina;
//	}
//}

void afisaeazaSubarbore(NodArbore*radacina, int id){
	if (radacina) {
		radacina = parcurgerePreOrdineptID(radacina, id);
		afisareInOrdine(radacina);
	}
}
int InaltimeArbore(NodArbore* radacina) {

	int height = 0;
	if (radacina) {
		int inaltimeStanga = InaltimeArbore(radacina->stanga);
		int inaltimeDreapta = InaltimeArbore(radacina->dreapta);

		if (inaltimeStanga > inaltimeDreapta) {
			height = inaltimeStanga;
		}
		else
		{
			height = inaltimeDreapta;
		}

		return height + 1;
	}
	return 0;
}

int InaltimeSubarbore(NodArbore* radacina, int id) {
	int inaltime = 0;
	if (radacina) {
		radacina = parcurgerePreOrdineptID(radacina, id);
		
		inaltime = InaltimeArbore(radacina);
		return inaltime;
	}
	return 0;
}


void main() {

	NodArbore* radacina = NULL;
	radacina =inserareNod(radacina, initiereRucsac("NIKE", 26, 5, 6));
	radacina = inserareNod(radacina, initiereRucsac("Puma", 31, 4, 4));
	radacina = inserareNod(radacina, initiereRucsac("Addidas", 25, 5, 8));
	radacina = inserareNod(radacina, initiereRucsac("NIKE", 29, 5, 3));
	radacina = inserareNod(radacina, initiereRucsac("Under Armour", 35, 7, 5));
	radacina = inserareNod(radacina, initiereRucsac("Puma", 20, 3, 7));
	radacina = inserareNod(radacina, initiereRucsac("InterSport", 29, 7, 9));
	radacina = inserareNod(radacina, initiereRucsac("Addidas", 25, 5, 2));

	afisareInOrdine(radacina);

	int nrSubNoduri = 0;

	nrSubNoduri=SubNoduri(radacina, 6, nrSubNoduri);

	printf("\n numar subnoduri:%d", nrSubNoduri);

	nrSubNoduri = SubNoduri(radacina, 8, nrSubNoduri);

	printf("\n numar subnoduri:%d", nrSubNoduri);

	printf("\n Subarborele cu radacina 4 este: ");
		afisaeazaSubarbore(radacina, 4);

	int inaltime = InaltimeSubarbore(radacina, 4);
	printf("\n Subarborele 4 are inaltimea egala cu:%d ", inaltime);

	radacina = stergereNod(radacina, 2);

	afisareInOrdine(radacina);

}