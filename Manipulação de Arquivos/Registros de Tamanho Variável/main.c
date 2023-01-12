#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_REG 150
#define TAM_STR 30

struct {
  int lista;
}
cabecalho;

int importar(char * argv);
void copiar_conteudo(FILE * arq1, FILE * arq2);

int executar_operacoes(char * argv);
int busca_registro(char * chave, FILE * arq);
int remover_registro(char * chave, FILE * arq);
int inserir_registro(char * novo_buffer, FILE * arq);

int imprimir_led();

int main(int argc, char * argv[]) {

  if (argc == 3 && strcmp(argv[1], "-i") == 0) {

    printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
    importar(argv[2]);

  } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {

    printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
    executar_operacoes(argv[2]);

  } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {

    printf("Modo de impressao da LED ativado ...\n");
    imprimir_led();

  } else {

    fprintf(stderr, "Argumentos incorretos!\n");
    fprintf(stderr, "Modo de uso:\n");
    fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
    fprintf(stderr, "$ %s -p\n", argv[0]);
    exit(EXIT_FAILURE);

  }

  return 0;
}

int importar(char * argv) {
  FILE * arq1, * arq2;

  if ((arq1 = fopen(argv, "r")) == NULL || (arq2 = fopen("dados.dat", "w+b")) == NULL) {
    printf("Erro ao abrir o(s) arquivo(s).\n");
    exit(1);
  } else {
    copiar_conteudo(arq1, arq2);
    printf("\nImportação concluída com sucesso!\n");
  }

  fclose(arq1);
  fclose(arq2);
  return 0;
}

void copiar_conteudo(FILE * arq1, FILE * arq2) {
  char buffer[TAM_REG];
  short byte_size, i = 1;
  cabecalho.lista = -1;

  fwrite( & cabecalho, sizeof(cabecalho), 1, arq2);
  while (fgets(buffer, TAM_REG, arq1) != NULL) {
    byte_size = strlen(buffer) - 1;

    if (i == 100) {
      byte_size = strlen(buffer);
    }

    fwrite( & byte_size, sizeof(byte_size), 1, arq2);
    fwrite( & buffer, byte_size, 1, arq2);
    i++;
  }
}

int executar_operacoes(char * argv) {
  FILE * arq, * arq1;
  char buffer[TAM_REG], novo_buffer[TAM_REG], opcao, * chave, * campo;

  if ((arq = fopen(argv, "r")) == NULL || (arq1 = fopen("dados.dat", "r+b")) == NULL) {
    printf("Erro ao abrir o(s) arquivo(s).\n");
    exit(1);
  }

  while (fgets(buffer, TAM_REG, arq)) {
    opcao = buffer[0];

    switch (opcao) {

    case 'i':

      fseek(arq, -(strlen(buffer) - 2), SEEK_CUR);
      fgets(novo_buffer, TAM_REG, arq);
      novo_buffer[(strlen(novo_buffer) - 1)] = '\0';

      campo = strtok(buffer, "|");
      campo = strtok(campo, "i ");
      printf("\nInserção do registro de chave \"%s\" (%ld bytes)\n", campo, strlen(novo_buffer));

      inserir_registro(novo_buffer, arq1);

      break;

    case 'r':

      chave = strtok(buffer, "r ");
      chave[strlen(chave) - 1] = '\0';
      printf("\nRemoção do registro de chave \"%s\"\n", chave);
      remover_registro(chave, arq1);

      break;

    case 'b':

      chave = strtok(buffer, "b ");
      chave[(strlen(chave) - 1)] = '\0';
      printf("\nBusca pelo registro de chave \"%s\"\n", chave);

      busca_registro(chave, arq1);

      break;

    default:
      break;

    }
  }

  fclose(arq);
  fclose(arq1);
  return 1;
}

int busca_registro(char * chave, FILE * arq) {
  char buffer[TAM_REG];
  char * campo;
  short byte_size, tam_buffer, counter = 0, size;

  rewind(arq);
  fseek(arq, sizeof(int), SEEK_SET);
  fread( & byte_size, sizeof(short), 1, arq);
  fgets(buffer, (byte_size + 1), arq);
  tam_buffer = strlen(buffer);
  while (!feof(arq)) {
    campo = strtok(buffer, "|");
    if (strcmp(campo, chave) == 0) {
      while (campo != NULL && counter != 6) {
        counter++;
        size = size + strlen(campo) + 1;
        printf("%s|", campo);
        campo = strtok(NULL, "|");
      }
      printf(" (%d bytes) \n", size);
      return 1;
    }

    fread( & byte_size, sizeof(short), 1, arq);
    fgets(buffer, (byte_size + 1), arq);
    tam_buffer = strlen(buffer);
    counter = 0;
    size = 0;
  }

  printf("O registro não foi encontrado.\n");
  return 0;
}

