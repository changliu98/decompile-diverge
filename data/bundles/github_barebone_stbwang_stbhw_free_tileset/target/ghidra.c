void stbhw_free_tileset(stbhw_tileset *ts)

{
  int i;
  stbhw_tileset *ts_local;
  
  for (i = 0; i < ts->num_h_tiles; i = i + 1) {
    free(ts->h_tiles[i]);
  }
  for (i = 0; i < ts->num_v_tiles; i = i + 1) {
    free(ts->v_tiles[i]);
  }
  free(ts->h_tiles);
  free(ts->v_tiles);
  ts->h_tiles = (stbhw_tile **)0x0;
  ts->v_tiles = (stbhw_tile **)0x0;
  ts->max_h_tiles = 0;
  ts->num_h_tiles = 0;
  ts->max_v_tiles = 0;
  ts->num_v_tiles = 0;
  return;
}