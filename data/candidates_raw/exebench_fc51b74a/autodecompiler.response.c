void jogada(int posicao, int tabuleiro[3][3], int jogador)
{
 if(jogador%2==0)
 {
  switch(posicao)
  {
   case 1:
    tabuleiro[0][0]=-3;
    break;
   case 2:
    tabuleiro[0][1]=-3;
    break;
   case 3:
    tabuleiro[0][2]=-3;
    break;
   case 4:
    tabuleiro[1][0]=-3;
    break;
   case 5:
    tabuleiro[1][1]=-3;
    break;
   case 6:
    tabuleiro[1][2]=-3;
    break;
   case 7:
    tabuleiro[2][0]=-3;
    break;
   case 8:
    tabuleiro[2][1]=-3;
    break;
   case 9:
    tabuleiro[2][2]=-3;
  }
 }
 else
 {
  switch(posicao)
  {
   case 1:
    tabuleiro[0][0]=-2;
    break;
   case 2:
    tabuleiro[0][1]=-2;
    break;
   case 3:
    tabuleiro[0][2]=-2;
    break;
   case 4:
    tabuleiro[1][0]=-2;
    break;
   case 5:
    tabuleiro[1][1]=-2;
    break;
   case 6:
    tabuleiro[1][2]=-2;
    break;
   case 7:
    tabuleiro[2][0]=-2;
    break;
   case 8:
    tabuleiro[2][1]=-2;
    break;
   case 9:
    tabuleiro[2][2]=-2;
  }
 }
}