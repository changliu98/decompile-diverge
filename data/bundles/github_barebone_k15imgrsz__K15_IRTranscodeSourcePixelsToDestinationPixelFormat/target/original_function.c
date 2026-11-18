kir_internal void _K15_IRTranscodeSourcePixelsToDestinationPixelFormat(kir_resize_context* p_Context)
{
	kir_u32 sourceWidth = p_Context->sourceWidth;
	kir_u32 sourceHeight = p_Context->sourceHeight;
	kir_u8* sourcePixels = p_Context->sourcePixels;

	kir_pixel_format sourceFormat = p_Context->sourceFormat;
	kir_pixel_format destinationFormat = p_Context->destinationFormat;

	//FK: check if we actually have to transcode pixels
	if (sourceFormat != destinationFormat)
	{
		kir_u8* transcodedSourcePixels = (kir_u8*)K15_IR_MALLOC(sourceWidth * sourceHeight * kir_format_to_byte_lut[destinationFormat]);

		if (sourceFormat == K15_IR_PIXEL_FORMAT_R8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
			_K15_IRTranscodeFromR8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
			_K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
			_K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8)
			_K15_IRTranscodeFromR8G8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
			_K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
			_K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8)
			_K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
			_K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
			_K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8)
			_K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
			_K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
		else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
			_K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);

		p_Context->transcodedSourcePixels = transcodedSourcePixels;
	}
}