#include "Votacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILHO_ESQ 0
#define FILHO_DIR 1

ARVORE_BINARIA *CriarArvore ()
{
    ARVORE_BINARIA *arvore = (ARVORE_BINARIA*) malloc (sizeof(ARVORE_BINARIA));

    if (arvore != NULL)
    {
       arvore->raiz = NULL;
    }

    return arvore;
};

NO *CriarRaiz (ARVORE_BINARIA *arvore, int titulo, char *nome)
{
    arvore->raiz = (NO*) malloc (sizeof(NO));

    if(arvore->raiz != NULL)
    {
       arvore->raiz->filho_esq = NULL;
       arvore->raiz->filho_dir = NULL;
       arvore->raiz->titulo_eleitor = titulo;
       strcpy((arvore->raiz->voto), nome);
    }

    return arvore->raiz;
};

NO *InserirFilho (int filho, NO *no, int titulo, char *novo_nome)
{
    NO *novo = (NO *) malloc(sizeof (NO));

    if (novo != NULL)
    {
        novo->filho_dir = NULL;
        novo->filho_esq = NULL;
        novo->titulo_eleitor = titulo;
        strcpy((novo->voto), novo_nome);

        if (filho == FILHO_ESQ)
            no->filho_esq = novo;
        else
            no->filho_dir = novo;
    }

    return novo;
};

int Inserir_Aux (NO *raiz, int novo_titulo, char *novo_nome)
{
   if (raiz->titulo_eleitor > novo_titulo)
   {
        if (raiz->filho_esq != NULL)
            return Inserir_Aux (raiz->filho_esq, novo_titulo, novo_nome);
        else
            return (InserirFilho (FILHO_ESQ, raiz, novo_titulo, novo_nome) != NULL);
   }
   else if (raiz->titulo_eleitor < novo_titulo)
   {
        if (raiz->filho_dir != NULL)
            return Inserir_Aux (raiz->filho_dir, novo_titulo, novo_nome);
        else
            return (InserirFilho (FILHO_DIR, raiz, novo_titulo, novo_nome) != NULL);
   } else
        return 0;
};

int Inserir (ARVORE_BINARIA *arvore, int titulo, char *nome)
{
    int i = 1;

    if (arvore->raiz == NULL){
        printf ("\n   Não há registros de Cadastro dos Títulos de Eleitores. Por favor, crie um!");
        return (CriarRaiz (arvore, titulo, nome) != NULL);
    } else
        return Inserir_Aux (arvore->raiz, titulo, nome);
};

void EmOrdem_Aux (NO *raiz)
{
    if(raiz != NULL)
    {
       EmOrdem_Aux (raiz->filho_esq);
       printf("\n                    %d", raiz->titulo_eleitor);
       EmOrdem_Aux (raiz->filho_dir);
    }

};

void EmOrdem (ARVORE_BINARIA *arvore)
{
    EmOrdem_Aux (arvore->raiz);
};

int Busca_Aux (NO *raiz, int titulo_chave)
{
    if (raiz == NULL)
        return -1;
    else if (raiz->titulo_eleitor > titulo_chave)
        return Busca_Aux (raiz->filho_esq, titulo_chave);
    else if (raiz->titulo_eleitor < titulo_chave)
        return Busca_Aux (raiz->filho_dir, titulo_chave);
    else
        return raiz->titulo_eleitor;

    NO *pnovo = (NO*) malloc(sizeof(NO));

    if (pnovo != NULL) {
        pnovo->filho_dir = NULL;
        pnovo->filho_esq = NULL;
        pnovo->titulo_eleitor = titulo_chave;
    }

    return pnovo->titulo_eleitor;
};


int Busca (ARVORE_BINARIA *arvore, int titulo_chave)
{
    return Busca_Aux (arvore->raiz, titulo_chave);
};

NO* Remover_Aux (NO *raiz, int titulo_chave)
{
    if(raiz == NULL) {
        printf("\n   Título não encontrado!");
        return NULL;
    } else {
         if(raiz->titulo_eleitor == titulo_chave) {
            if(raiz->filho_esq == NULL && raiz->filho_dir == NULL) {        // REMOVE NÓS FOLHAS
                free(raiz);
                return NULL;
            } else {
                if(raiz->filho_esq == NULL || raiz->filho_dir == NULL) {   // REMOVER NÓS COM APENAS 1 FILHO
                    NO *aux;
                    if(raiz->filho_esq != NULL)
                        aux = raiz->filho_esq;
                    else
                        aux = raiz->filho_dir;
                    free(raiz);
                    return aux;
                } else {
                     NO *aux = raiz->filho_esq;
                     while(aux->filho_dir != NULL)
                        aux = aux->filho_dir;
                     raiz->titulo_eleitor = aux->titulo_eleitor;
                     aux->titulo_eleitor = titulo_chave;
                     raiz->filho_esq = Remover_Aux (raiz->filho_esq, titulo_chave);
                     return raiz;
                 }
             }
         } else {
              if(titulo_chave < raiz->titulo_eleitor)
                  raiz->filho_esq = Remover_Aux(raiz->filho_esq, titulo_chave);
              else
                  raiz->filho_dir = Remover_Aux(raiz->filho_dir, titulo_chave);
              return raiz;
           }
    }
};

NO *Remover (ARVORE_BINARIA *arvore, int titulo_chave)
{
    return Remover_Aux (arvore->raiz, titulo_chave);
};

