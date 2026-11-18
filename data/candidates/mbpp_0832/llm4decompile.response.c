int func0(char *input)
{
    int i, index, number, max;
    char temp[256];

    index = 0;
    max = 0;
    for (i = 0; input[i] != '\0'; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            temp[index] = input[i];
            index++;
        }
        else
        {
            if (index != 0)
            {
                temp[index] = '\0';
                number = atoi(temp);
                if (number > max)
                    max = number;
                index = 0;
            }
        }
    }
    if (index != 0)
    {
        temp[index] = '\0';
        number = atoi(temp);
        if (number > max)
            max = number;
    }

    return max;
}