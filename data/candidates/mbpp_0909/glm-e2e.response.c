int func0(int num) {
    int n = num - 1;
    int result = 0;
    
    while (n > 0) {
        char s1[12];
        char s2[20];
        int len;
        int i;
        char temp;
        
        sprintf(s1, "%d", n);
        strcpy(s2, s1);
        len = strlen(s2);
        
        i = 0;
        while (i < len / 2) {
            temp = s2[i];
            s2[i] = s2[len - 1 - i];
            s2[len - 1 - i] = temp;
            i++;
        }
        
        if (strcmp(s1, s2) == 0) {
            result = n;
            break;
        }
        
        n--;
    }
    
    return result;
}