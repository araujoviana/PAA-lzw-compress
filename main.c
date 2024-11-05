/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
** Nome: Enzo Carvalho Pagliarini
** RA: 10425707
*/

// TODO comentar as coisas

#include <stdio.h>
#include <stdlib.h>
// REVIEW pode usar isso?
#include <string.h>

#define MAX_SEQUENCIA 100

// Dicionário para armazenar as sequências usadas na compactação da entrada do
// usuário
struct dicionario {
  char **sequencia;
  int *indice;
};

void preencher_dicionario(struct dicionario dic);
char *compactar_string(char *string_entrada, struct dicionario dic);
int verificar_presenca(char *sequencia, struct dicionario dic);

// Entrada do usuário
char entrada[300];

int main(int argc, char *argv[]) {
  int numero_elementos = 56;

  struct dicionario dic;
  dic.sequencia = malloc(numero_elementos * sizeof(char *));

  preencher_dicionario(dic);

  // Lê a entrada do usuário
  printf("Insira o texto a ser compactado: ");
  fgets(entrada, sizeof(entrada), stdin);

  compactar_string(entrada, dic);

  return 0;
}

// Preenche o dicionário com todas as letras do alfabeto latino, maiúsculas e
// minúsculas, e os indices com suas posições corretas
void preencher_dicionario(struct dicionario dic) {
  int contador_indice = 0;
  for (int i = 0; i < 26; i++) {
    dic.sequencia[i] = malloc(2 * sizeof(char));
    dic.sequencia[i][0] = 'A' + i;
    dic.sequencia[i][1] = '\0';
    dic.indice[contador_indice] = contador_indice;
    contador_indice++;
  }

  for (int i = 0; i < 26; i++) {
    dic.sequencia[26 + i] = malloc(2 * sizeof(char));
    dic.sequencia[26 + i][0] = 'a' + i;
    dic.sequencia[26 + i][1] = '\0';
    dic.indice[contador_indice] = contador_indice;
    contador_indice++;
  }
}

// Compacta a entrada do usuário usando a compactação LZW
char *compactar_string(char *string_entrada, struct dicionario dic) {

  // TODO comentário aqui
  char sequencia_compactada[MAX_SEQUENCIA] = "";
  char sequencia_atual[MAX_SEQUENCIA] = "";

  // Itera sobre a entrada do usuário
  char *char_atual = string_entrada;
  while (*char_atual) {
    char char_proximo = *char_atual;

    // Adiciona o caractere atual à sequência atual,
    // TODO explicar pq essa função
    strncat(sequencia_atual, &char_proximo, 1);

    // Se a sequencia estiver presente no dicionário concatena o caracter à
    // sequencia
    if (verificar_presenca(string_entrada, dic)) {
      char_atual++;
    } else {
      strncat(sequencia_compactada, sequencia_atual,
              MAX_SEQUENCIA - strlen(sequencia_compactada) - 1);
      snprintf(sequencia_atual, sizeof(sequencia_atual), "%c", char_proximo);
      char_atual++;
    }
  }

  if (strlen(sequencia_atual) > 0) {
    strncat(sequencia_compactada, sequencia_atual, MAX_SEQUENCIA - strlen(sequencia_compactada) -1);
  }
  return sequencia_compactada;
}

// TODO mudar esse nome de função e dos argumentos
int verificar_presenca(char *entrada, struct dicionario dic) {
  // Itera sobre cada sequência dentro do dicionário
  char **sequencia_atual = dic.sequencia;
  while (*sequencia_atual) {
    // Verifica se a sequência do usuário é igual à sequência atual do
    // dicionário
    if (!(strcmp(entrada, *sequencia_atual))) {
      return 1;
    }
    sequencia_atual++;
  }
  return 0;
}
