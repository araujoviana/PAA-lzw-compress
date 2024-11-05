/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
** Nome: Enzo Carvalho Pagliarini
** RA: 10425707
*/

// TODO comentar as coisas

#include <stdio.h>
#include <stdlib.h>

char *compactar_string(char *string_entrada, char *dicionario);
int verificar_presenca(char *sequencia, char *dicionario);

char entrada[300];
/*******************************************************************************/
/* char dicionario[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
 */
/*                      'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
 */
/*                      'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
 */
/*                      'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
 */
/*                      's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; */
/*******************************************************************************/

int main(int argc, char *argv[]) {

  // Aloca o dicionário inicial para conter os alfabeto latino em maiúsculo e
  // minúsculo
  int initial_size = 56;
  char *dicionario = malloc(initial_size * sizeof(char));

  // Insere todas as letras dentro do dicionário
  for (int i = 0; i < 26; i++) {
    dicionario[i] = 'a' + i;      // Minúsculo
    dicionario[26 + i] = 'A' + i; // Maiúsculo
  }

  printf("Insira o texto: ");

  fgets(entrada, sizeof(entrada), stdin);

  compactar_string(entrada, dicionario);

  return 0;
}

// Compacta a entrada do usuário usando a compactação LZW
char *compactar_string(char *string_entrada, char *dicionario) {

  // Itera sobre a string
  char *c = string_entrada;
  while (*c) {
    if (verificar_presenca(c, dicionario)) { // TODO aqui!!! faz ele relocar memória caso n tenha aqui o negocio
      printf("Existe: %c\n", *c);
    } else {
      printf("Não existe: %c\n", *c);
    }
    *c++;
  }

  return string_entrada;
}

// TODO mudar esse nome de função
int verificar_presenca(char *sequencia, char *dicionario) {
  char *d = dicionario;
  while (*d) {
    if (*d == *sequencia) {
      return 1;
    }
    *d++;
  }
  return 0;
}
