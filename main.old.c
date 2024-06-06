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
 * DONE: Implementar a função de fechamento do dia
 * DONE: Implementar a função de fechamento do voo
 * DONE: Implementar a função de impressão de todos os passageiros
 * DONE: Identificar quando o avião está cheio. Talvez seria legal colocar
 * as opções de menu em uma função. Seria legal uma flag para indicar se o voo
 * está aberto ou fechado e se está cheio ou não.
 * DONE: Implementar a função de registro de passageiros
 * DONE: Implementar a função de modificação de reservas
 * DONE: Implementar a função de abertura de voo
 * DONE: Implementar a função de impressão de um passageiro
 * DONE: Implementar a função de alocação de vetores
 * DONE: Implementar a função de realocação de vetores
 * DONE: Cancelar reserva
 *
 * TODO: Ver se na função de finalizar dia, precisa
 * guardar em um arquivo e "salvar o estado do programa"
 * assim que finalizar o dia.
 * Caso seja necessário isso, precisamos de uma função que
 * escreva todos os passageiros em um arquivo. Ademais, precisamos de uma
 * função que salve o estado do programa, como as flags, número de passageiros,
 * etc. Imagino que não deva ser díficil. Talvez no While podemos fazer uma
 * comparação se existe um arquivo com passageiros, se existir, carregamos eles.
 * */

/**
 * Os Casos testes já estão
 *implementados com input
 *e output. Tem um script na
 *shell que realiza o trabalho
 *de fazer o diff entre eles,
 *para saber se o input e output
 *são iguais*/

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
int abertura_voo(void);
passageiro registrar_passageiro(passageiro novo_passageiro);
int achar_passageiro(passageiro *tot_passageiros, int num_passageiros,
                     char *cpf);
void modificar_reserva(passageiro *tot_passageiros, int num_passageiros);
void printf_passageiro(passageiro pass);
void printf_voo(passageiro pass);
void consulta_passageiro(passageiro *tot_passageiros, int num_passageiros);
passageiro *cancelar_reserva(passageiro *tot_passageiros, int num_passageiros);
void fechamento_dia(passageiro *tot_passageiros, int num_passageiros);
void fechamento_voo(passageiro *tot_passageiros, int num_passageiros);
void printf_underline(void);
void free_vet(passageiro *tot_passageiros, int num_passageiros);

