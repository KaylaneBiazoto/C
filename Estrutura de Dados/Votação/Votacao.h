#define TAM 30

typedef struct no NO;
typedef struct arvore_binaria ARVORE_BINARIA;
typedef struct candidato CANDIDATO;

struct no
{
    int titulo_eleitor;
    char voto [TAM];
    NO *filho_esq;
    NO *filho_dir;
};

struct arvore_binaria
{
    NO *raiz;
};

struct candidato
{
    CANDIDATO *prox;
    int titulo;
    char nome [TAM];
    int num_votos;
};

ARVORE_BINARIA *CriarArvore ();
NO *CriarRaiz (ARVORE_BINARIA *arvore, int titulo, char *nome);

NO *InserirFilho (int filho, NO *no, int titulo, char *novo_nome);
int Inserir_Aux (NO *raiz, int novo_titulo, char *novo_nome);
int Inserir (ARVORE_BINARIA *arvore, int titulo, char *nome);

int Busca_Aux (NO *raiz, int titulo_chave);
int Busca (ARVORE_BINARIA *arvore, int titulo_chave);

int MaiorTitulo (NO *raiz);
int MenorTitulo (NO *raiz);

void EmOrdem_Aux (NO *raiz);
void EmOrdem (ARVORE_BINARIA *arvore);

NO* Remover_Aux (NO *raiz, int titulo_chave);
NO *Remover (ARVORE_BINARIA *arvore, int titulo_chave);

void DeletarArvore_Aux(NO *raiz);
void DeletarArvore (ARVORE_BINARIA *arvore);

CANDIDATO *Cria_Registro_Candidatos ();

CANDIDATO *Inserir_Candidato (CANDIDATO *candidato, int titulo_eleitor, char nome[30]);
CANDIDATO *Remover_Candidato (CANDIDATO *candidato, int titulo_eleitor);

void Exibir(CANDIDATO *candidato);

void Adicionar_Voto (CANDIDATO *candidato, int titulo_eleitor);

int Apagar_Voto (CANDIDATO *candidato, int titulo_eleitor);
CANDIDATO *Apagar (CANDIDATO *candidato);

int Busca2 (CANDIDATO *candidato, int titulo_eleitor);
