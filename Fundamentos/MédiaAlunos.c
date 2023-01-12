/* Informar quatro notas bimestrais de 30 aluno, sendo que esses dados devem ser armazenados em um agregado homogêneo
bidimensional. Deverá informar a média anual final de cada um dos trinta alunos,o número de alunos cuja nota do terceiro bimestre
ficou entre 3,0 e 6,0, e a quantidade de aluno cuja média foi maior do que a do último aluno de todos (o trigésimo aluno). */

#include <stdio.h>
#define N_alunos 30
#define N_notas 4
float notas[N_alunos][N_notas], soma[N_alunos], media[N_alunos];
int i, j, aluno = 0, maior = 0;

void main (void)
{
    printf("Forneça 4 notas bimestrais para 30 alunos.\n");

    for(i = 0; i < N_alunos; i++)
    {
        for(j = 0; j < N_notas; j++)
        {
            printf("Nota %d do aluno %d: ", j + 1, i + 1);
            scanf("%f", &notas[i][j]); //Pega as quatro notas para os 30 alunos

            soma[i] = soma[i] + notas[i][j]; //Faz a soma das notas daquele aluno
        }

        media[i] = soma[i] / N_notas; //Faz a media daquele aluno

        printf("\n");
    }

    for(i = 0; i < N_alunos; i++)
    {
        if(notas[i][2] > 3.0 && notas[i][2] < 6.0)
            aluno++; //Conta quantos alunos tiveram tal nota no 3 bimestre

        if(media[i] > media[N_alunos - 1])
            maior++; //Conta quantos alunos tiveram a média maior que a do último

        printf("\nMédia do aluno [%d]: ", i + 1);
        printf("%.2f", media[i]);
    }

    printf("\n\nQuantidade de alunos com a nota do terceiro bimestre entre 3.0 e 6.0: %d\n", aluno);

    printf("\nMédia maior que a do último aluno: %d\n", maior);
}
