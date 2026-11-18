void __cdecl adjust_mode_num(int *mode)
{
    // Clamp the value of *mode to the range [0, 9]
    *mode = (*mode < 0) ? 0 : (*mode > 9 ? 9 : *mode);
}