
void reverseIntRange(int *pStart, int *pEnd, int size)
{
int temp;
temp = *pStart;
*pStart = size - *pEnd;
*pEnd = size - temp;
}
