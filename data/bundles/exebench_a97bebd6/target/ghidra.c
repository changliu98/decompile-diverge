void calcula_target(int *red,int *pacman,int *target)

{
  int *target_local;
  int *pacman_local;
  int *red_local;
  
  *target = (*pacman - *red) + *pacman;
  target[1] = (pacman[1] - red[1]) + pacman[1];
  return;
}