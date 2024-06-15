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
  char classe[10]; // 0 para econômica e 1 para executiva
  float preco;
  char origem[4];  // aeroporto de origem
  char destino[4]; // aeroporto de destino
} passageiro;
void *allocate_vet(int N);
void *reallocate_vet(void *vet, int N);
void opcao_menu(char comando[3]);
void abertura_voo();
passageiro *registrar_passageiro(passageiro *vet_passageiros, int N,
                                 char path[], int *capacidade);
void consultar_reserva(passageiro *vet_passageiros, int num_passageiros);
void modificar_reserva(passageiro *vet_passageiros, int num_passageiros);
int cancelar_reserva(passageiro *vet_passageiros, int num_passageiros);
void printf_underline(void);
void printf_voo(passageiro pass);
void printf_passageiro(passageiro pass);
passageiro *carregar_lista_passgeiros(passageiro *vet_passageiros, char path[],
                                      int *N);
void fechar_dia(passageiro *vet_passageiros, int N, char path[]);
int checar_se_voo_aberto(char path[]);
void free_vet(passageiro *tot_passageiros, int num_passageiros);
void fechamento_voo(passageiro *tot_passageiros, int num_passageiros,
                    char path[]);
int checar_capacidade(int num_passageiros, char path[]);

int main(void) {
  char comando[3];
  passageiro *vet_passageiros;
  int num_passageiros = 0;
  int flag = 1;
  vet_passageiros = (passageiro *)allocate_vet(0);
  int voo_aberto = checar_se_voo_aberto(PATH_VOO);
  while (!voo_aberto) {
    opcao_menu(comando);
    if (strcmp(comando, "AV") == 0) {
      abertura_voo();
      voo_aberto = 1;
    }
  }
  if (voo_aberto) {
    vet_passageiros =
        carregar_lista_passgeiros(vet_passageiros, PATH_VOO, &num_passageiros);
  }
  int capacidade = checar_capacidade(num_passageiros, PATH_VOO);
  if (capacidade == 0) {
    fechamento_voo(vet_passageiros, num_passageiros, PATH_VOO);
    flag = 1;
    while (flag) {
      if (strcmp(comando, "CR") == 0) {
        consultar_reserva(vet_passageiros, num_passageiros);
      } else if (strcmp(comando, "FD") == 0) {
        fechar_dia(vet_passageiros, num_passageiros, PATH_VOO);
        flag = 0;
      }
    }
  }
  while (flag && voo_aberto && capacidade) {
    opcao_menu(comando);
    if (strcmp(comando, "RR") == 0) {
      vet_passageiros = registrar_passageiro(vet_passageiros, num_passageiros,
                                             PATH_VOO, &capacidade);
      num_passageiros++; /* Pensar se vale mais a pena colocar a flag aqui
                          *também ou se é melhor fazer como na main antiga */
    } else if (strcmp(comando, "CR") == 0) {
      consultar_reserva(vet_passageiros, num_passageiros);
    } else if (strcmp(comando, "MR") == 0) {
      modificar_reserva(vet_passageiros, num_passageiros);
    } else if (strcmp(comando, "FD") == 0) {
      fechar_dia(vet_passageiros, num_passageiros, PATH_VOO);
      flag = 0;
    }
  }
  return 0;
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

void opcao_menu(char comando[3]) { scanf("%s", comando); }

void abertura_voo() {
  FILE *arq;
  arq = fopen(PATH_VOO, "w");
  int assentos;
  float preco_eco, preco_exec;
  scanf("%d %f %f", &assentos, &preco_eco, &preco_exec);
  fprintf(arq, "%d %d %.2f %.2f\n", 0, assentos, preco_eco, preco_exec);
  /* Esse 0 a mais vai ser a quantidade de assentos vendidos no dia.
   *Vamos modificar ela só no fechamendo do dia. A cada novo dia,
   *vamos pegar o valor de lá.*/
  fclose(arq);
}

passageiro *registrar_passageiro(passageiro *vet_passageiros, int N,
                                 char path[], int *capacidade) {
  FILE *arq;
  arq = fopen(path, "a+");
  *capacidade = checar_capacidade(N, PATH_VOO);
  if (*capacidade == 0) {
    fechamento_voo(vet_passageiros, N, PATH_VOO);
    return vet_passageiros;
  } else {
    vet_passageiros = (passageiro *)reallocate_vet(
        vet_passageiros, (N + 1) * sizeof(passageiro));
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
}

void consultar_reserva(passageiro *vet_passageiros, int num_passageiros) {
  /**
   * @brief      Consulta a reserva por CPF e imprime os dados na tela
   *
   * @details    A partir do CPF digitado, busca o passageiro correspondente
   *             na struct e chama a função printf_passageiro para exibir
   *             os dados na tela
   *
   * @param      passageiro *vet_passageiros
   * @param      int num_passageiros
   *
   * @return     void
   */
  int indice = 0; // Incremento conforme o passageiro não corresponde ao CPF
  char cpf_consultado[15];

  scanf("%s", cpf_consultado);

  for (; indice < num_passageiros; indice++) {
    if (strcmp(cpf_consultado, vet_passageiros[indice].cpf) == 0) {
      printf_passageiro(vet_passageiros[indice]);
      break;
    }
  }
}

void modificar_reserva(passageiro *vet_passageiros, int num_passageiros) {
  /**
   * @brief      Modifica a reserva por CPF e imprime os dados na tela
   *
   * @details    Recebe do usuário o CPF consultado e os novos dados na forma
   *             "CPF_consultado nome sobrenome CPF assento>"
   *             A partir do CPF digitado, busca o passageiro correspondente
   *             na struct e modifica seus dados
   *             Ao final, chama a função printf_passageiro para exibir os
   *             novos dados na tela
   *
   * @param      passageiro *vet_passageiros
   * @param      int num_passageiros
   *
   * @return     void
   */
  int indice = 0; // Incremento conforme o passageiro não corresponde ao CPF
  char cpf_consultado[15];

  scanf("%s", cpf_consultado);
  for (; indice < num_passageiros; indice++) {
    if (strcmp(cpf_consultado, vet_passageiros[indice].cpf) == 0) {
      break;
    }
  }

  // Realocação (não se sabe o tamanho do novo nome e/ou sobrenome)
  vet_passageiros[indice].nome =
      reallocate_vet(vet_passageiros[indice].nome, 50);
  vet_passageiros[indice].sobrenome =
      reallocate_vet(vet_passageiros[indice].sobrenome, 50);

  scanf("%s %s %s %s", vet_passageiros[indice].nome,
        vet_passageiros[indice].sobrenome, vet_passageiros[indice].cpf,
        vet_passageiros[indice].assento);

  // Realocação
  vet_passageiros[indice].nome = reallocate_vet(
      vet_passageiros[indice].nome, strlen(vet_passageiros[indice].nome) + 1);
  vet_passageiros[indice].sobrenome =
      reallocate_vet(vet_passageiros[indice].sobrenome,
                     strlen(vet_passageiros[indice].sobrenome) + 1);

  // Imprime os novos dados
  printf("Reserva modificada:\n");
  printf_passageiro(vet_passageiros[indice]);
}

int cancelar_reserva(passageiro *vet_passageiros, int num_passageiros) {
  /*
   * @brief      Cancela a reserva por CPF
   *
   * @details    Através do CPF digitado, busca o passageiro correspondente
   *             e obtém seu índice em vet_passageiros
   *             A partir do passageiro cancelado até e incluindo o penúltimo
   *             passageiro, copia os dados do passageiro seguinte para o
   *             passageiro atual. Os dados universais para o vôo são
   *             ignorados
   *             Por fim, reduz o nº de passageiros em 1 e retorna para main
   *
   * @param      passageiro *vet_passageiros
   * @param      int num_passageiros
   *
   * @return     num_passageiros - 1
   */
  int indice = 0; // Incremento conforme o passageiro não corresponde ao CPF
  char cpf_consultado[15];

  scanf("%s", cpf_consultado);
  for (; indice < num_passageiros; indice++) {
    if (strcmp(cpf_consultado, vet_passageiros[indice].cpf) == 0) {
      break;
    }
  }

  for (int i = indice; i < num_passageiros - 1; i++) {
    /* Realoca os nome e sobrenome do passageiro i em função do tamanho
    dos nome e sobrenome do passageiro i+1 */
    vet_passageiros[i].nome = (char *)reallocate_vet(
        vet_passageiros[i + 1].nome, strlen(vet_passageiros[i + 1].nome) + 1);
    vet_passageiros[i].sobrenome =
        (char *)reallocate_vet(vet_passageiros[i].sobrenome,
                               strlen(vet_passageiros[i + 1].sobrenome) + 1);

    // Copia os dados do passageiro i+1 para o passageiro i
    strcpy(vet_passageiros[i].nome, vet_passageiros[i + 1].nome);
    strcpy(vet_passageiros[i].sobrenome, vet_passageiros[i + 1].sobrenome);
    strcpy(vet_passageiros[i].cpf, vet_passageiros[i + 1].cpf);
    strcpy(vet_passageiros[i].assento, vet_passageiros[i + 1].assento);
    strcpy(vet_passageiros[i].classe, vet_passageiros[i + 1].classe);
    vet_passageiros[i].preco = vet_passageiros[i + 1].preco;
  }

  return (num_passageiros - 1);
}

passageiro *carregar_lista_passgeiros(passageiro *vet_passageiros, char path[],
                                      int *N) {
  /**
   * @brief      Carrega a lista de passageiros de um arquivo
   *
   * @details    Recebe um vetor de passageiros e um caminho para um arquivo
   *            que contém informações de passageiros. O arquivo deve estar
   *            no formato:
   *            nome sobrenome cpf dia mes ano num_voo assento classe preco
   *            origem destino
   *             O vetor de passageiros é alocado dinamicamente e retornado
   *            para o usuário.
   *
   * @param      passageiro *vet_passageiros  Vetor de passageiros
   * @param      path  Caminho para o arquivo
   * @param      N     Número de passageiros
   *
   * @return     *passageiro Vetor de passageiros
   */
  FILE *arq;
  arq = fopen(path, "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo\n");
    exit(1);
  }
  fscanf(arq, "%d", N); // Lê o número de passageiros
  vet_passageiros = (passageiro *)allocate_vet(*N * sizeof(passageiro));
  fscanf(arq, "%*[^\n]"); // Ignora a primeira linha
  for (int i = 0; i < *N; i++) {
    vet_passageiros[i].nome = (char *)allocate_vet(50);
    vet_passageiros[i].sobrenome = (char *)allocate_vet(50);
    fscanf(arq, "%s %s %s %d %d %d %s %s %s %f %s %s", vet_passageiros[i].nome,
           vet_passageiros[i].sobrenome, vet_passageiros[i].cpf,
           &vet_passageiros[i].dia, &vet_passageiros[i].mes,
           &vet_passageiros[i].ano, vet_passageiros[i].num_voo,
           vet_passageiros[i].assento, vet_passageiros[i].classe,
           &vet_passageiros[i].preco, vet_passageiros[i].origem,
           vet_passageiros[i].destino);
    vet_passageiros[i].nome = (char *)reallocate_vet(
        vet_passageiros[i].nome, strlen(vet_passageiros[i].nome) + 1);
    vet_passageiros[i].sobrenome = (char *)reallocate_vet(
        vet_passageiros[i].sobrenome, strlen(vet_passageiros[i].sobrenome) + 1);
  }

  fclose(arq);
  return vet_passageiros;
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
  printf("Classe: %s\n", pass.classe);
  printf("Trecho: %s %s\n", pass.origem, pass.destino);
  printf("Valor: %.2f\n", pass.preco);
  printf_underline();
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
  printf_underline();
  return;
}

void fechar_dia(passageiro *vet_passageiros, int N, char path[]) {
  /**
   * @brief      Fecha o dia
   *
   * @details    Recebe um vetor de passageiros e o número
   * de passageiros, e fecha o dia, imprimindo os passageiros
   * e o total arrecadado. Ademais, ele atualiza o arquivo
   * de voos, colocando o número de passageiros no início
   * do arquivo.
   *
   * @param      passageiro *vet_passageiros, vetor de passageiros
   * @param      int N, número de passageiros
   *
   * @return     void, apenas imprime
   */
  FILE *arq;
  arq = fopen(path, "r+");
  fseek(arq, 0, SEEK_SET);
  fprintf(arq, "%d", N);
  fclose(arq);

  float total = 0;
  for (int i = 0; i < N; i++) {
    printf_voo(vet_passageiros[i]);
    total += vet_passageiros[i].preco;
  }
  printf("Total arrecadado: %.2f\n", total);
  free_vet((void *)vet_passageiros, N);
  return;
}

int checar_se_voo_aberto(char path[]) {
  /**
   * @brief      Checa se o voo está aberto
   *
   * @details    Abre o arquivo de voos e checa se o voo
   * está aberto ou fechado. Se estiver aberto, retorna 1,
   * se estiver fechado, retorna 0.
   *
   * @param      void
   *
   * @return     int, 1 para aberto, 0 para fechado
   */
  FILE *arq;
  int flag;
  arq = fopen(path, "r");
  if (arq == NULL) {
    flag = 0;
  } else {
    flag = 1;
  }
  return flag;
}

void fechamento_voo(passageiro *tot_passageiros, int N, char path[]) {
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
  FILE *arq;
  arq = fopen(path, "r+");
  fseek(arq, 0, SEEK_SET);
  fprintf(arq, "%d", N);
  fclose(arq);
  float total = 0; // Valor total
  printf("Voo Fechado!\n");
  for (int i = 0; i < N; i++) {
    printf_voo(tot_passageiros[i]);
    total += tot_passageiros[i].preco;
  }
  printf("Valor Total: %.2f\n", total);
  printf_underline();
  free_vet(tot_passageiros, N);
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

int checar_capacidade(int num_passageiros, char path[]) {
  FILE *arq;
  int capacidade_total;
  arq = fopen(path, "r+");
  fscanf(arq, "%*d"); /* ignora o primeiro valor
                       *que no nosso caso é o número
                       *já alocado */
  fscanf(arq, "%d", &capacidade_total);
  if (num_passageiros >= capacidade_total) {
    return 0;
  } else {
    return 1;
  }
}
