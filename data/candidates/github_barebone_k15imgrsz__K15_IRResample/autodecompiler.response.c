int _K15_IRResample( K15_IRContext* p_Context )
{
    int filter = p_Context->m_filter;
    int wrap_mode = p_Context->m_wrap_mode;
    unsigned char* p_source_pixels;
    unsigned char* p_destination_pixels;
    unsigned int destination_width;
    unsigned int destination_height;
    unsigned int source_width;
    unsigned int source_height;
    unsigned int pixel_format;
    unsigned int source_pitch;
    unsigned int destination_pitch;
    unsigned int temp_width;
    unsigned int temp_height;
    unsigned int temp_buffer_size_in_bytes;
    unsigned int destination_pixel_data_size_in_bytes;
    unsigned int bytes_per_pixel;
    unsigned int source_bytes_per_pixel;
    unsigned int bytes_per_line;
    unsigned int temp_pitch;
    unsigned int temp_bytes_per_line;
    unsigned int temp_bytes_per_line_offset;
    unsigned int temp_bytes_per_line_padding;
    unsigned int temp_bytesperline;
    unsigned int temp_bytesperline_offset;
    unsigned int temp_bytesperline_padding;
    unsigned int temp_bytesperline_total;
    unsigned int temp_bytesperline_total_offset;
    unsigned int temp_bytesperline_total_total;
    unsigned int temp_bytesperline_total_total_offset;
    unsigned int temp_bytesperline_total_total_total;
    unsigned int temp_bytesperline_total_total_total_offset;
    unsigned int temp_bytesperline_total_total_total_total;
    unsigned int temp_bytesperline_total_total_total_total_offset;
    unsigned int temp_bytesperline_total_total_total_total_total;
    unsigned int temp_bytesperline_total_total_total_total_total_offset;
    unsigned int temp_bytesperline_total_total_total_total_total_total;
    unsigned int temp_bytesperline_total_total_total_total_total_total_offset;
    unsigned int temp_bytesperline_total_total_total_total_total_total_total;
    unsigned int temp_bytesperline_total_total_total_total_total_total_total_offset;
kerror_t error;

    if ( p_Context->m_pSourcePixels )
    {
        p_source_pixels = p_Context->m_pSourcePixels;
    }
    else
    {
        p_source_pixels = p_Context->m_pSourceBitmapMemory;
    }

    p_destination_pixels = p_Context->m_pDestinationBitmapMemory;

    destination_width = p_Context->m_destinationWidth;
    destination_height = p_Context->m_destinationHeight;
    source_height = p_Context->m_sourceHeight;
    source_width = p_Context->m_sourceWidth;
    wrap_mode = p_Context->m_wrap_mode;
    pixel_format = p_Context->m_pixelFormat;

    bytes_per_pixel = kir_format_to_byte_lut[ pixel_format ];

    destination_pixel_data_size_in_bytes = destination_width * destination_height * bytes_per_pixel;

    memset( p_destination_pixels, 0, destination_pixel_data_size_in_bytes );

    switch ( filter )
    {
    case 0:
        _K15_IRSampleNearestNeighbour( p_source_pixels, p_Context->m_pDestinationBitmapMemory, p_Context->m_sourceWidth, p_Context->m_sourceHeight, p_Context->m_destinationWidth, p_Context->m_destinationHeight, p_Context->m_pixelFormat );
        break;

    case 1:
    case 2:
        {

            temp_width = destination_width;
            temp_height = source_height;

            pixel_format = p_Context->m_pixelFormat;

            bytes_per_pixel = kir_format_to_byte_lut[ pixel_format ];

            temp_buffer_size_in_bytes = temp_width * temp_height * bytes_per_pixel;

            unsigned char* p_temp_pixels = (unsigned char*)malloc( temp_buffer_size_in_bytes );
            memset( p_temp_pixels, 0, temp_buffer_size_in_bytes );

            if ( filter == 1 )
            {
                _K15_IRHorizontallySampleBilinear( p_source_pixels, p_temp_pixels, source_width, source_height, temp_width, temp_height, wrap_mode, pixel_format );

                temp_width = source_height;
                temp_height = destination_width;

                destination_width = p_Context->m_destinationHeight;
                destination_height = p_Context->m_destinationWidth;

                _K15_IRHorizontallySampleBilinear( p_temp_pixels, p_destination_pixels, temp_width, temp_height, destination_width, destination_height, wrap_mode, pixel_format );
            }
            else if ( filter == 2 )
            {
                _K15_IRHorizontallySampleBicubic( p_source_pixels, p_temp_pixels, source_width, source_height, temp_width, temp_height, wrap_mode, pixel_format );

                temp_width = source_height;
                temp_height = destination_width;

                destination_width = p_Context->m_destinationHeight;
                destination_height = p_Context->m_destinationWidth;

                _K15_IRHorizontallySampleBicubic( p_temp_pixels, p_destination_pixels, temp_width, temp_height, destination_width, destination_height, wrap_mode, pixel_format );
            }

        }
        break;

    default:
        return 1;
    }

    return 0;
}