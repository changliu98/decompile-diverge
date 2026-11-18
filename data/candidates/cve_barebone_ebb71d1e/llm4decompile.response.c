unsigned char *DecompressRTF(variableLength *data, int *size)
{
    unsigned char *output;
    unsigned char *work;
    unsigned char *header;
    unsigned int headerSize = 207;
    unsigned int uncompressedSize;
    unsigned int compressedSize;
    unsigned int magic;
    unsigned int offset;
    unsigned int length;
    unsigned int end;
    unsigned int in;
    unsigned int out;
    unsigned int flags;
    unsigned int flagCount;
    unsigned int i;

    header = (unsigned char *)calloc(headerSize,1);
    if (header == NULL)
    {
        printf("Out of Memory at %s : %i\n", "/work/harness.c", 79);
        return NULL;
    }

    memcpy(header, "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman \\fswiss \\fmodern \\fscript \\fdecor MS Sans SerifSymbolArialTimes New RomanCourier{\\colortbl\\red0\\green0\\blue0\n\r\\par \\pard\\plain\\f0\\fs20\\b\\i\\u\\tab\\tx", headerSize - 1);

    if (data->size < 20)
    {
        printf("File too small\n");
        return NULL;
    }

    uncompressedSize = SwapDWord(data->data, 4);
    compressedSize = SwapDWord(data->data + 4, 4);
    magic = SwapDWord(data->data + 8, 4);

    if (uncompressedSize != data->size - 4)
    {
        printf(" Size Mismatch: %u != %i\n", uncompressedSize, data->size - 4);
        free(header);
        return NULL;
    }

    if (magic == 0x414C454D)
    {
        output = (unsigned char *)calloc(compressedSize, 1);
        if (output == NULL)
        {
            printf("Out of Memory at %s : %i\n", "/work/harness.c", 108);
            return NULL;
        }

        memcpy(output, data->data + 4, compressedSize);
    }
    else if (magic == 0x75465A4C)
    {
        flags = 0;
        flagCount = 0;

        if (0xFFFFFFFF - compressedSize < headerSize)
        {
            printf("Corrupted file\n");
            exit(-1);
        }

        work = (unsigned char *)calloc(compressedSize + headerSize, 1);
        if (work == NULL)
        {
            printf("Out of Memory at %s : %i\n", "/work/harness.c", 120);
            return NULL;
        }

        memcpy(work, header, headerSize);

        in = 16;
        out = headerSize;

        while (out < compressedSize + headerSize)
        {
            if ((flagCount % 8) == 0)
            {
                flags = data->data[in++];
                flagCount = 0;
            }
            else
            {
                flags >>= 1;
            }

            flagCount++;

            if ((flags & 1) == 1)
            {
                offset = (out & 0xFFFFF000) + ((data->data[in++] << 4) | (data->data[in++] >> 4));
                if (offset >= out)
                    offset -= 0x1000;

                length = (data->data[in++] & 0xF) + 2;
                end = offset + length;

                while (offset < end && out < compressedSize + headerSize && offset < compressedSize + headerSize)
                {
                    work[out++] = work[offset++];
                }
            }
            else if (out < compressedSize + headerSize && in < (unsigned int)data->size)
            {
                work[out++] = data->data[in++];
            }
            else
            {
                printf("Corrupted stream\n");
                exit(-1);
            }
        }

        output = (unsigned char *)calloc(compressedSize, 1);
        if (output == NULL)
        {
            printf("Out of Memory at %s : %i\n", "/work/harness.c", 158);
            return NULL;
        }

        memcpy(output, work + headerSize, compressedSize);
        free(work);
        *size = compressedSize;
        free(header);
        return output;
    }
    else
    {
        printf("Unknown compression type (magic number %x)\n", magic);
    }

    free(header);
    return NULL;
}