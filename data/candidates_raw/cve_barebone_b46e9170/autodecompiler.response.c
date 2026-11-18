static int
cac_cac1_read_binary (SCCard * card, unsigned int fileid,
       unsigned char *buffer, size_t length, SCAddress * addr)
{
  struct cac_data *data = (struct cac_data *) card->drv_data;
  int ret = 0, r;
  size_t retlen, len;
  unsigned char *cert_buffer = NULL, cert_type, *cert_ptr;
  size_t cert_len, cert_size;
  size_t readlen;

  if (data->cached_file_id)
    {
      if (fileid > data->cached_file_len)
 {
   r = -1220 - 1;
   goto done;
 }
      if (length < data->cached_file_len - fileid)
 len = length;
      else
 len = data->cached_file_len - fileid;
      retlen = len;
      memcpy (buffer, data->cached_file + fileid, retlen);
      r = retlen;
      goto done;
    }

  free (data->cached_file);
  data->cached_file = NULL;
  data->cached_file_len = 0;

  ret = cac_cac1_get_certificate (card, &cert_buffer, &cert_size);
  if (ret < 0)
    goto done;

  if (cert_size < 2)
    {
      ret = -1305 - 1;
      goto done;
    }

  cert_type = cert_buffer[0];
  cert_ptr = cert_buffer + 1;
  cert_len = cert_size - 1;

  if ((cert_type & 0x03) == 0x01)
    {
      ret = -1408 - 1;
      if (ret)
 goto done;
    }
  else
    {
      if (cert_len > 0)
 {
   data->cached_file = (unsigned char *) malloc (cert_len);
   if (!data->cached_file)
     {
       ret = -1404 - 1;
       goto done;
     }
   data->cached_file_len = cert_len;
   memcpy (data->cached_file, cert_ptr, cert_len);
 }
    }

  data->cached_file_id = 1;

  if (length < data->cached_file_len - fileid)
    readlen = length;
  else
    readlen = data->cached_file_len - fileid;

  retlen = readlen;
  if (retlen && data->cached_file)
    memcpy (buffer, data->cached_file + fileid, retlen);

  ret = retlen;

done:
  if (cert_buffer)
    free (cert_buffer);

  r = ret;
done:
  return r;
}