/* Usuário digitar uma palavra de até 20 caracteres e depois um caractere.
Retorne o número de vezes que o caractere ocorre na palavra digitada */

#include <stdio.h>
#include <string.h>
char string[20], letra;
int i,l;

void main(void)
{
    printf("Digite uma palavra: ");
    gets(string);
    fflush(stdin);
    printf("\nFrase digitada: %s\n", string);

    printf("\nDigite uma letra: ");
    scanf("%c", &letra);
    printf("\nA letra digitada foi: %c\n", letra);

    for(i = 0; i <=strlen(string) - 1; i++)
    {
       if (letra == string[i])
       {
           l++;
       }
    }
    printf("\nA letra se repete na palavra informada %i vezes.\n", l);
}
