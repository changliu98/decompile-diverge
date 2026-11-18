

#include <assert.h>

#include <string.h>



char make_flip(char ch) {

    return (ch == '0') ? '1' : '0';

}



int get_flip_with_starting_character(const char *str, char expected) {

    int flip_count = 0;

    int length = strlen(str);

    for (int i = 0; i < length; i++) {

        if (str[i] != expected) {

            flip_count++;

        }

        expected = make_flip(expected);

    }

    return flip_count;

}



int func0(const char *str) {
  return (get_flip_with_starting_character(str, '0') <
          get_flip_with_starting_character(str, '1'))
             ? get_flip_with_starting_character(str, '0')
             : get_flip_with_starting_character(str, '1');
}
