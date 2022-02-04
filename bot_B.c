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

void movimentaCima()
{
  printf("UP\n");
}

void movimentaBaixo()
{
  printf("DOWN\n");
}

void movimentaDireita()
{
  printf("RIGHT\n");
}

void movimentaEsquerda()
{
  printf("LEFT\n");
}

void cmdPescar()
{
  printf("FISH\n");
}

void cmdVender()
{
  printf("SELL\n");
}

void moverX(Barco meuBarco, bool pescar)
{
  if (pescar)
  {
    fprintf(stderr, "MOVENDO EM X PARA PORTO\n");
    if (meuBarco.xBot < meuBarco.xPeixeProximo)
    {
      movimentaDireita();
    }
    else
    {
      movimentaEsquerda();
    }
  }
  else
  {
    if (meuBarco.xBot < meuBarco.xPortoProximo)
    {
      movimentaDireita();
    }
    else
    {
      movimentaEsquerda();
    }
  }
}

void moverY(Barco meuBarco, bool pescar)
{
  if (pescar)
  {
    if (meuBarco.yBot < meuBarco.yPeixeProximo)
    {
      movimentaBaixo();
    }
    else
    {
      movimentaCima();
    }
  }
  else
  {
    if (meuBarco.yBot < meuBarco.yPortoProximo)
    {
      movimentaBaixo();
    }
    else
    {
      movimentaCima();
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
      cmdPescar();
      meuBarco->pesoAtual++;
      if (meuBarco->pesoAtual == 10)
      {
        fprintf(stderr, "PESO ATUAL: %i\n", meuBarco->pesoAtual);
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
      // fprintf(stderr, "ir ao porto EM X barco: %i  porto: %i\n ", meuBarco->xBot, meuBarco->xPortoProximo);

      moverX(*meuBarco, *pescar);
    }
    else if (meuBarco->yBot != meuBarco->yPortoProximo)
    {
      moverY(*meuBarco, *pescar);
    }
    else
    {
      cmdVender();
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
  // matriz do professor estava espelhada x = y y = x
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

  // if(nasceuEncimaDePeixe)
    // fprintf(stderr, "\nNASCEU ENCIMA \n\n");


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
      // IF POSIÇÃO ATUAL DO BOT TIVER PEIXE NA POSIÇÃO DA MATRIZ, PASSA ATUAL
      //  VERIFICA SE JA NASCEU ENCIMA

      // está nos limites? (top)
      if (!(meuBarco->yBot - count < 0 || meuBarco->yBot - count > rangeY))
      {
        // verifica top
        if (temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot - count))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot;
          meuBarco->yPeixeProximo = meuBarco->yBot - count;

          return;
        }
      }
      // está nos limites right?
      if (!(meuBarco->xBot + count < 0 || meuBarco->xBot + count > rangeX))
      {
        // verifica right
        if (temPeixe(mapaDados, meuBarco->xBot + count, meuBarco->yBot))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot + count;
          meuBarco->yPeixeProximo = meuBarco->yBot;

          return;
        }
      }
      // verifica bottom
      if (!(meuBarco->yBot + count < 0 || meuBarco->yBot + count > rangeY))
      {
        // verifica top
        if (temPeixe(mapaDados, meuBarco->xBot, meuBarco->yBot + count))
        {
          meuBarco->xPeixeProximo = meuBarco->xBot;
          meuBarco->yPeixeProximo = meuBarco->yBot + count;

          return;
        }
      }
      // verifica left
      if (!(meuBarco->xBot - count < 0 || meuBarco->xBot - count > rangeX))
      {
        // verifica left
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

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int **mapaDados, Barco *meuBarco, Porto *Portos,
              int *numeroPortos, bool portosLidos)
{
  char id[MAX_STR];
  int n, x, y;
  int countPortos = 0;

  // lê os dados da área de pesca
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      scanf("%i", &mapaDados[i][j]);

      // ELIMINA PEIXES NÃO PESCÁVEIS {VERIFICAR SE EH 11 21 31 OU 10 20 30}
      if (mapaDados[i][j] == 11 || mapaDados[i][j] == 21 || mapaDados[i][j] == 31) // VER DEPOIS IMPORTANTE 11 OU 12
      {
        // fprintf(stderr, "\nvira mar i=%i j=%i \n\n", i, j);
        // VIRA MAR
        mapaDados[i][j] = 0;
      }
      // VERIFICA POSIÇÃO DO PORTO
      if (!portosLidos)
      {
        if (mapaDados[i][j] == 1)
        {
          // LENDO ARRAY DE PORTOS
          Portos[countPortos].xPorto = j;
          Portos[countPortos].yPorto = i;
          *numeroPortos = *numeroPortos + 1;
          countPortos++;
        }
      }
    }
  }

  // lê os dados dos bots
  scanf(" BOTS %i", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%s %i %i", id, &y, &x);
    if (strcmp(meuBarco->id, id) == 0)
    {
      meuBarco->xBot = x;
      meuBarco->yBot = y;
      peixeMaisProximo(mapaDados, meuBarco, h, w);
      // VERIFICAR PEIXE MAIS PRÓXIMO CHAMA FUNÇÃO ATÉ ACHAR UMA COORDENADA
      calcularPortoMaisProximo(meuBarco, Portos, *numeroPortos);
    }
  }
}

int main()
{
  char line[MAX_STR]; // dados temporários
  char myId[MAX_STR]; // identificador do bot em questão

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  int h, w;
  scanf("AREA %i %i", &h, &w); // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", myId);       // ...e o id do bot

  // CRIANDO MAPA LOCAL

  int **mapaDados = (int **)malloc(sizeof(int *) * h);
  for (int i = 0; i < w; i++)
    mapaDados[i] = malloc(sizeof(int) * w);

  // CRIANDO MAPA DE PORTOS
  struct Porto Portos[MAX_PRT];
  int numeroPortos = 0;
  bool portosLidos = false;

  // CRIAR OBJETO DE BARCO E PASSA A MEMORIA
  struct Barco meuBarco;
  strcpy(meuBarco.id, myId);
  meuBarco.pesoAtual = 0;
  meuBarco.xPortoProximo = -1;
  meuBarco.yPortoProximo = -1;
  meuBarco.xPeixeProximo = -1;
  meuBarco.yPeixeProximo = -1;

  // !pescar = vender
  bool pescar = true;

  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  // fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA ===
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1)
  {

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(h, w, mapaDados, &meuBarco, Portos, &numeroPortos, portosLidos);
    portosLidos = true;

    executarProximaAcao(&meuBarco, mapaDados, &pescar);

    // fprintf(stderr, "XBOT: %i YBOT: %i XPEIXE: %i YPEIXE: %i PEIXESQTD: %i XPORTO: %i YPORTO: %i\n\n", meuBarco.xBot, meuBarco.yBot, meuBarco.xPeixeProximo, meuBarco.yPeixeProximo, meuBarco.pesoAtual, meuBarco.xPortoProximo, meuBarco.yPortoProximo);

    // for (int i = 0; i < h; i++)
    // {
    //   for (int j = 0; j < w; j++)
    //   {
    //     fprintf(stderr, "%i  ", mapaDados[i][j]);
    //   }
    //   fprintf(stderr, "\n");
    // }

    // fprintf(stderr, "Meu id = %s\n", meuBarco.id);

    // LOGICA ESCOLHA

    scanf("%s", line);
  }

  return 0;
}