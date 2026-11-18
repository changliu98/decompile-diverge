// Function testfunc16 takes five integer pointers as arguments
void testfunc16(int *ptr_first, int *ptr_second, int *ptr_third, int *ptr_fourth, int *ptr_fifth)
{
    // Increment the second element of the array pointed to by p2 by 100
    ptr_second[1] = ptr_second[1] + 100;
    
    // Cast p4 to a char pointer, dereference it to get the char value,
    // cast p4 itself to char (truncating the pointer value),
    // add them together, and store the result back as a char
    *(char *)ptr_fourth = (char)*ptr_fourth + (char)ptr_fourth;
}