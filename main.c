/**
 Trabalho de Introdução à Ciência da Computação I
 Professor: Rudinei Goularte
 Alunos:
 Marco Túlio Mello Silva - 12548657
 Enzo Key Yamashita - 13678630
 *********************************

 O programa é um sistema de gerenciamento de voos. No caso,
 apenas 1 voo. O programa tem as seguintes funcionalidades:
  - Abertura de voo
  - Registro de passageiros
  - Consulta de reserva
  - Modificação de reserva
  - Cancelamento de reserva
  - Fechamento do dia
  - Fechamento do voo

  O programa é dividido em funções, cada uma com uma funcionalidade
  específica.

Os passageiros são chamados salvos em um arquivo chamado voos.txt.
A estrutura do arquivo é a seguinte:
  - Header: Int(0,1), Int, Int, Float, Float
     + Primeiro Int: 0 para voo fechado, 1 para voo aberto
     + Segundo Int: Número de assentos reservados
     + Terceiro Int: Número de assentos totais
     + Float: Preço da econômica
     + Float: Preço da executiva
  - Corpo: Nome, Sobrenome, CPF, Dia, Mês, Ano, Número do Voo, Assento, Classe,
           Preço, Origem, Destino
      + Passaeiros registrados, cada um em uma linha

A cada fechamento de dia, ou voo, o programa descarrega o vetor de passageiros
na memória, para o arquivo. Para isso, ele copia o header do arquivo anterior
para um arquivo temporário, que será o novo arquivo principal, e um a um
escreve os passageiros.
Essa necessidade de copiar para outro arquivo vem da função de cancelar
passageiro, para que não fique um espaço vazio no arquivo.

* O flow do programa
O programa, inicialmente checa se já existe um arquivo de voo,
sendo necessário isso para carregar os passageiros para a memória.
Se não tiver, ele entra num loop que só permite o usuário a opção
de AV. Isso é necessário para não acontecer nenhum problema de
tentar consultar um passageiro, sendo que nosso vetor nem alocado está.

Uma vez com o arquivo feito, ele carrega os passageiros para a memória.
Com o arquivo carregado, ele checa se o voo está aberto, ou seja, se
o header do arquivo é 1. Se não estiver, ele entra no loop de voo fechado
que só permite os comandos CR e FD. Caso o voo esteja aberto, ele entra
no loop de voo aberto, que permite todos os comandos.

Caso Feche o dia, ele coloca todos os passageiros no arquivo, e imprime
o total arrecadado, junto com a quantidade de passageiros alocados. Caso
feche o voo, ele também coloca todos no arquivo e imprime os dados necessários
de cada passageiro.

* Struct de Passageiro
A struct de passageiro é feito com todos os dados necessários para um
passageiro. Os nomes são alocados dinamicamente, pois não sabemos o tamanho
deles. CPF, número do voo, assento, classe, origem e destino são fixos, pois
sabemos o tamanho deles.

* Funções
- allocate_vet: Aloca um vetor de N posições. Feito de forma genérica
para poder se reutilizado mais facilmente
- reallocate_vet: Realoca um vetor de N posições. Feito de forma genérica
para poder se reutilizado mais facilmente
- opcao_menu: Recebe um comando do usuário. Função simples.
- abertura_voo: Abre o voo, escrevendo no arquivo dado pelo
argumento path[]. Ele lê a quantidade de assentos, bem como
o valor da passagem econômica e executiva, nessa ordem. Os tipos
dessas variáveis são int, float e float, respectivamente. No arquivo
ele também escreve algumas informações auxiliares.
- registrar_passageiro: Registra um passageiro no arquivo. Ele
recebe um vetor de passageiros, o número de passageiros, o path
do arquivo e a capacidade do voo. Ele aloca um novo passageiro,
caso tenha capacidade. Se não tiver capacidade, ele automaticamente
fecha o voo. Caso tenha capacidade, ele aloca estáticamente e
arbitráriamente o nome e sobrenome do passageiro e lê todos os
inputs. Uma vez lido, ele realoca o nome e sobrenome para o tamanho
correto. Ele retorna o vetor de passageiros.
- consultar_reserva: Consulta a reserva de um passageiro. Ele
recebe um vetor de passageiros e o número de passageiros. Dentro
da função ele lê o CPF do passageiro e imprime os dados do passageiro
com o CPF correspondente. Para achar o CPF, ele faz uma comparação
de strings.
- modificar_reserva: Modifica a reserva de um passageiro. Recebe
o CPF de busca e os novos campos do passageiro. Realiza a busca, uma
vez achado, faz a realocação dos nomes e sobrenomes e copia os novos
dados para o passageiro.
- cancelar_reserva: Cancela a reserva de um passageiro. Recebe o CPF
do passageiro a ser cancelado. Realiza a busca, uma vez achado, ele
copia os dados do passageiro seguinte para o passageiro atual. Realiza
essa mudança para não ficar nenhum buraco no nosso vetor.
- printf_passageiro: Printa um passageiro. Recebe um passageiro e
printa todos os dados dele. Ele é chamado em consultar reserva e
modificar reserva.
- printf_underline: Printa underline. Printa 50 underline, para
separar os comandos.
- printf_voo: Printa apenas as informações pertinentes para o voo.
Ou seja, nome, cpf e assento
- fechar_dia: Fecha o dia. Recebe um vetor de passageiros, o número
de passageiros e o path do arquivo. Ele atualiza o arquivo com o
número de passageiros, imprime os passageiros e o total arrecadado.
- checar_se_voo_existe: Checa se o voo está aberto. Recebe o path do arquivo
e retorna 1 se o voo estiver aberto, 0 se estiver fechado.
- fechamento_voo: Fecha o voo. Recebe um vetor de passageiros, o número
de passageiros e o path do arquivo. Ele atualiza o arquivo com o
número de passageiros, imprime os passageiros e o total arrecadado.
Ela modifica no header o valor que checamos para ver se o voo está
ou não aberto
- free_vet: Libera a memória alocada para o vetor de passageiros.
Especifica para o vetor de passageiros, porém, é o único que alocamos
dinâmicamente.
- carregar_lista_passgeiros: Carrega a lista de passageiros de um arquivo.
Recebe um vetor de passageiros, o path do arquivo e o número de passageiros.
Ele lê o arquivo e aloca dinamicamente os nomes e sobrenomes dos passageiros.
Ele retorna o vetor de passageiros.
- checar_voo: Checa a disponibilidade do voo. Recebe o número de passageiros
e o path do arquivo. Ele checa se o voo está aberto e se o número de passageiros
é menor que a capacidade total. Retorna 1 se o voo estiver aberto e a capacidade
não estiver excedida, 0 caso contrário.

* Variáveis
- comando: Variável que armazena o comando do usuário
- vet_passageiros: Vetor de passageiros
- num_passageiros: Número de passageiros
- flag: Variável de controle para os loops
- voo_aberto: Variável que checa se o voo está aberto
- disp_voo: Variável que checa a disponibilidade do voo
- v: Struct secundária que armazena as informações do voo,
usada apenas para facilitar a cópia de um arquivo para outro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_VOO "voos.txt"

typedef struct {
  char *nome;
  char *sobrenome;
  char cpf[15]; /* Estático pois todos tem o mesmo tamanho */
  int dia;
  int mes;
  int ano;
  char num_voo[5]; /* Estático pois todos tem o mesmo tamanho */
  char assento[4];
  char classe[10]; /* Estático pois todos tem o mesmo tamanho */
  float preco;
  char origem[4];  /* Estático pois todos tem o mesmo tamanho */
  char destino[4]; /* Estático pois todos tem o mesmo tamanho */
} passageiro;
void *allocate_vet(int N);
void *reallocate_vet(void *vet, int N);
void opcao_menu(char comando[3]);
void abertura_voo(char path[]);
passageiro *registrar_passageiro(passageiro *vet_passageiros, int N,
                                 char path[], int *disponibilidade);