int main(void) {
  char comando[3];
  int flag_entrada = 1;
  int flag = 1;
  int capacidade_maxima;
  int num_passageiros = 0;
  passageiro *tot_passageiros =
      (passageiro *)allocate_vet(0 * sizeof(passageiro)); // inicializa vetor
  while (flag_entrada) {
    entrada_opcao_menu(comando);
    if (strcmp(comando, "AV") == 0) {
      capacidade_maxima = abertura_voo();
      flag_entrada = 0;
    }
  }
  while (capacidade_maxima && flag) {
    entrada_opcao_menu(comando);
    if (strcmp(comando, "RR") == 0) { // TODO Flag de voo
      num_passageiros++; // Pode ser uma boa colocar isso numa função
      capacidade_maxima--;
      tot_passageiros = (passageiro *)reallocate_vet(
          tot_passageiros, num_passageiros * sizeof(passageiro));
      tot_passageiros[num_passageiros - 1] =
          registrar_passageiro(tot_passageiros[num_passageiros - 1]);
    } else if (strcmp(comando, "EX") == 0) { // Comando de saída
      flag = 0;
    } else if (strcmp(comando, "MR") == 0) { // Comando modificar voo
      modificar_reserva(tot_passageiros, num_passageiros);
    } else if (strcmp(comando, "CR") == 0) { // Comando consultar reserva
      consulta_passageiro(tot_passageiros, num_passageiros);
    } else if (strcmp(comando, "CA") == 0) { // Comando cancelar reserva
      tot_passageiros = cancelar_reserva(tot_passageiros, num_passageiros);
      num_passageiros--;
      capacidade_maxima++;
    } else if (strcmp(comando, "FD") == 0) { // Comando fechamento do dia
      fechamento_dia(tot_passageiros, num_passageiros);
    } else if (strcmp(comando, "FV") == 0) { // Comando fechamento do voo
      fechamento_voo(tot_passageiros, num_passageiros);
      flag = 0;
    }
  }
  if (capacidade_maxima == 0) {
    fechamento_voo(tot_passageiros, num_passageiros);
  }
  return 0;
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
int abertura_voo(void) {

  /**
   * @brief      Abre um voo
   *
   * @details    Abre um voo, pedindo os dados
   * necessários para preencher o arquivo voo.txt.
   * Provavelmente seria legal colocar como um define o
   * nome do arquivo.
   * @param      void
   *
   * @return     void, escreve no arquivo voo.txt
   */

  FILE *arquivo;
  int assentos;
  float preco_eco, preco_exec;
  arquivo = fopen("voo.txt", "w");
  if (arquivo == NULL) {
    printf("Erro na abertura do arquivo\n");
    return 0;
  }
  scanf("%d %f %f", &assentos, &preco_eco, &preco_exec);
  fprintf(arquivo, "%d, %.2f, %.2f\n", assentos, preco_eco, preco_exec);
  fclose(arquivo);
  return assentos;
}

void *reallocate_vet(void *vetor, int N) {
  /**
   * @brief      Realoca um vetor de tamanho N
   *
   * @details    Realoca um espaço de memória de tamanho
   * N, de forma que podemos fazer um casting para qualquer
   * outro tipo de ponteiro. Isso evitar ter que fazer
   * uma função para alocar char, int, etc. Vai ser
   * necessário fazer um casting para o tipo de ponteiro
   * que queremos. Útil na hora de cancelar uma reserva.
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
   * necessários para preencher a struct passageiro. A função
   * ta bem feia quanto ao preenchimento da struct, mas ela funciona.
   * Acho que seria legal colocar um define para o tamanho dos
   * vetores. Não termos número mágicos no código.
   *
   * @param      passageiro, struct passageiro que vamos preencher
   *
   * @return     passageiro, struct passageiro preenchida
   */
  FILE *fp;

  if ((fp = fopen("fechamento.txt", "r")) == NULL) {
    fp = fopen("fechamento.txt", "w");
  } else {
    fp = fopen("fechamento.txt", "a");
  }
  novo_passageiro.nome = (char *)allocate_vet(50);
  novo_passageiro.sobrenome = (char *)allocate_vet(50);
  char classe[10];
  scanf("%s %s %s %d %d %d %s %s %s %f %s %s", novo_passageiro.nome, // Ugly
        novo_passageiro.sobrenome, novo_passageiro.cpf, &novo_passageiro.dia,
        &novo_passageiro.mes, &novo_passageiro.ano, novo_passageiro.num_voo,
        novo_passageiro.assento, classe, &novo_passageiro.preco,
        novo_passageiro.origem, novo_passageiro.destino);
  if (strcmp(classe, "economica") == 0) {
    novo_passageiro.classe = 0;
  } else {
    novo_passageiro.classe = 1;
  }
  fputs(novo_passageiro.nome, fp);
  fputc(' ', fp);
  fputs(novo_passageiro.sobrenome, fp);
  fputc(' ', fp);
  fputs(novo_passageiro.cpf, fp);
  fputc(' ', fp);
  fprintf(fp, " %d %d %d ", novo_passageiro.dia, novo_passageiro.mes,
          novo_passageiro.ano);
  fputs(novo_passageiro.num_voo, fp);
  fputc(' ', fp);
  fputs(novo_passageiro.assento, fp);
  fputc(' ', fp);
  if (novo_passageiro.classe == 0) {
    fputs("economica ", fp);
  } else {
    fputs("executiva ", fp);
  }
  fprintf(fp, "%.2f ", novo_passageiro.preco);
  fputs(novo_passageiro.origem, fp);
  fputc(' ', fp);
  fputs(novo_passageiro.destino, fp);
  fputc(' ', fp);
  fprintf(fp, "\n");
  fclose(fp);
  // Pensar melhor
  return novo_passageiro;
}

void printf_passageiro(passageiro pass) {
  /**
   * @brief      Printa um passageiro
   *
   * @details    Printa um passageiro, no formato
   * especificado no enunciado do trabalho. A função
   * é bem simples, só aceita um passageiro por vez.
   *
   * @param      passageiro, struct passageiro que vamos printar
   *
   * @return     void
   */

  puts(pass.cpf);
  printf("%s %s\n", pass.nome, pass.sobrenome);
  printf("%d/%d/%d\n", pass.dia, pass.mes, pass.ano);
  printf("Voo: %s\n", pass.num_voo);
  printf("Assento: %s\n", pass.assento);
  if (pass.classe == 0) {
    printf("Classe: economica\n");
  } else {
    printf("Classe: executiva\n");
  }
  printf("Trecho: %s %s\n", pass.origem, pass.destino);
  printf("Valor: %.2f\n", pass.preco);
  printf_underline();
}

void printf_voo(passageiro pass) {
  /**
   * @brief      Imprime apenas as informações do Voo
   *
   * @details    Recebe o passageiro e imprime apenas o CPF
   * Nome e assento, nada mais. Para ser utilizado apenas
   * no voo fechado
   *
   * @param      passageiro pass, estrutura do passageiro
   *
   * @return     void, apenas imprime
   */
  printf("%s\n", pass.cpf);
  printf("%s %s\n", pass.nome, pass.sobrenome);
  printf("%s\n", pass.assento);
  return;
}

void modificar_reserva(passageiro *tot_passageiros, int num_passageiros) {

  /**
   * @brief      Modifica a reserva de um passageiro
   *
   * @details    Modifica a reserva de um passageiro, pedindo os dados
   * necessários para preencher a struct passageiro. Ele escreve na
   * struct passageiro os novos dados. A função acha o passageiro
   * pelo cpf. Se não achar, printa que o passageiro não foi encontrado.
   * Como dado no enunciado, podemos modificar o nome, sobrenome, cpf e
   * assento.
   *
   * @param      tot_passageiros, vetor de passageiros
   * @param      num_passageiros, número de passageiros
   * util para fazermos o loop
   *
   *
   * @return     void, escreve na struct passageiro
   */
  char cpf_consulta[15];   // Cpf para buscar o passageiro
  char assento_novo[4];    // Assento novo
  char cpf_novo[15];       // Cpf novo
  char nome_novo[50];      // Nome novo
  char sobrenome_novo[50]; // Sobrenome novo
  int posicao;             // Posição do passageiro no vetor
  scanf("%s %s %s %s %s", cpf_consulta, nome_novo, sobrenome_novo, cpf_novo,
        assento_novo);

  posicao = achar_passageiro(tot_passageiros, num_passageiros, cpf_consulta);
  if (posicao == -1) {
    printf("Passageiro não encontrado\n");
    return;
  } else {
    strcpy(tot_passageiros[posicao].nome, nome_novo);
    strcpy(tot_passageiros[posicao].sobrenome, sobrenome_novo);
    strcpy(tot_passageiros[posicao].cpf, cpf_novo);
    strcpy(tot_passageiros[posicao].assento, assento_novo);
  }
  printf("Reserva Modificada:\n");
  printf_passageiro(tot_passageiros[posicao]);
  return;
}

int achar_passageiro(passageiro *tot_passageiros, int num_passageiros,
                     char *cpf) {
  /**
   * @brief      Acha um passageiro
   *
   * @details    Acha o índice de um passageiro pelo cpf
   * no vetor de passageiros. Se não achar, retorna -1.
   * Ele não retorna 0, pois o índice 0 pode ser um passageiro.
   * Ele percorre o vetor apenas uma vez, até achar. Assume-se
   * que o cpf é único.
   *
   * @param      cpf, char com o cpf do passageiro
   * @param      tot_passageiros, vetor de passageiros
   *
   * @return     int, posição do passageiro no vetor
   */

  int i;
  for (i = 0; i < num_passageiros; i++) {
    if (strcmp(tot_passageiros[i].cpf, cpf) == 0) {
      return i;
    }
  }
  return -1;
}

void consulta_passageiro(passageiro *tot_passageiros, int num_passageiros) {
  /**
   * @brief      Consulta um passageiro
   *
   * @details    Consulta um passageiro, imprimindo
   * os dados de um passageiro. Ele acha o passageiro
   * pelo cpf. Se não achar, printa que o passageiro não foi encontrado.
   *
   *
   * @param      cpf, char com o cpf do passageiro
   * @param      tot_passageiros, vetor de passageiros
   *
   * @return     void
   */

  char cpf[15];
  int posicao;
  scanf("%s", cpf);
  posicao = achar_passageiro(tot_passageiros, num_passageiros, cpf);
  if (posicao == -1) {
    printf("Passageiro não encontrado\n");
    return;
  } else {
    printf_passageiro(tot_passageiros[posicao]);
  }
}

passageiro *cancelar_reserva(passageiro *tot_passageiros, int num_passageiros) {
  /**
   * @brief      Cancela a reserva de um passageiro
   *
   * @details    Cancela a reserva de um passageiro, apagando
   * todas as informações que ele possuia. Ele acha o passageiro
   * pelo cpf. Se não achar, printa que o passageiro não foi encontrado.
   * Ele faz um realocamento do vetor de passageiros, de forma que não
   * perdemos nenhum outro passageiro. Ele retorna o vetor de passageiros, já
   * realocado e sem o passageiro que foi cancelado.
   *
   * @param      tot_passageiros, vetor de passageiros
   * @param      num_passageiros, número de passageiros
   *
   * @return     passageiro, vetor de passageiros
   */

  char cpf[15];
  int posicao;
  scanf("%s", cpf);
  posicao = achar_passageiro(tot_passageiros, num_passageiros, cpf);
  if (posicao == -1) {
    printf("Passageiro não encontrado\n");
    return tot_passageiros;
  } else {
    tot_passageiros[posicao] = tot_passageiros[num_passageiros - 1];
    num_passageiros--;
    tot_passageiros = (passageiro *)reallocate_vet(
        tot_passageiros, num_passageiros * sizeof(passageiro));
    return tot_passageiros;
  }
}

void fechamento_dia(passageiro *tot_passageiros, int num_passageiros) {
  /**
   * @brief      Fecha o dia
   *
   * @details    Fecha o dia, imprimindo todos os passageiros
   * registrados e o valor total.
   * @param      tot_passageiros, vetor de passageiros
   * @param      num_passageiros, número de passageiros
   *
   * @return     void
   */
  float total = 0; // Valor total
  printf("Fechamento do dia:\n");
  printf("Quantidade de reservas: %d\n", num_passageiros);
  for (int i = 0; i < num_passageiros; i++) {
    printf_passageiro(tot_passageiros[i]);
    total += tot_passageiros[i].preco;
  }
  printf("Posição: %.2f\n", total);
  printf_underline();
}

void fechamento_voo(passageiro *tot_passageiros, int num_passageiros) {
  /**
   * @brief      Fecha o voo
   *
   * @details    Fecha o voo, não permitindo mais a modificação
   * de reservas. Como ele é o último comando, ele também
   * libera a memória alocada para o vetor de passageiros.
   *
   * @param      tot_passageiros, vetor de passageiros
   * @param      num_passageiros, número de passageiros
   *
   * @return     void
   */
  float total = 0; // Valor total
  printf("Voo Fechado!\n");
  for (int i = 0; i < num_passageiros; i++) {
    printf_voo(tot_passageiros[i]);
    total += tot_passageiros[i].preco;
  }
  printf("Valor Total: %.2f\n", total);
  printf_underline();
  free_vet(tot_passageiros, num_passageiros);
}

void printf_underline(void) {
  /**
   * @brief      Printa underline
   *
   * @details    Printa 50 underline, para separar
   * os comandos.
   *
   * @param      void
   *
   * @return     void
   */

  for (int i = 0; i < 50; i++) {
    printf("-");
  }
  printf("\n");
  return;
}

void free_vet(passageiro *tot_passageiros, int num_passageiros) {
  /**
   * @brief      Libera a memória alocada
   *
   * @details    Libera a memória alocada para o vetor
   * de passageiros. Como esse é o único tipo de vetor
   * que alocamos, não precisamos de um ponteiro void.
   *
   * @param      tot_passageiros, vetor de passageiros
   * @param      num_passageiros, número de passageiros
   *
   * @return     void
   */

  for (int i = 0; i < num_passageiros; i++) {
    free(tot_passageiros[i].nome);
    free(tot_passageiros[i].sobrenome);
    tot_passageiros[i].nome = NULL;      // segurança
    tot_passageiros[i].sobrenome = NULL; // segurança
  }
  free(tot_passageiros);
  tot_passageiros = NULL; // segurança
  return;
}
