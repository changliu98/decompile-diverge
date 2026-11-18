void goertzel_filter_v1 ( short int * delay, short int input, short int coefficient )
{
    short int product;

 product = (short int) (( (long) delay[1] * coefficient ) >> 14) - delay[2];


 delay[2] = delay[1];
 delay[1] = (short int)( (input >> 7) + product);
}