void consultar_reserva(passageiro *vet_passageiros, int num_passageiros);
void modificar_reserva(passageiro *vet_passageiros, int num_passageiros);
int cancelar_reserva(passageiro *vet_passageiros, int num_passageiros);
void printf_underline(void);
void printf_voo(passageiro pass);
void printf_passageiro(passageiro pass);
passageiro *carregar_lista_passgeiros(passageiro *vet_passageiros, char path[],
                                      int *N);
void fechar_dia(passageiro *vet_passageiros, int N, char path[]);
int checar_se_voo_existe(char path[]);
void free_vet(passageiro *tot_passageiros, int num_passageiros);
void fechamento_voo(passageiro *tot_passageiros, int num_passageiros,
                    char path[]);
int checar_voo(int num_passageiros, char path[]);

int main(void) {
  char comando[3];
  passageiro *vet_passageiros;
  int num_passageiros = 0;
  int flag = 1;
  vet_passageiros = NULL;
  int voo_aberto = checar_se_voo_existe(PATH_VOO);
  /* Checa se tem um voo aberto */
  while (!voo_aberto) {
    opcao_menu(comando);
    if (strcmp(comando, "AV") == 0) {
      abertura_voo(PATH_VOO);
      voo_aberto = 1;
    }
  }
  /* Se tiver um voo aberto, carrega
    os passageiros para a memória */
  if (voo_aberto) {
    vet_passageiros =
        carregar_lista_passgeiros(vet_passageiros, PATH_VOO, &num_passageiros);
  }
  /* Checa a disponibilidade do voo. No header o voo tem que estar aberto,
    ou seja, tem que ser 1, e o num de passageiros tem que ser menor que
   a capacidade total */
  int disp_voo = checar_voo(num_passageiros, PATH_VOO);
  /* Se o voo estiver fechado, ele fecha o voo e imprime os passageiros
    e o total arrecadado. Ele só tem a disponibilidade de CR e FD */
  if (disp_voo == 0) {
    fechamento_voo(vet_passageiros, num_passageiros, PATH_VOO);
    flag = 1;
    while (flag) {
      opcao_menu(comando);
      if (strcmp(comando, "CR") == 0) {
        consultar_reserva(vet_passageiros, num_passageiros);
      } else if (strcmp(comando, "FD") == 0) {
        fechar_dia(vet_passageiros, num_passageiros, PATH_VOO);
        flag = 0;
      }
    }
  }
  /* Se o voo estiver aberto, ele tem todas as opções */
  while (flag && voo_aberto && disp_voo) {
    opcao_menu(comando);
    if (strcmp(comando, "RR") == 0) {
      vet_passageiros = registrar_passageiro(vet_passageiros, num_passageiros,
                                             PATH_VOO, &disp_voo);
      num_passageiros++;
    } else if (strcmp(comando, "CR") == 0) {
      consultar_reserva(vet_passageiros, num_passageiros);
    } else if (strcmp(comando, "MR") == 0) {
      modificar_reserva(vet_passageiros, num_passageiros);
    } else if (strcmp(comando, "FD") == 0) {
      fechar_dia(vet_passageiros, num_passageiros, PATH_VOO);
      flag = 0;
    } else if (strcmp(comando, "CA") == 00) {
      num_passageiros = cancelar_reserva(vet_passageiros, num_passageiros);
    } else if (strcmp(comando, "FV") == 0) {
      fechamento_voo(vet_passageiros, num_passageiros, PATH_VOO);
      flag = 0;
      free_vet(vet_passageiros, num_passageiros);
    }
  }
  return 0;
}

