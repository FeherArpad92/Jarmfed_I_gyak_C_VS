/******************************************************************************
 * Created:
 * Author :
******************************************************************************/
/******************************************************************************
* Include files
******************************************************************************/

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>


/******************************************************************************
* Function:         int main(void)
* Description:      main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
	//konstans
	const char forras[] = "Hello, szabvanyos konyvtar";

	//legyen nagyobb egyenlo, mint a forras
	//allokáció malloc is avagy dinamikus memória foglalással
	char cel[50];
	//ez statikus megoldás
	strcpy_s(cel,sizeof(forras), forras);

	printf("Forras string: %s\n", forras);
	printf("A cel string: %s\n", cel);

	if (strcmp(forras, cel) == 0) {
		printf("A ketto string megegyezik!\n");
	}

	//2. feladat
	char elso[100] = "Hello ";
	//konstans, hogy véletlen ne írjuk át
	const char masodik[] = "World!";

	printf("az elso string: %s\n", elso);
	printf("a masodik string: %s\n", masodik);

	strcat_s(elso, sizeof(elso), masodik);
	printf("az elso string: %s\n", elso);
	printf("a masodik string: %s\n", masodik);

	//3. feladat
	double szam;
	printf("Adjon meg egy potiziv szamot: ");
	scanf_s("%lf", &szam);

	if (szam < 0.0) {
		printf("A szam nem pozitiv!");
		return 1;
	}

	double gyok = sqrt(szam);

	printf("Az eredeti szam: %f \n", szam);
	printf("Az gyok: %f \n", gyok);

	printf("Az eredeti szam: %.4f \n", szam);
	printf("Az gyok: %.4f \n", gyok);

	printf("Az eredeti szam: %.10f \n", szam);
	printf("Az gyok: %.10f \n", gyok);

	printf("A gyok negyzete: %.10f \n", gyok*gyok);

	//4. feladat
	double alap, kitevo;

	printf("Adja meg az alapot: ");
	scanf_s("%lf", &alap);
	printf("Adja meg a kitevot: ");
	scanf_s("%lf", &kitevo);

	

	double eredmeny = pow(alap, kitevo);

	printf("A hatvanyozas eredmenye az alapnak (%lf) a kitevore(%lf): %lf\n", alap,kitevo, eredmeny);
	
	//5.feladat
	printf("A pi erteke: %f\n", M_PI);
	printf("A pi erteke: %.2f\n", M_PI);
	printf("A pi erteke: %.15f\n", M_PI);
	printf("A pi erteke: %.25f\n", M_PI);

	printf("A eurler szam erteke: %.20f\n", M_E);
	printf("A gyok 2 erteke: %.20f\n", M_SQRT2);

	//6. feladat
	printf("Adja meg egy szog erteket fokban: ");
	double szog;
	scanf_s("%lf", &szog);

	double szog_rad = szog * (M_PI / 180.0);

	printf("A szog erteker fokban: %lf\nA szog ertekere radianban: %lf", szog, szog_rad);

	double s = sin(szog_rad);
	double c = cos(szog_rad);
	double tg = tan(szog_rad);

	printf("A szinusz ereteke: %lf", s);
	printf("A cos ereteke: %lf", c);
	printf("A tg ereteke: %lf", tg);

	double ellenorzes = s * s + c * c;
	printf("Az ellenorzes erteke: %lf", ellenorzes);



	while (1)
	{

	}
}


/******************************************************************************
* Interrupt Routines
******************************************************************************/





