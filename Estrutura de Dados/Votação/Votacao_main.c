#include "Votacao.c"
#include <stdio.h>
#include <string.h>

int main (void)
{
    ARVORE_BINARIA *ArvoreArmazenamento;
    CANDIDATO *Candidato = Cria_Registro_Candidatos();
    char opcao, voto[TAM], nome, op;
    int titulo, *tituloValido, votoint;

    printf("  ..................................................................\n");
    printf("\n   Você deseja iniciar uma nova votação? [s/ n]: ");
    scanf("%c", &opcao);
    fflush(stdin);

    if(opcao == 's' || opcao == 'S')
    {
        ArvoreArmazenamento = CriarArvore();

        printf("\n     Digite o primeiro título de eleitor: ");
        scanf("%d", &titulo);

        ArvoreArmazenamento->raiz = CriarRaiz(ArvoreArmazenamento, titulo, voto);
    } else
     {
        printf("\n     A votação não será iniciada!\n");
        exit(0);
     }

    printf("\n   Você deseja continuar com a votação? [s/ n]: ");
    fflush(stdin);
    scanf("%c", &opcao);

    if (opcao == 's' || opcao == 'S')
    {
        do{
            printf("\n     Digite o título do novo eleitor: ");
            scanf("%d", &titulo);

            Inserir (ArvoreArmazenamento, titulo, voto);

            fflush(stdin);
            printf("\n   Deseja continuar? [s/ n]: ");
            scanf("%c", &opcao);
        } while (opcao != 'n');
    }

    fflush(stdin);
    printf("\n   Há alguém que deseja retirar seu título? [s/ n]: ");
    scanf("%c", &opcao);

    if(opcao == 's' || opcao == 'S')
    {
        do{
            printf("\n       Informe o seu título de eleitor: ");
            scanf("%d", &titulo);
            fflush(stdin);
            if (Busca (ArvoreArmazenamento, titulo) == titulo)
            {
               ArvoreArmazenamento->raiz = Remover (ArvoreArmazenamento,titulo);
               printf("\n       Seu título foi retirado com sucesso!\n");
            } else
                printf("\n   O título fornecido não participou. Por gentileza, insira um novo título.\n");

            printf("\n   Deseja continuar? [s/ n]: ");
            fflush(stdin);
            scanf("%c", &opcao);

        } while (opcao != 'n');
    }


    printf("\n             . . . . . . . . . .");
    printf("\n        Títulos de eleitores válidos:\n");

    EmOrdem (ArvoreArmazenamento);
    printf("\n             . . . . . . . . . .\n");


    ARVORE_BINARIA *ArvoreVotacao = CriarArvore();

    printf("\n   Escolha um dos eleitores válidos para votar:\n");

    do{
        printf("\n      Forneça o seu título: ");
        scanf("%d", &titulo);

        if(Busca (ArvoreArmazenamento, titulo) == titulo)        // PRIMEIRA BUSCA PARA VER SE O TÍTULO É VÁLIDO (SE ESTÁ NA PRIMEIRA ÁRVORE)
        {
            if(Busca (ArvoreVotacao, titulo) == -1)              // SEGUNDA BUSCA PARA VER SE O ELEITOR JÁ NÃO VOTOU ANTES
            {
                printf("\n      Digite as informações do candidato para qual você dedicará seu voto:\n");

                    do{
                        printf("\n        Título do candidato: ");
                        scanf("%d", &votoint);

                        if(votoint == titulo)
                            printf("\n     Você não pode votar em si mesmo(a). Por gentileza, insira um título diferente.\n");

                        if(Busca (ArvoreArmazenamento, votoint) != votoint)
                            printf("\n     O título para o qual você está votando não é válido. Por gentileza, insira um título diferente:\n");
                    } while (votoint == titulo || Busca (ArvoreArmazenamento, votoint) != votoint);

                if(ArvoreVotacao->raiz == NULL)
                {
                    printf("\n        Nome do candidato: ");
                    fflush(stdin);
                    gets(voto);

                    Candidato = Inserir_Candidato(Candidato, votoint, voto);

                    ArvoreVotacao->raiz = CriarRaiz(ArvoreVotacao, titulo, voto);

                } else if(ArvoreVotacao->raiz != NULL)
                  {
                    printf("\n        Nome do candidato: ");
                    fflush(stdin);
                    gets(voto);

                    if(Busca2(Candidato, votoint) == 1){
                       Adicionar_Voto(Candidato, votoint);
                    }
                    else
                       Candidato = Inserir_Candidato (Candidato, votoint, voto);

                       Inserir (ArvoreVotacao, titulo, voto);
                  }

            } else
                printf("\n      Erro! Um mesmo título não pode votar duas vezes! Tente novamente.\n");
        } else
             printf("\n      Erro! O título inserido não é válido! Por gentileza, insira um título válido.\n");

        printf("\n   Deseja continuar? [s/ n]: ");
        fflush(stdin);
        scanf("%c", &opcao);

    } while (opcao != 'n');

    printf("\n             . . . . . . . .");
    printf("\n          Eleitores que votaram:\n");
    EmOrdem(ArvoreVotacao);
    printf("\n             . . . . . . . .\n");

    fflush(stdin);
    printf("\n   Há alguém que deseja retirar seu voto? [s/ n]: ");
    scanf("%c", &opcao);

    if(opcao == 's' || opcao == 'S')
    {
        do{
            printf("\n       Informe o seu título de eleitor: ");
            scanf("%d", &titulo);
            fflush(stdin);
            if (Busca (ArvoreVotacao, titulo) == titulo)
            {
                printf("\n       Informe o título do candidato que você votou: ");
                scanf("%d", &votoint);

                printf("\n   Deseja retirar seu voto? [s/ n]: ");
                fflush (stdin);
                scanf("%c", &op);
            } else
                printf("\n   O título fornecido não participou em nenhuma votação. Por gentileza, insira um novo título.\n");

            if (op == 's' || op == 'S')
            {
                if(Busca (ArvoreVotacao, titulo) == titulo && Busca2 (Candidato, votoint) == 1)
                {
                    ArvoreVotacao->raiz = Remover (ArvoreVotacao,titulo);
                    Apagar_Voto(Candidato, votoint);
                    printf("\n       Seu voto foi retirado com sucesso!\n");
                } else
                    printf("\n   Algo deu errado. Por gentileza, tente novamente.\n");
            }

            printf("\n   Deseja continuar? [s/ n]: ");
            fflush(stdin);
            scanf("%c", &opcao);

        } while (opcao != 'n');
    }

    printf("\n\n   A votação será finalizada.\n\n   Você concluiu todas as suas etapas.\n\n\n   Veja abaixo os dados da votação:\n");

    printf ("\n        ---------------------------------\n");
    printf ("\n          Resultado parcial da eleição:\n");
    Exibir (Candidato);

    if( ArvoreVotacao->raiz == NULL)
        printf("\n          Nenhum título votou.\n");
    else
    {
        printf("             . . . . . . . .");
        printf ("\n          Títulos que votaram:\n");
        EmOrdem (ArvoreVotacao);
        printf("\n             . . . . . . . .\n");

        printf ("\n          Maior título que já votou: %d", MaiorTitulo (ArvoreVotacao->raiz));
        printf ("\n          Menor título que já votou: %d", MenorTitulo (ArvoreVotacao->raiz));
        printf("\n");
    }

    printf ("\n        ---------------------------------\n");

    printf("\n     Pressione qualquer tecla para que as árvores sejam deletadas.\n");
    fflush(stdin);
    getchar();
    printf("\n     As árvores de votação serão deletadas.\n\n     Obrigada pela sua participação! :)\n");

    Candidato = Apagar (Candidato);

    if(ArvoreVotacao->raiz != NULL)
        DeletarArvore (ArvoreVotacao);

    if(ArvoreArmazenamento->raiz != NULL)
        DeletarArvore (ArvoreArmazenamento);

    if (ArvoreArmazenamento->raiz == NULL && ArvoreVotacao->raiz == NULL)
        printf("\n     Árvores deletadas com sucesso!\n\n");

    printf("\n  ..................................................................\n");
};
