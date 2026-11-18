int read_image_descriptor(GifFileType* GifFileOut)
{
 int code;
 unsigned char byte;

 GifFileOut->ImageDesc.LeftPosition = read_num(GifFileOut->fd);
 GifFileOut->ImageDesc.TopPosition = read_num(GifFileOut->fd);

 if ((GifFileOut->ImageDesc.LeftPosition >= GifFileOut->SWidth) ||
  (GifFileOut->ImageDesc.TopPosition >= GifFileOut->SHeight)) {
  code = -1;
  goto out;
 }

 GifFileOut->ImageDesc.Width = read_num(GifFileOut->fd);
 GifFileOut->ImageDesc.Height = read_num(GifFileOut->fd);

 if (GifFileOut->ImageDesc.Width > (GifFileOut->SWidth - GifFileOut->ImageDesc.LeftPosition))
  GifFileOut->ImageDesc.Width = GifFileOut->SWidth - GifFileOut->ImageDesc.LeftPosition;

 if (GifFileOut->ImageDesc.Height > (GifFileOut->SHeight - GifFileOut->ImageDesc.TopPosition))
  GifFileOut->ImageDesc.Height = GifFileOut->SHeight - GifFileOut->ImageDesc.TopPosition;

 read(&GifFileOut->fd, &byte, 1);

 int interlace = byte & 0x40;
 if (byte & 0x80) {
  GifFileOut->ImageDesc.ColorMap = (ColorMapType*)GifFileOut;
  GifFileOut->ImageDesc.ColorMap->ColorCount = 1 << ((byte & 7) + 1);
  read(GifFileOut->fd, &GifFileOut->ImageDesc.ColorMap->Colors[0],
   GifFileOut->ImageDesc.ColorMap->ColorCount * 3);
 } else {
  GifFileOut->ImageDesc.ColorMap = &GifFileOut->GlobalColorMap;
 }

 code = read_image_data(GifFileOut, interlace);

out:

 return code;
}