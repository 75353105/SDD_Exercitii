#include<stdio.h>
#include<malloc.h>
#include<math.h>
#pragma warning(disable:4996)
typedef struct rampa rampa;
float* v;
struct rampa {

	float lungime;
	double inaltime;
	float declivitate;
	int nrMasini;
	float* viteze;
	char* numeDeal;

};
struct rampa initiere(float lungime,double inaltime,float declivitate,int nrMasini,const float* viteze, const char* numeDeal)
{
	struct rampa rmp;
	rmp.lungime = lungime;
	rmp.inaltime = inaltime;
	rmp.declivitate = declivitate;
	rmp.nrMasini = nrMasini;
	rmp.viteze = malloc(sizeof(float)*rmp.nrMasini);
	for (int i = 0; i < rmp.nrMasini; i++)
	{
		rmp.viteze[i] = viteze[i];
	}
	rmp.numeDeal = malloc((strlen(numeDeal) + 1) * sizeof(char));
	strcpy(rmp.numeDeal, numeDeal);

	return rmp;
}
struct rampa copiere(struct rampa r)
{
	struct rampa rmp;
	rmp.lungime = r.lungime;
	rmp.inaltime = r.inaltime;
	rmp.declivitate = r.declivitate;
	rmp.nrMasini = r.nrMasini;
	rmp.viteze = malloc(sizeof(float) * rmp.nrMasini);
	for (int i = 0; i < rmp.nrMasini; i++)
	{
		rmp.viteze[i] = r.viteze[i];
	}
	rmp.numeDeal = malloc((strlen(r.numeDeal) + 1) * sizeof(char));
	strcpy(rmp.numeDeal, r.numeDeal);

	return rmp;
}
struct rampa citireTastatura()
{
	struct rampa r;
	printf("Lungimea rampei: ");
	scanf("%f", &r.lungime);
	printf("Inaltimea rampei: ");
	scanf("%lf", &r.inaltime);
	printf("Declivitatea rampei: ");
	scanf("%f", &r.declivitate);
	printf("Panta are numele de: ");
	char nume[40];
	scanf("%s", nume);
	r.numeDeal = (char*)malloc((strlen(nume)+1) * sizeof(char));
	strcpy(r.numeDeal, nume);
	printf("Numarul de masini care circula zilnic pe rampa: ");
	scanf("%d", &r.nrMasini);
	printf("introduceti vitezele masinilor care merg pe rampa: ");
	r.viteze = (float*)malloc(sizeof(float) * r.nrMasini);
	for (int i = 0; i < r.nrMasini; i++)
	{
		scanf("%f", &r.viteze[i]);
	}

	return r;
}
float vitezaMedie(struct rampa r)
{
	float vitezaMedie = 0;
	for (int i = 0; i < r.nrMasini; i++)
	{
		vitezaMedie = r.viteze[i] + vitezaMedie;
	}
	vitezaMedie = vitezaMedie / r.nrMasini;
	return vitezaMedie;
}
float schimbaDeclivitatea(struct rampa r, float d)
{
	r.declivitate= d;
	return r.declivitate;
}
void schimbaNume(struct rampa* r, const char* n)
{
	free((*r).numeDeal);
	(*r).numeDeal = malloc(strlen(n) + 1);
	strcpy((*r).numeDeal, n);
}
//(*r) inseamna o dereferentiere
void scoateViteze(struct rampa *r, int poz)
{
	v = calloc((*r).nrMasini, sizeof(float));
	for (int i = 0; i < (*r).nrMasini; i++)
	{
		v[i] = (*r).viteze[i];
	}
	free((*r).viteze);
	(*r).nrMasini--;
	(*r).viteze = malloc(sizeof(float) * (*r).nrMasini);
	int nr = 0;
	for (int i = 0; i <= (*r).nrMasini; i++)
	{
		if (i != poz)
		{
			(*r).viteze[nr] = v[i];
			nr++;
		}
		
	}
	free(v);
}
void concatenare_rampe(struct rampa** r1, struct rampa** r2,int *nrRampe1, int*nrRampe2 )
{
	int nrRampe3 = (*nrRampe1) + (*nrRampe2);
	struct rampa* cop = malloc(sizeof(struct rampa) * nrRampe3);

	for (int i = 0; i < (*nrRampe1); i++)
	{
		cop[i] = copiere((*r1)[i]);
	}
	int nr = 0;
	for (int i = (*nrRampe1); i < nrRampe3; i++)
	{
		cop[i] = copiere((*r2)[nr]);
		nr++;
	}

	free((*r1));

	(*r1) = malloc(sizeof(struct rampa) * nrRampe3);
	for (int i = 0; i < nrRampe3; i++)
	{
		(*r1)[i] = copiere(cop[i]);
	}

	free(cop);


}

