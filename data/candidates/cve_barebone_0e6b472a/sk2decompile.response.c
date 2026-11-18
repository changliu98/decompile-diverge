int AVI_read_audio(AVI_file *file, unsigned char *buffer, int bytes,
                   int *continued) {
  int total, left, toread;
  if (!file->initialized) {
    AVI_error = 7;
    return -1;
  }
  if (!file->streams[file->current_audio_stream].index) {
    AVI_error = 13;
    return -1;
  }
  total = 0;
  if (bytes == 0) {
    file->streams[file->current_audio_stream].current_index++;
    file->streams[file->current_audio_stream].current_offset = 0;
  }
  *continued = 1;
  while (bytes > 0) {
    left = file->streams[file->current_audio_stream]
               .index[file->streams[file->current_audio_stream].current_index]
               .length -
           file->streams[file->current_audio_stream].current_offset;
    if (left == 0) {
      if (file->streams[file->current_audio_stream].current_index >=
          file->streams[file->current_audio_stream].index_count - 1)
        return total;
      file->streams[file->current_audio_stream].current_index++;
      file->streams[file->current_audio_stream].current_offset = 0;
      *continued = 0;
      continue;
    }
    if (bytes < left)
      toread = bytes;
    else
      toread = left;
    gf_fseek(file->f,
             file->streams[file->current_audio_stream]
                 .index[file->streams[file->current_audio_stream].current_index]
                 .position +
                 file->streams[file->current_audio_stream].current_offset,
             0);
    if (avi_read(file->f, buffer + total, toread) != toread) {
      AVI_error = 3;
      return -1;
    }
    bytes -= toread;
    total += toread;
    file->streams[file->current_audio_stream].current_offset += toread;
  }
  return total;
}