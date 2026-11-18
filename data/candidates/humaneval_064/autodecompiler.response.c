int func0(char *word)
{
    char *vowels = "aeiouAEIOU";
    int i, len, scnt;

    scnt = 0;
    len = strlen(word);

    for (i = 0; ; i++) {
 if (i >= len) break;
 if (strchr(vowels, word[i])) scnt++;
 else continue;
 while (i < len && strchr(vowels, word[i])) i++;
    }

    if (len > 0 && (word[len-1] == 'y' || word[len-1] == 'Y')) scnt++;

    return(scnt);
}