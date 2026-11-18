pyc_object *__cdecl get_complex_object(RzBinPycObj *pyc, RzBuffer *buffer)
{
    bool error = false;
    pyc_object *ret = (pyc_object *)calloc(1uLL, sizeof(pyc_object));
    if (!ret)
        return NULL;

    // Determine length of the real part based on Python version magic number
    unsigned int n1 = (pyc->magic_int > 0xF26D) ? get_st32(buffer, &error) : get_ut8(buffer, &error);
    if (error)
    {
        free(ret);
        return NULL;
    }

    unsigned char *s1 = (unsigned char *)malloc(n1 + 1);
    if (!s1)
    {
        free(ret);
        return NULL;
    }

    if (rz_buf_read(buffer, s1, n1) != n1)
    {
        free(s1);
        free(ret);
        return NULL;
    }
    s1[n1] = 0;

    // Determine length of the imaginary part based on Python version magic number
    unsigned int n2 = (pyc->magic_int > 0xF26D) ? get_st32(buffer, &error) : get_ut8(buffer, &error);
    if (error)
    {
        free(s1);
        free(ret);
        return NULL;
    }

    unsigned char *s2 = (unsigned char *)malloc(n2 + 1);
    if (!s2)
    {
        free(s1);
        free(ret);
        return NULL;
    }

    if (rz_buf_read(buffer, s2, n2) != n2)
    {
        free(s1);
        free(s2);
        free(ret);
        return NULL;
    }
    s2[n2] = 0;

    // Format as a Python complex string representation
    ret->type = TYPE_COMPLEX;
    ret->data = rz_str_newf("%s+%sj", (const char *)s1, (const char *)s2);

    free(s1);
    free(s2);

    if (!ret->data)
    {
        free(ret);
        return NULL;
    }

    return ret;
}