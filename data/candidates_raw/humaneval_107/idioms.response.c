int *count_palindromes(int n)
{
    int *counts = (int *)malloc(sizeof(int)*2);
    counts[0] = 0;
    counts[1] = 0;
    int i;
    for(i = 1; i <= n; i++)
    {
        int reversed = 0;
        int number = i;
        while(number > 0)
        {
            reversed = (reversed * 10) + (number % 10);
            number = number / 10;
        }
        if(i == reversed)
        {
            if(i % 2 == 0)
            {
                counts[0]++;
            }
            else
            {
                counts[1]++;
            }
        }
    }
    return counts;
}