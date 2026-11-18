int __cdecl func0(const char **operato, const int *operand, int operato_size, int operand_size)
{
    int *num = (int *)malloc(sizeof(int) * operand_size);
    int *posto = (int *)malloc(sizeof(int) * operand_size);
    
    // Initialize values and union-find representatives
    for (int i = 0; i < operand_size; ++i)
    {
        num[i] = operand[i];
        posto[i] = i;
    }

    // Helper macro to find the root representative of an operand
    #define FIND(idx) \
        while (posto[posto[idx]] != posto[idx]) \
            posto[idx] = posto[posto[idx]]

    // Pass 1: Exponentiation (**)
    for (int i = 0; i < operato_size; ++i)
    {
        if (strcmp(operato[i], "**") == 0)
        {
            FIND(i);
            FIND(i + 1);
            num[posto[i]] = (int)pow((double)num[posto[i]], (double)num[posto[i + 1]]);
            posto[i + 1] = posto[i]; // Union the two operands
        }
    }

    // Pass 2: Multiplication (*) and Integer Division (//)
    for (int i = 0; i < operato_size; ++i)
    {
        if (strcmp(operato[i], "*") == 0 || strcmp(operato[i], "//") == 0)
        {
            FIND(i);
            FIND(i + 1);
            
            if (strcmp(operato[i], "*") == 0)
                num[posto[i]] *= num[posto[i + 1]];
            else
                num[posto[i]] /= num[posto[i + 1]];
                
            posto[i + 1] = posto[i]; // Union the two operands
        }
    }

    // Pass 3: Addition (+) and Subtraction (-)
    for (int i = 0; i < operato_size; ++i)
    {
        if (strcmp(operato[i], "+") == 0 || strcmp(operato[i], "-") == 0)
        {
            FIND(i);
            FIND(i + 1);
            
            if (strcmp(operato[i], "+") == 0)
                num[posto[i]] += num[posto[i + 1]];
            else
                num[posto[i]] -= num[posto[i + 1]];
                
            posto[i + 1] = posto[i]; // Union the two operands
        }
    }

    int result = num[0];
    free(num);
    free(posto);
    return result;
}