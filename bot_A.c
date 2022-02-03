#include <stdio.h>
#include <string.h>

#define MAX_STR 50

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w) {
  char id[MAX_STR];
  int v, n, x, y;

  // lê os dados da área de pesca
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &v);
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

  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA === 
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1) {

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w);

    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("DOWN\n");

    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
  }

  return 0;
}


// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <math.h>

// #define MAX_LINE 50

// void desalocarEspaco(int h, int w, int *mapaDados[h][w])
// {
//   for (int i = 0; i < h; i++)
//   {
//     for (int j = 0; j < w; j++)
//     {
//       free(mapaDados[i][j]);
//     }
//   }
// }

// int verificarLaterais(int xBot, int yBot, int h, int w)
// {
//   int limiteTop = 0;
//   int limiteBottom = h - 1;

//   int limiteLeft = 0;
//   int limiteRight = w - 1;

//   // configurando limites do bot
//   if (xBot == limiteTop)
//   {
//     if (yBot == limiteLeft)
//       return 8;

//     if (yBot == limiteRight)
//       return 2;

//     return 1;
//   }

//   if (xBot == limiteBottom)
//   {
//     if (yBot == limiteLeft)
//       return 6;

//     if (yBot == limiteRight)
//       return 4;

//     return 5;
//   }

//   if (yBot == limiteLeft)
//     return 7;

//   if (yBot == limiteRight)
//     return 3;

//   return 0;
// }

// void escolherDirecaoAleatoria()
// {
//   int r = rand() % 3;

//   switch (r)
//   {
//   case 0:
//     printf("UP\n");
//     break;
//   case 1:
//     printf("RIGHT\n");
//     break;
//   case 2:
//     printf("DOWN\n");
//     break;
//   case 3:
//     printf("LEFT\n");
//     break;
//   }
// }

// /* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
// void readData(int h, int w, char myId[MAX_LINE], int *mapaDados[h][w], int * xBot, int * yBot)
// {
//   char id[MAX_LINE];
//   int  n, xb, yb;

//   for (int i = 0; i < h; i++)
//   {
//     for (int j = 0; j < w; j++)
//     {
//       mapaDados[i][j] = (int *)malloc(sizeof(int *));
//       scanf("%i", mapaDados[i][j]);
//     }
//   }
//   scanf(" BOTS %i", &n); // lê a quantidade de bots
//   for (int i = 0; i < n; i++)
//   {
//     scanf("%s %i %i", id, &xb, &yb); // lê o id dos bots e suas posições
//     if(strcmp(myId, id) == 0){
//       *xBot = xb;
//       *yBot = yb;
//     }
//   }
// }

// int main()
// {
//   char line[MAX_LINE]; // dados temporários
//   char myId[MAX_LINE]; // identificador do bot em questão

//   setbuf(stdin, NULL);
//   setbuf(stdout, NULL);
//   setbuf(stderr, NULL);

//   // === INÍCIO DA PARTIDA ===
//   int h, w;
//   scanf("AREA %i %i", &h, &w); // dimensão da área de pesca: altura (h) x largura (w)
//   // readData(h, w);               // lê os dados do jogo
//   scanf(" ID %s", myId); // por fim, sabe qual seu próprio id
//   fprintf(stderr, "%s\n", myId);
//   int *mapaDados[h][w];
//   int *xBot;
//   int *yBot;

//   // === PARTIDA ===
//   while (1)
//   {
//     // Lê dados
//     readData(h, w, myId, mapaDados, xBot, yBot);

//     /*
//          1      
//    8/----------\ 2
//     |          |
//     |     0    |
//    7|          |3 
//     |          |
//    6\----------/4
//           5
//     */
//     // faz um scanner nas laterais para obter a informação de perigo e evitar multas
//     //int lateralEmPerigo = verificarLaterais(*xBot, *yBot, h, w);

//     //int range = ceil((h / 4) + 1);

//     fprintf(stderr, "(%i, %i)\n(%i, %i)", *xBot, *yBot, w, h);

//     // for (int i = 0; i < h; i++)
//     // {
//     //   for (int j = 0; j < w; j++)
//     //   {
//     //     fprintf(stderr, "%i ", *mapaDados[i][j]);
//     //   }
//     //   fprintf(stderr, "\n");
//     // }

//     // INSERIR UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

//     // envia a ação escolhida (nesse exemplo, ir para esquerda)
//     printf("LEFT\n");

//     // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
//     scanf("%s", line);
//     // fgets(line, MAX_LINE, stdin);
//   }

//   desalocarEspaco(h, w, mapaDados);
//   free(xBot);
//   free(yBot);
//   return 0;
// }