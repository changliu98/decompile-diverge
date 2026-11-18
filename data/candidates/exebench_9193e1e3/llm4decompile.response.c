void clip_coord(int *coord, int min, int max)
{
    *coord = (*coord < min) ? min : *coord;
    *coord = (*coord > max) ? max : *coord;
}