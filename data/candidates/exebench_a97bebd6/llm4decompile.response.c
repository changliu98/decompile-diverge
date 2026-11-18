void calcula_target(int red[2], int pacman[2], int target[2])
{
    target[0] = pacman[0] + (pacman[0] - red[0]);
    target[1] = pacman[1] + (pacman[1] - red[1]);
}