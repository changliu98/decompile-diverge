void intercambiar(int *pos1, int *pos2)
{
    int aux;

    if (pos1 == pos2)
        return;

    aux = *pos1;
    *pos1 = *pos2;
    *pos2 = aux;
}