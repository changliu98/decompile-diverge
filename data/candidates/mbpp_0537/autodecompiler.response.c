char *func0(char *input){
    char *token;
    int word_count = 0;
    char *words[100];
    while(1){
        token = strtok(input, " ");
        input = NULL;
        if(token == NULL){
            break;
        }
        for(int i=0; i<word_count; i++){
            if(strcmp(words[i], token] == 0){
                return token;
            }
        }
        words[word_count++] = token;
    }
    return "None";
}