/* Faça um programa em C que exiba os valores inteiros entre m e n, sendo que m será um inteiro
maior que n, portanto o intervalo será decrescente. */

#include <stdio.h>
#include <locale.h>
int n, m;

void main (void)
{
    setlocale(LC_ALL, "Portuguese");
    printf("Forneça um valor para n: ");
    scanf("%d", &n);
    printf("Forneça um valor para m que seja MAIOR que n: ");
    scanf("%d", &m);

    while( m > n  + 1)
    {
        m = m - 1;
        printf("%d ", m);
    }
}
