#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STR 50
#define MAX_PRT 25
#define MAX_WEIGHT 10

typedef struct Porto
{
  int xPorto;
  int yPorto;
} Porto;

typedef struct Barco
{
  char id[MAX_STR];
  int xBot;
  int yBot;
  int pesoAtual;

  int xPortoProximo;
  int yPortoProximo;

  int xPeixeProximo;
  int yPeixeProximo;

} Barco;

void desalocarMemoria(int **mapaDados, int w){
  for (int i = 0; i < w; i++) {
    free(mapaDados[i]);
  }
  free(mapaDados);
}

void movimentaCima(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Andou Cima \n");
  fclose(fp);

  printf("UP\n");
}

void movimentaBaixo(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Andou Baixo \n");
  fclose(fp);

  printf("DOWN\n");
}

void movimentaDireita(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Andou Direita \n");
  fclose(fp);

  printf("RIGHT\n");
}

void movimentaEsquerda(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Andou Esquerda \n");
  fclose(fp);

  printf("LEFT\n");
}

void cmdPescar(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Pescou \n");
  fclose(fp);

  printf("FISH\n");
}

void cmdVender(Barco *meuBarco)
{
  FILE *fp = fopen("LogBots.txt", "a");
  fprintf(fp, "\nBot A Vendeu \n");
  fclose(fp);

  printf("SELL\n");
}

void moverX(Barco meuBarco, bool pescar)
{
  if (pescar)
  {
    if (meuBarco.xBot < meuBarco.xPeixeProximo)
    {
      movimentaDireita(&meuBarco);
    }
    else
    {
      movimentaEsquerda(&meuBarco);
    }
  }
  else
  {
    if (meuBarco.xBot < meuBarco.xPortoProximo)
    {
      movimentaDireita(&meuBarco);
    }
    else
    {
      movimentaEsquerda(&meuBarco);
    }
  }
}

void moverY(Barco meuBarco, bool pescar)
{
  if (pescar)
  {
    if (meuBarco.yBot < meuBarco.yPeixeProximo)
    {
      movimentaBaixo(&meuBarco);
    }
    else
    {
      movimentaCima(&meuBarco);
    }
  }
  else
  {
    if (meuBarco.yBot < meuBarco.yPortoProximo)
    {
      movimentaBaixo(&meuBarco);
    }
    else
    {
      movimentaCima(&meuBarco);
    }
  }
}

void executarProximaAcao(Barco *meuBarco, int **mapaDados, bool *pescar)
{
  if (*pescar && meuBarco->pesoAtual < 10)
  {
    if (meuBarco->xBot != meuBarco->xPeixeProximo)
    {
      moverX(*meuBarco, *pescar);
    }
    else if (meuBarco->yBot != meuBarco->yPeixeProximo)
    {
      moverY(*meuBarco, *pescar);
    }
    else
    {
      cmdPescar(meuBarco);
      meuBarco->pesoAtual++;
      if (meuBarco->pesoAtual == 10)
      {
        *pescar = false;
        meuBarco->xPeixeProximo = -1;
        meuBarco->yPeixeProximo = -1;
      }
    }
  }
  else
  {
    if (meuBarco->xBot != meuBarco->xPortoProximo)
    {
      moverX(*meuBarco, *pescar);
    }
    else if (meuBarco->yBot != meuBarco->yPortoProximo)
    {
      moverY(*meuBarco, *pescar);
    }
    else
    {
      cmdVender(meuBarco);
      meuBarco->pesoAtual = 0;
      *pescar = true;
    }
  }
}

void calcularPortoMaisProximo(Barco *meuBarco, Porto *Portos, int numeroPortos)
{
  int xDiff = 0;
  int yDiff = 0;
  int totalDiff = 0;
  int index = 0;

  for (int i = 0; i < numeroPortos; i++)
  {
    if (i == 0)
    {
      xDiff = abs(Portos[i].xPorto - meuBarco->xBot);
      yDiff = abs(Portos[i].yPorto - meuBarco->yBot);
      index = i;
      totalDiff = xDiff + yDiff;
    }
    else
    {
      int totalDiffAux = 0;

      totalDiffAux = abs(Portos[i].xPorto - meuBarco->xBot) + abs(Portos[i].yPorto - meuBarco->yBot);

      if (totalDiffAux < totalDiff)
      {
        index = i;
        totalDiff = totalDiffAux;
      }
    }
  }

  meuBarco->xPortoProximo = Portos[index].xPorto;
  meuBarco->yPortoProximo = Portos[index].yPorto;
}

