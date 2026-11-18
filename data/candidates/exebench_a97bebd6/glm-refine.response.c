void __cdecl calcula_target(const int *red, const int *pacman, int *target)
{
    // Calculate the vector from Blinky (red) to Pacman, and add it to Pacman's position.
    // Mathematically: target = pacman + (pacman - red) = 2 * pacman - red
    
    // X coordinate
    *target = (*pacman * 2) - *red;
    
    // Y coordinate
    target[1] = (pacman[1] * 2) - red[1];
}