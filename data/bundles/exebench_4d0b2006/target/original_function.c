void squeeze(char s1[], char s2[])
{
        int i, j, k, contains;

        for (i = 0, k = 0; s1[i] != '\0'; ++i) {
                contains = 0;
                for (j = 0; s2[j] != '\0'; ++j) {
                        if (s1[i] == s2[j])
                                contains = 1;
                }
                if (contains == 0)
                        s1[k++] = s1[i];
        }
        s1[k] = '\0';
}