#include<stdio.h>
#include<malloc.h>
#include<string.h>
#pragma warning(disable:4996)

struct Ciocolata
{
	char* tipCiocolata;
	int *gramaj;
	float *pret;
	int nrCiocolate;
	float nrCalorii;
	float procentLapte;
	float procentCacao;
};

struct Ciocolata initiere(const char* tipCiocolata, const int* gramaj, const float* pret, int nrCiocolate,
	float nrCalorii, float procentLapte, float procentCacao)
{
	struct Ciocolata c;
	c.tipCiocolata = malloc(sizeof(char) * (strlen(tipCiocolata) + 1));
	strcpy(c.tipCiocolata, tipCiocolata);
	c.nrCalorii = nrCalorii;
	c.nrCiocolate = nrCiocolate;
	c.gramaj = malloc(sizeof(int) * c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		c.gramaj[i] = gramaj[i];
	}
	c.pret = malloc(sizeof(float) * c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		c.pret[i] = pret[i];
	}
	c.procentCacao = procentCacao;
	c.procentLapte = procentLapte;

	return c;
}

//copierea stucturii
struct Ciocolata copiereCiocolata(struct Ciocolata ci)
{
	struct Ciocolata c;
	c.tipCiocolata = malloc(sizeof(char) * (strlen(ci.tipCiocolata) + 1));
	strcpy(c.tipCiocolata, ci.tipCiocolata);
	c.nrCalorii = ci.nrCalorii;
	c.nrCiocolate = ci.nrCiocolate;
	c.gramaj = malloc(sizeof(int) * c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		c.gramaj[i] = ci.gramaj[i];
	}
	c.pret = malloc(sizeof(float) * c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		c.pret[i] = ci.pret[i];
	}
	c.procentCacao = ci.procentCacao;
	c.procentLapte = ci.procentLapte;

	return c;
}

//o metoda pentru vector
float aflaNrCalorii(struct Ciocolata* ciocolate, int nrCiocolate)
{
	float totalCalorii = 0;
	for (int i = 0; i < nrCiocolate; i++)
	{
		totalCalorii = totalCalorii + ciocolate[i].nrCalorii;
	}
	return totalCalorii;
}
//afisarea unei ciocolate
void afisareCiocolata(struct Ciocolata c)
{
	printf("Tip ciocolata: %s. Procent de lapte: %5.2f. Procent de cacao: %5.2f.\n", c.tipCiocolata, c.procentLapte, c.procentCacao);
	printf("Nr calorii:%5.2f\n", c.nrCalorii);
	printf("Nr ciocolate: %d\n", c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		printf("Gramaj[%d]: %d, ", i, c.gramaj[i]);
	}
	printf("\n");
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		printf("Pret[%d]: %5.2f, ",i, c.pret[i]);
	}
	printf("\n");
}
//adaugarea unei ciocolate
void push_ciocolate(struct Ciocolata c,struct Ciocolata **ciocolate, int *nrCiocolate )
{
	//se face marirea vectorului de structuri ciocolate
	(*nrCiocolate)++;
	//se creeaza o copie pentru a memora tot pana cand va fi sters de tot ciocolate
	struct Ciocolata* cop = malloc(sizeof(struct Ciocolata) * (*nrCiocolate));

	//se introduc valorle din ciocolate una cate una in cop
	for (int i = 0; i < (*nrCiocolate) - 1; i++)
	{
		cop[i] = (*ciocolate)[i];
	}

	cop[(*nrCiocolate) - 1] = copiereCiocolata(c);
	free((*ciocolate));
	(*ciocolate) = malloc(sizeof(struct Ciocolata) * (*nrCiocolate));
	for (int i = 0; i < (*nrCiocolate); i++)
	{
		(*ciocolate)[i] = copiereCiocolata(cop[i]);
	}
}
void remove_ciocolata(struct Ciocolata** ciocolate, int* nrCiocolate)
{
	(*nrCiocolate)--;
	struct Ciocolata* cop = malloc(sizeof(struct Ciocolata) * (*nrCiocolate));

	for (int i = 0; i < (*nrCiocolate); i++)
	{
		cop[i] = copiereCiocolata((*ciocolate)[i]);
	}
	free((*ciocolate));
	(*ciocolate) = malloc(sizeof(struct  Ciocolata) * (*nrCiocolate));
	for (int i = 0; i < (*nrCiocolate); i++)
	{
		(*ciocolate)[i] = copiereCiocolata(cop[i]);
	}
}
//concatenarea de vectori

void ciocolateConcatenate(struct Ciocolata** c1, struct Ciocolata** c2, int* nrCiocolate1, int* nrCiocolate2  )
{
	struct Ciocolata* cop = malloc(sizeof(struct Ciocolata)*(*nrCiocolate1));

	for (int i = 0; i < ( * nrCiocolate1); i++)
	{
		cop[i] = copiereCiocolata((*c1)[i]);
	}

	free((*c1));
	int nr3;
	nr3 = (*nrCiocolate1) + (*nrCiocolate2);
	(*c1) = malloc(sizeof(struct Ciocolata) * (nr3));

	for (int i = 0; i < (*nrCiocolate1); i++)
	{
		(*c1)[i] = copiereCiocolata(cop[i]);
	}
	
	int nr = 0;
	for (int i = (*nrCiocolate1); i < nr3; i++)
	{
		(*c1)[i] = copiereCiocolata((*c2)[nr]);
		nr++;
	}
	(*nrCiocolate1) = nr3;
	free(cop);
}



