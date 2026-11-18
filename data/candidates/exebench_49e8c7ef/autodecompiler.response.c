void
clib_mallinfo(GLcontext *ctx,
                   GLuint64EXT *total_mem,
                   GLuint64EXT *free_mem,
                   GLuint64EXT *used_mem,
                   GLuint64EXT *total_mapped_mem,
                   GLuint64EXT *free_mapped_mem)
{
   *total_mem = ~0ULL;
   *free_mem = ~0ULL;
   *used_mem = ~0ULL;
   *total_mapped_mem = ~0ULL;
   *free_mapped_mem = ~0ULL;
}