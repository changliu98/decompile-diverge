char * func0(int n, char **test_list)
{
    int i, j, k, pos, found, max, index, unique;
    char word[50];
    char *str;

    unique = 0;
    for (i = 0; i < n; i++) {
        str = test_list[i];
        pos = 0;
        while (*str != 0) {
            if (!isblank(*str)) {
                word[pos++] = *str;
            } else if (pos > 0) {
                word[pos] = 0;
                found = 0;
                for (j = 0; j < unique; j++) {
                    if (!strcmp(func0::words[j].word, word)) {
                        func0::words[j].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(func0::words[unique].word, word);
                    func0::words[unique].count = 1;
                    unique++;
                }
                pos = 0;
            }
            str++;
        }
        if (pos > 0) {
            word[pos] = 0;
            found = 0;
            for (j = 0; j < unique; j++) {
                if (!strcmp(func0::words[j].word, word)) {
                    func0::words[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(func0::words[unique].word, word);
                func0::words[unique].count = 1;
                unique++;
            }
        }
    }

    max = 0;
    index = 0;
    for (i = 0; i < unique; i++) {
        if (func0::words[i].count > max) {
            max = func0::words[i].count;
            index = i;
        }
    }

    return func0::words[index].word;
}