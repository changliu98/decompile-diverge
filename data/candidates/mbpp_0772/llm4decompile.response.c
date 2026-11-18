char* func0(char* test_str, int K)
{
    char temp_copy[1000];
    strncpy(temp_copy, test_str, 1000);
    temp_copy[1000 - 1] = '\0';

    char* res = (char*)malloc(strlen(test_str) + 1);
    if (!res) {
        perror("malloc failed");
        exit(1);
    }
    *res = '\0';

    char* token = strtok(temp_copy, " ");
    while (token) {
        if (strlen(token) != K) {
            strcat(res, token);
            strcat(res, " ");
        }
        token = strtok(NULL, " ");
    }

    size_t last_char = strlen(res) - 1;
    if (last_char > 0 && res[last_char] == ' ')
        res[last_char] = '\0';

    return res;
}