bool temPeixe(int **mapaDados, int xAlvo, int yAlvo)
{
  int conteudoPosicaoAtualBot = mapaDados[yAlvo][xAlvo];

  if (conteudoPosicaoAtualBot > 11 && conteudoPosicaoAtualBot < 40)
  {
    return true;
  }

  return false;
}

void peixeMaisProximo(int **mapaDados, Barco *meuBarco, int h, int w)
{
  bool nasceuEncimaDePeixe = temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot);
  meuBarco->xPeixeProximo = -1;
  meuBarco->yPeixeProximo = -1;

  int count = 1;
  int rangeX = w - 1;
  int rangeY = h - 1;

  if (nasceuEncimaDePeixe && temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot))
  {
    meuBarco->xPeixeProximo = meuBarco->xBot;
    meuBarco->yPeixeProximo = meuBarco->yBot;
    return;
  }
  else
  {
    while (meuBarco->yPeixeProximo == -1 || meuBarco->xPeixeProximo == -1)
    {
      if (!(meuBarco->yBot - count < 0 || meuBarco->yBot - count > rangeY))
      {
        if (temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot - count))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot;
          meuBarco->yPeixeProximo = meuBarco->yBot - count;

          return;
        }
      }
      if (!(meuBarco->xBot + count < 0 || meuBarco->xBot + count > rangeX))
      {
        if (temPeixe(mapaDados, meuBarco->xBot + count, meuBarco->yBot))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot + count;
          meuBarco->yPeixeProximo = meuBarco->yBot;

          return;
        }
      }
      if (!(meuBarco->yBot + count < 0 || meuBarco->yBot + count > rangeY))
      {
        if (temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot + count))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot;
          meuBarco->yPeixeProximo = meuBarco->yBot + count;

          return;
        }
      }
      if (!(meuBarco->xBot - count < 0 || meuBarco->xBot - count > rangeX))
      {
        if (temPeixe(mapaDados, meuBarco->xBot - count, meuBarco->yBot))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot - count;
          meuBarco->yPeixeProximo = meuBarco->yBot;

          return;
        }
      }
      count++;
    }
  }
}

void readData(int h, int w, int **mapaDados, Barco *meuBarco, Porto *Portos,
              int *numeroPortos, bool portosLidos)
{
  char id[MAX_STR];
  int n, x, y;
  int countPortos = 0;

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      scanf("%i", &mapaDados[i][j]);

      if (mapaDados[i][j] == 11 || mapaDados[i][j] == 21 || mapaDados[i][j] == 31)
      {
        mapaDados[i][j] = 0;
      }
      if (!portosLidos)
      {
        if (mapaDados[i][j] == 1)
        {
          Portos[countPortos].xPorto = j;
          Portos[countPortos].yPorto = i;
          *numeroPortos = *numeroPortos + 1;
          countPortos++;
        }
      }
    }
  }

  scanf(" BOTS %i", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%s %i %i", id, &y, &x);
    if (strcmp(meuBarco->id, id) == 0)
    {
      meuBarco->xBot = x;
      meuBarco->yBot = y;
      peixeMaisProximo(mapaDados, meuBarco, h, w);
      calcularPortoMaisProximo(meuBarco, Portos, *numeroPortos);
    }
  }
}

int main()
{
  char line[MAX_STR];
  char myId[MAX_STR];

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  int h, w;
  scanf("AREA %i %i", &h, &w);
  scanf(" ID %s", myId);

  int **mapaDados = (int **)malloc(sizeof(int *) * h);
  for (int i = 0; i < w; i++)
    mapaDados[i] = malloc(sizeof(int) * w);

  struct Porto Portos[MAX_PRT];
  int numeroPortos = 0;
  bool portosLidos = false;

  struct Barco meuBarco;
  strcpy(meuBarco.id, myId);
  meuBarco.pesoAtual = 0;
  meuBarco.xPortoProximo = -1;
  meuBarco.yPortoProximo = -1;
  meuBarco.xPeixeProximo = -1;
  meuBarco.yPeixeProximo = -1;

  bool pescar = true;

  FILE *fp = fopen("LogBots.txt", "w");
  fprintf(fp, "Projeto de ITP - OCMA\nAlunos: Elbert Natan       - 20210052554\n        João Victor Dantas - 20210054361\n\n******************************************* LOG DE MOVIMENTOS DO BOT *******************************************\n");
  fclose(fp);

  while (1)
  {
    readData(h, w, mapaDados, &meuBarco, Portos, &numeroPortos, portosLidos);
    portosLidos = true;
    executarProximaAcao(&meuBarco, mapaDados, &pescar);
    scanf("%s", line);
  }

  desalocarMemoria(mapaDados, w);

  return 0;
}