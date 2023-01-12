#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TAM_MAX_BUCKET 5
#define SUCCESS 0
#define FAILURE 1

typedef struct {
    int prof;
    int cont;
    int chaves[TAM_MAX_BUCKET];
} BUCKET;

typedef struct {
    int bucket_ref;
} DIR_CELL;

typedef struct {
    DIR_CELL *cells;
    int dir_prof;
} DIRETORIO;

// Diretório global
DIRETORIO diretorio;

int importar();
void inicializacao();
void impressao_diretorio();
void impressao_bucket();
void finalizacao();

int make_address (int key, int profundidade);
int op_add(BUCKET *bucket, int key);
int op_find(int key, BUCKET *found_bucket);
void bk_add_key(BUCKET *bucket, int key);
int bk_split(BUCKET *bucket, short rrn);
void dir_double();
void find_new_range(BUCKET *old_bucket, int *new_start, int *new_end);
void dir_ins_bucket(int bucket_address, int start, int end);

int main(int argc, char * argv[]) {

  if (argc == 3 && strcmp(argv[1], "-i") == 0) {

    printf("Modo de importacao de chave ativado ... nome do arquivo = %s\n", argv[2]);
    importar();

  } else if (argc == 3 && strcmp(argv[1], "-pd") == 0) {

    printf("Impressao das informacoes do diretorio ... nome do arquivo = %s\n", argv[2]);
    impressao_diretorio();

  } else if (argc == 3 && strcmp(argv[1], "-pb") == 0) {

    printf("Impressao das informacoes dos buckets ... nome do arquivo = %s\n", argv[2]);
    impressao_bucket();
  } 
  
  else {

    fprintf(stderr, "Argumentos incorretos!\n");
    fprintf(stderr, "Modo de uso:\n");
    fprintf(stderr, "$ %s (-i|-pd|-pb) nome_arquivo\n", argv[0]);
    exit(EXIT_FAILURE);

  }

  return 0;
}

int importar() {

    inicializacao();
    finalizacao();
    return SUCCESS;

}

void inicializar_bucket (BUCKET *bucket) {

    int i = 0;
    bucket->prof = 0;
    bucket->cont = 0;
    while (i < TAM_MAX_BUCKET) {
        bucket->chaves[i] = -1;
        i++;
    }
}

void inicializar_diretorio (DIRETORIO *diretorio) {

    diretorio->dir_prof = 0;
    // Alocando espaço para a primeira célula vazia do diretório
    diretorio->cells = malloc (sizeof(DIR_CELL));
    
    diretorio->cells[0].bucket_ref = 0;
}

void inicializacao () {

    FILE *arq_dir, *arq_bucket, *arq_chaves;

    // Inicializando um diretorio e alocando espaço para sua célula
    inicializar_diretorio(&diretorio);

    // Abrindo/Criando o arquivo para o diretório e verificando se ele já têm informação
    if((arq_dir = fopen("dir.dat", "rb")) != NULL){

        int tamanho;
        fread(&diretorio.dir_prof, sizeof(diretorio.dir_prof), 1, arq_dir);
        tamanho = pow(2, diretorio.dir_prof);
        diretorio.cells = malloc (sizeof(DIR_CELL) * tamanho);

        for(int i = 0; i < tamanho; i++) {
            fread(&diretorio.cells[i].bucket_ref, sizeof(DIR_CELL), 1, arq_dir);
        }
        
    } else {
        
        // Inicializando um bucket vazio
        BUCKET bucket;
        inicializar_bucket(&bucket);

        // Colocando o bucket no arquivo
        arq_bucket = fopen("bucket.dat", "wb");
        fwrite(&bucket, 1, sizeof(bucket), arq_bucket);
        fclose(arq_bucket);

        // Transformando as chaves do chaves.txt em int
        arq_chaves = fopen("chaves-50.txt", "r");
        char chave_str[2];
        int chave_int, j = 1, i = 1;

        while (i <= 50) {
            if(j < 10) {
                fread(&chave_str, 1, 1, arq_chaves);
                chave_int = atoi(chave_str);
                op_add(&bucket, chave_int);
                fseek(arq_chaves, 1, SEEK_CUR);
                j++;
            } else {
                fread(&chave_str, 2, 1, arq_chaves);
                fseek(arq_chaves, 1, SEEK_CUR);
                chave_int = atoi(chave_str);
                op_add(&bucket, chave_int);
            }
            i++;
        }

        fclose(arq_chaves);
    }
}

