/******************************************************************************
* Include files
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <corecrt_math_defines.h>

/******************************************************************************
* Macros
******************************************************************************/

// 1.1. feladat
#define ABS(x) ((x) < 0 ? -(x) : (x))

// 1.2. feladat
#define SQUARE(x) \
    double gyok = 0; \
    gyok = sqrt(x); \

// 1.3. feladat
#define IS_EVEN(y) ((y) % 2 == 0 ? printf("A megadott szam paros.\n") : printf("A megadott szam paratlan.\n"))

// 1.4. feladat
#define IS_DEVISIBLE(x, y) ((x) % (y) == 0 ? printf("Nincs maradek.\n") : printf("Van maradek.\n"))

// 1.5. feladat
#define CIRCLE_AREA(r) \
    float terulet = pow(r,2)*M_PI

// 1.6. feladat
#define FACTORIAL(n)  \
    int faktorialis = 1; \
    for (int i = 1; i <=(n); i++) \
    { \
        faktorialis *= i; \
    } \

// 1.7. feladat
#define IS_TRIANGLE_POSSIBLE(a, b, c) \
    int eredmeny = 0; \
    if( a < b+c) \
    { \
        eredmeny = 1;\
    } \
    else \
    { \
        eredmeny = 0; \
    } \
    if (b < a+c && eredmeny == 1) \
    { \
        eredmeny = 1; \
    } \
    else \
    { \
        eredmeny = 0; \
    } \
    if (c < b+a && eredmeny == 1) \
    { \
        eredmeny = 1; \
    } \
    else \
    { \
        eredmeny = 0; \
    } \

// 1.8. feladat
#define IS_PRIME(n) \
    int prim = 1; \
    if((n) <= 1) \
    { \
        printf("Nem prim.\n"); \
        prim = 0; \
    } \
    else \
    { \
        for(int i = 2; i*i <= (n); i++) \
        { \
            if((n) % i == 0) \
            { \
                printf("Nem prim.\n"); \
                prim = 0; \
                break; \
            } \
        } \
    } \
    if (prim == 1) \
    { \
        printf("Prim.\n"); \
    } \

// 1.9. feladat
#define TO_UPPER_CASE(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 'a' + 'A' : (c))

/******************************************************************************
* Constants
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
struct Node {
    char name[50];
    int score;
    struct Node* next;
};

int hiba = 0;

struct Node_2 {
    char name_2[100];
    int height;
    struct Node_2* next_2;
};

struct Node_3 {
    char name_3[100];
    struct Node_3* next_3;
};

/******************************************************************************
* External Variables
******************************************************************************/

/******************************************************************************
* Local Function Declarations
******************************************************************************/
void haromszog(double atfogo, double szog);
void negalt(char* str, char* bemenet, char* kimenet);
int maganhangzok(const char* mondat);
float celsius_fahrenheit(float celsius);
int szokoev(int ev);
int legnagyobb_kozos_oszto(int a, int b);
void nagybetu(char* mondat);
int fibonacci(int n);
void rendezes(int arr[], int n);
void datum(const char* date);
int length_with_pointer(const char* str);
int szorzat(int* array, int length);
void nevek(char* fullname);
void min_max(int* arr, int length, int** min, int** max);
void reverse_string(char szoveg[]);
struct Node* createNode(char* name, int score);
void insertNode(struct Node** head, char* name, int score);
void sortList(struct Node** head);
void printList(struct Node* head);
struct Node_2* createNode_2(char* name_2, int height);
void printList_2(struct Node_2* head_2);
void calculateAverageHeightAndTallest(struct Node_2* head_2, float* averageHeight, char* tallestStudent, int* maxHeight);
struct Node_3* createNode_3(char* name_3);
void printList_3(struct Node_3* head_3);
struct Node_3* insertInOrder(struct Node_3* head_3, char* name_3);

/******************************************************************************
* Local function Definitions
******************************************************************************/

