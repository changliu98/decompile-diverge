void
trataCoordenadas(char *linha, int *horizontal, int *vertical)
{
    *vertical = linha[0] - 97;

    if((linha[3] == '\0') || (linha[3] == '\n'))
        *horizontal = linha[2] - 49;
    else
        *horizontal = ((linha[2] - 48) * 10) + (linha[3] - 48) - 1;
}