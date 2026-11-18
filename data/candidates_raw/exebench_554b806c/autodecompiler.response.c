int check_end_spectrum(float *spectrum, int size)
{
    int i = 0;
    char flag;

    while(1) {
        if(i > size) {
            flag = 1;
            break;
        }
        if(spectrum[i] > 8388608.0) {
            flag = 0;
            break;
        }
        i++;
    }
    return flag;
}