/******************************************************************************
* Function:         int main(void)
* Description:      main function
* Input:
* Output:
* Notes:
******************************************************************************/
int main(void)
{
    // 1.1. feladat
    printf("1.1. feladat\n");
    int x = 0;
    printf("Adjon meg egy szamot!: ");
    scanf_s("%d", &x);
    printf("A megadott szam abszolut erteke: %d\n", ABS(x));

    // 1.2. feladat
    printf("\n1.2. feladat\n");
    double x_1_2 = 4;
    SQUARE(x_1_2);
    printf("A megadott szam gyoke: %f\n", gyok);


    // 1.3. feladat
    printf("\n1.3. feladat\n");
    int y = 0;
    printf("Adjon meg egy szamot!:");
    scanf_s("%d", &y);
    IS_EVEN(y);

    // 1.4. feladat
    printf("\n1.4. feladat\n");
    int x_1_4 = 4;
    int y_1_4 = 2;
    IS_DEVISIBLE(x_1_4, y_1_4);

    // 1.5. feladat
    printf("\n1.5. feladat\n");
    int r = 20;
    CIRCLE_AREA(r);
    printf("A kor terulete: %f\n", terulet);

    //1.6. feladat
    printf("\n1.6. feladat\n");
    int n_1_6 = 4;
    FACTORIAL(n_1_6);
    printf("A megadott szam faktorialisa: %d\n", faktorialis);

    // 1.7. feladat
    printf("\n1.7. feladat\n");
    int a, b, c;
    printf("Adja meg a-t!: ");
    scanf_s("%d", &a);
    printf("Adja meg b-t!: ");
    scanf_s("%d", &b);
    printf("Adja meg c-t!: ");
    scanf_s("%d", &c);
    IS_TRIANGLE_POSSIBLE(a, b, c);
    printf("Az eredmeny: %d\n", eredmeny);

    // 1.8. feladat
    printf("\n1.8. feladat\n");
    int n_1_8 = 28;
    IS_PRIME(n_1_8);

    // 1.9. feladat
    printf("\n1.9. feladat.\n");
    char kis = 'b';
    char nagy = TO_UPPER_CASE(kis);
    printf("A nagybetu: %c\n", nagy);

    // 2.1. feladat
    printf("\n2.1. feladat\n");
    int atfogo, szog;
    printf("Adja meg az oldalhosszt!: ");
    scanf_s("%d", &atfogo);
    printf("Adja meg a szoget!: ");
    scanf_s("%d", &szog);
    haromszog(atfogo, szog);

    // 2.2. feladat
    printf("\n2.2. feladat\n");
    char mondat_2_2[100] = "jo utat a kozlekesnek";
    int count = maganhangzok(mondat_2_2);
    printf("A mondatban %d maganhangzo talalhato.\n", count);

    // 2.3. feladat
    printf("\n2.3. feladat\n");
    float celsius = 0;
    printf("Adjon meg egy homerseklet erteket Celsiusban: ");
    scanf_s("%f", &celsius);
    float fahrenheit = celsius_fahrenheit(celsius);
    printf("A megadott homerseklet fahrenheitben: %f\n", fahrenheit);

    // 2.4. feladat
    printf("\n2.4. feladat\n");
    int ev;
    printf("Adjon meg egy evet: ");
    scanf_s("%d", &ev);
    if (szokoev(ev)) {
        printf("A megadott ev szokoev.\n");
    }
    else {
        printf("A megadott ev nem szokoev.\n");
    }

    // 2.5. feladat
    printf("\n2.5. feladat\n");
    int szam1, szam2;
    printf("Adja meg az elso szamot: ");
    scanf_s("%d", &szam1);
    printf("Adja meg a masodik szamot: ");
    scanf_s("%d", &szam2);
    int lko = legnagyobb_kozos_oszto(szam1, szam2);
    printf("A megadott ket szam legnagyobb kozos osztoja: %d\n", lko);

    // 2.6. feladat
    printf("\n2.6. feladat\n");
    char mondat_2_6[256] = "Jo utat a kozlekesnek.";
    nagybetu(mondat_2_6);
    printf("A nagybetus mondat: %s\n", mondat_2_6);

    // 2.7. feladat
    printf("\n2.7. feladat\n");
    int n_2_8;
    printf("Adjon meg egy szamot: ");
    scanf_s("%d", &n_2_8);
    int fibonacci_szam = fibonacci(n_2_8);
    printf("A megadott szamhoz tartozo Fibonacci-szam: %d\n", fibonacci_szam);

    // 2.8. feladat
    printf("\n2.8. feladat\n");
    char bemenet[10];
    char kimenet[9];

    printf("Adjon meg egy 8 bites logikai erteket (csak 0-t vagy 1-t tartalmazhat): ");
    scanf_s("%9s", bemenet, (unsigned)sizeof(bemenet));

    negalt(bemenet, bemenet, kimenet);
    if (hiba == 0)
    {
        printf("A logikai ertek negaltja: %s\n", kimenet);
    }

    // 2.9. feladat
    printf("\n2.9. feladat\n");
    int arr[4];
    printf("Adja meg a tomb elemeit:\n");

    for (int i = 0; i < 4; i++)
    {
        scanf_s("%d", &arr[i]);
    }
    rendezes(arr, 4);
    printf("A rendezett tomb:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 3.1. feladat
    printf("\n3.1. feladat\n");
    char date[] = "2024/12/29";
    datum(date);

    // 3.2. feladat
    printf("\n3.2. feladat\n");
    char elso[] = "szep ";
    char masodik[] = "napot ";
    char harmadik[] = "kivanok ";
    char* osszefuzott = (char*)malloc(strlen(elso) + strlen(masodik) + strlen(harmadik) + 3);
    strcpy_s(osszefuzott, strlen(elso) + strlen(masodik) + strlen(harmadik) + 3, elso);
    strcat_s(osszefuzott, strlen(elso) + strlen(masodik) + strlen(harmadik) + 3, masodik);
    strcat_s(osszefuzott, strlen(elso) + strlen(masodik) + strlen(harmadik) + 3, harmadik);
    printf("Az osszefuzott szoveg: %s\n", osszefuzott);

    int hossz_1 = strlen(osszefuzott);
    printf("Az osszefuzott szoveg hossza (beepitett fuggvennyel): %d\n", hossz_1);

    int hossz_2 = length_with_pointer(osszefuzott);
    printf("Az osszefuzott szoveg hossza (pointerrel): %d\n", hossz_2);

    // 3.3 feladat
    printf("\n3.3. feladat\n");
    int n_3_3;
    printf("Adja meg a tomb hosszat: ");
    scanf_s("%d", &n_3_3);
    int* array = (int*)malloc(n_3_3 * sizeof(int));
    if (array == NULL)
    {
        printf("Memoria foglalasi hiba!\n");
        return 1;
    }

    printf("Adja meg a tomb elemeit:\n");
    for (int i = 0; i < n_3_3; i++)
    {
        printf("array[%d] = ", i);
        scanf_s("%d", &array[i]);
    }

    int result = szorzat(array, n_3_3);
    printf("A tomb elemeinek szorzata: %d\n", result);
    free(array);

    // 3.4. feladat
    printf("\n3.4. feladat\n");
    char teljes_nev[] = "Kovacs Janos";
    nevek(teljes_nev);

    // 3.5. feladat
    printf("\n3.5. feladat\n");
    int szamok[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
    int length = sizeof(szamok) / sizeof(szamok[0]);
    int* min = NULL;
    int* max = NULL;
    min_max(szamok, length, &min, &max);
    if (min != NULL && max != NULL)
    {
        printf("Minimum: %d, memoriacime: %p\n", *min, (void*)min);
        printf("Maximum: %d, memoriacime: %p\n", *max, (void*)max);
    }

    // 3.6. feladat
    printf("\n3.6. feladat\n");
    char szoveg[] = "labda";
    reverse_string(szoveg);
    printf("A megforditott karakterlanc: %s\n", szoveg);

    // 3.7. feladat
    printf("\n3.7. feladat\n");
    struct Node* head = NULL;

    insertNode(&head, "Kovacs Janos", 85);
    insertNode(&head, "Nemeth Anna", 95);
    insertNode(&head, "Szabo Peter", 75);
    insertNode(&head, "Toth Ilona", 90);
    insertNode(&head, "Varga Laszlo", 80);

    printf("Eredeti lista:\n");
    printList(head);

    sortList(&head);

    printf("\nRendezett lista (csokkeno sorrendben a pontszamok alapjáa):\n");
    printList(head);

    struct Node* current = head;
    struct Node* next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    // 3.8. feladat
    printf("\n3.8. feladat\n");
    struct Node_2* head_2 = createNode_2("Anna", 165);
    head_2->next_2 = createNode_2("Bela", 180);
    head_2->next_2->next_2 = createNode_2("Cecil", 170);
    head_2->next_2->next_2->next_2 = createNode_2("David", 175);
    head_2->next_2->next_2->next_2->next_2 = createNode_2("Emma", 160);

    printf("A lista elemei:\n");
    printList_2(head_2);

    float averageHeight;
    char tallestStudent[100];
    int maxHeight;

    calculateAverageHeightAndTallest(head_2, &averageHeight, tallestStudent, &maxHeight);

    printf("\nAtlagmagassag: %.2f cm\n", averageHeight);
    printf("A legmagasabb tanulo: %s, Magassag: %d cm\n", tallestStudent, maxHeight);

    struct Node_2* current_2 = head_2;
    struct Node_2* next_2;
    while (current_2 != NULL)
    {
        next = current_2->next_2;
        free(current_2);
        current_2 = next;
    }

    // 3.9. feladat
    printf("\n3.9. feladat\n");
    struct Node_3* head_3 = createNode_3("Anna");
    head_3->next_3 = createNode_3("Bela");
    head_3->next_3->next_3 = createNode_3("Cecil");
    head_3->next_3->next_3->next_3 = createNode_3("David");
    head_3->next_3->next_3->next_3->next_3 = createNode_3("Zsolt");

    printf("Eredeti lista:\n");
    printList_3(head_3);

    char newStudentName[100];
    printf("Kerem adja meg a hatodik tanulo nevet: ");

    scanf_s("%99s", newStudentName, (unsigned)_countof(newStudentName));

    head_3 = insertInOrder(head_3, newStudentName);

    printf("\nModositott lista (6 elemmel):\n");
    printList_3(head_3);

    struct Node_3* current_3 = head_3;
    struct Node_3* next_3;
    while (current_3 != NULL)
    {
        next_3 = current_3->next_3;
        free(current_3);
        current_3 = next_3;
    }

    while (1)
    {

    }
}

/******************************************************************************
* Function:         void haromszog(double atfogo, double szog)
* Description:      haromszog ertekeinek meghatarozasa
* Input:            double atfogo, double szog
* Output:
* Notes:            2.1. feladat
******************************************************************************/
void haromszog(double atfogo, double szog)
{
    float befogo_1 = sin(szog) * atfogo;
    float befogo_2 = cos(szog) * atfogo;
    float szog_3 = 180 - 90 - szog;

    printf("A haromszog befogoi %f, %f, a harmadik szog: %f\n", befogo_1, befogo_2, szog_3);
}

/******************************************************************************
* Function:         int maganhangzok(const char* mondat)
* Description:      karakterlancban talalhato maganhangzokat szamolja meg
* Input:            const char* mondat
* Output:           int count
* Notes:            2.2. feladat
******************************************************************************/
int maganhangzok(const char* mondat)
{
    int count = 0;
    const char* p = mondat;

    while (*p != '\0')
    {
        char c = *p;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        {
            count++;
        }
        p++;
    }
    return count;
}
/******************************************************************************
* Function:         float celsius_fahrenheit(float celsius)
* Description:      celsius-fahrenheit atvaltas
* Input:            float celsius
* Output:           float fahrenheit
* Notes:            2.3. feladat
******************************************************************************/
float celsius_fahrenheit(float celsius)
{
    float fahrenheit = celsius * 1.8 + 32;
    return fahrenheit;
}

/******************************************************************************
* Function:         int szokoev(int ev)
* Description:      szokoev-e a megadott ev
* Input:            int ev
* Output:           int szokoev
* Notes:            2.4. feladat
******************************************************************************/
int szokoev(int ev)
{
    if ((ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0))
    {
        return 1;
    }
    return 0;
}

/******************************************************************************
* Function:         int legnagyobb_kozos_oszto(int a, int b)
* Description:      visszaadja ket szam legnagyobb kozos osztojat
* Input:            int a, int b
* Output:           int lko
* Notes:            2.5. feladat
******************************************************************************/
int legnagyobb_kozos_oszto(int a, int b) 
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/******************************************************************************
* Function:         void nagybetu(char* mondat)
* Description:      megadott mondtad minden szavanak kezdobetujet nagybetuve alakitja
* Input:            char* mondat
* Output:           
* Notes:            2.6. feladat
******************************************************************************/
void nagybetu(char* mondat)
{
    int i;
    if (mondat[0] >= 'a' && mondat[0] <= 'z')
    {
        mondat[0] = mondat[0] - ('a' - 'A');
    }
    for (i = 1; mondat[i] != '\0'; i++)
    {
        if (mondat[i] == ' ' && mondat[i + 1] != '\0' && mondat[i + 1] >= 'a' && mondat[i + 1] <= 'z')
        {
            mondat[i + 1] = mondat[i + 1] - ('a' - 'A');
        }
    }
}

/******************************************************************************
* Function:         int fibonacci(int n)
* Description:      szamhoz tartozo Fibonacci-szamot adja vissza
* Input:            int n
* Output:           int Fibonacci
* Notes:            2.7. feladat
******************************************************************************/
int fibonacci(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
/******************************************************************************
* Function:         void negalt(char* str, char* bemenet, char* kimenet)
* Description:      logikai ertek negaltjat adja viszza
* Input:            char* str, char* bemenet, char* kimenet
* Output:
* Notes:            2.8. feladat
******************************************************************************/
void negalt(char* str, char* bemenet, char* kimenet)
{
    if (strlen(str) != 8)
    {
        printf("A megadott ertek nem 8 bit-es!\n");
        hiba = 1;
    }

    for (int i = 0; i < 8; i++)
    {
        if (str[i] != '0' && str[i] != '1')
        {
            printf("A megadott ertek nem logikai!\n");
            hiba = 1;
            return;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        kimenet[i] = (bemenet[i] == '0') ? '1' : '0';
    }
    kimenet[8] = '\0';

}

/******************************************************************************
* Function:         void rendezes(int arr[], int n)
* Description:      tomb novekno sorrendbe rendezese
* Input:            int arr[], int n
* Output:
* Notes:            2.9. feladat
******************************************************************************/
void rendezes(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/******************************************************************************
* Function:         void datum(const char* date)
* Description:      datum szetbontasa
* Input:            const char* date
* Output:
* Notes:            3.1. feladat
******************************************************************************/
void datum(const char* date)
{
    int year, month, day;
    if (strlen(date) != 10 || date[4] != '/' || date[7] != '/')
    {
        printf("Hibas datum formatum.\n");
        return;
    }
    year = atoi(date);
    month = atoi(date + 5);
    day = atoi(date + 8);

    printf("Ev: %d\n", year);
    printf("Honap: %d\n", month);
    printf("Nap: %d\n", day);
}

/******************************************************************************
* Function:         int length_with_pointer(const char* str)
* Description:      szoveg hosszanak kiszamitasa
* Input:            const char* str
* Output:           int length
* Notes:            3.2. feladat
******************************************************************************/
int length_with_pointer(const char* str)
{
    const char* ptr = str;
    int length = 0;
    while (*ptr != '\0')
    {
        length++;
        ptr++;
    }
    return length;
}

/******************************************************************************
* Function:         int szorzat(int* array, int length)
* Description:      tomb elemeinek osszeszorzasa
* Input:            int* array, int length
* Output:           int szorzat
* Notes:            3.3. feladat
******************************************************************************/
int szorzat(int* array, int length)
{
    int product = 1;
    for (int i = 0; i < length; i++)
    {
        product *= array[i];
    }
    return product;
}

/******************************************************************************
* Function:         void nevek(char* teljes_nev)
* Description:      nev szetbontasa
* Input:            char* teljes_nev
* Output:           
* Notes:            3.4. feladat
******************************************************************************/
void nevek(char* teljes_nev)
{
    char* keresztnev = NULL;
    char* start = teljes_nev;

    while (*teljes_nev != '\0')
    {
        if (*teljes_nev == ' ')
        {
            keresztnev = teljes_nev + 1;
            break;
        }
        teljes_nev++;
    }

    if (keresztnev != NULL)
    {
        *(keresztnev - 1) = '\0';

        printf("Vezeteknev: %s\n", start);
        printf("Keresztnev: %s\n", keresztnev);
    }
}

/******************************************************************************
* Function:         void min_max(int* arr, int length, int** min, int** max)
* Description:      tomb ertekei kozul kivalasztja a legkisebbet es a legnagyobbat
* Input:            int* arr, int length, int** min, int** max
* Output:
* Notes:            3.5. feladat
******************************************************************************/
void min_max(int* arr, int length, int** min, int** max)
{
    if (length <= 0)
    {
        *min = NULL;
        *max = NULL;
        return;
    }

    *min = arr;
    *max = arr;

    for (int i = 1; i < length; i++)
    {
        if (arr[i] < **min)
        {
            *min = &arr[i];
        }
        if (arr[i] > **max)
        {
            *max = &arr[i];
        }
    }
}

/******************************************************************************
* Function:         void reverse_string(char szoveg[])
* Description:      karaktertomb megforditasa
* Input:			char szoveg[]
* Output:			megforditott tomb
* Notes:            3.6. feladat
******************************************************************************/
void reverse_string(char szoveg[])
{
    int hossz = strlen(szoveg);
    for (int i = 0; i < hossz / 2; i++)
    {
        char temp = szoveg[i];
        szoveg[i] = szoveg[hossz - 1 - i];
        szoveg[hossz - 1 - i] = temp;
    }
}

/******************************************************************************
* Function:         struct Node* createNode(char* name, int score)
* Description:      uj node letrehozasa
* Input:			char* name, int score
* Output:			uj node
* Notes:            3.7. feladat
******************************************************************************/
struct Node* createNode(char* name, int score)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy_s(newNode->name, sizeof(newNode->name), name);
    newNode->score = score;
    newNode->next = NULL;
    return newNode;
}

/******************************************************************************
* Function:         void insertNode(struct Node** head, char* name, int score)
* Description:      uj node beszurasa a lista vegere
* Input:			struct Node** head, char* name, int score
* Output:
* Notes:            3.7. feladat
******************************************************************************/
void insertNode(struct Node** head, char* name, int score)
{
    struct Node* newNode = createNode(name, score);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

/******************************************************************************
* Function:         void sortList(struct Node** head)
* Description:      lancolt lista csokkeno sorrendbe rendezese pontszamok alapjan
* Input:			struct Node** head
* Output:
* Notes:            3.7. feladat
******************************************************************************/
void sortList(struct Node** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    struct Node* current, * index;
    int tempScore;
    char tempName[50];

    for (current = *head; current->next != NULL; current = current->next)
    {
        for (index = current->next; index != NULL; index = index->next)
        {
            if (current->score < index->score)
            {
                tempScore = current->score;
                current->score = index->score;
                index->score = tempScore;

                strcpy_s(tempName, sizeof(tempName), current->name);
                strcpy_s(current->name, sizeof(current->name), index->name);
                strcpy_s(index->name, sizeof(index->name), tempName);
            }
        }
    }
}

void printList(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL)
    {
        printf("Nev: %s, Pont: %d\n", current->name, current->score);
        current = current->next;
    }
}

/******************************************************************************
* Function:         struct Node_2* createNode_2(char* name_2, int height)
* Description:      lista letrehozasa
* Input:			char* name_2, int height
* Output:           
* Notes:            3.8. feladat
******************************************************************************/
struct Node_2* createNode_2(char* name_2, int height)
{
    struct Node_2* newNode = (struct Node_2*)malloc(sizeof(struct Node_2));
    strcpy_s(newNode->name_2, sizeof(newNode->name_2), name_2);
    newNode->height = height;
    newNode->next_2 = NULL;
    return newNode;
}

/******************************************************************************
* Function:         void printList_2(struct Node_2* head_2)
* Description:      lancolt lista kiirasa
* Input:			struct Node_2* head_2
* Output:
* Notes:            3.8. feladat
******************************************************************************/
void printList_2(struct Node_2* head_2)
{
    struct Node_2* current_2 = head_2;
    while (current_2 != NULL)
    {
        printf("Nev: %s, Magassag: %d cm\n", current_2->name_2, current_2->height);
        current_2 = current_2->next_2;
    }
}

/******************************************************************************
* Function:         void calculateAverageHeightAndTallest(struct Node_2* head_2, float* averageHeight, char* tallestStudent, int* maxHeight)
* Description:      atlagmagassagot es a legmagasabb tanulot adja vissza
* Input:			struct Node_2* head_2, float* averageHeight, char* tallestStudent, int* maxHeight
* Output:
* Notes:            3.8. feladat
******************************************************************************/
void calculateAverageHeightAndTallest(struct Node_2* head_2, float* averageHeight, char* tallestStudent, int* maxHeight)
{
    int totalHeight = 0;
    int count = 0;
    *maxHeight = 0;

    struct Node_2* current_2 = head_2;
    while (current_2 != NULL)
    {
        totalHeight += current_2->height;
        count++;
        if (current_2->height > *maxHeight)
        {
            *maxHeight = current_2->height;
            strcpy_s(tallestStudent, sizeof(tallestStudent), current_2->name_2);
        }
        current_2 = current_2->next_2;
    }

    if (count > 0)
    {
        *averageHeight = (float)totalHeight / count;
    }
    else
    {
        *averageHeight = 0;
    }
}

/******************************************************************************
* Function:         struct Node_3* createNode_3(char* name_3)
* Description:      lista letrehozasa
* Input:			char* name_3
* Output:
* Notes:            3.9. feladat
******************************************************************************/
struct Node_3* createNode_3(char* name_3)
{
    struct Node_3* newNode_3 = (struct Node_3*)malloc(sizeof(struct Node_3));
    strcpy_s(newNode_3->name_3, sizeof(newNode_3->name_3), name_3);
    newNode_3->next_3 = NULL;
    return newNode_3;
}

/******************************************************************************
* Function:         void printList_3(struct Node_3* head_3)
* Description:      lista kiirasa
* Input:			struct Node_3* head_3
* Output:
* Notes:            3.9. feladat
******************************************************************************/
void printList_3(struct Node_3* head_3)
{
    struct Node_3* current_3 = head_3;
    while (current_3 != NULL)
    {
        printf("Nev: %s\n", current_3->name_3);
        current_3 = current_3->next_3;
    }
}

/******************************************************************************
* Function:         struct Node_3* insertInOrder(struct Node_3* head_3, char* name_3)
* Description:      ABC sorrendbe rendezes
* Input:			struct Node_3* head_3, char* name_3
* Output:
* Notes:            3.9. feladat
******************************************************************************/
struct Node_3* insertInOrder(struct Node_3* head_3, char* name_3)
{
    struct Node_3* newNode_3 = createNode_3(name_3);

    if (head_3 == NULL || strcmp(newNode_3->name_3, head_3->name_3) < 0)
    {
        newNode_3->next_3 = head_3;
        return newNode_3;
    }

    struct Node_3* current_3 = head_3;
    while (current_3->next_3 != NULL && strcmp(current_3->next_3->name_3, newNode_3->name_3) < 0)
    {
        current_3 = current_3->next_3;
    }

    newNode_3->next_3 = current_3->next_3;
    current_3->next_3 = newNode_3;

    return head_3;
}