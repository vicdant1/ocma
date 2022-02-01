#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 50

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int ** mapaDados) {
  char id[MAX_STR];
  int n, x, y;

  // lê os dados da área de pesca
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &mapaDados[i][j]);
    }
  }
  
  // lê os dados dos bots
  scanf(" BOTS %i", &n);
  // o " " antes de BOTS é necessário para ler o '\n' da linha anterior
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", id, &x, &y);
  }
}

int main() {
  char line[MAX_STR];   // dados temporários
  char myId[MAX_STR];   // identificador do bot em questão

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  int h, w;
  scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", myId);        // ...e o id do bot
  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior
  int** mapaDados = (int *) malloc(sizeof(int) * h);
  for(int i=0; i < w; i++)
      mapaDados[i] = malloc(sizeof(int) * w);

  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA === 
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1) {

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w, mapaDados);

    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("LEFT\n");

    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
  }

  return 0;
}