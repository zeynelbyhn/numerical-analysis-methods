#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EULER 2.7182818284590452
#define MAX 100
#define PI 3.141592653589793

// String olarak girdigim fonksiyonun parcalara ayrilmasi icin kullandigim struct yapilari
typedef struct
{
    char *str;
    double val;
} Operand;

typedef struct
{
    Operand operandStack[MAX];
    int operandTop;

    char operatorStack[MAX];
    int operatorTop;
} StackContext;

void printMenu();
// Fonksiyon prototipleri
void pushOperand(StackContext *, Operand); // stack'e eleman ekler
Operand popOperand(StackContext *);        // stack'ten eleman cikarir
void pushOperator(StackContext *, char);   // stack'e operator ekler +,-,*...
char popOperator(StackContext *);          // stack'tan operator alir
char peekOperator(StackContext *);         // en ustteki operator'u gostermek icin kullanilir.

int precedence(char);
void processOperator(StackContext *);

// YONTEMLER
void Bisection();
void RegulaFalsi();
void NewtonRaphson();
void inverseMatrix();
void Cholesky();
void GaussSeidel();
void sayisalTurev();
void Simpson13();
void Simpson38();
void trapezYontemi();
void GregoryNewton();

// Fonksiyon alma ve deger koyma
float getFuncValue(char func[], float);
void getFunc(char *);

// kendi ek fonksiyonlarim;
int my_strlen(char *);
void my_strcpy(char *, char *);
void my_strcat(char *, char *);
float **mallocMatris(int);
float **callocMatris(int);
void printMatris(float **, int);
void freeMatris(float **, int);
int faktoriyel(float i);

int main()
{
    int simp;
    int yontem;

    do
    {
        printMenu();
        printf("\nLutfen kullanacaginiz yontem icin 1-10 arasi tuslayiniz. Cikis yapmak icin 0 tuslayabilirsiniz.\n");

        scanf("%d", &yontem);
        if (yontem == 1)
        {
            Bisection();
        }
        if (yontem == 2)
        {
            RegulaFalsi();
        }
        if (yontem == 3)
        {
            NewtonRaphson();
        }
        if (yontem == 4)
        {
            inverseMatrix();
        }
        if (yontem == 5)
        {
            Cholesky();
        }
        if (yontem == 6)
        {
            GaussSeidel();
        }
        if (yontem == 7)
        {
            sayisalTurev();
        }
        if (yontem == 8)
        {
            printf("hangi yontemi kullanmak istersiniz? Simpson 1/3 icin 3, Simpson 3/8 icin 8'i tuslayin: ");
            scanf("%d", &simp);
            if (simp == 3)
            {
                Simpson13();
            }
            else
            {
                Simpson38();
            }
        }
        if (yontem == 9)
        {
            trapezYontemi();
        }
        if (yontem == 10)
        {
            GregoryNewton();
        }

    } while (yontem != 0);

    printf("Cikis yapiliyor...\n");
    return 0;
}

void printMenu()
{
    printf(" =  YONTEMLER  =\n");
    printf("-------------------------\n");
    printf("0: CIKIS\n");
    printf("1: BISECTION\n");
    printf("2: REGULA FALSI\n");
    printf("3: NEWTON RAPHSON\n");
    printf("4: MATRISIN TERSINI ALMA\n");
    printf("5: CHOLESKY\n");
    printf("6: GAUSS SEIDEL\n");
    printf("7: SAYISAL TUREV\n");
    printf("8: SIMPSON YONTEMLERI\n");
    printf("9: TRAPEZ YONTEMI\n");
    printf("10: NEWTON ENTERPOLASYONU\n");
}
void Bisection()
{
    char func[MAX];

    float start, end, mid;
    float eps;
    float startValue, endValue, midValue;
    float error; // iterasyondaki hata degerimiz
    int itr = 1;
    float previousMid = 0;

    getFunc(func);

    printf("Lutfen [a,b] araligini giriniz: ");
    scanf("%f %f", &start, &end);
    printf("Lutfen hata degerini giriniz: ");
    scanf("%f", &eps); // epsulon degeri

    startValue = getFuncValue(func, start);
    endValue = getFuncValue(func, end);
    while (startValue * endValue > 0)
    {
        printf("Bu aralikta kok yoktur lutfen [a,b] degerlerini tekrar giriniz.\n");
        scanf("%f %f", &start, &end);
        startValue = getFuncValue(func, start);
        endValue = getFuncValue(func, end);
    }
    if (startValue == 0)
    {

        printf("Kok degeri araliklardan biri olarak girildi.\n");
        printf("Kok = %f\n", start);
    }
    else if (endValue == 0)
    {

        printf("Kok degeri araliklardan biri olarak girildi.\n");
        printf("Kok = %f\n", end);
    }
    else
    {
        do
        {
            printf("\n%d. iterasyon, [%f,%f]\n", itr, start, end);
            printf("f(%.2f) = %.2f, f(%.2f) = %.2f, f(%.2f) x f(%.2f) < 0\n", start, startValue, end, endValue, start, end);
            mid = (start + end) / 2;
            midValue = getFuncValue(func, mid);
            printf("mid = %.2f, f(%.2f) = %.2f\n", mid, mid, midValue);
            error = fabs(mid - previousMid);
            printf("Hata degeri = %f\n", error);
            // yeni start end degerlerini yazdik
            previousMid = mid;
            if (midValue < 0)
            {
                if (startValue < 0 && endValue > 0)
                {
                    start = mid;
                }
                else if (startValue > 0 && endValue < 0)
                {
                    end = mid;
                }
            }
            else if (midValue > 0)
            {
                if (startValue < 0 && endValue > 0)
                {
                    end = mid;
                }
                else if (startValue > 0 && endValue < 0)
                {
                    start = mid;
                }
            }
            startValue = getFuncValue(func, start);
            endValue = getFuncValue(func, end);
            itr++;
        } while (error > eps);
        printf("\nYAKLASIK KOK: %f\n\n\n", mid);
    }
}

