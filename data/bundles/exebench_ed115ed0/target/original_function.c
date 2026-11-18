void operacao_dist(int pacman[3], int dir[2], int x, int y)
{
 int linha, coluna;

 linha = pacman[0] + x;
 coluna = pacman[1] + y;
 dir[0] = linha;
 dir[1] = coluna;
}