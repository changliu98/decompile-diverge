void operacao_dist(int *pacman, int *dir, int x, int y){
  int coluna = pacman[1]+y;
  dir[0]=pacman[0]+x;
  dir[1]=coluna;
}