int remover_registro(char * chave, FILE * arq) {
  char buffer[TAM_REG], * campo;
  int offset = sizeof(int) + sizeof(short);
  short byte_size;

  rewind(arq);
  fread( & cabecalho, sizeof(cabecalho), 1, arq);

  fseek(arq, sizeof(int), SEEK_SET);
  fread( & byte_size, sizeof(short), 1, arq);
  fgets(buffer, (byte_size + 1), arq);

  while (!feof(arq)) {
    campo = strtok(buffer, "|");

    if (strcmp(campo, chave) == 0) {
      fseek(arq, offset, SEEK_SET);
      fputc('*', arq);
      fwrite( & cabecalho, sizeof(cabecalho), 1, arq);

      cabecalho.lista = offset - 2;
      rewind(arq);
      fwrite( & cabecalho, sizeof(cabecalho), 1, arq);
      printf("Registro removido! (%d bytes) \nLocal: offset = %d bytes (0x%x)\n", byte_size, cabecalho.lista, cabecalho.lista);

      return 1;
    }

    offset = offset + byte_size + sizeof(byte_size);
    fread( & byte_size, sizeof(short), 1, arq);
    fgets(buffer, (byte_size + 1), arq);
  }

  printf("Erro: registro nao encontrado!\n");
  return 0;
}

int inserir_registro(char * novo_buffer, FILE * arq) {
  int atual = -1, prox = -1, anterior = -1, extra_size = 2 + 1 + 4 + 2;
  short byte_size, novo_byte_size;
  // lista --> atual
  // aux1 --> prox
  // aux2 --> anterior

  fseek(arq, 0, SEEK_SET);
  fread( & atual, sizeof(int), 1, arq);

  novo_byte_size = strlen(novo_buffer);

  if (atual == -1) { // led vazia
    fseek(arq, 0, SEEK_END);
    fwrite( & novo_byte_size, sizeof(novo_byte_size), 1, arq);
    fputs(novo_buffer, arq);

    printf("Local: fim do arquivo\n");
    return 1;
  } else {
    // atual = lista;
    // fseek(arq, atual, SEEK_SET);
    // fseek(arq, 3, SEEK_CUR);
    // fread( & prox, sizeof(prox), 1, arq);

    while (atual != -1) {
      fseek(arq, atual, SEEK_SET);
      fread( & byte_size, sizeof(byte_size), 1, arq);
      fseek(arq, 1, SEEK_CUR);
      fread( & prox, sizeof(prox), 1, arq);
      
      if (byte_size > (novo_byte_size+extra_size)) {
        fseek(arq, atual, SEEK_SET);
        short espaco_livre = byte_size - novo_byte_size - sizeof(short);
        fwrite( & espaco_livre, sizeof(espaco_livre), 1, arq);
        fputc('*', arq);
        fwrite( & prox, sizeof(prox), 1, arq);
        fseek(arq, atual, SEEK_SET);
        fseek(arq, (espaco_livre + sizeof(short)), SEEK_CUR);
        fwrite( & novo_byte_size, sizeof(novo_byte_size), 1, arq);
        fputs(novo_buffer, arq);

        printf("Tamanho do espaço reutilizado: %d bytes\n", byte_size);
        printf("Local: offset = %d bytes (0x%x)\n", atual, atual);
        return 1;
        
      } else if (byte_size == novo_byte_size || byte_size > novo_byte_size) {

        if (anterior != -1) { // o espaco nao esta na cabeca
          fseek(arq, anterior+sizeof(byte_size)+1, SEEK_SET); //faz seek e ja pula o campo de tam e o *
          fwrite(&prox, sizeof(prox), 1, arq); // faz o anterior apontar para o prox
        } else { // o espaco esta na cabeca
          rewind(arq);
          fwrite( & prox, sizeof(prox), 1, arq);
        }
        fseek(arq, atual+sizeof(byte_size), SEEK_SET);
        fputs(novo_buffer, arq);
        if (byte_size > novo_byte_size) fputc('\0', arq); //caso tenha alguma sobrinha

        printf("Tamanho do espaço reutilizado: %d bytes\n", byte_size);
        printf("Local: offset = %d bytes (0x%x)\n", atual, atual);
        return 1;
      }
      anterior = atual;
      atual = prox;
    }

    if (atual == -1) { // nenhum espaco da led serviu
      fseek(arq, 0, SEEK_END);
      fwrite( & novo_byte_size, sizeof(novo_byte_size), 1, arq);
      fputs(novo_buffer, arq);

      printf("Local: fim do arquivo\n");
      return 1;
    }
  }

  return 0;
}

int imprimir_led() {
  FILE * arq;
  char buffer[TAM_REG];
  int aux;

  if ((arq = fopen("dados.dat", "r+b")) == NULL) {
    printf("Erro ao abrir o arquivo de dados.\n");
    exit(1);
  }

  fread( & cabecalho, sizeof(cabecalho), 1, arq);

  if (cabecalho.lista == -1) {
    printf("A lista está vazia.\n");
    return 1;
  } else {
    printf("[%d] ", cabecalho.lista);
    fseek(arq, (cabecalho.lista + 3), SEEK_SET);
    fread( & aux, sizeof(int), 1, arq);
    printf("[%d] ", aux);

    while (aux != -1) {
      fseek(arq, (aux + 3), SEEK_SET);
      fread( & aux, sizeof(aux), 1, arq);
      printf("[%d] ", aux);
    }
    printf("\n");
    return 1;
  }
  return 0;
}