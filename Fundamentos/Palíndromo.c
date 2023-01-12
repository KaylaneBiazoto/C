/* Usuário digitar uma string de até 20 caracteres e, informe
se o conteúdo é um palíndromo ou não. */

#include <stdio.h>
#include <string.h>
char string[20];
int i = 0, diferentes = 0, tamanho;

void main(void)
{
    printf("Digite uma palavra: ");
    gets(string);
    printf("\nFrase digitada: %s \n\n", string);

    tamanho = strlen(string);
    tamanho--;

    while(tamanho >= i)
    {
        if(string[i] != string[tamanho])
        {
            diferentes++;
        }
        i++;
        tamanho--;
    }

    if(diferentes == 0)
        printf("É palíndroma!\n");
    else
        printf("Não é palíndroma!\n");
}
