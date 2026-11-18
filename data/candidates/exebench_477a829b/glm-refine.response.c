void std::swap<int>(int* ptrX, int* ptrY)
{
    int temp = *ptrX;
    *ptrX = *ptrY;
    *ptrY = temp;
}