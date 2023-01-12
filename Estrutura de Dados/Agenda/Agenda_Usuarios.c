#include "Agenda.c"
#include <stdio.h>

int main (void){

    AGENDA *agenda;
    char continuar, nome[TAM];
    int opcao;

    do{
         printf("\n   --------------------------------------------------      ");
         printf("\n                         MENU\n");
         printf("    1) Criar agenda");
         printf("            5) Remover um usuário\n");
         printf("    2) Inserir usuário");
         printf("         6) Apagar a agenda\n");
         printf("    3) Imprimir a agenda");
         printf("       7) Sair da agenda\n");
         printf("    4) Buscar um usuário\n");
         printf("   --------------------------------------------------      \n");

         printf("\n  Escolha uma das opções do menu: ");
         scanf("%d", &opcao);

         switch(opcao){
         case 1:
            agenda = Cria_agenda ();
            break;
         case 2:
            agenda = Inserir_usuario(agenda);
            break;

         case 3:
            Imprimir_agenda(agenda);
            break;

         case 4:
            Buscar_usuario(agenda);
            break;

         case 5:
            agenda = Remover_usuario(agenda);
            break;

         case 6:
            agenda = Apagar_agenda(agenda);
            break;

         case 7:
            Sair(opcao);
            break;


         default:
            printf("\n  Opção inválida!\n");
         };

         printf("\n____________\n");
         printf("\n  Você deseja continuar com o menu? [s/n]:  ");
         fflush (stdin);
         scanf("%c", &continuar);

       } while (continuar != 'n');
};
