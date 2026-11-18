int AVI_read_audio(avi_t *AVI, void *audbuf, int bytes, int *continuous)
{
    int todo;
    int nr;

    if (!AVI->mode) {
        AVI_errno = 7;
        return -1;
    }

    if (!AVI->track[AVI->aptr].audio_index) {
        AVI_errno = 13;
        return -1;
    }

    nr = 0;

    if (bytes == 0) {
        AVI->track[AVI->aptr].audio_posc++;
        AVI->track[AVI->aptr].audio_posb = 0;
    }

    *continuous = 1;

    while (bytes > 0) {
        todo = AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len - AVI->track[AVI->aptr].audio_posb;
        if (todo == 0) {
            if (AVI->track[AVI->aptr].audio_posc < AVI->track[AVI->aptr].audio_chunks - 1) {
                AVI->track[AVI->aptr].audio_posc++;
                AVI->track[AVI->aptr].audio_posb = 0;
                *continuous = 0;
                continue;
            }
            else {
                return nr;
            }
        }
        if (todo > bytes) todo = bytes;

        gf_fseek(AVI->fdes, AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].pos + AVI->track[AVI->aptr].audio_posb, 0);
        if (avi_read(AVI->fdes, ((char *)audbuf) + nr, todo) != todo) {
            AVI_errno = 3;
            return -1;
        }

        bytes -= todo;
        nr += todo;
        AVI->track[AVI->aptr].audio_posb += todo;
    }

    return nr;
}