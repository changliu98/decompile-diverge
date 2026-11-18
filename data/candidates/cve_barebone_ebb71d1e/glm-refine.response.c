#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_UNCOMPRESSED 1095517517
#define MAGIC_COMPRESSED   1967544908
#define PREBUF_SIZE        0xD0
#define PREBUF_SKIP        207

unsigned __int8 *__cdecl DecompressRTF(variableLength *p, int *size)
{
    unsigned int compressedSize, uncompressedSize, magic;
    unsigned int in = 16, out = PREBUF_SKIP;
    unsigned __int8 *src = p->data;
    unsigned __int8 *comp_Prebuf, *dsta, *dstb;
    int flags = 0, flagCount = 0;

    if (p->size < 20)
    {
        printf("File too small\n");
        return NULL;
    }

    comp_Prebuf = (unsigned __int8 *)calloc(PREBUF_SIZE, 1);
    if (!comp_Prebuf)
    {
        printf("Out of Memory at %s : %i\n", "/work/harness.c", 79);
        return NULL;
    }
    
    memcpy(
        comp_Prebuf,
        "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman \\fswiss \\fmodern \\fscript \\fdecor MS Sans S"
        "erifSymbolArialTimes New RomanCourier{\\colortbl\\red0\\green0\\blue0\n"
        "\r\\par \\pard\\plain\\f0\\fs20\\b\\i\\u\\tab\\tx",
        PREBUF_SIZE - 1
    );

    compressedSize = SwapDWord(src, 4);
    uncompressedSize = SwapDWord(src + 4, 4);
    magic = SwapDWord(src + 8, 4);

    if (compressedSize != p->size - 4)
    {
        printf(" Size Mismatch: %u != %i\n", compressedSize, (unsigned int)(p->size - 4));
        free(comp_Prebuf);
        return NULL;
    }

    if (magic == MAGIC_UNCOMPRESSED)
    {
        dstb = (unsigned __int8 *)calloc(uncompressedSize, 1);
        if (!dstb)
        {
            printf("Out of Memory at %s : %i\n", "/work/harness.c", 108);
            return NULL;
        }
        memcpy(dstb, src + 4, uncompressedSize);
        *size = uncompressedSize;
        free(comp_Prebuf);
        return dstb;
    }

    if (magic != MAGIC_COMPRESSED)
    {
        printf("Unknown compression type (magic number %x)\n", magic);
        free(comp_Prebuf);
        return NULL;
    }

    if (0x7FFFFFFF - uncompressedSize <= PREBUF_SKIP - 1)
    {
        printf("Corrupted file\n");
        exit(-1);
    }

    dsta = (unsigned __int8 *)calloc(uncompressedSize + PREBUF_SKIP, 1);
    if (!dsta)
    {
        printf("Out of Memory at %s : %i\n", "/work/harness.c", 120);
        return NULL;
    }

    memcpy(dsta, comp_Prebuf, PREBUF_SIZE - 1);

    while (out < uncompressedSize + PREBUF_SKIP)
    {
        if (flagCount++ % 8)
        {
            flags >>= 1;
        }
        else
        {
            flags = src[in++];
        }

        if (flags & 1)
        {
            unsigned int offset = src[in];
            unsigned int length = src[in + 1];
            in += 2;

            offset = (length >> 4) | (offset << 4);
            length = (length & 0xF) + 2;
            offset += (out >> 12) << 12;

            if (offset >= out)
                offset -= 4096;

            unsigned int end = length + offset;
            while (offset < end && out < uncompressedSize + PREBUF_SKIP && offset < uncompressedSize + PREBUF_SKIP)
            {
                dsta[out++] = dsta[offset++];
            }
        }
        else
        {
            if (out >= uncompressedSize + PREBUF_SKIP || in >= p->size)
            {
                printf("Corrupted stream\n");
                exit(-1);
            }
            dsta[out++] = src[in++];
        }
    }

    dstb = (unsigned __int8 *)calloc(uncompressedSize, 1);
    if (!dstb)
    {
        printf("Out of Memory at %s : %i\n", "/work/harness.c", 158);
        return NULL;
    }

    memcpy(dstb, dsta + PREBUF_SKIP, uncompressedSize);
    free(dsta);
    *size = uncompressedSize;
    free(comp_Prebuf);
    
    return dstb;
}