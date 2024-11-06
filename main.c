#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQUENCIA 100
#define TAMANHO_ALFABETO 52

struct dicionario {
  char **sequencia; // Conteúdo da sequência
  int *codigo;      // Indice da sequência
  int tamanho;      // Número de sequências no dicionário
};

void preencher_dicionario(struct dicionario *dic);
void adicionar_sequencia(struct dicionario *dic, char *sequencia);
char *compactar_string(char *string_entrada, struct dicionario *dic);
int verificar_presenca(char *sequencia_atual, struct dicionario *dic);

char entrada[300];

int main(int argc, char *argv[]) {
  struct dicionario dic;
  dic.sequencia = malloc(TAMANHO_ALFABETO * sizeof(char *));
  dic.codigo = malloc(TAMANHO_ALFABETO * sizeof(int));
  dic.tamanho = 0;

  preencher_dicionario(&dic);

  printf("Insira o texto a ser compactado: ");
  fgets(entrada, sizeof(entrada), stdin);
  entrada[strcspn(entrada, "\n")] = 0;

  char *entrada_compactada = compactar_string(entrada, &dic);
  printf("Texto compactado: %s\n", entrada_compactada);

  for (int i = 0; i < dic.tamanho; i++) {
    free(dic.sequencia[i]);
  }
  free(dic.sequencia);
  free(dic.codigo);

  return 0;
}

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
  dic->sequencia = realloc(dic->sequencia, (dic->tamanho + 1) * sizeof(char *));
  dic->sequencia[dic->tamanho] = malloc((strlen(sequencia) + 1) * sizeof(char));
  strcpy(dic->sequencia[dic->tamanho], sequencia);

  int *temp = realloc(dic->codigo, (dic->tamanho + 1) * sizeof(int));
  if (temp == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
  }
  dic->codigo = temp;
  dic->codigo[dic->tamanho] = dic->tamanho;
  dic->tamanho++;
}

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
      adicionar_sequencia(dic, sequencia_atual);
      snprintf(sequencia_compactada + strlen(sequencia_compactada),
               MAX_SEQUENCIA - strlen(sequencia_compactada), "%d ",
               dic->codigo[verificar_presenca(sequencia_atual, dic) - 1]);
      snprintf(sequencia_atual, sizeof(sequencia_atual), "%c", char_proximo);
      char_atual++;
    }
  }
  return sequencia_compactada;
}

int verificar_presenca(char *sequencia_atual, struct dicionario *dic) {
  for (int i = 0; i < dic->tamanho; i++) {
    if (strcmp(sequencia_atual, dic->sequencia[i]) == 0) {
      return i + 1;
    }
  }
  return 0;
}
