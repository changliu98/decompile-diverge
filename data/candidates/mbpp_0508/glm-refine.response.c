define MAX_COMMON 100

bool __cdecl func0(char **list1, char **list2, int size1, int size2)
{
    char *common_elements[MAX_COMMON];
    int common_size = 0;

    // 1. Find all unique common elements between list1 and list2
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            if (strcmp(list1[i], list2[j]) == 0)
            {
                bool is_unique = true;
                for (int k = 0; k < common_size; ++k)
                {
                    if (strcmp(common_elements[k], list1[i]) == 0)
                    {
                        is_unique = false;
                        break;
                    }
                }
                if (is_unique)
                {
                    common_elements[common_size++] = list1[i];
                }
            }
        }
    }

    char *ordered_l1[MAX_COMMON];
    char *ordered_l2[MAX_COMMON];
    int count1 = 0;
    int count2 = 0;

    // 2. Extract elements from list1 in the order they appear in common_elements
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < common_size; ++j)
        {
            if (strcmp(list1[i], common_elements[j]) == 0)
            {
                ordered_l1[count1++] = list1[i];
            }
        }
    }

    // 3. Extract elements from list2 in the order they appear in common_elements
    for (int i = 0; i < size2; ++i)
    {
        for (int j = 0; j < common_size; ++j)
        {
            if (strcmp(list2[i], common_elements[j]) == 0)
            {
                ordered_l2[count2++] = list2[i];
            }
        }
    }

    // 4. The sequences must be of the same length
    if (count1 != count2)
        return false;

    // 5. Verify that the ordered sequences match exactly
    for (int i = 0; i < count1; ++i)
    {
        if (strcmp(ordered_l1[i], ordered_l2[i]) != 0)
            return false;
    }

    return true;
}