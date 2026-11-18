char * func0(char * file_name)
{
    int length = strlen(file_name);
    int i = 0;
    int num_digit = 0;
    int num_dot = 0;
    char first = file_name[0];
    char * ext = file_name + length - 4;

    if (length < 5)
        return "No";

    if (first >= 'A' && first <= 'Z' || first >= 'a' && first <= 'z')
    {
        if (!strcmp(ext, ".txt") || !strcmp(ext, ".exe") || !strcmp(ext, ".dll"))
        {
            for (i = 0; i < length; i++)
            {
                if (file_name[i] >= '0' && file_name[i] <= '9')
                    num_digit++;
                if (file_name[i] == '.')
                    num_dot++;
            }

            if (num_digit < 4 && num_dot == 1)
                return "Yes";
            else
                return "No";
        }
        else
            return "No";
    }
    else
        return "No";
}