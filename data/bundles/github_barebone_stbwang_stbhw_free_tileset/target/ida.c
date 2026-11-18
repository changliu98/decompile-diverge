void __cdecl stbhw_free_tileset(stbhw_tileset *ts)
{
  int i; // [rsp+4h] [rbp-Ch]
  int ia; // [rsp+4h] [rbp-Ch]

  for ( i = 0; i < ts->num_h_tiles; ++i )
    free(ts->h_tiles[i]);
  for ( ia = 0; ia < ts->num_v_tiles; ++ia )
    free(ts->v_tiles[ia]);
  free(ts->h_tiles);
  free(ts->v_tiles);
  ts->h_tiles = 0LL;
  ts->v_tiles = 0LL;
  ts->max_h_tiles = 0;
  ts->num_h_tiles = 0;
  ts->max_v_tiles = 0;
  ts->num_v_tiles = 0;
}