#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 50

typedef struct Porto{
  int xPorto;
  int yPorto;
}Porto;

typedef struct Barco{
  int xBot;
  int yBot;
  int kg;
}Barco;

void peixeMaisProximo(int ** mapaDados, int * yPeixe, int * xPeixe, int yBot, int xBot){
while(yPeixe==-1 || xPeixe==-1){
//IF POSIÇÃO ATUAL DO BOT TIVER PEIXE NA POSIÇÃO DA MATRIZ, PASSA ATUAL
  
}
}

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int ** mapaDados, int * xBot, int * yBot, char myId[MAX_STR], int * yPeixe, int * xPeixe) {
  char id[MAX_STR];
  int n, x, y;

  // lê os dados da área de pesca
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &mapaDados[i][j]);

      //ELIMINA PEIXES NÃO PESCÁVEIS
      if(mapaDados[i][j]==11 ||mapaDados[i][j]==21 ||mapaDados[i][j]==31){
        mapaDados[i][j] = 0;
      }
      //VERIFICA POSIÇÃO DO PORTO
      if(mapaDados[i][j] == 1){
        //CRIAR MATRIZ DE PORTOS E ADICIONAR O PORTO
      }

    }
  }
  // lê os dados dos bots
  scanf(" BOTS %i", &n);
  // o " " antes de BOTS é necessário para ler o '\n' da linha anterior
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", id, &x, &y);
    if(strcmp(myId, id) == 0){
      *xBot = x;
      *yBot = y;
      peixeMaisProximo(mapaDados, &yPeixe, &xPeixe, y, x);
      //VERIFICAR PEIXE MAIS PRÓXIMO CHAMA FUNÇÃO ATÉ ACHAR UMA COORDENADA
    }
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
  int ** mapaDados = (int **) malloc(sizeof(int *) * h);
  for(int i=0; i<w; i++)
    mapaDados[i] = malloc(sizeof(int) * w);


  //CRIAR OBJETO DE BARCO E PASSA A MEMORIA
  int xBot;
  int yBot;

  int xPeixe = -1;
  int yPeixe = -1;


  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA === 
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1) {

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w, mapaDados, &xBot, &yBot, myId, &xPeixe, &yPeixe);

    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("RIGHT\n");
    printf("UP\n");
    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
  }

  return 0;
}