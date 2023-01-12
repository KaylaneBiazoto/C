/* Faça um programa em C que exiba os valores inteiros compreendidos entre 1 e n, sendo que n
será um inteiro fornecido pelo usuário */

#include <stdio.h>
#include <locale.h>
int n, intervalo = 1;

void main (void)
{
    //Pede um número ao usuário
    setlocale(LC_ALL, "Portuguese");
    printf("Forneça um número inteiro: ");
    scanf("%d", &n);

   //Caso o n seja um número positivo
    while (intervalo < n - 1)
    {
      intervalo = intervalo + 1;
      printf("%d ", intervalo);
    }

    //Caso o n seja um número negativo
    while (intervalo > n + 1)
    {
      intervalo = intervalo - 1;
      printf("%d", intervalo);
    }

   //Caso não haja números entre eles
    if (n == 1 || n == 0 || n == 2)
        printf("Não há números inteiros entre eles.");
}
