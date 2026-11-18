static _Bool dyld_cache_load(struct RBinFile *rbin, void **dyld_cache, struct RBuffer *buf, unsigned long loadaddr, struct Sdb *sdb)
{
  struct RDyldCache *dyld = (RDyldCache*)dyld_calloc(1, sizeof(RDyldCache));
  dyld->magic[0] = 0x63616364;
  dyld->magic[1] = 0x62696c65;
  dyld->magic[2] = 0x63;
  dyld->buf = rbin_to_dyld_buf(buf);
  dyld_load_header(dyld);
  if (dyld->hdr == ((void *)0))
    goto fail;
  dyld_load_maps(dyld);
  if (dyld->maps == ((void *)0))
    goto fail;
  dyld->accel = dyld_load_accel(dyld->buf, dyld->hdr, dyld->maps);
  dyld->bins = dyld_load_binaries(rbin, dyld);
  if (dyld->bins == ((void *)0))
    goto fail;
  dyld->locsym = dyld_load_locsym(dyld);
  dyld->rebase_infos = dyld_load_rebase_infos(rbin, dyld);
  if (dyld->rebase_infos == ((void *)0))
    goto fail;
  if (dyld_load_rebase_data(dyld))
    goto success;
  if (pending_bin_files == ((void *)0))
  {
    pending_bin_files = dyld_load_pending_bin_files();
    if (pending_bin_files == ((void *)0))
      goto fail;
  }
  chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(pending_bin_files, rbin->rbin);
  dyld_load_pending_bin(dyld, rbin->rbin->iob.io);
success:
  *dyld_cache = dyld;
  return 1;
fail:
  dyld_destroy(dyld);
  return 0;
}