int make_address (int key, int profundidade) {

    // Cria um endereço em forma de bits e o inverte para a chave

    int retVal  = 0,
    mask    = 1,
    hashVal = key,
    lowBit  = 0;

    int i;
    for(i = 1; i <= profundidade; i++) {
        retVal  = retVal << 1;
        lowBit  = hashVal & mask;
        retVal  = retVal | lowBit;
        hashVal = hashVal >> 1;
    }
    
    return retVal;

}

int op_add(BUCKET *bucket, int key) {

    BUCKET *found_bucket = malloc(sizeof(BUCKET));
    // inicializar_bucket(&found_bucket);

    // Procura pela chave. Se existir, não a adiciona, pois não pode haver duplicata.
    if (op_find(key, found_bucket) == SUCCESS){
        printf("A chave já está em um bucket. Por favor, insira uma chave diferente.\n");
        return FAILURE;
    } else
        bk_add_key(found_bucket, key);

    return SUCCESS;
}

int op_find(int key, BUCKET *found_bucket) {

    // Calcula o endereço da chave em bits
    int address = make_address(key, diretorio.dir_prof);

    // Obtém o bucket neste endereço
    short rrn_found_bucket = diretorio.cells[address].bucket_ref;

    // Procura para ver se a chave está dentro do bucket encontrado
    FILE *arq_bucket = fopen("bucket.dat", "rb");
    fseek(arq_bucket, sizeof(BUCKET) * rrn_found_bucket, SEEK_CUR);
    // Lendo found_bucket para a memória
    fread(&found_bucket->prof, sizeof(found_bucket->prof), 1, arq_bucket);
    fread(&found_bucket->cont, sizeof(found_bucket->cont), 1, arq_bucket);
    // Caso a encontre, retorna SUCCESS e não vai ser adicionada
    for(int i = 0; i < TAM_MAX_BUCKET; i++) {
        fread(&found_bucket->chaves[i], sizeof(found_bucket->chaves[i]), 1, arq_bucket);
        if(found_bucket->chaves[i] == key)
            return SUCCESS;
    }

    // Caso não a encontre, retorna FAILURE
    fclose(arq_bucket);
    return FAILURE;
}

void bk_add_key(BUCKET *bucket, int key) {
    FILE *arq_bucket = fopen("bucket.dat", "rb+");

    // Encontra o rrn do bucket
    int address = make_address(key, diretorio.dir_prof);
    short rrn_found_bucket = diretorio.cells[address].bucket_ref;

    // Ao encontrar o bucket, verifica se há espaço para inserir a chave nele
    if (bucket->cont < TAM_MAX_BUCKET) {
        bucket->chaves[bucket->cont] = key;
        
        // Vai até onde o bucket está armazenado no arquivo
        fseek(arq_bucket, sizeof(BUCKET) * rrn_found_bucket, SEEK_CUR);
        fseek(arq_bucket, (sizeof(bucket->prof) + sizeof(bucket->cont) + (bucket->cont * sizeof(int))), SEEK_CUR);
        fwrite(&bucket->chaves[bucket->cont], sizeof(int), 1, arq_bucket);

        bucket->cont++;
        rewind(arq_bucket);
        fseek(arq_bucket, sizeof(BUCKET) * rrn_found_bucket, SEEK_CUR);
        fseek(arq_bucket, sizeof(bucket->prof), SEEK_CUR);
        fwrite(&bucket->cont, sizeof(bucket->cont), 1, arq_bucket);

    } else {

        bk_split(bucket, rrn_found_bucket);
        op_add(bucket, key);

    }

    fclose(arq_bucket);
}

