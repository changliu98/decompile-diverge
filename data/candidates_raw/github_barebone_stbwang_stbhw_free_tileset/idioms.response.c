void stbhw_tileset_free(struct stbhw_tileset *ts)
{
  int i;
  for (i = 0; i < ts->num_h_tiles; i++)
    stbhw_tile_free(ts->h_tiles[i]);
  for (i = 0; i < ts->num_v_tiles; i++)
    stbhw_tile_free(ts->v_tiles[i]);
  stbhw_tile_free(ts->h_tiles);
  stbhw_tile_free(ts->v_tiles);
  ts->h_tiles = ((void *)0);
  ts->v_tiles = ((void *)0);
  ts->max_h_tiles = 0;
  ts->num_h_tiles = 0;
  ts->max_v_tiles = 0;
  ts->num_v_tiles = 0;
}