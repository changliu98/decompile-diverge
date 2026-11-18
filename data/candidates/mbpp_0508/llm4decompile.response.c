int func0(char **l1, char **l2, int size1, int size2)
{
    char *common_elements[100];
    int common_elements_size = 0;
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
        {
            if (!strcmp(l1[i], l2[j]))
            {
                int is_unique = 1;
                for (int k = 0; k < common_elements_size; k++)
                {
                    if (!strcmp(common_elements[k], l1[i]))
                    {
                        is_unique = 0;
                        break;
                    }
                }
                if (is_unique)
                {
                    common_elements[common_elements_size] = l1[i];
                    common_elements_size++;
                }
            }
        }
    }
    char *ordered_l1[100];
    char *ordered_l2[100];
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < common_elements_size; j++)
        {
            if (!strcmp(l1[i], common_elements[j]))
            {
                ordered_l1[index1] = l1[i];
                index1++;
            }
        }
    }
    for (int i = 0; i < size2; i++)
    {
        for (int j = 0; j < common_elements_size; j++)
        {
            if (!strcmp(l2[i], common_elements[j]))
            {
                ordered_l2[index2] = l2[i];
                index2++;
            }
        }
    }
    if (index1 != index2)
    {
        return 0;
    }
    for (int i = 0; i < index1; i++)
    {
        if (strcmp(ordered_l1[i], ordered_l2[i]))
        {
            return 0;
        }
    }
    return 1;
}