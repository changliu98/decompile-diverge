// Function to add 'a' to the value pointed to by 'pi' and 'b' to the value pointed to by 'pj'
void TwoOutArgs(int value_a, int *ptr_first, int value_b, int *ptr_second)
{
    // Update the value pointed to by 'pi' by adding 'a' to it
    *ptr_first = value_a + *ptr_first;
    // Update the value pointed to by 'pj' by adding 'b' to it
    *ptr_second = value_b + *ptr_second;
}