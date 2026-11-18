void calcula_target(int *red, int *pacman, int *target)
{
  target[0] = (pacman[0]*2) - red[0];
  target[1] = (pacman[1]*2) - red[1];
}