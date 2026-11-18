int openI2CBus(int *bus,char * device)
{
        *bus = open(device, O_RDWR);
        if (*bus<0)
         return 1;

        return 0;
}