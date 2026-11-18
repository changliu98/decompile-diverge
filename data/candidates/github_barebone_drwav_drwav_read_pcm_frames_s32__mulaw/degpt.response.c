drwav_uint64
drwav_read_pcm_frames_s32__mulaw(drwav *wav_file, drwav_uint64 frames_requested, drwav_int32 *output_buffer)
{
    drwav_uint32 bytes_per_frame;
    drwav_uint64 total_frames_read;
    drwav_uint8 raw_sample_buffer[4096];
    drwav_uint64 frames_read;
    drwav_uint64 frames_to_read_current;
    drwav_uint64 samples_read;
    drwav_uint32 bytes_per_sample;
    drwav_uint32 bytes_per_frame;
    drwav_uint8 raw_sample_buffer [4096];
    drwav_uint64 total_frames_read;
    drwav_int32 *output_buffer_ptr;
    drwav_uint64 frames_remaining;
    drwav *pWav_local;
    drwav_uint64 frames_returned;
    
    // Initialize the sample buffer to zero to ensure clean memory before reading raw data
    memset(raw_sample_buffer,0,0x1000);
    
    // Get the number of bytes per PCM frame for the WAV file
    bytes_per_frame_val = drwav_get_bytes_per_pcm_frame(wav_file);
    
    // If bytes per frame is zero, no data can be read
    if (bytes_per_frame_val == 0) {
      frames_returned = 0;
    }
    else {
      // Calculate bytes per sample by dividing bytes per frame by number of channels
      bytes_per_sample_val = bytes_per_frame_val / wav_file->channels;
      
      // Validate that bytes per sample is non-zero and that bytes per frame is evenly divisible by channels
      if ((bytes_per_sample_val == 0) || (bytes_per_frame_val % (uint)wav_file->channels != 0)) {
        frames_returned = 0;
      }
      else {
        // Initialize total frames read counter to zero
        total_frames_read = 0;
        
        // Create local pointers/variables for iteration to avoid modifying original arguments directly if needed
        output_buffer_ptr = output_buffer;
        
        // Loop until all requested frames are read or no more data is available
        for (frames_remaining = frames_requested; frames_remaining != 0;
            frames_remaining = frames_remaining - frames_read_current) {
          
          // Determine the number of frames to read in this iteration, capped by buffer size limits
          if (frames_remaining < SUB168((ZEXT816(0) << 0x40 | ZEXT816(0x1000)) / ZEXT416(bytes_per_frame_val),0))
          {
            frames_to_read_chunk = frames_remaining;
          }
          else {
            frames_to_read_chunk = SUB168((ZEXT816(0) << 0x40 | ZEXT816(0x1000)) / ZEXT416(bytes_per_frame_val),0);
          }
          
          // Read raw PCM frames into the sample buffer
          frames_read_current = drwav_read_pcm_frames(wav_file,frames_to_read_chunk,raw_sample_buffer);
          
          // If no frames were read, break the loop as end of file or error
          if (frames_read_current == 0) break;
          
          // Assert that the number of frames read does not exceed the requested amount for this iteration
          if (frames_to_read_chunk < frames_read_current) {
                      /* WARNING: Subroutine does not return */
            __assert_fail("framesRead <= framesToReadThisIteration","func.c",0x1f0a,
                          "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"
                         );
          }
          
          // Calculate total number of samples (frames * channels) for conversion
          total_samples = frames_read_current * wav_file->channels;
          
          // Assert that the converted data will fit within the output buffer constraints
          if (0x1000 < total_samples * bytes_per_sample_val) {
                      /* WARNING: Subroutine does not return */
            __assert_fail("0","func.c",0x1f0f,
                          "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"
                         );
          }
          
          // Convert mu-law encoded samples from sampleData to signed 32-bit integers in pBufferOut_local
          drwav_mulaw_to_s32(output_buffer_ptr,raw_sample_buffer,total_samples);
          
          // Advance the output buffer pointer by the number of samples processed
          output_buffer_ptr = output_buffer_ptr + total_samples;
          
          // Add the frames read in this iteration to the total count
          total_frames_read = frames_read_current + total_frames_read;
        }
        // Store the total number of frames successfully read
        frames_returned = total_frames_read;
      }
    }
    // Return the total number of PCM frames read
    return frames_returned;
}