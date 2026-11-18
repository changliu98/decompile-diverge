int func0( int array[], int n, int key, int *compares )
{
    *compares = 0;
    char found = 0;

    while (1)
    {
        unsigned char _cond = (*compares < n) ^ found;
        if (!_cond)
            break;

        if (key == array[*compares])
            found = 1;
        else
            *compares = *compares + 1;
    }

    return found & 1;
}