void *allocate_vet(int N) {

  /**
   * @brief      Alocação de memória
   *
   * @details    Recebe N, que é o número de
   * bytes que queremos alocar. Ele aloca
   * a memória, caso tenha alocado com sucesso
   * retorna o vetor, se não, retorna um erro
   *
   * @param      int N  Número de bytes
   *
   * @return     void*  Vetor alocado
   */

  void *vet = (void *)malloc(N);
  if (vet == NULL) {
    printf("Erro ao alocar memória\n");
    exit(1);
  }
  return vet;
}

void *reallocate_vet(void *vet, int N) {

  /**
   * @brief      Realocação de Vet
   *
   * @details    Realiza a realocão de um vetor
   * void *vet para N bytes. Caso tenha realocado
   * com sucesso, retorna o vetor, se não, retorna
   * um erro
   *
   * @param      void *vet  vetor que vamos realocar
   * @param      int N      Número de bytes
   *
   * @return     void *vet_aux  Vetor realocado
   */

  void *vet_aux = (void *)realloc(vet, N);
  if (vet_aux == NULL) {
    printf("Erro ao realocar memória\n");
    exit(1);
  }
  return vet_aux;
}

void opcao_menu(char comando[3]) {

  /**
   * @brief      Captura a entrada do usuário
   *
   * @details    Lê a entrada do usuário e coloca esse
   * valor no argumento passado.
   *
   * @param      char comando[3]  Vetor que vamos colocar
   * a entrada do usuário
   *
   * @return     void
   */

  scanf("%s", comando);
}

