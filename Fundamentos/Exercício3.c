/* Faça um programa em C que exiba os valores inteiros pares compreendidos entre 1 e n, sendo
que n será um inteiro fornecido pelo usuário; */

#include <stdio.h>
#include <locale.h>
int n;
int i = 1;

void main (void)
{
    setlocale(LC_ALL, "Portuguese");
    printf("Forneça um número: ");
    scanf("%d", &n);

    printf("Os números pares entre 1 e %d são:  ", n);

    while (i < n)
    {
      if (i % 2 == 0)
     {
         printf("%d ", i);
     }
        i++;
    }

    while (i > n)
    {
        if (i % 2 == 0)
        {
            printf("%d ", i);
        }
        i--;
    }
}
