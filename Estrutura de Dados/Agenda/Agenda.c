#include "Agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AGENDA *Cria_agenda ()
{
   printf("\n     Sua agenda foi criada com sucesso!");
   return NULL;
};

AGENDA *Inserir_usuario (AGENDA *agenda)
{
    AGENDA *novo_usuario, *aux, *aux1;

    if (agenda == NULL)                            // INSERÇÃO DE UM ÚNICO USUÁRIO NA AGENDA
    {
       agenda = (AGENDA*) malloc(sizeof(AGENDA));

       printf ("\n  Informe os seguintes dados para inserir o primeiro usuário:\n");

       printf ("\n     Nome: ");
       fflush (stdin);
       scanf("%s", &agenda->nome_usuario);
       printf ("     Número de telefone:  ");
       scanf ("%d", &agenda->num_telefone);
       printf ("     Rua: ");
       fflush (stdin);
       gets (agenda->Rua);
       printf ("     Número: ");
       scanf ("%d", &agenda->Numero);

       printf ("\n     O primeiro usuário foi inserido!");

       agenda->proximo = NULL;

    } else if (agenda != NULL)
      {
         novo_usuario = (AGENDA*) malloc(sizeof(AGENDA));

         printf ("\n  Informe os seguintes dados para inserir o novo usuário:");

         fflush (stdin);
         printf ("\n\n     Nome: ");
         gets (novo_usuario->nome_usuario);
         printf ("     Número de telefone: ");
         scanf ("%d", &novo_usuario->num_telefone);
         printf ("     Rua: ");
         fflush (stdin);
         gets (novo_usuario->Rua);
         printf ("     Número: ");
         scanf ("%d", &novo_usuario->Numero);

         printf ("\n     Um novo usuário foi inserido!");

         novo_usuario->proximo = NULL;

      if (novo_usuario->nome_usuario[0] < agenda->nome_usuario[0])      // INSERÇÃO DE UM USUÁRIO NO INÍCIO DA AGENDA
      {
          novo_usuario->proximo = agenda;
          agenda = novo_usuario;
          novo_usuario = NULL;
      }
      else
      {
          aux = agenda;

          while ((aux != NULL) && (novo_usuario->nome_usuario[0] > aux->nome_usuario[0]))
          {
              aux1 = aux;
              aux = aux->proximo;
          }

         if (aux == NULL)           // INSERÇÃO DE UM USUÁRIO NO FINAL DA AGENDA
         {
            aux1->proximo = novo_usuario;

            novo_usuario = NULL;
            aux1 = NULL;
         }
         else                      // INSERÇÃO DE UM USUÁRIO NO MEIO DA AGENDA
         {
            aux1->proximo = novo_usuario;
            novo_usuario->proximo = aux;

            novo_usuario = NULL;
            aux = NULL;
            aux1 = NULL;
         }
       }
    }
    return agenda;
};

void Imprimir_agenda (AGENDA *agenda)
{
    AGENDA* aux;

    aux = agenda;

    if (agenda == NULL){
        printf("\n  A agenda está vazia!\n\n  Escolha a opção '2)' para fazer a inserção de usuário(os) na agenda e assim poder imprimir ela.");
    } else
      {
        printf("\n     Segue abaixo os usuários de sua agenda:\n");

        while(aux != NULL)
        {
          printf("\n        ----");
          printf("\n      Nome: %s   Número de telefone: %d\n", aux->nome_usuario, aux->num_telefone);
          printf("      Rua: %s    Número: %d", aux->Rua, aux->Numero);

          aux = aux->proximo;
        }
      }
};

