#define TAM 20

typedef struct agenda AGENDA;

struct agenda
{
    char nome_usuario[TAM];
    int num_telefone;

    char Rua[TAM];
    int Numero;

    AGENDA *proximo;
};

AGENDA *Cria_agenda ();
AGENDA *Inserir_usuario (AGENDA *agenda);
void Imprimir_agenda (AGENDA *agenda);
int Buscar_usuario (AGENDA *agenda);
AGENDA *Remover_usuario (AGENDA *agenda);
AGENDA *Apagar_agenda (AGENDA *agenda);
void Sair (int num);

