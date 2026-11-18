int func0(const char *str) {
    int flips_starting_with_0 = get_flip_with_starting_character(str, '0');
    int flips_starting_with_1 = get_flip_with_starting_character(str, '1');
    
    int min_flips;
    if (flips_starting_with_0 < flips_starting_with_1) {
        min_flips = flips_starting_with_0;
    } else {
        min_flips = flips_starting_with_1;
    }
    
    return min_flips;
}