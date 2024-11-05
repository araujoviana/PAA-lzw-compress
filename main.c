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

  compactar_string(entrada);

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

  char *w;
  char c;

  // Itera sobre a string
  char *d = string_entrada;
  *w = *d;
  while (*d) {
    c = *w + 1;
    if (verificar_presenca(w)) {
      strcat(w, &c);
    } else {
      printf("%s", w); // FIXME imprima o valor numérico no dicionário
    }

    *d++;
  }

  return string_entrada;
}

// TODO mudar esse nome de função
int verificar_presenca(char *sequencia, struct dicionario dic) {
  char *d = dicionario;
  while (*d) {
    if (*d == *sequencia) {
      return 1;
    }
    *d++;
  }
  return 0;
}
