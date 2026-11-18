static void idctMcu(unsigned char mcuBlock)
{
    idctRows();
    idctCols();

    switch(gScanType)
    {
        case 0:
            copyY(0);
            break;
        case 1:
        {
            unsigned int i = mcuBlock;

            if (i == 0) copyY(0);
            else if (--i == 0) convertCb(0);
            else if (--i == 0) convertCr(0);
            break;
        }
        case 3:
        {
            unsigned int i = mcuBlock;

            switch(i)
            {
                case 0:
                    copyY(0);
                    break;
                case 1:
                    copyY(128);
                    break;
                case 2:
                    upsampleCbV(0, 0);
                    upsampleCbV(32, 128);
                    break;
                case 3:
                    upsampleCrV(0, 0);
                    upsampleCrV(32, 128);
                    break;
            }
            break;
        }
        case 2:
        {
            unsigned int i = mcuBlock;

            switch(i)
            {
                case 0:
                    copyY(0);
                    break;
                case 1:
                    copyY(64);
                    break;
                case 2:
                    upsampleCbH(0, 0);
                    upsampleCbH(4, 64);
                    break;
                case 3:
                    upsampleCrH(0, 0);
                    upsampleCrH(4, 64);
                    break;
            }
            break;
        }
        case 4:
        {
            unsigned int i = mcuBlock;

            switch(i)
            {
                case 0:
                    copyY(0);
                    break;
                case 1:
                    copyY(64);
                    break;
                case 2:
                    copyY(128);
                    break;
                case 3:
                    copyY(192);
                    break;
                case 4:
                    upsampleCb(0, 0);
                    upsampleCb(4, 64);
                    upsampleCb(32, 128);
                    upsampleCb(36, 192);
                    break;
                case 5:
                    upsampleCr(0, 0);
                    upsampleCr(4, 64);
                    upsampleCr(32, 128);
                    upsampleCr(36, 192);
                    break;
            }
            break;
        }
    }
}