// REGULA FALSI
void RegulaFalsi()
{
    char func[MAX];
    float start, end, new;
    float startValue, endValue, newValue;
    float eps, error; // eps epsilon
    int itr = 1;
    float previousNew = 0;
    getFunc(func);
    printf("Lutfen [a,b] araligini giriniz: ");
    scanf("%f %f", &start, &end);
    printf("Lutfen hata degerini giriniz: ");
    scanf("%f", &eps); // epsilon degeri
    startValue = getFuncValue(func, start);
    endValue = getFuncValue(func, end);
    while (startValue * endValue > 0)
    {
        printf("Bu aralikta kok yoktur lutfen [a,b] degerlerini tekrar giriniz.\n");
        scanf("%f %f", &start, &end);
        startValue = getFuncValue(func, start);
        endValue = getFuncValue(func, end);
    }
    if (startValue == 0)
    {

        printf("Kok degeri araliklardan biri olarak girildi.\n");
        printf("Kok = %f\n", start);
    }
    else if (endValue == 0)
    {

        printf("Kok degeri araliklardan biri olarak girildi.\n");
        printf("Kok = %f\n", end);
    }
    else
    {
        do
        {
            printf("\n\n%d. iterasyon, [%f,%f]\n", itr, start, end);
            printf("f(%.2f) = %.2f, f(%.2f) = %.2f, f(%.2f) x f(%.2f) < 0\n", start, startValue, end, endValue, start, end);
            new = (start * endValue - end * startValue) / (endValue - startValue);
            newValue = getFuncValue(func, new);
            printf("new = %.2f, f(%.2f) = %.2f\n", new, new, newValue);
            error = fabs(new - previousNew);

            printf("Hata degeri = %f", error);
            // yeni start end degerlerini yazdik

            if (startValue * newValue < 0)
            {
                end = new;
            }
            else
            {
                start = new;
            }
            startValue = getFuncValue(func, start);
            endValue = getFuncValue(func, end);
            previousNew = new;
            itr++;
        } while (error > eps);
        printf("\n\nYAKLASIK KOK: %f\n", new);
    }
}

// =========== NEWTON RAPHSON =======================
void NewtonRaphson()
{
    char func[MAX];
    getFunc(func);
    float newX, x;
    float eps, error; // eps epsilon
    float h = 0.001;
    float xValue;
    int itr = 1;
    float temp;

    printf("Lutfen Xo degerini giriniz:  ");
    scanf("%f", &x);

    printf("Lutfen hata degerini giriniz. \n");
    scanf("%f", &eps); // epsulon degeri
    xValue = getFuncValue(func, x);
    if (xValue == 0)
    {
        printf("Girilen deger zaten fonksiyonun kokudur.\n");
        
    }
    else
    {
        do
        {
            xValue = getFuncValue(func, x);
            temp = x + h;
            newX = x - (xValue / ((getFuncValue(func, temp) - getFuncValue(func, x)) / h));
            error = fabs(newX - x);
            printf("iterasyon degeri: %d\n", itr);
            printf("Xn = %f, Xn+1 = %f\n\n", x, newX);
            x = newX;
            itr++;
        } while (error > eps);
    }

    printf("YAKLASIK KOK: %f\n", x);
}

// MATRISIN TERSINI ALMA

