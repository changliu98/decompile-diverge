uint64_t drmp3_get_pcm_frame_count(struct drmp3* pMP3) {
    uint64_t frameCount;

    if (pMP3 == NULL) {
        frameCount = 0;
    } else {
        // Check if the current PCM frame cursor is valid (not -1)
        if (*(uint64_t*)((char*)pMP3 + 0x7e28) != (uint64_t)-1) {
            uint64_t currentFrame = *(uint64_t*)((char*)pMP3 + 0x7e28);
            
            // Clamp the current frame to the decoded frames boundary
            if (currentFrame >= *(uint64_t*)((char*)pMP3 + 0x7e1c)) {
                currentFrame -= *(uint64_t*)((char*)pMP3 + 0x7e1c);
            }
            
            // Clamp the current frame to the total frames boundary
            if (currentFrame >= *(uint64_t*)((char*)pMP3 + 0x7e20)) {
                currentFrame -= *(uint64_t*)((char*)pMP3 + 0x7e20);
            }
            
            frameCount = currentFrame;
        } else {
            // If the cursor is invalid, calculate it by scanning the file
            if (!drmp3__seek_and_read_pcm_frames(pMP3, 0, &frameCount)) {
                frameCount = 0;
            }
        }
    }

    return frameCount;
}