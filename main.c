#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_VOO "voos.txt"

typedef struct {
  char *nome;      // nome do passageiro. Não sabemos o tamanho do nome
  char *sobrenome; // sobrenome do passageiro.
  char cpf[15];    // CPF do passageiro
  int dia;
  int mes;
  int ano;
  char num_voo[5]; // número do voo
  char assento[4];
  char classe[9]; // 0 para econômica e 1 para executiva
  float preco;
  char origem[4];  // aeroporto de origem
  char destino[4]; // aeroporto de destino
} passageiro;

void *allocate_vet(int N);
void *reallocate_vet(void *vet, int N);
void opcao_menu(char comando[3], char *info);
void abertura_voo();
passageiro *registrar_passageiro(passageiro *vet_passageiros, int N);

int main(void) {
  char comando[3];
  char *info; // Armazena a string digitada - o comando
  passageiro *vet_passageiros;
  int num_passageiros = 0;
  int flag = 1;
  vet_passageiros = (passageiro *)allocate_vet(0);
  info = (char *)allocate_vet(100);
  while (flag) {
    opcao_menu(comando, info);
    if (strcmp(comando, "AV") == 0) {
      abertura_voo();
    } else if (strcmp(comando, "RR") == 0) {
      registrar_passageiro(vet_passageiros, num_passageiros);
      num_passageiros++;
    } else if (strcmp(comando, "EX") == 0) {
      flag = 0;
    }
    free(info);
    return 0;
  }
}

void *allocate_vet(int N) {
  void *vet = (void *)malloc(N);
  if (vet == NULL) {
    printf("Erro ao alocar memória\n");
    exit(1);
  }
  return vet;
}

void *reallocate_vet(void *vet, int N) {
  void *vet_aux = (void *)realloc(vet, N);
  if (vet_aux == NULL) {
    printf("Erro ao realocar memória\n");
    exit(1);
  }
  return vet_aux;
}

void opcao_menu(char comando[3], char *info) { 
  char string[100];

  fgets(string, sizeof(string), stdin);
  sscanf(string, " %[^ ] %[^\n]", comando, info);
}

void abertura_voo() {
  FILE *arq;
  arq = fopen(PATH_VOO, "w");
  int assentos;
  float preco_eco, preco_exec;
  scanf("%d %f %f", &assentos, &preco_eco, &preco_exec);
  fprintf(arq, "%d %.2f %.2f\n", assentos, preco_eco, preco_exec);
  fclose(arq);
}

passageiro *registrar_passageiro(passageiro *vet_passageiros, int N) {
  FILE *arq;
  arq = fopen(PATH_VOO, "a");
  vet_passageiros = (passageiro *)reallocate_vet(vet_passageiros,
                                                 (N + 1) * sizeof(passageiro));
  vet_passageiros[N].nome = (char *)allocate_vet(50);
  vet_passageiros[N].sobrenome = (char *)allocate_vet(50);
  scanf("%s %s %s %d %d %d %s %s %s %f %s %s", vet_passageiros[N].nome,
        vet_passageiros[N].sobrenome, vet_passageiros[N].cpf,
        &vet_passageiros[N].dia, &vet_passageiros[N].mes,
        &vet_passageiros[N].ano, vet_passageiros[N].num_voo,
        vet_passageiros[N].assento, vet_passageiros[N].classe,
        &vet_passageiros[N].preco, vet_passageiros[N].origem,
        vet_passageiros[N].destino);
  vet_passageiros[N].nome = (char *)reallocate_vet(
      vet_passageiros[N].nome, strlen(vet_passageiros[N].nome) + 1);
  vet_passageiros[N].sobrenome = (char *)reallocate_vet(
      vet_passageiros[N].sobrenome, strlen(vet_passageiros[N].sobrenome) + 1);
  fprintf(arq, "%s %s %s %d %d %d %s %s %s %.2f %s %s\n",
          vet_passageiros[N].nome, vet_passageiros[N].sobrenome,
          vet_passageiros[N].cpf, vet_passageiros[N].dia,
          vet_passageiros[N].mes, vet_passageiros[N].ano,
          vet_passageiros[N].num_voo, vet_passageiros[N].assento,
          vet_passageiros[N].classe, vet_passageiros[N].preco,
          vet_passageiros[N].origem, vet_passageiros[N].destino);
  fclose(arq);
  return vet_passageiros;
}
