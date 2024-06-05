/**
 * @file main.c
 *
 * @brief      Implementação de um sistema de reserva de passagens aéreas
 *            utilizando ponteiros e alocação dinâmica de memória. O sistema
 *            permite a abertura de um voo, o registro de passageiros e a
 *            modificação de reservas. Ele permite fechamento do dia, que
 * imprime os dados de todos os passageiros registrados, junto com o valor
 * total. Existe também o fechamento do voo, que não permite mais a modificação
 *            de reservas.
 *            O sistema é composto por uma struct passageiro, que contém os
 * dados de um passageiro, e funções para alocar e realocar vetores, entrada de
 * opções do menu, abertura de voo, registro de passageiros, modificação de
 * reservas e impressão de um passageiro.
 *
 * */

/**
 * TODO: Implementar a função de fechamento do dia
 * TODO: Implementar a função de fechamento do voo
 * TODO: Implementar a função de impressão de todos os passageiros
 * TODO: Identificar quando o avião está cheio. Talvez seria legal colocar
 * as opções de menu em uma função. Seria legal uma flag para indicar se o voo
 * está aberto ou fechado e se está cheio ou não.
 * DONE: Implementar a função de registro de passageiros
 * DONE: Implementar a função de modificação de reservas
 * DONE: Implementar a função de abertura de voo
 * DONE: Implementar a função de impressão de um passageiro
 * DONE: Implementar a função de alocação de vetores
 * DONE: Implementar a função de realocação de vetores
 *
 *
 * */

/**
 * Os casos de teste estão na pasta e
 * por enquanto estão sendo utilizados
 * apenas para ver se o programa consegue
 * registrar mais de 1 pessoa e realizar modificações
 * nas reservas.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nome;      // nome do passageiro. Não sabemos o tamanho do nome
  char *sobrenome; // sobrenome do passageiro.
  char cpf[15];    // CPF do passageiro
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

void *reallocate_vet(void *vetor, int N);
void *allocate_vet(int N);
void entrada_opcao_menu(char *comando);
void abertura_voo(void);
passageiro registrar_passageiro(passageiro novo_passageiro);
void modificar_reserva(passageiro *tot_passageiros, int num_passageiros);
void printf_passageiro(passageiro);

int main(void) {
  char comando[3];
  int flag = 1;
  int num_passageiros = 0;
  passageiro *tot_passageiros;
  while (flag) {
    entrada_opcao_menu(comando);
    if (strcmp(comando, "AV") == 0) {
      abertura_voo();
    } else if (strcmp(comando, "RR") == 0) {
      num_passageiros++;
      printf("%d\n", num_passageiros);
      tot_passageiros = (passageiro *)reallocate_vet(
          tot_passageiros, num_passageiros * sizeof(passageiro));
      tot_passageiros[num_passageiros - 1] =
          registrar_passageiro(tot_passageiros[num_passageiros - 1]);
    } else if (strcmp(comando, "EX") == 0) {
      flag = 0;

    } else if (strcmp(comando, "MR") == 0) {
      modificar_reserva(tot_passageiros, num_passageiros);
    }
  }

  printf_passageiro(tot_passageiros[0]);
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
void entrada_opcao_menu(char *comando) {

  /**
   * @brief      Pega a entrada do usuário
   *
   * @details    Pega a entrada do usuário e coloca
   * no ponteiro comando.
   *
   * @param      char *comando, ponteiro para onde vamos
   * colocar a entrada do usuário
   *
   * @return     void
   */

  scanf("%s", comando);
}
void abertura_voo(void) {

  /**
   * @brief      Abre um voo
   *
   * @details    Abre um voo, pedindo os dados
   * necessários para preencher o arquivo voo.txt.
   *
   * @param      void
   *
   * @return     void
   */

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

void *reallocate_vet(void *vetor, int N) {
  /**
   * @brief      Realoca um vetor de tamanho N
   *
   * @details    Realoca um espaço de memória de tamanho
   * N, de forma que podemos fazer um casting para qualquer
   * outro tipo de ponteiro. Isso evitar ter que fazer
   * uma função para alocar char, int, etc.
   *
   * @param      Int N, número de bites que vamos alocar
   *
   * @return     *void ponteiro para o local que alocamos
   */

  void *vetor_novo;
  vetor_novo = (void *)realloc(vetor, N);
  return vetor_novo;
}

passageiro registrar_passageiro(passageiro novo_passageiro) {
  /**
   * @brief      Registra um passageiro
   *
   * @details    Registra um passageiro, pedindo os dados
   * necessários para preencher a struct passageiro.
   *
   * @param      passageiro, struct passageiro que vamos preencher
   *
   * @return     passageiro, struct passageiro preenchida
   */
  novo_passageiro.nome = (char *)allocate_vet(50);
  novo_passageiro.sobrenome = (char *)allocate_vet(50);
  scanf("%s %s %s %d %d %d %s %s %d %f %s %s", novo_passageiro.nome, // Ugly
        novo_passageiro.sobrenome, novo_passageiro.cpf, &novo_passageiro.dia,
        &novo_passageiro.mes, &novo_passageiro.ano, novo_passageiro.num_voo,
        novo_passageiro.assento, &novo_passageiro.classe,
        &novo_passageiro.preco, novo_passageiro.origem,
        novo_passageiro.destino);
  return novo_passageiro;
}

void printf_passageiro(passageiro passageiro) {
  /**
   * @brief      Printa um passageiro
   *
   * @details    Printa um passageiro, pedindo os dados
   * necessários para preencher a struct passageiro.
   *
   * @param      passageiro, struct passageiro que vamos printar
   *
   * @return     void
   */

  puts(passageiro.cpf);
  printf("%s %s\n", passageiro.nome, passageiro.sobrenome);
  printf("%d/%d/%d\n", passageiro.dia, passageiro.mes, passageiro.ano);
  printf("Voo: %s\n", passageiro.num_voo);
  printf("Assento: %s\n", passageiro.assento);
  if (passageiro.classe == 0) {
    printf("Classe: Econômica\n");
  } else {
    printf("Classe: Executiva\n");
  }
  printf("Trecho: %s %s\n", passageiro.origem, passageiro.destino);
  printf("Preço: %.2f\n", passageiro.preco);
}

void modificar_reserva(passageiro *tot_passageiros, int num_passageiros) {

  char cpf[15];
  char assento[4];

  scanf("%s %s", cpf, assento);

  /**
   * @brief      Modifica a reserva de um passageiro
   *
   * @details    Modifica a reserva de um passageiro, pedindo os dados
   * necessários para preencher a struct passageiro.
   *
   * @param      cpf, char com o cpf do passageiro
   * @param      assento, char com o assento do passageiro
   * @param      tot_passageiros, vetor de passageiros
   *
   * @return     void
   */

  int i;
  for (i = 0; i < num_passageiros; i++) {
    if (strcmp(tot_passageiros[i].cpf, cpf) == 0) {
      strcpy(tot_passageiros[i].assento, assento);
    }
  }
}
