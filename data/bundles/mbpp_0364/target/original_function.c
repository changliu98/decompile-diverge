int func0(const char *str) {
  return (get_flip_with_starting_character(str, '0') <
          get_flip_with_starting_character(str, '1'))
             ? get_flip_with_starting_character(str, '0')
             : get_flip_with_starting_character(str, '1');
}