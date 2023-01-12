# Descrição

O arquivo games.txt possui informações sobre jogos. Os dados dos jogos estão armazenados em formato texto, sendo que os campos de um mesmo jogo, separados por “|”, estão em uma única linha.

O programa deverá oferecer as seguintes funcionalidades:

• Importação dos dados;

• Busca de registro pelo IDENTIFICADOR;

• Inserção de novo registro;

• Remoção de registro.

Todas as operações serão realizadas sem interação direta com o usuário, utilizando para isso a linha de comando com passagem de parâmetros.

# Operação de busca

Formato: b CHAVE

• b é o identificador da operação de busca e CHAVE é a string da chave de busca.

Exemplo: Busca do registro de chave 85

b 85

# Operação de inserção

Formato: i REGISTRO

• i é o identificador da operação de inserção e REGISTRO é a string de um registro completo (no mesmo formato encontrado no arquivo de importação) a ser inserido no arquivo de registros.

Exemplo: Inserção do registro de chave 144

i 144|The Sims|2000|Life simulation|Electronic Arts|PC|

# Comando de remoção

Formato: r CHAVE

• r é o identificador da operação de remoção e CHAVE é a string da chave de busca para a remoção.

Exemplo: Remoção do registro de chave 29

r 29

# Output Esperado

Considere como exemplo o arquivo de operações abaixo:

b 22

i 147|Resident Evil 2|1998|Survival horror|Capcom|PlayStation|

r 99

r 230

i 181|Pac-Man|1980|Maze|Namco|Arcade|

i 144|The Sims|2000|Life simulation|Electronic Arts|PC|

Para cada operação executada, o programa deverá apresentar na tela uma informação sobre o resultado da operação. Utilizando como exemplo o arquivo de operações mostrado acima, o programa deverá apresentar:

Busca pelo registro de chave "22"
22|Tetris|1984|Puzzle|Elorg|Electronika 60| (43 bytes)

Insercao do registro de chave "147" (60 bytes)
Local: fim do arquivo

Remocao do registro de chave "99"
Registro removido! (94 bytes)
Local: offset = 6290 bytes (0x1892)

Remocao do registro de chave "230"
Erro: registro nao encontrado!

Insercao do registro de chave "181" (35 bytes)
Tamanho do espaco reutilizado: 94 bytes
Local: offset = 6290 bytes (0x1892)

Insercao do registro de chave "144" (53 bytes)
Local: fim do arquivo
