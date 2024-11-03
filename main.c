/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
** Nome: Enzo Carvalho Pagliarini
** RA: 10425707
*/

#include <stdio.h>

char entrada[300];

int main(int argc, char *argv[]) {
  printf("Insira o texto: ");

  fgets(entrada, sizeof(entrada), stdin);

  printf("%s", entrada);
  return 0;
}