int rrn_novo_bucket(){

    // rrn do novo_bucket que será inserido no final do arquivo
    int rrn;
    FILE * arq_bucket = fopen("bucket.dat", "rb");
    fseek(arq_bucket, 0, SEEK_END);
    rrn = ftell(arq_bucket)/sizeof(BUCKET);
    return rrn;

}

void inserir_bucket (BUCKET *bucket, int chave) {

    bucket->chaves[bucket->cont] = chave;
    bucket->cont++;

}

void redistribuir_chaves(BUCKET *bucket, BUCKET *novo_bucket, int start, int end){
    
    // Copia as chaves do bucket para um vetor auxiliar
    int vetor[TAM_MAX_BUCKET];
    for(int i = 0; i < TAM_MAX_BUCKET; i++) {

        vetor[i] = bucket->chaves[i];
        // Retira as chaves do bucket
        bucket->chaves[i] = -1;
    }

    bucket->cont = 0;
    
    // Para todas as chaves do vetor auxilar, calcula o endereço com a prof do bucket
    for(int i = 0; i < TAM_MAX_BUCKET; i++) {

        int address = make_address(vetor[i], bucket->prof);
        // Se address estiver entre start e end, insire no bucket, senão, insira no novo
        if(address >= start && address <= end)
            inserir_bucket(novo_bucket, vetor[i]);
        else
            inserir_bucket(bucket, vetor[i]);
            
    }

}

int bk_split(BUCKET *bucket, short rrn) {

    FILE *arq_bucket = fopen("bucket.dat", "rb+");

    // Se a profundidade dos dois forem iguais, é preciso dobrar o diretório
    if (bucket->prof == diretorio.dir_prof)
        dir_double(diretorio);
        
    int end_novo_bucket, new_start, new_end;

    // Cria um novo bucket
    BUCKET novo_bucket;
    inicializar_bucket(&novo_bucket);

    // Atribuí o endereço do novo_bucket ao end_novo_bucket
    end_novo_bucket = rrn_novo_bucket();

    find_new_range(bucket, &new_start, &new_end);
    dir_ins_bucket(end_novo_bucket, new_start, new_end);

    bucket->prof++;
    novo_bucket.prof = bucket->prof;

    // Redistribuíndo as chaves
    redistribuir_chaves(bucket, &novo_bucket, new_start, new_end);

    // Escrevendo o old_bucket no arquivo
    fseek(arq_bucket, sizeof(BUCKET) * rrn, SEEK_CUR);
    fwrite(&bucket->prof, sizeof(bucket->prof), 1, arq_bucket);
    fwrite(&bucket->cont, sizeof(bucket->cont), 1, arq_bucket);
    fwrite(&bucket->chaves,(TAM_MAX_BUCKET * sizeof(int)), 1, arq_bucket);

    // Escrevendo o novo_bucket no arquivo
    rewind(arq_bucket);
    int local_bucket = end_novo_bucket * sizeof(BUCKET);
    fseek(arq_bucket, local_bucket, SEEK_CUR);
    fwrite(&novo_bucket.prof, sizeof(novo_bucket.prof), 1, arq_bucket);
    fwrite(&novo_bucket.cont, sizeof(novo_bucket.cont), 1, arq_bucket);
    fwrite(&novo_bucket.chaves,(TAM_MAX_BUCKET * sizeof(int)), 1, arq_bucket);

    fclose(arq_bucket);
}

void dir_double() {

    // Aumenta o tamanho do diretório
    int tam_atual = pow(2, diretorio.dir_prof);
    int novo_tam = 2 * tam_atual;

    DIRETORIO novo_diretorio;
    novo_diretorio.cells = malloc (sizeof(DIR_CELL) * novo_tam);
    for(int i = 0; i < tam_atual; i++) {
        novo_diretorio.cells[i*2].bucket_ref = diretorio.cells[i].bucket_ref;
        novo_diretorio.cells[i*2 + 1].bucket_ref = diretorio.cells[i].bucket_ref;
    }

    free(diretorio.cells);

    diretorio.cells = malloc(sizeof(DIR_CELL) * novo_tam);
    diretorio.cells = novo_diretorio.cells;
    diretorio.dir_prof++;

}

