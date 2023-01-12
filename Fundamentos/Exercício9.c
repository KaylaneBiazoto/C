//Elementos abaixo da diagonal principal tem o i > j
//Elementos acima da diagonal principal tem o i < j

#include <stdio.h>
#define N_linhas 10
#define N_colunas 10
int matriz[N_linhas][N_colunas];
int i, j, soma = 0;

void main (void)
{
    printf("Forneça valores para uma matriz 10x10.\n");

    for(i = 0; i < N_linhas; i++)
    {
        for(j = 0; j < N_colunas; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
        printf("\n");
    }

    printf("Matriz gerada:\n\n");

    for(i = 0; i < N_linhas; i++)
    {
        for(j = 0; j < N_colunas; j++)
        {
            printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nAbaixo da diagonal principal:\n\n");

    for(i = 0; i < N_linhas; i++)
    {
        for(j = 0; j < N_colunas; j++)
        {
            if(i > j)
            {
                printf(" %d ",matriz[i][j]);
                soma = soma + matriz[i][j];
            }
        }
    }
    printf("\n\nA soma entre todos os valores abaixo da diagonal princpal é: %d\n",soma);
}

