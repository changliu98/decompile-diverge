
static int setsize(unsigned long capacity,unsigned int *cyls,unsigned int *hds,
    unsigned int *secs) {
    unsigned int rv = 0;
    unsigned long heads, sectors, cylinders, temp;

    cylinders = 1024L;
    sectors = 62L;

    temp = cylinders * sectors;
    heads = capacity / temp;
    if (capacity % temp) {
     heads++;
     temp = cylinders * heads;
     sectors = capacity / temp;

     if (capacity % temp) {
           sectors++;
           temp = heads * sectors;
           cylinders = capacity / temp;
       }
    }
    if (cylinders == 0) rv=(unsigned)-1;

    *cyls = (unsigned int) cylinders;
    *secs = (unsigned int) sectors;
    *hds = (unsigned int) heads;
    return(rv);
}