void find_new_range(BUCKET *old_bucket, int *new_start, int *new_end) {

    int mask = 1;
    int shared_address = make_address(old_bucket->chaves[0], old_bucket->prof);
    int new_shared = shared_address << 1;
    new_shared = new_shared | mask;
    int bits_to_fill = diretorio.dir_prof - (old_bucket->prof + 1);
    *new_start = *new_end = new_shared;
    for(int j = 1; j < bits_to_fill; j++) {
        *new_start = *new_start << 1;
        *new_end = *new_end << 1;
        *new_end = *new_end | mask;
    }
}

void dir_ins_bucket(int bucket_address, int start, int end) {
    
    // O diretório começa a apontar ao novo bucket que foi inserido
    for(int j = start; j <= end; j++) {
        diretorio.cells[j].bucket_ref = bucket_address;
    }
}

void finalizacao() {
    
    FILE *arq_dir = fopen("dir.dat", "wb");
    int tamanho = pow(2, diretorio.dir_prof);

    // Escrevendo o diretório no arquivo
    fwrite(&(diretorio.dir_prof), sizeof(diretorio.dir_prof), 1, arq_dir);

    for(int i = 0; i < tamanho; i++) {
        fwrite(&(diretorio.cells[i].bucket_ref), sizeof(DIR_CELL), 1, arq_dir);
    }
    
    //Fechando o arquivo
    fclose(arq_dir);  
}

/* ---------------- IMPRESSÃO DO DIRETÓRIO E DOS BUCKETS ---------------- */

void impressao_diretorio () {
    
    FILE *arq_dir, *arq_bucket;
    int tamanho, total_buckets;
    
    if((arq_bucket = fopen("bucket.dat", "rb")) != NULL) {
        fseek(arq_bucket, 0, SEEK_END);
        total_buckets = (ftell(arq_bucket)/sizeof(BUCKET));
    }

    if((arq_dir = fopen("dir.dat", "rb")) != NULL) {

       printf("\n----- Diretorio -----\n");

       // Profundidade 
       fread(&diretorio.dir_prof, sizeof(diretorio.dir_prof), 1, arq_dir);
       
       // Descobrindo o tamanho e alocando espaço para os address nas cells
       tamanho = pow(2, diretorio.dir_prof);
       diretorio.cells = malloc (sizeof(DIR_CELL) * tamanho);
       
       for(int i = 0; i < tamanho; i++) {
            fread(&diretorio.cells[i].bucket_ref, sizeof(DIR_CELL), 1, arq_dir);
            printf("\ndir[%d] = bucket(%d)", i, diretorio.cells[i].bucket_ref);
       }

       // Print das informações do diretório
       printf("\n\nProfundidade = %d", diretorio.dir_prof);
       printf("\nTamanho atual = %d", tamanho);
       printf("\nTotal de buckets = %d\n", total_buckets);
    } else 
        printf("Erro ao abrir o arquivo de diretório.\n");

    fclose(arq_bucket);
    fclose(arq_dir);
}

void impressao_bucket() {

    FILE *arq_bucket;

    if((arq_bucket = fopen("bucket.dat", "rb")) != NULL) {
        
        fseek(arq_bucket, 0, SEEK_END);
        int total_buckets = (ftell(arq_bucket)/sizeof(BUCKET));

        printf("\n----- Buckets -----\n");
        
        int i = 0;
        BUCKET aux;
        inicializar_bucket(&aux);
        
        rewind(arq_bucket);
        while (i < total_buckets) {
            fread(&(aux.prof), sizeof(aux.prof), 1, arq_bucket);
            fread(&(aux.cont), sizeof(aux.cont), 1, arq_bucket);
            fread(&(aux.chaves), TAM_MAX_BUCKET * 4, 1, arq_bucket);
            printf("\nBucket %d (Prof = %d):\n", i, aux.prof);
            for(int j = 0; j < TAM_MAX_BUCKET; j++) {
                printf("Chave[%d] = %d\n", j, aux.chaves[j]);
            }
            i++;
        }
    } else
        printf("Erro ao abrir o arquivo de buckets.\n");

    fclose(arq_bucket);
}
