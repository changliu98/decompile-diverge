void intercambiar(int *pos1, int *pos2)
{
    if (pos1 != pos2)
    {

        int aux=*pos1;
        *pos1=*pos2;
        *pos2=aux;
    }
}