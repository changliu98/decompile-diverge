
void rgb2hsv( int r, int g, int b, int *h, int *s, int *v )
{
    int max;
    int min;

    max = r > g ? r : g;
    if( b > max ) max = b;

    min = r < g ? r : g;
    if( b < min ) min = b;

    if( max == 0 )
    {
        *v = 0;
        *h = 0; *s = 0;
        return;
    }
    else if( max == min )
    {
        *h = 0;
    }
    else if( max == r && g >= b )
    {
        *h = ( 10 * 60 * ( g - b )/( max - min ) );
    }
    else if( max == r && g < b )
    {
        *h = ( 10 * ( 60 * ( g - b )/( max - min ) + 360 ));
    }
    else if( max == g )
    {
        *h = ( 10 * ( 60 * ( b - r )/( max - min ) + 120 ));
    }
    else
    {
        *h = ( 10 * ( 60 * ( r - g )/( max - min ) + 240 ));
    }


    while( *h < 0 ) *h += 3600;
    while( *h >= 3600 ) *h-= 3600;

    *s = (( max - min )*255)/max;
    *v = max;
}
