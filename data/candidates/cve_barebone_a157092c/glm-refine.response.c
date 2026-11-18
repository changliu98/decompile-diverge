void *__cdecl get_register(int name, int copy)
{
    yankreg_T *reg;
    int i;

    get_yank_register(name, 0);
    
    reg = (yankreg_T *)alloc(sizeof(yankreg_T));
    if (!reg)
        return NULL;

    // Copy the current register state into our new struct
    reg->y_array = y_current->y_array;
    reg->y_size = y_current->y_size;
    reg->y_type = y_current->y_type;
    reg->y_width = y_current->y_width;

    if (copy)
    {
        // Deep copy: allocate new array and duplicate strings
        if (reg->y_size)
            reg->y_array = (char_u **)alloc(8 * reg->y_size);
        else
            reg->y_array = NULL;

        if (reg->y_array)
        {
            for (i = 0; i < reg->y_size; ++i)
                reg->y_array[i] = vim_strsave(y_current->y_array[i]);
        }
    }
    else
    {
        // Move: transfer ownership, nullify the original array pointer
        y_current->y_array = NULL;
    }

    return reg;
}