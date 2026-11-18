static int cac_read_binary(cac_connection_t *cac, unsigned int offset,
                           unsigned char *buffer, unsigned int buffer_size,
                           unsigned long timeout) {
  cac_data_t *cac_data = cac->data;
  int result = 0;
  unsigned char *certificate = NULL;
  unsigned char certificate_type;
  unsigned char *certificate_data;
  unsigned int certificate_data_size;
  unsigned int bytes_to_copy;
  if (cac_data->certificate_valid) {
    if (offset > cac_data->certificate_size) return -1219;
    if (buffer_size < cac_data->certificate_size - offset)
      bytes_to_copy = buffer_size;
    else
      bytes_to_copy = cac_data->certificate_size - offset;
    memcpy(buffer, cac_data->certificate + offset, bytes_to_copy);
    return bytes_to_copy;
  }
  free(cac_data->certificate);
  cac_data->certificate = NULL;
  cac_data->certificate_size = 0;
  result = cac_cac1_get_certificate(cac, &certificate, &certificate_data_size);
  if (result < 0) goto done;
  if (certificate_data_size == 0) {
    result = -1305;
    goto done;
  }
  certificate_type = certificate[0];
  certificate_data = certificate + 1;
  certificate_data_size--;
  if ((certificate_type & 0x03) == 0x01) {
    result = -1408;
    goto done;
  }
  if (certificate_data_size > 0) {
    cac_data->certificate = malloc(certificate_data_size);
    if (cac_data->certificate == NULL) {
      result = -1404;
      goto done;
    }
    cac_data->certificate_size = certificate_data_size;
    memcpy(cac_data->certificate, certificate_data, certificate_data_size);
  }
  cac_data->certificate_valid = 1;
  if (buffer_size < cac_data->certificate_size - offset)
    bytes_to_copy = buffer_size;
  else
    bytes_to_copy = cac_data->certificate_size - offset;
  if (bytes_to_copy > 0 && cac_data->certificate != NULL)
    memcpy(buffer, cac_data->certificate + offset, bytes_to_copy);
  result = bytes_to_copy;
done:
  if (certificate != NULL) free(certificate);
  return result;
}