/* Ao final, o algoritmo deverá informar em quantos dias ocorreu uma
temperatura maior do que a do último dia do período. */

#include <stdio.h>
float temperatura[12];
int i = 0, maior = 0;

void main(void)
{
    printf("Forneça o valor para 12 temperaturas diárias.\n");
    for(i = 0; i < 12; i++)
    {
        printf("\nTemperatura %d: ", i+1);
        scanf("%f", &temperatura[i]);
    }

    for(i = 0; i < 12; i++)
    {
        if (temperatura[i] > temperatura[11])
            maior++;
    }

    printf("\nOcorreu uma temperatura maior que a do última dia %d vezes.", maior);
}