//nou vector pentru elementele care respecta conditii
struct Ciocolata* cuLapteSiMiere(struct Ciocolata* c,int nrCiocolate,int *n)
{
	int nr = 0;
	char* text = NULL;
		text=malloc(sizeof(char) * (strlen("cu lapte si miere") + 1));
	strcpy(text, "cu lapte si miere");
	for (int i = 0; i < nrCiocolate; i++)
	{
		if (strcmp(c[i].tipCiocolata, text)==0)
			nr++;
	}
	struct Ciocolata* cop = malloc(sizeof(struct Ciocolata) * nr);
	int m = 0;
	for (int i = 0; i < nrCiocolate; i++)
	{
		//de ce naiba merge doar daca fac cu c[i] si nu cu dereferentiere.... nu ma intreba... o tine cumva de adrese
		if (strcmp(c[i].tipCiocolata, text) == 0)
		{
			cop[i] = copiereCiocolata(c[i]);
		}
	}
	(*n) = nr;
	free(text);
	return cop;
}

//citim o structura din fisier text

struct Ciocolata citireCiocolataDinFisier(const char* nume)
{
	struct Ciocolata c;
	FILE* f;
	f = fopen(nume, "r");
	char num[100];
	fscanf(f, "%s",&num);
	c.tipCiocolata = malloc(sizeof(char) * (strlen(num) + 1));
	strcpy(c.tipCiocolata, num);
	fscanf(f, "%f", &c.nrCalorii);
	fscanf(f, "%d", &c.nrCiocolate);
	c.gramaj = malloc(sizeof(float) * c.nrCiocolate);
	c.pret = malloc(sizeof(float) * c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		fscanf(f, "%d", &c.gramaj[i]);
	}
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		fscanf(f, "%f", &c.pret[i]);
	}
	fscanf(f, "%f", &c.procentCacao);
	fscanf(f, "%f", &c.procentLapte);

	return c;
}

//afisarea ciocolatei in fisier

void afisareCiocolataInFisier(struct Ciocolata c, FILE* f)
{
	fprintf(f, "%s\n", c.tipCiocolata);
	fprintf(f, "%5.2f\n", c.nrCalorii);
	fprintf(f, "%d\n", c.nrCiocolate);
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		fprintf(f, "%d ", c.gramaj[i]);
	}
	fprintf(f, "\n");
	for (int i = 0; i < c.nrCiocolate; i++)
	{
		fprintf(f, "%5.2f ", c.pret[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "%5.2f\n", c.procentCacao);
	fprintf(f, "%5.2f\n", c.procentLapte);
	fprintf(f, "\n\n");
}

void main()
{
  
	struct Ciocolata Toblerone;
	int gramaje[] = {150,200,250};
	float preturi[] = { 5.0,6.3,7.2 };
	float preturi2[] = { 4.5,7,8.2 };
	float preturi3[] = { 5,6,7 };
	Toblerone = initiere("cu lapte si miere", gramaje,preturi,3,420, 45.0f,30.0f );
	/*struct Ciocolata Milka;
	Milka = copiereCiocolata(Toblerone);
	afisareCiocolata(Toblerone);
	afisareCiocolata(Milka);*/
	struct  Ciocolata RitterSport = initiere("neagra", gramaje, preturi2, 3, 365, 20.0f, 65.0f);
	struct Ciocolata Poiana = initiere("cu alune", gramaje, preturi3, 3, 550, 45.0f, 25.0f);
	struct Ciocolata* multeCiocolate=malloc(sizeof(struct Ciocolata)*2);
	int nrCiocolate = 2;
	multeCiocolate[0] = copiereCiocolata(Toblerone);
	multeCiocolate[1] = copiereCiocolata(RitterSport);
	push_ciocolate(Poiana, &multeCiocolate, &nrCiocolate);
	for (int i = 0; i < nrCiocolate; i++)
	{
		afisareCiocolata(multeCiocolate[i]);
	}
	printf("\n");
	remove_ciocolata(&multeCiocolate, &nrCiocolate);
	printf("\n");
	for (int i = 0; i < nrCiocolate; i++)
	{
		afisareCiocolata(multeCiocolate[i]);
	}
	printf("\n");
	int nr = 0;
	struct Ciocolata* lsm = cuLapteSiMiere(multeCiocolate, nrCiocolate,&nr);
	for (int i = 0; i < nr; i++)
	{
		afisareCiocolata(lsm[i]);
	}
	ciocolateConcatenate(&multeCiocolate, &lsm, &nrCiocolate, &nr);
	for (int i = 0; i < nrCiocolate; i++)
	{
		afisareCiocolata(multeCiocolate[i]);
	}
	for (int i = 0; i < nrCiocolate; i++)
	{
		free(multeCiocolate[i].pret);
		free(multeCiocolate[i].gramaj);
		free(multeCiocolate[i].tipCiocolata);
	}
	for (int i = 0; i < nr; i++)
	{
		free(lsm[i].pret);
		free(lsm[i].gramaj);
		free(lsm[i].tipCiocolata);
	}
	printf("\n");
	
	//dezalocari de spatiu
	free(lsm);
	free(multeCiocolate);
	/*free(Milka.gramaj);
	free(Milka.pret);
	free(Milka.tipCiocolata);*/
	free(Toblerone.gramaj);
	free(Toblerone.tipCiocolata);
	free(Toblerone.pret);
	//----------------------------------------------------------------------------
	struct Ciocolata ciocolate;
    ciocolate=citireCiocolataDinFisier("Ciocolate.txt");
	
	FILE* g;
	g = fopen("Afisare.txt", "w");
	afisareCiocolataInFisier(ciocolate, g);
	fclose(g);
}