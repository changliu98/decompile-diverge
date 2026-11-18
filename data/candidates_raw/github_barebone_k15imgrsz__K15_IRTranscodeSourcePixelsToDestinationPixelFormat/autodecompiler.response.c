void _K15_IRTranscode(K15_IRContext *p_Context)
{
    unsigned int width = p_Context->m_SourceWidth;
    unsigned int height = p_Context->m_SourceHeight;
    unsigned char *p_InputPixels = p_Context->m_pSourcePixels;
    K15_IRFormat inputFormat = p_Context->m_SourceFormat;
    K15_IRFormat outputFormat = p_Context->m_DestinationFormat;

    if (inputFormat != outputFormat)
    {
        unsigned char *p_OutputPixels = (unsigned char *)malloc(width * height * kir_format_to_byte_lut[outputFormat]);

        if (inputFormat == 0 && outputFormat == 1)
            _K15_IRTranscodeFromR8ToR8G8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 0 && outputFormat == 2)
            _K15_IRTranscodeFromR8ToR8G8B8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 0 && outputFormat == 3)
            _K15_IRTranscodeFromR8ToR8G8B8A8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 1 && outputFormat == 0)
            _K15_IRTranscodeFromR8G8ToR8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 1 && outputFormat == 2)
            _K15_IRTranscodeFromR8G8ToR8G8B8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 1 && outputFormat == 3)
            _K15_IRTranscodeFromR8G8ToR8G8B8A8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 2 && outputFormat == 0)
            _K15_IRTranscodeFromR8G8B8ToR8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 2 && outputFormat == 1)
            _K15_IRTranscodeFromR8G8B8ToR8G8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 2 && outputFormat == 3)
            _K15_IRTranscodeFromR8G8B8ToR8G8B8A8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 3 && outputFormat == 0)
            _K15_IRTranscodeFromR8G8B8A8ToR8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 3 && outputFormat == 1)
            _K15_IRTranscodeFromR8G8B8A8ToR8G8(p_InputPixels, p_OutputPixels, width, height);
        else if (inputFormat == 3 && outputFormat == 2)
            _K15_IRTranscodeFromR8G8B8A8ToR8G8B8(p_InputPixels, p_OutputPixels, width, height);

        p_Context->m_pDestinationPixels = p_OutputPixels;
    }
}