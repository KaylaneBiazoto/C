/* Armazenar 10 nomes (com no máximo 30 caracteres), ao final, exiba na tela todos
os nomes de pessoas que começam com a letra c (minúscula ou maiúscula).*/

#include <stdio.h>
#include <string.h>
char vetor_string[10][30], c, C;
int i = 0;

void main (void)
{
    printf("Forneça 10 nomes.\n");

    for(i = 0; i < 10; i++)
    {
        printf("\nNome %d: ", i+1);
        gets(vetor_string[i]);
        fflush(stdin);
    }

    printf("\nOs nomes que iniciam com a letra c, são: \n\n");

    for (i = 0; i <= 9; i++)
   {
      if (vetor_string[i][0] == 'c' || vetor_string[i][0] == 'C')
      {
         printf("%s \n",vetor_string[i]);
      }

   }
}
