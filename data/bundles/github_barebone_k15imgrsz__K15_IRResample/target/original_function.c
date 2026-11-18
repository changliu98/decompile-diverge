kir_internal kir_result _K15_IRResample(kir_resize_context* p_Context)
{
	kir_filter filter = p_Context->filter;
	kir_u32 flags = p_Context->flags;
	kir_u8* sourcePixels = (p_Context->transcodedSourcePixels ? p_Context->transcodedSourcePixels : p_Context->sourcePixels);
	kir_u8* destinationPixels = p_Context->destinationPixels;
	kir_u32 destinationWidth = p_Context->destinationWidth;
	kir_u32 destinationHeight = p_Context->destinationHeight;
	kir_u32 sourceHeight = p_Context->sourceHeight;
	kir_u32 sourceWidth = p_Context->sourceWidth;
	kir_wrap_mode wrapMode = p_Context->wrapMode;
	kir_pixel_format pixelFormat = p_Context->destinationFormat;

	int bpp = kir_format_to_byte_lut[p_Context->destinationFormat];

	kir_u32 destinationPixelDataSizeInBytes = destinationWidth * destinationHeight * bpp;
	K15_IR_MEMSET(destinationPixels, 0, destinationPixelDataSizeInBytes);

	if (filter == K15_IR_NEAREST_NEIGHBOUR_FILTER)
	{
		_K15_IRSampleNearestNeighbour(sourcePixels, p_Context->destinationPixels,
			p_Context->sourceWidth, p_Context->sourceHeight, p_Context->destinationWidth, 
			p_Context->destinationHeight, p_Context->destinationFormat);
	}
	else if (filter == K15_IR_BILINEAR_FILTER ||
		filter == K15_IR_BICUBIC_FILTER)
	{
		kir_u32 tempWidth = destinationWidth;
		kir_u32 tempHeight = sourceHeight;

		kir_pixel_format format = p_Context->destinationFormat;
		kir_u32 bpp = kir_format_to_byte_lut[format];
		kir_u32 tempBufferSizeInBytes = tempWidth * tempHeight * bpp;
		kir_u8* horizontalTempBuffer = (kir_u8*)K15_IR_MALLOC(tempBufferSizeInBytes);
		K15_IR_MEMSET(horizontalTempBuffer, 0, tempBufferSizeInBytes);

		if (filter == K15_IR_BILINEAR_FILTER)
		{
			_K15_IRHorizontallySampleBilinear(sourcePixels, horizontalTempBuffer, 
				sourceWidth, sourceHeight, 
				tempWidth, tempHeight, 
				pixelFormat, wrapMode);
		
			//FK: Image now vertically aligned as opposed to horizintally.
			//	  Lets switch width and height, so everything is back to "normal".
			tempWidth = sourceHeight;
			tempHeight = destinationWidth;

			destinationWidth = p_Context->destinationHeight;
			destinationHeight = p_Context->destinationWidth;

			_K15_IRHorizontallySampleBilinear(horizontalTempBuffer, destinationPixels, 
				tempWidth, tempHeight, 
				destinationWidth, destinationHeight,
				pixelFormat, wrapMode);
		}
		else if (filter == K15_IR_BICUBIC_FILTER)
		{
			_K15_IRHorizontallySampleBicubic(sourcePixels, horizontalTempBuffer,
				sourceWidth, sourceHeight,
				tempWidth, tempHeight,
				pixelFormat, wrapMode);

			//FK: Image now vertically aligned as opposed to horizintally.
			//	  Lets switch width and height, so everything is back to "normal".
			tempWidth = sourceHeight;
			tempHeight = destinationWidth;

			destinationWidth = p_Context->destinationHeight;
			destinationHeight = p_Context->destinationWidth;

			_K15_IRHorizontallySampleBicubic(horizontalTempBuffer, destinationPixels, 
				tempWidth, tempHeight, 
				destinationWidth, destinationHeight,
				pixelFormat, wrapMode);
		}

	}

	return K15_IR_RESULT_SUCCESS;
}