void stbhw_free_tileset(struct Tileset *ts) {
    for (int i = 0; i < ts->h_count; i++) {
        free(ts->h_tiles[i]);
    }
    
    for (int i = 0; i < ts->v_count; i++) {
        free(ts->v_tiles[i]);
    }
    
    free(ts->h_tiles);
    free(ts->v_tiles);
    
    ts->h_tiles = NULL;
    ts->v_tiles = NULL;
    
    ts->h_count = 0;
    ts->v_count = 0;
    ts->h_count_2 = 0;
    ts->v_count_2 = 0;
}