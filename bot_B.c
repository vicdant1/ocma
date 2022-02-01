#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE 50

void desalocarEspaco(int h, int w, int *mapaDados[h][w])
{
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      free(mapaDados[i][j]);
    }
  }
}

int verificarLaterais(int xBot, int yBot, int h, int w)
{
  int limiteTop = 0;
  int limiteBottom = h - 1;

  int limiteLeft = 0;
  int limiteRight = w - 1;

  // configurando limites do bot
  if (xBot == limiteTop)
  {
    if (yBot == limiteLeft)
      return 8;

    if (yBot == limiteRight)
      return 2;

    return 1;
  }

  if (xBot == limiteBottom)
  {
    if (yBot == limiteLeft)
      return 6;

    if (yBot == limiteRight)
      return 4;

    return 5;
  }

  if (yBot == limiteLeft)
    return 7;

  if (yBot == limiteRight)
    return 3;

  return 0;
}

void escolherDirecaoAleatoria()
{
  int r = rand() % 3;

  switch (r)
  {
  case 0:
    printf("UP\n");
    break;
  case 1:
    printf("RIGHT\n");
    break;
  case 2:
    printf("DOWN\n");
    break;
  case 3:
    printf("LEFT\n");
    break;
  }
}

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int *mapaDados[h][w], int *xBot, int *yBot)
{
  char id[MAX_LINE];
  int n;

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      mapaDados[i][j] = (int *)malloc(sizeof(int *));
      scanf("%i", mapaDados[i][j]);
    }
  }
  scanf(" BOTS %i", &n); // lê a quantidade de bots
  for (int i = 0; i < n; i++)
  {
    scanf("%s %i %i", id, xBot, yBot); // lê o id dos bots e suas posições
  }
}

int main()
{
  char line[MAX_LINE]; // dados temporários
  char myId[MAX_LINE]; // identificador do bot em questão

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  int h, w;
  scanf("AREA %i %i", &h, &w); // dimensão da área de pesca: altura (h) x largura (w)
  // readData(h, w);               // lê os dados do jogo
  scanf(" ID %s", myId); // por fim, sabe qual seu próprio id
  fprintf(stderr, "%s\n", myId);
  int *mapaDados[h][w];
  int *xBot;
  int *yBot;

  // === PARTIDA ===
  while (1)
  {
    // Lê dados
    readData(h, w, mapaDados, xBot, yBot);

    /*
         1      
   8/----------\ 2
    |          |
    |     0    |
   7|          |3 
    |          |
   6\----------/4
          5
    */
    // faz um scanner nas laterais para obter a informação de perigo e evitar multas
    int lateralEmPerigo = verificarLaterais(*xBot, *yBot, h, w);

    int range = ceil((h / 4) + 1);

    fprintf(stderr, "(%i, %i)\n(%i, %i)", *xBot, *yBot, w, h);

    // for (int i = 0; i < h; i++)
    // {
    //   for (int j = 0; j < w; j++)
    //   {
    //     fprintf(stderr, "%i ", *mapaDados[i][j]);
    //   }
    //   fprintf(stderr, "\n");
    // }

    // INSERIR UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("LEFT\n");

    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
    // fgets(line, MAX_LINE, stdin);
  }

  desalocarEspaco(h, w, mapaDados);
  free(xBot);
  free(yBot);
  return 0;
}