void inverseMatrix()
{
    float factor;
    float pivot;
    int boyut;
    int i, j, k;
    float **matris;
    float **reverseMatris;
    printf("Lutfen matrisin boyutunu giriniz.\n");
    scanf("%d", &boyut);

    matris = mallocMatris(boyut);
    reverseMatris = callocMatris(boyut); // hepsini 0 aldım

    for (i = 0; i < boyut; i++)
    {
        reverseMatris[i][i] = 1;
    }

    for (i = 0; i < boyut; i++)
    {
        printf("matrisin %d. satiri icin %d tane eleman giriniz.\n", i + 1, boyut);
        for (j = 0; j < boyut; j++)
        {
            scanf("%f", &matris[i][j]);
        }
    } // matris elemanlarini aldim

    printf("\nGirilen matris:\n");
    printMatris(matris, boyut);

    for (j = 0; j < boyut; j++)
    {
        pivot = matris[j][j];

        // matrisin pivotu tersinin alinmasi icin 0'dan farkli olmali
        if (pivot == 0.0f)
        {
            printf("MATRIS TERSI ALINAMAZ.\n");
            return;
        }

        // satiri pivota böl
        for (k = 0; k < boyut; k++)
        {
            matris[j][k] /= pivot;
            reverseMatris[j][k] /= pivot;
        }

        // Alt satirlari sifirladim
        for (i = j + 1; i < boyut; i++)
        {
            factor = matris[i][j];
            for (k = 0; k < boyut; k++)
            {
                matris[i][k] -= factor * matris[j][k];
                reverseMatris[i][k] -= factor * reverseMatris[j][k];
            }
        }
    }

    // ust ucgeni sifirladim
    for (j = boyut - 1; j >= 0; j--)
    {
        for (i = j - 1; i >= 0; i--)
        {
            factor = matris[i][j];
            for (k = 0; k < boyut; k++)
            {
                matris[i][k] -= factor * matris[j][k];
                reverseMatris[i][k] -= factor * reverseMatris[j][k];
            }
        }
    }

    printf("\nmatrisin tersi:\n\n");
    printMatris(reverseMatris, boyut);

    freeMatris(matris, boyut);
    freeMatris(reverseMatris, boyut);
}

// CHOLESKY YONTEMI
void Cholesky()
{
    int boyut;
    int i, j, k;
    float **matris;         // AX B icin A matrisi
    float **lower, **upper; // Lower Upper
    float *result;          // AX B icin B matrisim
    float *y, *x;           // LU X = B icin aradaki matrisler

    printf("Lutfen matrisin boyutunu giriniz: ");
    scanf("%d", &boyut);

    result = (float *)malloc(boyut * sizeof(float));
    matris = mallocMatris(boyut);
    lower = callocMatris(boyut);
    upper = callocMatris(boyut);
    y = (float *)malloc(boyut * sizeof(float));
    x = (float *)malloc(boyut * sizeof(float));

    printf("Lutfen [A][X] = [B] icin A matrisinin elemanlarini giriniz:\n");
    for (i = 0; i < boyut; i++)
    {
        printf("%d. satir icin %d tane eleman giriniz:\n", i + 1, boyut);
        for (j = 0; j < boyut; j++)
        {
            scanf("%f", &matris[i][j]);
        }
    }

    printf("Lutfen [A][X] = [B] icin B matrisinin elemanlarini giriniz\n");
    for (i = 0; i < boyut; i++)
    {
        scanf("%f", &result[i]);
    }

    printf("Girilen Matris: \n");
    for (i = 0; i < boyut; i++)
    {
        for (j = 0; j < boyut; j++)
        {
            printf("%f ", matris[i][j]);
        }
        printf("[X%d] ", i);
        printf("%f\n", result[i]);
    }

    // Lower upper ayirdim
    for (i = 0; i < boyut; i++)
    {
        // Upper matirsi
        for (k = i; k < boyut; k++)
        {
            float sum = 0;
            for (j = 0; j < i; j++)
            {
                sum += lower[i][j] * upper[j][k];
            }
            upper[i][k] = matris[i][k] - sum;
        }

        // Lower matrisi
        for (k = i; k < boyut; k++)
        {
            if (i == k)
            {
                lower[i][i] = 1; // lower'in diyagoneli 1
            }
            else
            {
                float sum = 0;
                for (j = 0; j < i; j++)
                {
                    sum += lower[k][j] * upper[j][i];
                }
                lower[k][i] = (matris[k][i] - sum) / upper[i][i];
            }
        }
    }

    // LY = B,
    for (i = 0; i < boyut; i++)
    {
        y[i] = result[i];
        for (j = 0; j < i; j++)
        {
            y[i] -= lower[i][j] * y[j];
        }
    }
    // LUX = B
    // UX = Y
    for (i = boyut - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for (j = i + 1; j < boyut; j++)
        {
            x[i] -= upper[i][j] * x[j];
        }
        x[i] /= upper[i][i];
    }
    printf("\nLower matrisi: \n");
    printMatris(lower, boyut);
    printf("\nUpper matrisi: \n");
    printMatris(upper, boyut);

    printf("\nCozum x:\n");
    for (i = 0; i < boyut; i++)
    {
        printf("x[%d] = %f\n", i, x[i]);
    }

    printf("\n");

    // actigim matrisleri free ettim
    freeMatris(matris, boyut);
    freeMatris(lower, boyut);
    freeMatris(upper, boyut);
    free(result);
    free(x);
    free(y);
}

// GAUSS SEIDEL

