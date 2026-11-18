void copy_dice(const int *dice, int *copy)
{
    for (int i = 0; i < 6; i++)
    {
        copy[i] = dice[i];
    }
}