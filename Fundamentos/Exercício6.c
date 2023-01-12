/* Armazene as temperaturas diárias em um período de 12 dias.
Deverá informar em quantos dias a temperatura foi negativa e qual foi a
temperatura média no período. */

#include <stdio.h>
float temperatura[12];
float soma = 0, media = 0;
int i, negativa = 0;

void main(void)
{
    printf("Forneça o valor para 12 temperaturas diárias.\n");
    for(i = 0; i < 12; i++)
    {
        printf("\nTemperatura %d: ", i+1);
        scanf("%f", &temperatura[i]);

        soma = soma + temperatura[i];

        if(temperatura[i] < 0)
        {
            negativa++;
        }
    }

    media = soma / 12;

    printf("\nA quantidade de temperaturas negativas foi: %d", negativa);
    printf("\nA média das temperaturas é: %.2f", media);
}
