int func0(char *s) {
  int flip_0 = get_flip_with_starting_character(s, '0');
  int flip_1 = get_flip_with_starting_character(s, '1');
  return flip_0 < flip_1 ? flip_0 : flip_1;
}