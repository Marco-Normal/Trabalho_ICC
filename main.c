#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nome; // nome do passageiro. Não sabemos o tamanho do nome
  char
      *sobrenome; // sobrenome do passageiro. Não sabemos o tamanho do sobrenome
  char cpf[12];   // CPF do passageiro
  int dia;
  int mes;
  int ano;
  char num_voo[5]; // número do voo
  char assento[4];
  int classe; // 0 para econômica e 1 para executiva
  float preco;
  char origem[4];  // aeroporto de origem
  char destino[4]; // aeroporto de destino
} passageiro;

void *allocate_vet(int N);
void entrada_opcao_menu(char *comando);
void abertura_voo(void);
passageiro registrar_passageiro(passageiro);

int main(void) {
  char comando[3];
  int flag = 1;
  int num_passageiros;
  passageiro *tot_passageiros;
  while (flag) {
    entrada_opcao_menu(comando);
    if (strcmp(comando, "AV") == 0) {
      abertura_voo();
    } else if (strcmp(comando, "RR") == 0) {
      num_passageiros++;
      tot_passageiros = allocate_vet(
          num_passageiros * sizeof(passageiro)); // tem que ser um realloc
    }
  }
}
void *allocate_vet(int N) {
  /**
   * @brief      Aloca um vetor de tamanho N
   *
   * @details    Aloca um espaço de memória de tamanho
   * N, de forma que podemos fazer um casting para qualquer
   * outro tipo de ponteiro. Isso evitar ter que fazer
   * uma função para alocar char, int, etc.
   *
   * @param      Int N, número de bites que vamos alocar
   *
   * @return     *void ponteiro para o local que alocamos
   */

  void *vetor;
  vetor = (void *)malloc(N);
  return vetor;
}
void entrada_opcao_menu(char *comando) { scanf("%s", comando); }
void abertura_voo(void) {
  FILE *arquivo;
  int assentos;
  float preco_eco, preco_exec;
  arquivo = fopen("voo.txt", "w");
  if (arquivo == NULL) {
    printf("Erro na abertura do arquivo\n");
    return;
  }
  scanf("%d %f %f", &assentos, &preco_eco, &preco_exec);
  fprintf(arquivo, "%d, %.2f, %.2f\n", assentos, preco_eco, preco_exec);
  fclose(arquivo);
}
