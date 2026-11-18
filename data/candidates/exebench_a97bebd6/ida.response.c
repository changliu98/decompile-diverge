void __cdecl calcula_target(int *red, int *pacman, int *target)
{
  *target = *pacman + *pacman - *red;
  target[1] = pacman[1] + pacman[1] - red[1];
}