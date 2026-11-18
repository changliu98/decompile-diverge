void swapNumbers( int *pfirstNumber, int *psecondNumber )
{
    int temp;

    temp = *pfirstNumber;
    *pfirstNumber = *psecondNumber;
    *psecondNumber = temp;
}