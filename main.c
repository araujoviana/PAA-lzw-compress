// TODO Adicionar mais comentários

/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
** Nome: Enzo Carvalho Pagliarini
** RA: 10425707
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho máximo de uma sequência de caracteres
#define MAX_SEQUENCIA 100
// Quantidade de letras no alfabeto latino minúsculo e maiúsculo
#define TAMANHO_ALFABETO 52

// Dicionário para armazenar as sequências usadas na compactação da entrada do
// usuário
struct dicionario {
  char **sequencia; // Conteúdo da sequência
  int *codigo;      // Indice da sequência
  int tamanho;      // Número de sequências no dicionário
};

void preencher_dicionario(struct dicionario *dic);
void adicionar_sequencia(struct dicionario *dic, char *sequencia);
char *compactar_string(char *string_entrada, struct dicionario *dic);
int verificar_presenca(char *sequencia_atual, struct dicionario *dic);

// Entrada do usuário
char entrada[300];

int main(int argc, char *argv[]) {
  struct dicionario dic;
  dic.sequencia = malloc(TAMANHO_ALFABETO * sizeof(char *));
  dic.codigo = malloc(TAMANHO_ALFABETO * sizeof(int *));
  dic.tamanho = 0;

  preencher_dicionario(&dic);

  // Lê a entrada do usuário
  printf("Insira o texto a ser compactado: ");
  fgets(entrada, sizeof(entrada), stdin);

  // Remove a nova linha da entrada, se existir.
  // strcspn encontra o indice do caractere '\n'
  entrada[strcspn(entrada, "\n")] = 0;

  char *entrada_compactada = compactar_string(entrada, &dic);
  printf("Texto compactado: %s\n", entrada_compactada);

  // Libera a memória do dicionário
  for (int i = 0; i < TAMANHO_ALFABETO; i++) {
    free(dic.sequencia[i]);
  }
  free(dic.sequencia);
  free(dic.codigo);

  return 0;
}

// Preenche o dicionário com todas as letras do alfabeto latino, maiúsculas e
// minúsculas
void preencher_dicionario(struct dicionario *dic) {
  for (int i = 0; i < 26; i++) {
    dic->sequencia[i] = malloc(2 * sizeof(char));
    dic->sequencia[i][0] = 'A' + i;
    dic->sequencia[i][1] = '\0';
    dic->codigo[dic->tamanho] = dic->tamanho;
    dic->tamanho++;
  }

  for (int i = 0; i < 26; i++) {
    dic->sequencia[26 + i] = malloc(2 * sizeof(char));
    dic->sequencia[26 + i][0] = 'a' + i;
    dic->sequencia[26 + i][1] = '\0';
    dic->codigo[dic->tamanho] = dic->tamanho;
    dic->tamanho++;
  }
}

void adicionar_sequencia(struct dicionario *dic, char *sequencia) {
  dic->sequencia[dic->tamanho] = malloc((strlen(sequencia) + 1) * sizeof(char));
  strcpy(dic->sequencia[dic->tamanho], sequencia);
  dic->codigo[dic->tamanho] = dic->tamanho;
  dic->tamanho++;
}

// TODO Adicionar partes não presentes no dicionário a ele! só ta concatenando!
// Compacta a entrada do usuário usando a compactação LZW
char *compactar_string(char *string_entrada, struct dicionario *dic) {
  static char sequencia_compactada[MAX_SEQUENCIA] = "";
  char sequencia_atual[MAX_SEQUENCIA] = "";
  char *char_atual = string_entrada;

  while (*char_atual) {
    char char_proximo = *char_atual;
    strncat(sequencia_atual, &char_proximo, 1);

    if (verificar_presenca(sequencia_atual, dic)) {
      char_atual++;
    } else {
      // Output the code for the current sequence
      snprintf(sequencia_compactada + strlen(sequencia_compactada),
               MAX_SEQUENCIA - strlen(sequencia_compactada), "%d ",
               dic->codigo[verificar_presenca(sequencia_atual, dic) - 1]);

      // Add the new sequence to the dictionary
      adicionar_sequencia(dic, sequencia_atual);

      // Reset the current sequence
      snprintf(sequencia_atual, sizeof(sequencia_atual), "%c", char_proximo);
      char_atual++;
    }
  }

  // Append the last sequence if there is any
  if (strlen(sequencia_atual) > 0) {
    snprintf(sequencia_compactada + strlen(sequencia_compactada),
             MAX_SEQUENCIA - strlen(sequencia_compactada), "%d ",
             dic->codigo[verificar_presenca(sequencia_atual, dic) - 1]);
  }

  return sequencia_compactada;
}

// Verifica se a sequência está presente no dicionário
int verificar_presenca(char *sequencia_atual, struct dicionario *dic) {
  for (int i = 0; i < dic->tamanho; i++) {
    if (strcmp(sequencia_atual, dic->sequencia[i]) == 0) {
      return i + 1;
    }
  }
  return 0;
}
