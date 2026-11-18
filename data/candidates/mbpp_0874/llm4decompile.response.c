bool func0(char *str1, char *str2)
{
    int M = strlen(str1);
    int N = strlen(str2);

    if (M % N != 0) {
        return false;
    }

    for (int i = 0; i < M; i++) {
        if (str1[i] != str2[i % N]) {
            return false;
        }
    }

    return true;
}