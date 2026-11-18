int MPEG12_ParseSeqHdr( const unsigned char *pbuffer,
                        unsigned int buflen,
                        int *have_mpeg2,
                        unsigned int *height,
                        unsigned int *width,
                        double *frame_rate,
                        double *bitrate,
                        uint32_t *aspect_ratio )
{
    unsigned int ix;
    unsigned int scode;
    int found;
    unsigned int bitrate_int;
    unsigned int bitrate_ext;
    unsigned int aspect_code;
    unsigned int framerate_code;

    found = -1;
    *have_mpeg2 = 0;
    bitrate_int = 0;

    for( ix = 0; ix < buflen - 6; ix++ )
    {
        scode = ( (unsigned int)pbuffer[ix] << 24 )
              | ( (unsigned int)pbuffer[ix+1] << 16 )
              | ( (unsigned int)pbuffer[ix+2] << 8 )
              | ( (unsigned int)pbuffer[ix+3] );

        if( scode == 0x1B3 )
        {
            *width = ( (unsigned int)pbuffer[ix+4] << 8 )
                   | ( (unsigned int)pbuffer[ix+5] >> 4 );
            *height = ( (unsigned int)pbuffer[ix+5] & 0x0F ) << 8
                    | ( (unsigned int)pbuffer[ix+6] );

            aspect_code = ( (unsigned int)pbuffer[ix+7] >> 4 );
            if( aspect_ratio )
            {
                if( aspect_code == 2 )
                    *aspect_ratio = ( 4 << 16 ) | ( 3 );
                else if( aspect_code == 3 )
                    *aspect_ratio = ( 16 << 16 ) | ( 9 );
                else if( aspect_code == 4 )
                    *aspect_ratio = ( 221 << 16 ) | ( 100 );
                else
                    *aspect_ratio = 0;
            }

            framerate_code = ( (unsigned int)pbuffer[ix+7] & 0x0F );
            *frame_rate = mpeg12_frame_rate_table[framerate_code];

            bitrate_int = ( (unsigned int)pbuffer[ix+8] << 10 )
                        | ( (unsigned int)pbuffer[ix+9] << 2 )
                        | ( (unsigned int)pbuffer[ix+10] >> 6 );
            *bitrate = (double)bitrate_int * 400.0;

            ix += 10;
            found = 0;
        }
        else if( found == 0 )
        {
            if( scode == 0x1B5 )
            {
                if( ( (unsigned int)pbuffer[ix+4] >> 4 ) == 1 )
                {
                    *have_mpeg2 = 1;
                    *height = ( ( (unsigned int)pbuffer[ix+5] & 0x01 ) << 13 )
                            | ( ( (unsigned int)pbuffer[ix+6] & 0xF8 ) << 5 )
                            | ( *height & 0x0FFF );
                    *width = ( ( (unsigned int)pbuffer[ix+6] & 0x60 ) << 7 )
                           | ( *width & 0x0FFF );
                    bitrate_ext = ( ( (unsigned int)pbuffer[ix+6] & 0x1F ) << 7 )
                                | ( (unsigned int)pbuffer[ix+7] >> 1 );
                    bitrate_int |= bitrate_ext << 18;
                    *bitrate = (double)bitrate_int * 400.0;
                }
                ix += 4;
            }
            else if( scode == 0x100 )
            {
                return 0;
            }
        }
    }

    return found;
}