void GaussSeidel()
{
    int boyut;
    int i, j;
    float **matris;
    float *result;
    float *degisken;
    int maxIndex;
    float maxValue;
    float k;
    float tolerance;
    int flag = 0;
    float sum = 0;

    printf("Lutfen matrisin boyutunu giriniz.\n");
    scanf("%d", &boyut);
    degisken = (float *)malloc(sizeof(float) * boyut);
    result = (float *)malloc(sizeof(float) * boyut);
    matris = mallocMatris(boyut);

    printf("Lutfen [A][X]=[C] icin A'nin matris elemanlarini giriniz.\n");
    for (i = 0; i < boyut; i++)
    {
        printf("%d. satir icin %d tane eleman giriniz.\n", i + 1, boyut);
        for (j = 0; j < boyut; j++)
        {
            scanf("%f", &matris[i][j]);
        }
    }
    printf("Lutfen [A][X]=[C] icin C'nin elemanlarini giriniz.\n");
    for (j = 0; j < boyut; j++)
    {
        scanf("%f", &result[j]);
    }

    for (i = 0; i < boyut; i++)
    {
        maxIndex = i;
        maxValue = fabs(matris[i][i]);

        for (j = i + 1; j < boyut; j++)
        {
            if (fabs(matris[j][i]) > maxValue)
            {
                maxValue = fabs(matris[j][i]);
                maxIndex = j; // max indeksi buldum
            }
        }
        int k;
        float temp;
        // satir degistirdim;
        for (k = 0; k < boyut; k++)
        {
            temp = matris[i][k];
            matris[i][k] = matris[maxIndex][k];
            matris[maxIndex][k] = temp;

            // C icin;
            temp = result[i];
            result[i] = result[maxIndex];
            result[maxIndex] = temp;
        }
    }
    printf("Matrisin son hali: \n\n");
    for (i = 0; i < boyut; i++)
    {
        for (j = 0; j < boyut; j++)
        {
            printf("%f ", matris[i][j]);
        }
        printf("X%d %f", i + 1, result[i]);
        printf("\n");
    }

    printf("\nLutfen degiskenler icin sirasiyla %d tane baslangic degeri giriniz:\n", boyut);
    for (i = 0; i < boyut; i++)
    {
        printf("x%d : ", i + 1);
        scanf("%f", &degisken[i]);
        printf("\n");
    }

    printf("Lutfen hata degerini giriniz: ");
    scanf("%f", &tolerance);
    printf("\n");

    // hata olcmek icin
    float *oncekiDegisken = (float *)malloc(sizeof(float) * boyut);
    for (i = 0; i < boyut; i++)
    {
        oncekiDegisken[i] = degisken[i];
    }

    printf("Iterasyon ");
    for (i = 0; i < boyut; i++)
    {
        printf("   x%d        hata   ", i + 1, i + 1);
    }
    printf("\n");

    // ilk degerler iicin
    int itr = 1;
    float *geciciDegisken = (float *)malloc(sizeof(float) * boyut);

    do
    {
        // onceki degerleri sakladim
        for (i = 0; i < boyut; i++)
        {
            geciciDegisken[i] = degisken[i];
        }

        printf("    %d    ", itr);

        for (i = 0; i < boyut; i++)
        {
            if (itr == 1)
            {
                printf(" %f     -     ", degisken[i]);
            }
            else
            {
                printf(" %f  %f ", degisken[i], fabs(degisken[i] - oncekiDegisken[i]));
            }
        }
        printf("\n");

        for (i = 0; i < boyut; i++)
        {
            sum = result[i];
            for (j = 0; j < boyut; j++)
            {
                if (j != i)
                {
                    sum -= matris[i][j] * degisken[j];
                }
            }
            degisken[i] = sum / matris[i][i];
        }

        // Hata kontrolu
        flag = 1;
        for (i = 0; i < boyut; i++)
        {
            if (fabs(degisken[i] - geciciDegisken[i]) >= tolerance)
            {
                flag = 0;
            }
            oncekiDegisken[i] = geciciDegisken[i]; // bir önceki iterasyonda neydi
        }

        itr++;
        if (flag != 0)
        {
            printf("    %d    ", itr);
            for (i = 0; i < boyut; i++)
            {
                printf(" %f  %f ", degisken[i], fabs(degisken[i] - oncekiDegisken[i]));
            }
        }

    } while (flag == 0);
    printf("\nYAKLASIK SONUCLAR:\n");
    for (i = 0; i < boyut; i++)
    {
        printf("x%d = %f\n", i + 1, degisken[i]);
    }

    freeMatris(matris, boyut);
    free(result);
    free(degisken);
}

void sayisalTurev()
{
    char func[MAX];
    float h, nokta;
    float ileri, geri, merkezi;
    getFunc(func);
    printf("Lutfen turevini alacaginiz noktayi giriniz: ");
    scanf("%f", &nokta);
    printf("\nLutfen h degerini giriniz: ");
    scanf("%f", &h);
    ileri = (getFuncValue(func, nokta + h) - getFuncValue(func, nokta)) / h;
    geri = (getFuncValue(func, nokta) - getFuncValue(func, nokta - h)) / h;
    merkezi = (getFuncValue(func, nokta + h) - getFuncValue(func, nokta - h)) / (2 * h);
    printf("\n%s fonksiyonunun ", func);
    printf("%f noktasindaki\nIleri turevi: (f(%f+%f) - f(%f)) / %f = %f\n", nokta, nokta, h, nokta, h, ileri);
    printf("Geri Turevi: (f(%f) - f(%f-%f)) / %f = %f\n", nokta, nokta, h, h, geri);
    printf("Merkezi Turevi: (f(%f+%f) - f(%f-%f)) / %f = %f\n", nokta, h, nokta, h, 2 * h, merkezi);
}

