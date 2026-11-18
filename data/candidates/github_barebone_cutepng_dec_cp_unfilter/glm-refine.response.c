int __cdecl cp_unfilter(int w, int h, int bpp, uint8_t *raw)
{
    int len = bpp * w;
    if (len <= 0 || h <= 0) {
        return 1;
    }

    uint8_t *curr = raw + 1;
    uint8_t *prev = NULL;

    // Unfilter the first row (prev is implicitly all zeros)
    switch (*raw)
    {
        case 0: // None
        case 2: // Up (Adding 0 does nothing)
            break;
        case 1: // Sub
            for (int x = bpp; x < len; ++x)
                curr[x] += curr[x - bpp];
            break;
        case 3: // Average
            for (int x = bpp; x < len; ++x)
                curr[x] += curr[x - bpp] / 2;
            break;
        case 4: // Paeth
            for (int x = bpp; x < len; ++x)
                curr[x] += cp_paeth(curr[x - bpp], 0, 0);
            break;
        default:
            return 0; // Invalid filter type
    }

    prev = curr;
    curr += len;

    // Unfilter subsequent rows
    for (int y = 1; y < h; ++y)
    {
        uint8_t filter_type = *curr;
        uint8_t *data = curr + 1;

        switch (filter_type)
        {
            case 0: // None
                break;
            case 1: // Sub
                for (int x = bpp; x < len; ++x)
                    data[x] += data[x - bpp];
                break;
            case 2: // Up
                for (int x = 0; x < len; ++x)
                    data[x] += prev[x];
                break;
            case 3: // Average
                for (int x = 0; x < bpp; ++x)
                    data[x] += prev[x] / 2;
                for (int x = bpp; x < len; ++x)
                    data[x] += (prev[x] + data[x - bpp]) / 2;
                break;
            case 4: // Paeth
                for (int x = 0; x < bpp; ++x)
                    data[x] += prev[x];
                for (int x = bpp; x < len; ++x)
                    data[x] += cp_paeth(data[x - bpp], prev[x], prev[x - bpp]);
                break;
            default:
                return 0; // Invalid filter type
        }

        prev = data;
        curr = data + len;
    }

    return 1;
}