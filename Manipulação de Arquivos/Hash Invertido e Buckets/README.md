# Descrição

O objetivo é criar um programa que, a partir de um arquivo contendo uma lista de chaves, construa um hashing extensível. Além disso, o programa também deverá fornecer funcionalidades para imprimir informações
sobre o hashing.

O arquivo de chaves será um arquivo texto contendo apenas chaves numéricas, uma por linha. Cada chave lida (um número inteiro) deverá ser inserida em um hashing extensível com buckets de tamanho fixo. Para facilitar a
experimentação com buckets de diferentes tamanhos, o tamanho máximo do bucket é uma constante TAM_MAX_BUCKET.

Os buckets são criados e mantidos no arquivo de buckets. O diretório será armazenado no arquivo de diretório, mas será construído e manipulado em memória.

O programa oferece as seguintes funcionalidades:

● Importação do arquivo de chaves para o hashing extensível;

● Impressão das informações do hashing extensível.

As operações serão realizadas sem interação direta com o usuário, utilizando para isso a linha de comando com passagem de parâmetros.
