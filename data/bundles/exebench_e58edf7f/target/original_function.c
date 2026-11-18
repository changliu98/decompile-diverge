void toUpperCase(char *str)
{

    int index = 0;
    char smallCase;

    while(str[index])
    {

        for(smallCase = 'a'; smallCase <= 'z'; smallCase++)

            if(str[index] == smallCase)
                str[index] -= 32;

        index++;
    }

}