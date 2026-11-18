int writejpeg( const char *filename, int width, int height, byte *data ) {
	byte	*buffer;
	int		len;

	buffer = ri.Hunk_AllocateTempMemory( width * height * 4 + 18 );
	memset( buffer, 0, 18 );
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 24;	// pixel size

	// swap rgb to bgr
	len = width * height * 3;
	while ( len-- ) {
		buffer[18 + 2] = *data++;
		buffer[18 + 1] = *data++;
		buffer[18 + 0] = *data++;
		data++;
	}

	ri.FS_WriteFile( filename, buffer, 18 + width * height * 3 );

	ri.Hunk_FreeTempMemory( buffer );

	return 2;
}