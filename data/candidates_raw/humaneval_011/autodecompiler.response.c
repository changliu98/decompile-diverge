char * xor (char* string1, char* string2){
    int len1 = strlen(string1);
    int len2 = strlen(string2);

    int min_len;
    if(len1 < len2){
        min_len = len1;
    }else{
        min_len = len2;
    }

    char *xor_string = malloc(sizeof(char) * (min_len+1));
    if(xor_string == NULL){
        return NULL;
    }else{
        int i;
        for(i = 0; i<min_len;i++){
            xor_string[i] = (string1[i] == string2[i]) ? '0' : '1';
        }
        xor_string[min_len] = '\0';
        return xor_string;
    }
}