void adaugaViteze(struct rampa* r,float val, int poz )
{
	v = calloc((*r).nrMasini, sizeof(float));
	for (int i = 0; i < (*r).nrMasini; i++)
	{
		v[i] = (*r).viteze[i];
	}
	free((*r).viteze);
	(*r).nrMasini++;
	(*r).viteze = malloc(sizeof(float) * (*r).nrMasini);
	int nr = 0;
	for (int i = 0; i < (*r).nrMasini; i++)
	{
		if (i == poz)
		{
			(*r).viteze[nr] = val;
			nr++;
		}
		else
			if (i != poz&&i<poz)
			{
				(*r).viteze[nr] = v[i];
				nr++;
			}
			else
				if (i != poz && i > poz)
				{
					(*r).viteze[nr] = v[i - 1];
					nr++;
				}
	}
	free(v);
}
void push_rampa(struct rampa r, struct rampa** rampe, int* nrRampe)
{
	(*nrRampe)++;
	struct rampa* cop = malloc(sizeof(struct rampa) * (*nrRampe));

	for (int i = 0; i < (*nrRampe) - 1; i++)
	{
		cop[i] = copiere((*rampe)[i]);
	}
	 cop[(*nrRampe) - 1] = copiere(r);

	free((*rampe));

	(*rampe) = malloc(sizeof(struct rampa) * (*nrRampe));

	for (int i = 0; i < (*nrRampe); i++)
	{
		(*rampe)[i] = copiere(cop[i]);
	}

	free(cop);
}
void remove_rampa(struct rampa** rampe, int* nrRampe)
{
	(*nrRampe)--;
	struct rampa* cop = malloc(sizeof(struct rampa) * (*nrRampe));
	for (int i = 0; i < (*nrRampe); i++)
	{
		cop[i] = copiere((*rampe)[i]);
	}

	free((*rampe));
	(*rampe) = malloc(sizeof(struct rampa) * (*nrRampe));
	for (int i = 0; i < (*nrRampe); i++)
	{
		(*rampe)[i] = copiere(cop[i]);
	}
	free(cop);
}
struct rampa* aceeasiInaltime(struct rampa *rampe,int *nrRampe, int *nrRampeNou)
{
	int nr = 1;
	for (int i = 1; i < (*nrRampe); i++)
	{
		if (rampe[i].inaltime == rampe[0].inaltime)
		{
			nr++;
		}
	}
	(*nrRampeNou) = nr;
	struct rampa* cond = malloc(sizeof(struct rampa) * nr);

	int k = 0;
	for (int i = 0; i < (*nrRampe); i++)
	{
		if (rampe[i].inaltime == rampe[0].inaltime)
		{
			cond[k] = copiere(rampe[i]);
			k++;
		}
	}

