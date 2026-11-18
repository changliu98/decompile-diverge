char * func0(char *str1){

 char *words[100];
 char *word;
 int word_count = 0;
 int i;

 word = strtok(str1, " ");
 while(word != NULL){
  for(i = 0; i < word_count; i++){
   if(!strcmp(words[i], word))
    return word;
  }
  words[word_count++] = word;
  word = strtok(NULL, " ");
 }
 return "None";
}