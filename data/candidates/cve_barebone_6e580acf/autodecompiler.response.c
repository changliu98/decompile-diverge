char *xf_Pointer_get_window (WavpackContext *wpc)
{
    char *result;

    if (!wpc)
        result = NULL;
    else if (wpc->streamfile)
        result = wpc->streamfile->file_extension ? wpc->streamfile->file_extension : NULL;
    else if (!wpc->file2)
        result = NULL;
    else
        result = wpc->file2->file_extension;

    return result;
}