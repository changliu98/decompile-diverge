void ceasar(char* text, char offset)
{
    int i;
    for(i = 0; text[i] != '\0'; i++)
    {
        if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            int j;
            for(j = 0; j < offset; j++)
            {
                if(text[i] == 'Z')
                    text[i] = 'A' - 1;
                if(text[i] == 'z')
                    text[i] = 'a' - 1;
                text[i]++;
            }
        }
    }
}