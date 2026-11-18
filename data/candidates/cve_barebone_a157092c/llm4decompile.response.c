yankreg_T *
get_register(int name, int copy)
{
    yankreg_T	*reg;
    int	    i;

    get_yank_register(name, 0);

    reg = (yankreg_T *)alloc(sizeof(yankreg_T));
    if (reg != NULL)
    {
	reg->y_array = y_current->y_array;
	reg->y_len = y_current->y_size;
	reg->y_type = y_current->y_type;
	if (copy)
	{
	    if (reg->y_len)
		reg->y_array = (char_u **)alloc((long)reg->y_len *
							    sizeof(char_u *));
	    else
		reg->y_array = NULL;
	    if (reg->y_array != NULL)
		for (i = 0; i < reg->y_len; ++i)
		    reg->y_array[i] = vim_strsave(y_current->y_array[i]);
	}
	else
	    y_current->y_array = NULL;
    }
    return reg;
}