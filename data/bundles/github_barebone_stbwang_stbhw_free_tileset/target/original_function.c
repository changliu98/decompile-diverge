STBHW_EXTERN void stbhw_free_tileset(stbhw_tileset *ts)
{
   int i;
   for (i=0; i < ts->num_h_tiles; ++i)
      free(ts->h_tiles[i]);
   for (i=0; i < ts->num_v_tiles; ++i)
      free(ts->v_tiles[i]);
   free(ts->h_tiles);
   free(ts->v_tiles);
   ts->h_tiles = NULL;
   ts->v_tiles = NULL;
   ts->num_h_tiles = ts->max_h_tiles = 0;
   ts->num_v_tiles = ts->max_v_tiles = 0;
}