int Buscar_usuario(AGENDA *agenda)
{
    char nome[TAM];

    AGENDA* aux = agenda;

    if (agenda == NULL)
    {
        printf("\n  A agenda está vazia!\n\n  Escolha a opção '2)' para fazer a inserção de usuário(os) na agenda e assim poder buscar por um deles.");
        return 0;
    } else
      {
        printf("\n  Informe o nome do usuário que você deseja encontrar na agenda: ");
        fflush (stdin);
        gets(nome);

        while((aux->proximo != NULL) && strcmp(nome, aux->nome_usuario) != 0)
        {
            aux = aux->proximo;
        }

        if (strcmp(nome, aux->nome_usuario) == 0)
        {
            printf("\n     Segue os dados do usuário buscado:\n");
            printf("\n       Nome: %s   Número de telefone: %d\n", aux->nome_usuario, aux->num_telefone);
            printf("       Rua: %s    Número: %d", aux->Rua, aux->Numero);
            return 1;
        } else
          {
            printf ("\n     O usuário não foi encontrado.");
            return 0;
          }

      }
};

AGENDA *Remover_usuario (AGENDA *agenda)
{
    char nome[TAM];
    AGENDA *aux, *aux1;

    while (agenda == NULL){
        printf("\n  A agenda está vazia!\n\n  Escolha a opção '2)' para fazer a inserção de usuário(os) na agenda e assim poder remover um deles.");
        return 0;
    }

    printf("\n  Informe o nome do usuário que você deseja remover da agenda: ");
    fflush (stdin);
    gets(nome);

    if(strcmp(nome, agenda->nome_usuario) == 0 && agenda->proximo == NULL)              // REMOÇÃO DE UM ÚNICO USUÁRIO NA AGENDA
    {
        free(agenda);
        agenda = NULL;
        printf("\n     O único usuário foi removido com sucesso!\n");
    } else if (strcmp(nome, agenda->nome_usuario) == 0 && agenda->proximo != NULL)      // REMOÇÃO DO USUÁRIO NO INÍCIO DA AGENDA
      {
          aux = agenda;
          agenda = agenda->proximo;
          free(aux);
          printf("\n     O primeiro usuário foi removido com sucesso!\n");
      } else if (strcmp(nome, agenda->nome_usuario) == 0 && agenda->proximo == NULL)
        {
            aux = agenda;

            while(aux != NULL && strcmp(nome, aux->nome_usuario) != 0 )
            {
                aux1 = aux;
                aux = aux->proximo;
            }

            if(aux == NULL)                                                            // REMOÇÃO DO USUÁRIO NO FINAL DA AGENDA
            {
               aux1->proximo = NULL;
               free(aux);
               printf("\n     O último usuário foi removido com sucesso!\n");
            } else                                                                      // REMOÇÃO DO USUÁRIO NO MEIO DA AGENDA
              {
                 aux1->proximo = aux->proximo;
                 free(aux);
                 aux1 = NULL;
                 printf("\n     O usuário do meio foi removido com sucesso!\n");
              }
        } else
         {
            printf ("\n     O usuário não foi encontrado.");
         }


    return agenda;
};

AGENDA *Apagar_agenda(AGENDA *agenda)
{
    AGENDA *aux = agenda;
    char op;

    printf ("\n  Você escolheu a opção 'Apagar a agenda'. Deseja continuar? [s/ n]: ");
    fflush (stdin);
    scanf("%c", &op);

    if (op == 's' || op == 'S')
    {
        while(aux != NULL)
        {
            agenda = agenda->proximo;
            free(aux);
            aux = agenda;
        }

        if(aux == NULL){
            printf("\n     A agenda foi apagada!");
            return NULL;
        }
    } else
        return agenda;
};

void Sair (int num)
{
    char op;

    printf ("\n  Você escolheu a opção 'Sair da agenda'. Deseja continuar? [s/ n]: ");
    fflush (stdin);
    scanf("%c", &op);

    if(num == 7 && ((op == 's') || (op == 'S')))
    {
        printf("\n     O programa irá se encerrar. Obrigada por tê-lo usado! :)\n\n\n");
        getchar();
        exit(0);
    } else
        printf("\n  Algo deu errado. Por favor, tente novamente!");
};
