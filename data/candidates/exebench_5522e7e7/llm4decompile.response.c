void cenitPolarCrypt(char *str)
{
    int i, j;
    char *keys = "CENITcenitPOLARpolar";
    char *values = "POLARpolarCENITcenit";

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; keys[j] != '\0'; j++)
        {
            if (str[i] == keys[j])
            {
                str[i] = values[j];
                break;
            }
        }
    }
}