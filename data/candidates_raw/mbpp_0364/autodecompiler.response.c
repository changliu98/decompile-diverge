int get_min_flip(char *s)
{
 int min_flip;
 int flip_from_0_to_1, flip_from_1_to_0;

 flip_from_0_to_1 = get_flip_with_starting_character(s, '0');
 flip_from_1_to_0 = get_flip_with_starting_character(s, '1');

 if(flip_from_0_to_1 < flip_from_1_to_0)
 {
  min_flip = flip_from_0_to_1;
 }
 else
 {
  min_flip = flip_from_1_to_0;
 }

 return min_flip;
}