void fmtutil_macbitmap_read_pixmap_only_fields
               (deark *c,dbuf *f,fmtutil_macbitmap_info *bi,int64_t pos)

{
  ulong uVar1;
  int64_t iVar2;
  double dVar3;
  int64_t n;
  int64_t plane_bytes;
  int64_t pack_size;
  int64_t pixmap_version;
  int64_t pos_local;
  fmtutil_macbitmap_info *bi_local;
  dbuf *f_local;
  deark *c_local;
  
  de_dbg(c,"additional PixMap header fields, at %d",pos & 0xffffffff);
  de_dbg_indent(c,1);
  uVar1 = dbuf_getu16be(f,pos);
  de_dbg(c,"pixmap version: %d",uVar1 & 0xffffffff);
  iVar2 = dbuf_getu16be(f,pos + 2);
  bi->packing_type = iVar2;
  de_dbg(c,"packing type: %d",bi->packing_type & 0xffffffff);
  uVar1 = dbuf_getu32be(f,pos + 4);
  de_dbg(c,"pixel data length: %d",uVar1 & 0xffffffff);
  dVar3 = pict_read_fixed(f,pos + 8);
  bi->hdpi = dVar3;
  dVar3 = pict_read_fixed(f,pos + 0xc);
  bi->vdpi = dVar3;
  de_dbg(c,&DAT_00102071,bi->hdpi,bi->vdpi);
  iVar2 = dbuf_getu16be(f,pos + 0x10);
  bi->pixeltype = iVar2;
  iVar2 = dbuf_getu16be(f,pos + 0x12);
  bi->pixelsize = iVar2;
  iVar2 = dbuf_getu16be(f,pos + 0x14);
  bi->cmpcount = iVar2;
  iVar2 = dbuf_getu16be(f,pos + 0x16);
  bi->cmpsize = iVar2;
  de_dbg(c,"pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
         bi->pixeltype & 0xffffffff,bi->pixelsize & 0xffffffff,bi->cmpcount & 0xffffffff,
         bi->cmpsize & 0xffffffff);
  bi->pdwidth = (bi->rowbytes << 3) / bi->pixelsize;
  if (bi->pdwidth < bi->npwidth) {
    bi->pdwidth = bi->npwidth;
  }
  uVar1 = dbuf_getu32be(f,pos + 0x18);
  de_dbg(c,"plane bytes: %d",uVar1 & 0xffffffff);
  iVar2 = dbuf_getu32be(f,pos + 0x1c);
  bi->pmTable = (uint32_t)iVar2;
  de_dbg(c,"pmTable: 0x%08x",(ulong)bi->pmTable);
  uVar1 = dbuf_getu32be(f,pos + 0x20);
  de_dbg(c,"pmReserved: 0x%08x",uVar1 & 0xffffffff);
  de_dbg_indent(c,-1);
  return;
}