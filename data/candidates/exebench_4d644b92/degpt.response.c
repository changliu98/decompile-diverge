int twiddle1(int *ptr_x, int *ptr_y)
{
    // Update the value pointed to by xp: multiply the value pointed to by yp by 2, then add the current value of xp
    *ptr_x = 2 * *ptr_y + *ptr_x;
    // Return the new value of xp
    return *ptr_x;
}