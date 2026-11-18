

#include <stdio.h>

#include <string.h>

#include <assert.h>



#define NO_OF_CHARS 256



char *str_to_list(char *string) {

    static char temp[256];

    int i = 0;

    while (*string) {

        temp[i++] = *string++;

    }

    temp[i] = '\0';

    return temp;

}



char *lst_to_string(char *list, int res_ind) {

    static char result[256];

    strncpy(result, list, res_ind);

    result[res_ind] = '\0';

    return result;

}



int *get_char_count_array(char *string) {

    static int count[NO_OF_CHARS];

    memset(count, 0, sizeof(count));

    

    while (*string) {

        count[(int)(*string)]++;

        string++;

    }

    return count;

}



char *func0(char *string, char *second_string) {
  int *count = get_char_count_array(second_string);
  int ip_ind = 0, res_ind = 0;
  char *str_list = str_to_list(string);
  while (str_list[ip_ind] != '\0') {
    char temp = str_list[ip_ind];
    if (count[(int)temp] == 0) {
      str_list[res_ind++] = temp;
    }
    ip_ind++;
  }
  return lst_to_string(str_list, res_ind);
}