void Simpson13()
{
    char func[MAX];
    float a, b, x, sum = 0, result;
    float aValue, bValue;
    int n, i;
    float h;
    float xValue;
    getFunc(func);
    printf("Lutfen integralin sinirlarini giriniz: ");
    scanf("%f %f", &a, &b);
    printf("Lutfen Simpson 1/3 yontemi icin N degerini giriniz: ");
    scanf("%d", &n);
    while (n % 2 != 0)
    {
        printf("N degeri 2'nin kati olmali! Lutfen tekrar giriniz.\n");
        scanf("%d", &n);
    }

    aValue = getFuncValue(func, a);
    bValue = getFuncValue(func, b);
    printf(" X degeri   f(x) degeri\n");
    sum = 0;
    h = (b - a) / n;
    i = 0;
    x = a;
    while (x < b)
    {
        x = a + i * h;
        xValue = getFuncValue(func, x);
        if (x == a)
        {
            sum = xValue + sum;
        }
        else if (x == b)
        {
            sum = xValue + sum;
        }
        else if (i % 2 == 1)
        {
            sum = 4 * xValue + sum;
        }
        else if (i % 2 == 0)
        {
            sum = 2 * xValue + sum;
        }
        printf(" %f   %f\n", x, xValue);
        i++;
    }
    result = sum * (h / 3);
    printf("Simpson 1/3 icin yaklasik sonuc: %f\n", result);
}

void Simpson38()
{
    char func[MAX];
    float a, b, c, d, h, h1;
    float xValue, sum = 0, result = 0;
    int n;
    int i = 0;
    float x;
    getFunc(func);
    printf("Lutfen integralin sinirlarini giriniz: ");
    scanf("%f %f", &a, &b);
    printf("Lutfen Simpson 3/8 yontemi icin N degerini giriniz: ");
    scanf("%d", &n);
    h = (b - a) / n; // h = 3, n =2
    float x0, x1, x2, x3;
    float x0Value, x1Value, x2Value, x3Value;
    int k;
    for (k = 0; k < n; k++)
    {
        c = a + k * h;
        d = c + h;
        h1 = h / 3;
        x0 = c;
        x1 = c + h1;
        x2 = c + 2 * h1;
        x3 = c + 3 * h1;
        x0Value = getFuncValue(func, x0);
        x1Value = getFuncValue(func, x1);
        x2Value = getFuncValue(func, x2);
        x3Value = getFuncValue(func, x3);
        sum = (h / 8.0) * (x0Value + x3Value + 3 * (x1Value + x2Value));
        result = sum + result;
    }
    printf("yaklasik sonuc: %f\n", result);
}

void trapezYontemi()
{
    char func[MAX];
    int n;
    float x, xValue, result, sum = 0;
    float a, b, aValue, bValue; // sinirlar ve degerleri
    float h;
    getFunc(func);
    printf("Lutfen integralin sinirlarini giriniz: ");
    scanf("%f %f", &a, &b);
    printf("\nLutfen N degerini giriniz: ");
    scanf("%d", &n);
    printf(" X degeri -  f(x)\n");

    aValue = getFuncValue(func, a);
    printf("%f - %f\n", a, aValue);
    h = (b - a) / n;
    int i = 1;
    do
    {
        x = a + h * i;
        xValue = getFuncValue(func, x);
        sum = sum + xValue;
        printf("%f - %f\n", x, xValue);
        i++;

    } while (x < b - h);
    bValue = getFuncValue(func, b);
    printf("%f - %f\n", b, bValue);

    result = h * ((aValue + bValue) / 2 + sum);

    printf("%s fonksiyonun Trapez yontemi ile yaklasik sonucu: %f\n", func, result);
}

void GregoryNewton()
{

    float h;
    int nokta;
    float *Fx, *x;
    int i;
    float sonuc;
    printf("\nGregory Newton Enterpolasyonu icin kac tane nokta gireceksiniz? : ");
    scanf("%d", &nokta);
    Fx = (float *)malloc(sizeof(float) * nokta);
    x = (float *)malloc(sizeof(float) * nokta);
    printf("\nLutfen noktalari giriniz.\n");
    for (i = 0; i < nokta; i++)
    {
        printf("X%d = ", i + 1);
        scanf("%f", &x[i]);
    }
    printf("\nLutfen girdiginiz noktalar icin F(x) degerlerini giriniz.\n");
    for (i = 0; i < nokta; i++)
    {
        printf("F(%.2f) = ", x[i]);
        scanf("%f", &Fx[i]);
    }
    printf("Sonucu ogrenmek istediginiz noktayi giriniz: ");
    scanf("%f", &sonuc);

    float k;
    int j;
    h = x[1] - x[0];
    float fark[nokta][nokta]; // fark tablosu icin matris actim

    // ilk sutuna fx degerlerini koydum
    for (i = 0; i < nokta; i++)
    {
        fark[i][0] = Fx[i];
    }

    // farklari hesapladim
    for (j = 1; j < nokta; j++)
    {
        for (i = 0; i < nokta - j; i++)
        {
            fark[i][j] = fark[i + 1][j - 1] - fark[i][j - 1];
        }
    }

    printf("\nFark Tablosu:\n");
    for (i = 0; i < nokta; i++)
    {
        printf("X%d = %.2f: ", i+1, x[i]);
        for (j = 0; j < nokta - i; j++)
        {
            printf("%.2f ", fark[i][j]); // iki basamak yazdim
        }
        printf("\n");
    }

    float result = fark[0][0];
    k = (sonuc - x[0]) / h;
    float term = 1;
    for (i = 1; i < nokta; i++)
    {
        term *= (k - (i - 1)); // k*(k-1)*(k-2)*...
        result += (term * fark[0][i]) / faktoriyel(i);
    }

    printf("\n Yaklasik sonuc: %f\n", result);

    free(Fx);
    free(x);
}

