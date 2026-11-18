void operacao_dist(int *pacman,int *dir,int x,int y)

{
  int iVar1;
  int coluna;
  int linha;
  int y_local;
  int x_local;
  int *dir_local;
  int *pacman_local;
  
  iVar1 = pacman[1];
  *dir = *pacman + x;
  dir[1] = iVar1 + y;
  return;
}