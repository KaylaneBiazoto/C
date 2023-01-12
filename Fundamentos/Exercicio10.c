/* Armazenar o nome, idade, altura (em m) e peso (em kg) para um total
de 30 alunos de uma academia, sendo que esses dados devem ser armazenados em um vetor de
registros. Ao final, o programa deverá informar.
1. O número de alunos com idade superior à idade do último aluno cadastrado (o trigésimo
aluno).
2. O percentual de alunos cuja altura é superior a 1,90 m. */

#include <stdio.h>
#define N_alunos 30
int i, altura, idade;
float percentual;

struct academia
{
    char nome[50];
    int idade;
    float altura;
    float peso;
};

struct academia vetor_alunos[N_alunos];

void main(void)
{
    for(i = 0; i < N_alunos; i++)
    {
        printf("Digite seu nome: ");
        scanf("%s", &vetor_alunos[i].nome);

        printf("Digite sua idade: ");
        scanf("%d", &vetor_alunos[i].idade);

        printf("Digite sua altura em metros: ");
        scanf("%f", &vetor_alunos[i].altura);

        printf("Digite seu peso em quilogramas: ");
        scanf("%f", &vetor_alunos[i].peso);

        if(vetor_alunos[i].altura > 1.90)
            altura++;

        printf("\n");
    }

    for(int i = 0; i < N_alunos; i++)
    {
        if(vetor_alunos[i].idade > vetor_alunos[N_alunos-1].idade)
            idade++;
    }

    percentual = altura*100 / N_alunos;

    printf("O número de alunos com idade maior que a do último(trigésimo): %d\n", idade);
    printf("O percentual de alunos com altura maior que 1.90 é: %1.f%%\n", percentual);
}
