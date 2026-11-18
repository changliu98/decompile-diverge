void __cdecl stbhw_free_tileset(stbhw_tileset *ts)
{
  int i;

  // Free individual horizontal tiles
  for (i = 0; i < ts->num_h_tiles; ++i)
    free(ts->h_tiles[i]);

  // Free individual vertical tiles
  for (i = 0; i < ts->num_v_tiles; ++i)
    free(ts->v_tiles[i]);

  // Free the arrays holding the tiles
  free(ts->h_tiles);
  free(ts->v_tiles);

  // Reset state
  ts->h_tiles = NULL;
  ts->v_tiles = NULL;
  ts->max_h_tiles = 0;
  ts->num_h_tiles = 0;
  ts->max_v_tiles = 0;
  ts->num_v_tiles = 0;
}