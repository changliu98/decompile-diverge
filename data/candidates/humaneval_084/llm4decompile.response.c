char* func0(int N)
{
    char str[6];
    sprintf(str, "%d", N);
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
        sum += str[i] - '0';

    char* binary = malloc(33);
    int i = 0;
    if (sum == 0)
        binary[i++] = '0';
    else
        while (sum > 0)
        {
            binary[i++] = sum % 2 + '0';
            sum /= 2;
        }
    binary[i] = '\0';

    for (int j = 0; j < i / 2; j++)
    {
        char temp = binary[j];
        binary[j] = binary[i - j - 1];
        binary[i - j - 1] = temp;
    }

    return binary;
}