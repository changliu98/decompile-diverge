char *get_dict(int *array, int size){
  int i; int j;
  int count = 0;
  int found;
  struct dict *freq = (dict *)malloc(sizeof(dict)*100);
  int *test_tup = array;
  int test_size = size;
  char buffer[50];
  for(i = 0; i < test_size; i++){
    found = 0;
    for(j = 0; j < count; j++){
      if(freq[j].key == test_tup[i]){
        freq[j].value++;
        found = 1;
        break;
      }
    }
    if(!found){
      freq[count].key = test_tup[i];
      freq[count].value = 1;
      count++;
    }
  }
  char *str = (char *)malloc(sizeof(char)*1000);
  str[0] = '\0';
  strcat(str, "{");
  for(i = 0; i < count; i++){
    sprintf(buffer, "%d: %d", freq[i].key, freq[i].value);
    strcat(str, buffer);
    if(i < count - 1){
      strcat(str, ", ");
    }
  }
  strcat(str, "}");
  return str;
}