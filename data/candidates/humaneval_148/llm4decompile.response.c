char** func0(char* planet1, char* planet2, int* returnSize)
{
    char** result;
    int i, pos1, pos2, temp;
    static const char* PTR_s_Mercury[8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
    char* PTR_s_planets[8];
    memcpy(PTR_s_planets, PTR_s_Mercury, sizeof(char*) * 8);
    pos1 = -1;
    pos2 = -1;
    for (i = 0; i < 8; i++)
    {
        if (!strcmp(PTR_s_planets[i], planet1))
            pos1 = i;
        if (!strcmp(PTR_s_planets[i], planet2))
            pos2 = i;
    }
    if (pos1 == -1 || pos2 == -1 || pos1 == pos2)
    {
        *returnSize = 0;
        result = NULL;
    }
    else
    {
        if (pos1 > pos2)
        {
            temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        *returnSize = pos2 - pos1 - 1;
        if (*returnSize > 0)
        {
            result = (char**)malloc(sizeof(char*) * *returnSize);
            for (i = pos1 + 1; i < pos2; i++)
                result[i - pos1 - 1] = PTR_s_planets[i];
        }
        else
        {
            *returnSize = 0;
            result = NULL;
        }
    }
    return result;
}