int MaiorTitulo (NO *raiz)
{
    if(raiz == NULL) {
        printf("\n   A árvore está vazia!");
        return -1;
    }
    else if (raiz->filho_dir != NULL)
        return MaiorTitulo(raiz->filho_dir);
    else
        return raiz->titulo_eleitor;
};

int MenorTitulo (NO *raiz)
{
    if(raiz == NULL) {
        printf("\n    A árvore está vazia!");
        return -1;
    }
    else if (raiz->filho_esq != NULL)
        return MenorTitulo(raiz->filho_esq);
    else
        return raiz->titulo_eleitor;
};

void DeletarArvore_Aux (NO *raiz)
{
       if (raiz->filho_esq) {
          DeletarArvore_Aux (raiz->filho_esq);
          free (raiz->filho_esq);
       }

       if (raiz->filho_dir){
          DeletarArvore_Aux (raiz->filho_dir);
          free (raiz->filho_dir);
       }
};

void DeletarArvore (ARVORE_BINARIA *arvore)
{
     if (arvore->raiz->filho_dir != NULL && arvore->raiz->filho_esq != NULL) {
          DeletarArvore_Aux(arvore->raiz);
          free(arvore->raiz);
     }

     arvore->raiz = NULL;
};


CANDIDATO *Cria_Registro_Candidatos ()
{
    return NULL;
};

CANDIDATO *Inserir_Candidato (CANDIDATO *candidato, int titulo_eleitor, char nome[TAM])
{
    CANDIDATO *aux, *novo;

    if(candidato == NULL)
    {
        candidato = Cria_Registro_Candidatos();
        candidato = (CANDIDATO*) malloc (sizeof(CANDIDATO));
        candidato->titulo = titulo_eleitor;
        strcpy(candidato->nome, nome);
        candidato->num_votos = 1;
        candidato->prox = NULL;
    } else {
        aux = candidato;
        while(aux->prox != NULL)
            aux = aux->prox;     // Ao final do while, noatual aponta para o ultimo no
        novo = (CANDIDATO *) malloc(sizeof(CANDIDATO));// Aloca memoria para o novo no
        novo->titulo = titulo_eleitor;
        strcpy(novo->nome, nome);
        novo->num_votos = 1;
        novo->prox = NULL;
        aux->prox = novo;
      }

    return candidato;
};

CANDIDATO *Remover_Candidato (CANDIDATO *candidato, int titulo_eleitor)
{
    CANDIDATO *aux, *aux1;

    if (candidato == NULL) {
        printf("\n     Vazia.");
        return NULL;
    }

    if ((candidato->titulo == titulo_eleitor) && candidato->prox == NULL) {             // REMOÇÃO DE UM ÚNICO USUÁRIO DA candidato
        free(candidato);
        candidato = NULL;
    }
    else if ((titulo_eleitor == candidato->titulo) && candidato->prox != NULL) {       // REMOÇÃO DO USUÁRIO NO INÍCIO DA candidato
        aux = candidato;
        candidato = candidato->prox;
        free(aux);
    }
    else if ((titulo_eleitor == candidato->titulo) && candidato->prox == NULL)
    {
        aux = candidato;

        while(aux != NULL && titulo_eleitor != aux->titulo)
        {
            aux1 = aux;
            aux = aux->prox;
        }

        if(aux == NULL)                                                               // REMOÇÃO DO USUÁRIO NO FINAL DA candidato
        {
            aux1->prox = NULL;
            free(aux);
        } else {                                                                      // REMOÇÃO DO USUÁRIO NO MEIO DA candidato
            aux1->prox = aux->prox;
            free(aux);
            aux1 = NULL;
          }
    } else
        printf ("\n   O usuário não foi encontrado.");

    return candidato;
};

void Exibir (CANDIDATO *candidato)
{
    CANDIDATO *aux = candidato;

    if(candidato == NULL)
        printf("\n   Vazio.\n");
    else {
        while (aux != NULL) {
            printf("\n          Nome: %s", aux->nome);
            printf("\n          Título: %d ", aux->titulo);
            printf("\n          Número de Votos: %d", aux->num_votos);
            printf("\n");
            aux = aux->prox;
        }
    }
};

void Adicionar_Voto (CANDIDATO *candidato, int titulo_eleitor)
{
    CANDIDATO* aux = candidato;

    while((aux->prox != NULL) && aux->titulo != titulo_eleitor)
        aux = aux->prox;

    if (aux->titulo == titulo_eleitor)
        aux->num_votos++;
};

int Apagar_Voto (CANDIDATO *candidato, int titulo_eleitor)
{
    CANDIDATO* aux = candidato;

    while((aux->prox != NULL) && aux->titulo != titulo_eleitor)
        aux = aux->prox;

    if (aux->titulo == titulo_eleitor) {
        aux->num_votos--;
        return aux->num_votos;
    }
};

CANDIDATO *Apagar (CANDIDATO *candidato)
{
    CANDIDATO *aux = candidato;

    while(aux != NULL) {
        candidato = candidato->prox;
        free(aux);
        aux = candidato;
    }

    if(aux == NULL) {
        return NULL;
    }

    return candidato;
};

int Busca2 (CANDIDATO* candidato, int titulo_eleitor)
{
    CANDIDATO* aux = candidato;

    if (candidato == NULL) {
        return 0;
    } else {
        while((aux->prox != NULL) && aux->titulo != titulo_eleitor)
            aux = aux->prox;

        if (aux->titulo == titulo_eleitor)
            return 1;
        else
            return 0;
      }
};
