/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
** Nome: Enzo Carvalho Pagliarini
** RA: 10425707
*/

// TODO comentar as coisas

#include <stdio.h>

char *compactar_string(char *string_entrada);
int verificar_presenca(char *sequencia);

char entrada[300];
char dicionario[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                     'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                     'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                     'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                     's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, char *argv[]) {
  printf("Insira o texto: ");

  fgets(entrada, sizeof(entrada), stdin);

  compactar_string(entrada);

  return 0;
}

// Compacta a entrada do usuário usando a compactação LZW
char *compactar_string(char *string_entrada) {

  int dentro;

  // Itera sobre a string
  char *c = string_entrada;
  while (*c) {
    dentro = verificar_presenca(c);
    printf("%d\n", dentro);
    *c++;
  }

  return "NUTS";
}

// TODO mudar esse nome de função
int verificar_presenca(char *sequencia) {
  char *c = dicionario;
  while (*c) {
    if (*c == *sequencia) {
      return 1;
    }
    *c++;
  }
  return 0;
}