	return cond;


}
void afisare(struct rampa r)
{
	
	printf("Rampa are o lungime de: %5.2f", r.lungime);
	printf(" ,o inaltime de: %lf,", r.inaltime);
	printf(" o declivitate de: %f\n", r.declivitate);
	printf("Si se numeste: %s\n", r.numeDeal);
	printf("Prin aceasta rampa trec zilnic %d de masini, cu urmatoarele viteze\n", r.nrMasini);
	for (int i = 0; i < r.nrMasini; i++)
	{
		printf("%5.2f, ", r.viteze[i]);
	}
	printf("\n");
}
struct rampa citireRampeDinFisier(FILE *f)
{
	struct rampa rmp;
	fscanf(f, "%f", &rmp.lungime);
	fscanf(f, "%lf", &rmp.inaltime);
	fscanf(f, "%f", &rmp.declivitate);
	fscanf(f, "%d", &rmp.nrMasini);
	rmp.viteze = malloc(sizeof(float) * rmp.nrMasini);
	for (int i = 0; i < rmp.nrMasini; i++)
	{
		fscanf(f, "%f", &rmp.viteze[i]);
	}
	char aux[70];
	fscanf(f, "%s", &aux);
	rmp.numeDeal = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(rmp.numeDeal, aux);
	return rmp;
}
void citireVectorRampeDinFisier(const char* numeF, struct rampa** rampe, int* nrRampe)
{
	FILE* f;
	f = fopen(numeF, "r");
	int nr=0;
	fscanf(f, "%d", &nr);
	(*rampe) = malloc(sizeof(struct rampa) * nr);
	(*nrRampe) = nr;
	for (int i = 0; i < (*nrRampe); i++)
	{
		(*rampe)[i] = citireRampeDinFisier(f);
	}
}
void afisareVectorRampeLaConsola(struct rampa* rampe, int nrRampe)
{
	for (int i = 0; i < nrRampe; i++)
	{
		afisare(rampe[i]);
	}
}
void afisareInFisier(struct rampa ram,FILE* fisier)
{
	fprintf(fisier, "%f", ram.lungime);
	fprintf(fisier, "\n");
	fprintf(fisier, "%lf", ram.inaltime);
	fprintf(fisier, "\n");
	fprintf(fisier, "%f", ram.declivitate);
	fprintf(fisier, "\n");
	fprintf(fisier, "%d", ram.nrMasini);
	fprintf(fisier, "\n");
	for (int i = 0; i < ram.nrMasini; i++)
	{
		fprintf(fisier, "%f ,", ram.viteze[i]);
	}
	fprintf(fisier, "\n");
	fprintf(fisier, ram.numeDeal);
	fprintf(fisier, "\n");
}
void afisareVectorRampeInFisier(const char* numeFisier, struct rampa* rampe, int nrRampe)
{
	FILE* fisier;
	fisier = fopen(numeFisier, "w");
	for (int i = 0; i < nrRampe; i++)
	{
		afisareInFisier(rampe[i],fisier);
	}

}
struct rampa** creareMatriceDeRampe(struct rampa* r, int dimensiune, int *nrLinii,
	int **nrColoane, int pragMasini )
{
	(*nrLinii) = 2;
	(*nrColoane) = malloc(sizeof(int) * (*nrLinii));
	rampa** matrice = malloc(sizeof(rampa) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++)
	{
		(*nrColoane)[i] = 0;
		matrice[i] = NULL;
	}
	for (int i = 0; i < dimensiune; i++)
	{
		if (r[i].nrMasini > pragMasini)
			push_rampa(r[i], &(matrice[0]), &(*nrColoane)[0]);
		else
			push_rampa(r[i], &(matrice[1]), &(*nrColoane)[1]);
	}
	return matrice;
}
struct rampa** ordonareMatrice(struct rampa** r, int nrLinii, int nrColoane)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = i + 1; j < nrLinii; j++)
		{
			if (nrColoane - numarDeZerouri(r[i], nrColoane) > nrColoane - numarDeZerouri(r[j], nrColoane))
			{
				rampa* cp = malloc(sizeof(rampa) * nrColoane);
				cp = r[i];
				r[i] = r[j];
				r[j] = cp;
			}
		}
	}
	

	return r;

}
int numarDeZerouri(rampa* r, int col)
{
	int nr = 0;
	for (int i = 0; i < col; i++)
		if (r == NULL)
			nr++;
	return nr;
}
void afisareMatriceDeRampe(struct rampa** mat,int nrLinii, int *nrColoane)
{
	for (int i = 0; i < nrLinii; i++)
	{
		afisareVectorRampeLaConsola(mat[i], nrColoane[i]);
	}
}
void main()
{
	float vit[] = { 50,65,61,70,45 };
	struct rampa rpm=initiere(150, 25,10,5,vit,"Valea Neagra");
	//struct rampa rpm2=citireTastatura();
	//afisare(rpm);
	rpm.declivitate = schimbaDeclivitatea(rpm, 8);
	schimbaNume(&rpm, "Valea Rosie");
	//scoateViteze(&rpm, 3);
	adaugaViteze(&rpm, 41, 3);
	afisare(rpm);
	if (vitezaMedie(rpm) > 60)
	{
		printf("\n Se circula inconstient! Soferii trebuie avertizati sa mearga mai incet!");
	}
	else
		if (vitezaMedie(rpm) > 50)
		{
			printf("\n Conditiile de siguranta sunt de-abia respectate!");
		}
		else
		{
			printf("\n Soferii pun siguranta pe primul loc!");
		}
	struct rampa* rampe = NULL;
	int nrRampe = 0;
	citireVectorRampeDinFisier("Rampe.txt", &rampe, &nrRampe);
	afisareVectorRampeLaConsola(rampe, nrRampe);
	push_rampa(rpm, &rampe, &nrRampe);
	printf("\n");
	afisareVectorRampeLaConsola(rampe, nrRampe);
	remove_rampa(&rampe, &nrRampe);
	printf("\n");
	afisareVectorRampeLaConsola(rampe, nrRampe);
	struct rampa* cond = NULL;
	int nrCond = 0;
	cond = aceeasiInaltime(rampe, &nrRampe, &nrCond);
	afisareVectorRampeInFisier("Rezultate.txt", cond, nrCond);
	rampa** matrampa = NULL;
	int nrLinii = 0;
	int* dimensiuniColoane = NULL;
	matrampa = creareMatriceDeRampe(rampe, nrRampe, &nrLinii, &dimensiuniColoane, 4);
	printf("\n");

	afisareMatriceDeRampe(matrampa, nrLinii, dimensiuniColoane);
	matrampa = ordonareMatrice(matrampa, nrLinii, dimensiuniColoane);
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < (*dimensiuniColoane); j++)
		{
			if (matrampa[i][j].numeDeal != NULL)
				free(matrampa[i][j].numeDeal);
			if (matrampa[i][j].viteze != NULL)
			{
				matrampa[i][j].viteze = NULL;
				free(matrampa[i][j].viteze);
			}
		}
		matrampa[i] = NULL;
		free(matrampa[i]);
	}
	matrampa = NULL;
	free(matrampa);
	for (int i = 0; i < nrRampe; i++)
	{
		free(rampe[i].numeDeal);
		free(rampe[i].viteze);
	}
	rampe = NULL;
	free(rampe);
	for (int i = 0; i < nrCond; i++)
	{
		free(cond[i].numeDeal);
		cond[i].viteze = NULL;
		free(cond[i].viteze);
	}
	cond = NULL;
	free(cond);
	free(rpm.numeDeal);
	free(rpm.viteze);
	

	//free(rpm2.numeDeal);
	//free(rpm2.viteze);
}