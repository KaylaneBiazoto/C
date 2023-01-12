/* Faça um programa em C que exiba os valores inteiros compreendidos entre n e m, sendo que n e
m serão inteiros fornecidos pelo usuário */

#include <stdio.h>
#include <locale.h>
int n, m;

void main (void)
{
   //Pede um número ao usuário
    setlocale(LC_ALL, "Portuguese");
    printf("Forneça valores inteiros para n e m: ");
    scanf("%d %d", &n, &m);

  //Faz um loop para dois casos
    while(n != m - 1 && n != m + 1)
    {
        if (n < m)
       {
        n = n + 1;
        printf("%d ", n);
       }

        else
            if (n > m)
       {
        n = n - 1;
        printf("%d ", n);
       }
    }
}
