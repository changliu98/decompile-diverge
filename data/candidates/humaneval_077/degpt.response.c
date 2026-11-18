int func0(int input_value)
{
    int cube_root_candidate = 0;
    int absolute_input = abs(input_value);
    // Find the smallest integer i such that i^3 >= |a|
    while (cube_root_candidate * cube_root_candidate * cube_root_candidate < absolute_input) {
        cube_root_candidate++;
    }
    // Check if |a| is a perfect cube
    return (cube_root_candidate * cube_root_candidate * cube_root_candidate == absolute_input) ? 1 : 0;
}