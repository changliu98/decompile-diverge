char * func0(int n)
{
    int i, j;
    char temp;

    for (i = 0; n > 0; i++)
    {
        func0::binary[i] = (n % 2) + '0';
        n /= 2;
    }

    func0::binary[i] = '\0';

    for (j = 0, i--; j < i; j++, i--)
    {
        temp = func0::binary[j];
        func0::binary[j] = func0::binary[i];
        func0::binary[i] = temp;
    }

    return func0::binary;
}