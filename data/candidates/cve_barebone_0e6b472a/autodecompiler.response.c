int AVI_read_audio( struct avi_handle *ah, char *buffer, int size,
                  int *contin )
{
    int chunk_size, done;
    long long chunk_offset;
    unsigned int read_size;

    if( !ah->ah_audio ) {
        AVI_errno = 7;
        return -1;
    }

    if( ah->avih[ah->ah_curidx].idx_audio == NULL ) {
        AVI_errno = 13;
        return -1;
    }

    done = 0;

    if( size == 0 ) {
        ah->avih[ah->ah_curidx].i_audio += 1;
        ah->avih[ah->ah_curidx].o_audio = 0;
    }

    *contin = 1;

    while( size > 0 ) {
        chunk_size = ah->avih[ah->ah_curidx].idx_audio[
            ah->avih[ah->ah_curidx].i_audio ].size -
            ah->avih[ah->ah_curidx].o_audio;

        if( chunk_size == 0 ) {

            if( ah->avih[ah->ah_curidx].i_audio >=
                ah->avih[ah->ah_curidx].num_audio-1 ) {
                return done;
            } else {
                ah->avih[ah->ah_curidx].i_audio += 1;
                ah->avih[ah->ah_curidx].o_audio = 0;
                *contin = 0;
            }
        } else {
            if( size < chunk_size ) read_size = size;
            else read_size = chunk_size;

            chunk_offset = ah->avih[ah->ah_curidx].idx_audio[
                ah->avih[ah->ah_curidx].i_audio ].offset +
                ah->avih[ah->ah_curidx].o_audio;

            gf_fseek( ah->fd, chunk_offset, 0 );

            if( avi_read( ah->fd, buffer+done, read_size ) != read_size ) {
                while( 0 ) { printf__bench( "Error reading audio from file %s at offset %lld, size %d\n", ah->filename, chunk_offset, read_size ); };
                AVI_errno = 3;
                return -1;
            }

            size -= read_size;
            done += read_size;
            ah->avih[ah->ah_curidx].o_audio += read_size;
        }
    }

    return done;
}