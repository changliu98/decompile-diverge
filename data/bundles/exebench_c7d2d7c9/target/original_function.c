void passByPointer(int * x)
{
    (*x) = 4;
    (*x) *= 4;

    return;
}