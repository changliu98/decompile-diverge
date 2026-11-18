void __cdecl operacao_dist(int *pacman, int *dir, int x, int y)
{
  int coluna; // [rsp+0h] [rbp-20h]

  coluna = y + pacman[1];
  *dir = x + *pacman;
  dir[1] = coluna;
}