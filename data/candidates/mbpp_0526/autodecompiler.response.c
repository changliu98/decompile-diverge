char * func0(char * word){
    char * new_word;
    size_t length = strlen(word);
    new_word = (char *)malloc(sizeof(char)*(length+1));
    if(new_word == NULL){
        return NULL;
    }
    else{
        if(length > 0){
            new_word[0] = toupper(word[0]);
            size_t i;
            for(i = 1; i < length; i++){
                new_word[i] = tolower(word[i]);
            }
            new_word[length-1] = toupper(new_word[length-1]);
            new_word[length] = '\0';
        }
        return new_word;
    }
}