void abertura_voo(char path[]) {

  /**
   * @brief      Realiza a abertura de umvoo
   *
   * @details    Abre o voo, escrevendo na primeira linha
   * do arquivo com nome path[], informações dadas pelo usuário,
   * que são o número de assentos, o valor da classe econômica e
   * executiva. Ele escreve no arquivo, o número 1, que é para
   * indicar que o voo está aberto e 0, sendo a quantidade alocada de
   * assentos
   *
   * @param      char path[]  Nome do arquivo
   *
   * @return     void
   */

  FILE *arq;
  arq = fopen(path, "w");
  int assentos;
  float preco_eco, preco_exec;
  scanf("%d %f %f", &assentos, &preco_eco, &preco_exec);
  fprintf(arq, "%d %d %d %.2f %.2f\n", 1, 0, assentos, preco_eco, preco_exec);
  /* Esse 1 é para voo aberto */
  /* Esse 0 a mais vai ser a quantidade de assentos vendidos no dia.
   *Vamos modificar ela só no fechamendo do dia. A cada novo dia,
   *vamos pegar o valor de lá.*/
  fclose(arq);
}

passageiro *registrar_passageiro(passageiro *vet_passageiros, int N,
                                 char path[], int *disponibilidade) {

  /**
   * @brief      Registra um passageiro para o voo
   *
   * @details    Realiza o registro do passageiro para o voo.
   * Ele lê os dados do passageiro e aloca dinamicamente o nome
   * e sobrenome do passageiro. Antes de alocar, é checado se
   * o voo permite mais passageiros. Caso não, ele fecha automaticamente
   * o voo. Caso permita, ele lê inputs do usuário e coloca em uma
   * nova instância dentro do *vet_passageiros. Ele retorna o vetor
   * com o novo passageiro
   *
   * @param      passageiro *vet_passageiros Vetor de passageiros naquele voo
   * @param      int N                      Número de passageiros
   * @param      char path[]                Nome do arquivo
   * @param      int *disponibilidade       Disponibilidade do voo
   *
   * @return     passageiro *
   */

  *disponibilidade = checar_voo(N, PATH_VOO);
  if (*disponibilidade == 0) {
    fechamento_voo(vet_passageiros, N, PATH_VOO);
    free_vet(vet_passageiros, N);
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
    vet_passageiros[N].nome =
        (char *)reallocate_vet(/* Realocação para o tamanho certo */
                               vet_passageiros[N].nome,
                               strlen(vet_passageiros[N].nome) + 1);
    vet_passageiros[N].sobrenome = (char *)reallocate_vet(
        vet_passageiros[N].sobrenome, strlen(vet_passageiros[N].sobrenome) + 1);
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

  for (indice = 0; indice < num_passageiros; indice++) {
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
  printf("Reserva Modificada:\n");
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
  fseek(arq, 2, SEEK_SET);
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
  typedef struct {
    int aberto;
    int vendidos;
    int ass_totais;
    float econo;
    float exec;
  } voo;
  voo v; /* Struct auxiliar para fazer a cópia */
  FILE *arq, *tmp;
  tmp = fopen(path, "r+"); /* Vamos copiar do arquivo original */
  arq = fopen("tmp", "w"); /* para um arquivo temporário, que depois virará
                             o original */
  fscanf(tmp, "%d %d %d %f %f", &v.aberto, &v.vendidos, &v.ass_totais, &v.econo,
         &v.exec);
  fclose(tmp);
  fprintf(arq, "%d %d %d %.2f %.2f", v.aberto, v.vendidos, v.ass_totais,
          v.econo, v.exec);
  fseek(arq, 2, SEEK_SET); /* Pula a flag se o voo ta aberto ou não */
  fprintf(arq, "%d", N);   /* Pega o número de passageiros */
  fclose(arq);
  rename("tmp", path);
  arq = fopen(path, "a+");
  fprintf(arq, "\n");

  float total = 0;
  for (int i = 0; i < N; i++) {
    fprintf(arq, "%s %s %s %d %d %d %s %s %s %.2f %s %s\n",
            vet_passageiros[i].nome, vet_passageiros[i].sobrenome,
            vet_passageiros[i].cpf, vet_passageiros[i].dia,
            vet_passageiros[i].mes, vet_passageiros[i].ano,
            vet_passageiros[i].num_voo, vet_passageiros[i].assento,
            vet_passageiros[i].classe, vet_passageiros[i].preco,
            vet_passageiros[i].origem, vet_passageiros[i].destino);
    total += vet_passageiros[i].preco;
  }
  printf("Fechamento do dia:\n");
  printf("Quantidade de reservas: %d\n", N);
  printf("Posição: %.2f\n", total);
  printf_underline();
  fclose(arq);
  free_vet(vet_passageiros, N);
  return;
}

int checar_se_voo_existe(char path[]) {
  /**
   * @brief      Checa se o voo está disponível
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
    fclose(arq);
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
  typedef struct {
    int aberto;
    int vendidos;
    int ass_totais;
    float econo;
    float exec;
  } voo;
  voo v; /* Similar à função de fechar dia */
  FILE *arq, *tmp;
  tmp = fopen(path, "r+");
  arq = fopen("tmp", "w");
  fscanf(tmp, "%d %d %d %f %f", &v.aberto, &v.vendidos, &v.ass_totais, &v.econo,
         &v.exec);
  v.aberto = 0;
  fclose(tmp);
  fprintf(arq, "%d %d %d %.2f %.2f", v.aberto, v.vendidos, v.ass_totais,
          v.econo, v.exec);
  fseek(arq, 0, SEEK_SET);
  fseek(arq, 2, SEEK_SET);
  fprintf(arq, "%d", N);
  fclose(arq);
  rename("tmp", path);
  arq = fopen(path, "a+");
  fprintf(arq, "\n");
  float total = 0; // Valor total
  printf("Voo Fechado!\n\n");
  for (int i = 0; i < N; i++) {
    fprintf(arq, "%s %s %s %d %d %d %s %s %s %.2f %s %s\n",
            tot_passageiros[i].nome, tot_passageiros[i].sobrenome,
            tot_passageiros[i].cpf, tot_passageiros[i].dia,
            tot_passageiros[i].mes, tot_passageiros[i].ano,
            tot_passageiros[i].num_voo, tot_passageiros[i].assento,
            tot_passageiros[i].classe, tot_passageiros[i].preco,
            tot_passageiros[i].origem, tot_passageiros[i].destino);
    printf_voo(tot_passageiros[i]);
    printf("\n");
    total += tot_passageiros[i].preco;
  }
  printf("Valor Total: %.2f\n", total);
  printf_underline();
  fclose(arq);
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

int checar_voo(int num_passageiros, char path[]) {

  /**
   * @brief      Checa se o voo esta disponível
   *
   * @details    Checa se a flag do voo está disponível
   * e se existe espaço ou não para registrar mais passageiros
   *
   * @param      int num_passageiros número atual de passageiros
   * @param      char path[] nome do aquivo
   * @return     int 1 se ok, 0 se não
   */

  FILE *arq;
  int capacidade_total;
  int flag = 0;
  arq = fopen(path, "r+");
  fscanf(arq, "%d", &flag); /* ignora o primeiro valor
                             *que no nosso caso é o número
                             *já alocado */
  if (!flag) {
    return flag;
  }
  fscanf(arq, "%*d");
  fscanf(arq, "%d", &capacidade_total);
  fclose(arq);
  if (num_passageiros >= capacidade_total) {
    return 0;
  } else {
    return 1;
  }
}