int faktoriyel(float i)
{
    int sonuc = 1;
    int k;
    for (k = 1; k <= i; k++)
    {
        sonuc = sonuc * k;
    }
    return sonuc;
}

float **mallocMatris(int boyut)
{
    int i;
    float **matrix;
    matrix = (float **)malloc(boyut * sizeof(float *));
    if (matrix == NULL)
    {
        printf("BELLEK AYIRAMADI");
        exit(1);
    }
    for (i = 0; i < boyut; ++i)
    {
        matrix[i] = (float *)malloc(boyut * sizeof(float));
        if (matrix[i] == NULL)
        {
            printf("BELLEK AYIRAMADI");
            exit(1);
        }
    }
    return matrix;
}
float **callocMatris(int boyut)
{
    int i;
    float **matrix = (float **)calloc(boyut, sizeof(float *));
    if (matrix == NULL)
    {
        printf("BELLEK AYIRAMADI");
        exit(1);
    }

    for (i = 0; i < boyut; ++i)
    {
        matrix[i] = (float *)calloc(boyut, sizeof(float));
        if (matrix[i] == NULL)
        {
            printf("BELLEK AYIRAMADI");
            exit(1);
        }
    }
    return matrix;
}

void freeMatris(float **matrix, int boyut)

{
    int i;
    if (matrix == NULL)
    {
        return;
    }
    for (i = 0; i < boyut; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// FONKSIYON ALDIK
void getFunc(char *infix)
{
    printf("Lutfen fonksiyon giriniz.\n");
    scanf(" %[^\n]", infix);
}
// Fonksiyonlar

void pushOperand(StackContext *ctx, Operand op)
{
    ctx->operandStack[++ctx->operandTop] = op;
}

Operand popOperand(StackContext *ctx)
{
    return ctx->operandStack[ctx->operandTop--];
}

void pushOperator(StackContext *ctx, char op)
{
    ctx->operatorStack[++ctx->operatorTop] = op;
}

char popOperator(StackContext *ctx)
{
    return ctx->operatorStack[ctx->operatorTop--];
}

char peekOperator(StackContext *ctx)
{
    return ctx->operatorStack[ctx->operatorTop];
}

int my_strlen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

void my_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void my_strcat(char *dest, char *src)
{
    int i = my_strlen(dest);
    int j = 0;
    while (src[j] != '\0')
    {
        dest[i++] = src[j++];
    }
    dest[i] = '\0';
}

// ISLEM ONCELIGI
int precedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// ISLEMLERIN PROCESS EDILMESI
void processOperator(StackContext *ctx)
{
    char op = popOperator(ctx);

    Operand op1 = popOperand(ctx);
    Operand op2 = popOperand(ctx);

    int size = 2 + my_strlen(op1.str) + 1 + my_strlen(op2.str) + 1;
    char *expr = (char *)malloc(size * sizeof(char));

    expr[0] = op;
    expr[1] = ' ';
    expr[2] = '\0';
    my_strcat(expr, op1.str);
    my_strcat(expr, " ");
    my_strcat(expr, op2.str);

    double result = 0;
    if (op == '+')
        result = op1.val + op2.val;
    else if (op == '-')
        result = op1.val - op2.val;
    else if (op == '*')
        result = op1.val * op2.val;
    else if (op == '/')
        result = op1.val / op2.val;
    else if (op == '^')
        result = pow(op1.val, op2.val);

    Operand newOperand;
    newOperand.str = expr;
    newOperand.val = result;

    pushOperand(ctx, newOperand);
}

// STRING OLARAK MATRIS ALDIM VE SAGDAN SOLA OKUYARAK BUNU ISLEDIM
float getFuncValue(char infix[], float variable)
{
    StackContext ctx;
    ctx.operandTop = -1;
    ctx.operatorTop = -1;
    int len = my_strlen(infix);
    int i;
    for (i = len - 1; i >= 0; i--)
    {
        char ch = infix[i];

        if (ch == 'x')
        {
            Operand newOperand;
            newOperand.val = (double)variable;
            newOperand.str = (char *)malloc(2); // 'x' ve '\0' için 2 byte
            newOperand.str[0] = 'x';
            newOperand.str[1] = '\0';
            pushOperand(&ctx, newOperand);
        }
        else if (ch >= '0' && ch <= '9')
        {
            int j = i;
            while (j >= 0 && infix[j] >= '0' && infix[j] <= '9')
                j--;
            j++;
            int k;
            int num = 0;
            for (k = j; k <= i; k++)
                num = num * 10 + (infix[k] - '0');

            Operand newOperand;
            newOperand.val = (double)num;

            int digits = i - j + 1;
            newOperand.str = (char *)malloc(digits + 1);
            for (k = 0; k < digits; k++)
            {
                newOperand.str[k] = infix[j + k];
            }
            newOperand.str[digits] = '\0';

            pushOperand(&ctx, newOperand);
            i = j;
        }

        // arctan
        else if (i >= 4 && infix[i] == 'n' && infix[i - 1] == 'a' && infix[i - 2] == 't' && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a')
        {
            i -= 5;
            Operand value = popOperand(&ctx);
            double result = atan(value.val);
            Operand newOperand;
            newOperand.val = result;
            int len = 7 + my_strlen(value.str);
            newOperand.str = (char *)malloc(len);
            newOperand.str[0] = '\0';
            my_strcat(newOperand.str, "arctan ");
            my_strcat(newOperand.str, value.str);
            pushOperand(&ctx, newOperand);
        }

        // Arcsin (asin) fonksiyonu
        // Arcsin (asin) fonksiyonu
        else if (i >= 4 && infix[i] == 'n' && infix[i - 1] == 'i' && infix[i - 2] == 's' && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a')
        {
            i -= 5;
            Operand value = popOperand(&ctx);
            double val = value.val;
            if (val < -1 || val > 1)
            {
                printf("ARCSIN TANIMSIZDIR! Deger [-1,1] araliginda olmalidir.\n");
            }
            else
            {
                double result = asin(val);
                Operand newOperand;
                newOperand.val = result;
                int len = 7 + my_strlen(value.str);
                newOperand.str = (char *)malloc(len);
                newOperand.str[0] = '\0';
                my_strcat(newOperand.str, "arcsin ");
                my_strcat(newOperand.str, value.str);
                pushOperand(&ctx, newOperand);
            }
        }
        
        // Arccos (acos) fonksiyonu
        else if (i >= 4 && infix[i] == 's' && infix[i - 1] == 'o' && infix[i - 2] == 'c' && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a')
        {
            i -= 5;
            Operand value = popOperand(&ctx);
            double val = value.val;
            if (val < -1 || val > 1)
            {
                printf("ARCCOS TANIMSIZDIR! Deger [-1,1] araliginda olmalidir.\n");
            }
            else
            {
                double result = acos(val);
                Operand newOperand;
                newOperand.val = result;
                int len = 7 + my_strlen(value.str);
                newOperand.str = (char *)malloc(len);
                newOperand.str[0] = '\0';
                my_strcat(newOperand.str, "arccos ");
                my_strcat(newOperand.str, value.str);
                pushOperand(&ctx, newOperand);
            }
        }

        // Arccot (acot) fonksiyonu
        else if (i >= 4 && infix[i] == 't' && infix[i - 1] == 'o' && infix[i - 2] == 'c' && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a')
        {
            i -= 5;
            Operand value = popOperand(&ctx);
            double val = value.val;
            if (val == 0)
            {
                printf("ARCCOT TANIMSIZDIR! Deger 0 olamaz.\n");
            }
            else
            {
                double result = atan(1 / val);
                Operand newOperand;
                newOperand.val = result;
                int len = 7 + my_strlen(value.str);
                newOperand.str = (char *)malloc(len);
                newOperand.str[0] = '\0';
                my_strcat(newOperand.str, "arccot ");
                my_strcat(newOperand.str, value.str);
                pushOperand(&ctx, newOperand);
            }
        }
        // sin
        else if (i >= 2 && infix[i] == 'n' && infix[i - 1] == 'i' && infix[i - 2] == 's' && !(i >= 5 && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a'))
        {
            i -= 2;
            Operand value = popOperand(&ctx);
            double radian = value.val;
            double result = sin(radian);

            Operand newOperand;
            newOperand.val = result;
            int len = 4 + my_strlen(value.str);
            newOperand.str = (char *)malloc(len);
            newOperand.str[0] = '\0';
            my_strcat(newOperand.str, "sin ");
            my_strcat(newOperand.str, value.str);
            pushOperand(&ctx, newOperand);
        }
        // cos
        else if (i >= 2 && infix[i] == 's' && infix[i - 1] == 'o' && infix[i - 2] == 'c' && !(i >= 5 && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a'))
        {
            i -= 2;
            Operand value = popOperand(&ctx);
            double radian = value.val;
            double result = cos(radian);

            Operand newOperand;
            newOperand.val = result;
            int len = 4 + my_strlen(value.str);
            newOperand.str = (char *)malloc(len);
            newOperand.str[0] = '\0';
            my_strcat(newOperand.str, "cos ");
            my_strcat(newOperand.str, value.str);
            pushOperand(&ctx, newOperand);
        }
        // tan
        else if (i >= 2 && infix[i] == 'n' && infix[i - 1] == 'a' && infix[i - 2] == 't' && !(i >= 5 && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a'))
        {
            i -= 2;
            Operand value = popOperand(&ctx);
            double radian = value.val;
            if (cos(radian) == 0)
            {
                printf("TANJANT TANIMSIZDIR!\n");
            }
            else
            {
                double result = tan(radian);
                Operand newOperand;
                newOperand.val = result;
                int len = 4 + my_strlen(value.str);
                newOperand.str = (char *)malloc(len);
                newOperand.str[0] = '\0';
                my_strcat(newOperand.str, "tan ");
                my_strcat(newOperand.str, value.str);
                pushOperand(&ctx, newOperand);
            }
        }
        // cot
        else if (i >= 2 && infix[i] == 't' && infix[i - 1] == 'o' && infix[i - 2] == 'c' && !(i >= 5 && infix[i - 3] == 'c' && infix[i - 4] == 'r' && infix[i - 5] == 'a'))
        {
            i -= 2;
            Operand value = popOperand(&ctx);
            double radian = value.val;
            if (sin(radian) == 0)
            {
                printf("COTANJANT  TANIMSIZDIR!\n");
            }
            else
            {
                double result = 1 / tan(radian);
                Operand newOperand;
                newOperand.val = result;
                int len = 4 + my_strlen(value.str);
                newOperand.str = (char *)malloc(len);
                newOperand.str[0] = '\0';
                my_strcat(newOperand.str, "cot ");
                my_strcat(newOperand.str, value.str);
                pushOperand(&ctx, newOperand);
            }
        }
        else if (ch == '_')
        {
            Operand op1 = popOperand(&ctx);
            Operand op2 = popOperand(&ctx);

            double us = op2.val;
            double taban = op1.val;

            if (us <= 0 || taban <= 0 || taban == 1)
            {
                printf("Logaritma tanimsiz! (Negatif, sifir ya da taban=1 olamaz)\n");
                exit(1);
            }

            double result = log(us) / log(taban);
            Operand newOperand;
            newOperand.val = result;
            int len = 3 + my_strlen(op1.str) + my_strlen(op2.str);
            newOperand.str = (char *)malloc(len);
            newOperand.str[0] = '\0';
            my_strcat(newOperand.str, "_ ");
            my_strcat(newOperand.str, op2.str);
            my_strcat(newOperand.str, " ");
            my_strcat(newOperand.str, op1.str);
            pushOperand(&ctx, newOperand);
            i -= 3;
        }
        else if (ch == 'e')
        {
            Operand newOperand;
            newOperand.val = (double)EULER;
            newOperand.str = "e";
            pushOperand(&ctx, newOperand);
        }
        else if (ch == 'P')
        {

            Operand newOperand;
            newOperand.val = (double)PI;
            newOperand.str = "P";
            pushOperand(&ctx, newOperand);
        }
        // ========================================== EKSI ve ARTI KONTROLU
        else if (ch == '-')
        {
            if ((infix[i - 1] >= '0' && infix[i - 1] <= '9') || infix[i - 1] == 'x' || infix[i - 1] == 'e' || infix[i - 1] == 'P' || infix[i - 1] == ')')
            {
                while (ctx.operatorTop != -1 && precedence(peekOperator(&ctx)) > precedence(ch))
                {
                    processOperator(&ctx);
                }
                pushOperator(&ctx, ch);
            }
            else
            {
                float temp;
                temp = ctx.operandStack[ctx.operandTop].val;
                ctx.operandStack[ctx.operandTop].val = -1 * temp;
            }
        }
        else if (ch == '+')
        {
            if ((infix[i - 1] >= '0' && infix[i - 1] <= '9') || infix[i - 1] == 'x' || infix[i - 1] == 'e' || infix[i - 1] == 'P' || infix[i - 1] == ')')
            {
                while (ctx.operatorTop != -1 && precedence(peekOperator(&ctx)) > precedence(ch))
                {
                    processOperator(&ctx);
                }
                pushOperator(&ctx, ch);
            }
        }

        else if (ch == '*' || ch == '/' || ch == '^')
        {
            while (ctx.operatorTop != -1 && precedence(peekOperator(&ctx)) > precedence(ch))
            {
                processOperator(&ctx);
            }
            pushOperator(&ctx, ch);
        }
        else if (ch == ')')
        {
            pushOperator(&ctx, ch);
        }
        else if (ch == '(')
        {
            while (peekOperator(&ctx) != ')')
            {
                processOperator(&ctx);
            }
            popOperator(&ctx);
        }
    }

    while (ctx.operatorTop != -1)
    {
        processOperator(&ctx);
    }

    float result = ctx.operandStack[ctx.operandTop].val;

    return result;
}

void printMatris(float **matris, int boyut)
{
    int i, j;

    for (i = 0; i < boyut; i++)
    {
        for (j = 0; j < boyut; j++)
        {
            printf("%f ", matris[i][j]);
        }
        printf("\n");
    }
}
