#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <omp.h>
#include <time.h>

int main()
{
    long num_passos = 100000;
    int i;
    double pi, sum = 0.0, passo, passo_duplo, tempo_total;
    passo = 1.0 / (double)num_passos;
    time_t inicio, fim;
    inicio = clock();
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction (:+ sum)
        {
            for (i = 0; i < num_passos; i++)
            {
                x = (i + 0.5) * passo;
                sum = sum + 4.0 / (1.0 + x * x);
            }
        }
    }
    fim = clock();
    tempo_total = double(inicio - fim) * double(CLOCKS_PER_SEC);
    tempo_total *= 1000;
    pi = passo * sum;
    printf("Valor do pi: %.2lf\n", pi);
    printf("Tempo decorrido: %.1lf\n", tempo_total);
    int r = _getch();
}
