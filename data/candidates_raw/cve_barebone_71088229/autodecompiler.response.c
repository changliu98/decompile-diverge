static int exfat_create_file(struct exfat_dir_entry_iter *iter,
         struct exfat_inode_info **new_inode, int *num_entries)
{
 int ret;
 unsigned short checksum;
 int i;
 struct exfat_inode_info *inode = NULL;
 char need_delete = 0;
 struct exfat_dentry *dentry, *stream_de, *file_de;

 ret = exfat_de_iter_get(iter, 0, &file_de);
 if (ret || (file_de->type != 0x85)) {
  exfat_err("failed to get file dentry\n");
  ret = -22;
  goto out;
 }

 checksum = file_calc_checksum(iter);
 if (checksum != ((struct exfat_file_dentry *)file_de)->checksum) {
  *num_entries = 1;
  goto skip_dset;
 }

 if (((struct exfat_file_dentry *)file_de)->num_ext < 3) {
  *num_entries = 1;
  goto skip_dset;
 }

 ret = exfat_de_iter_get(iter, 1, &stream_de);
 if (ret || (stream_de->type != 0xc0)) {
  *num_entries = 2;
  goto skip_dset;
 }

 *new_inode = NULL;
 inode = exfat_alloc_inode(((struct exfat_file_dentry *)file_de)->attr);
 if (!inode) {
  ret = -12;
  goto out;
 }

 for (i = 2; i <= ((struct exfat_file_dentry *)file_de)->num_ext; i++) {
  ret = exfat_de_iter_get(iter, i, &dentry);
  if (ret || (dentry->type != 0xc1)) {
   if (i > 2 && (need_delete & 1)) {
    _ZN4chip7BitMaskINS_3app8Clusters10EnergyEvse7FeatureEjEC2IJS4_EEES4_DpOT__0(chip::BitMask<chip::app::Clusters::EnergyEvse::Feature,uint> * __restrict this, chip::app::Clusters::EnergyEvse::Feature && __restrict __args)
# 102 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/AmazfitTicino/chip-tool/refs/heads/master/src/platform/Zephyr/CHIPDevicePlatform.h"
                         ;
    ((struct exfat_stream_dentry *)stream_de)->checksum =
     ((unsigned short)(i - 1));
   }
   *num_entries = i + 1;
   goto skip_dset;
  }

  inode[(i - 2) * 15 + 13] = ((struct exfat_stream_dentry *)dentry)->name_len;
  inode[(i - 2) * 15 + 14] = ((struct exfat_stream_dentry *)dentry)->name_hash;
  memcpy__bench(inode + (i - 2) * 15 + 15, ((struct exfat_stream_dentry *)dentry)->name,
          ((struct exfat_stream_dentry *)dentry)->name_len * 2);
 }

 ret = check_name_dentry_set(iter, inode);
 if (ret) {
  *num_entries = ((struct exfat_file_dentry *)file_de)->num_ext + 1;
  goto skip_dset;
 }

 if ((((struct exfat_file_dentry *)file_de)->num_ext == 2) &&
     (((struct exfat_stream_dentry *)stream_de)->name_len <= 2)) {
  ret = handle_dot_dotdot_filename(iter, dentry,
       ((struct exfat_stream_dentry *)stream_de)->name_len);
  if (ret < 0) {
   *num_entries = ((struct exfat_file_dentry *)file_de)->num_ext + 1;
   goto skip_dset;
  }
 }

 inode[7] = ((struct exfat_stream_dentry *)stream_de)->flags;
 inode[9] = (((struct exfat_stream_dentry *)stream_de)->flags & 0x02) ? 1 : 0;
 inode[8] = ((struct exfat_stream_dentry *)stream_de)->size;
 if (inode[8] < ((struct exfat_stream_dentry *)stream_de)->valid_size) {
  *num_entries = ((struct exfat_file_dentry *)file_de)->num_ext + 1;
  *num_entries = ((struct exfat_file_dentry *)file_de)->num_ext + 1;
  goto skip_dset;
 }

 *num_entries = ((struct exfat_file_dentry *)file_de)->num_ext + 1;
 *new_inode = inode;

 ret = 0;
 goto out;

skip_dset:
 if (need_delete & 1) {
  _ZN4chip7BitMaskINS_3app8Clusters10EnergyEvse7FeatureEjEC2IJS4_EEES4_DpOT__0(chip::BitMask<chip::app::Clusters::EnergyEvse::Feature,uint> * __restrict this, chip::app::Clusters::EnergyEvse::Feature && __restrict __args)
# 152 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/AmazfitTicino/chip-tool/refs/heads/master/src/platform/Zephyr/CHIPDevicePlatform.h"
                   ;
  stream_de->type &= ~0x80;
 }

 for (i = 1; i < *num_entries; i++) {
  exfat_de_iter_get(iter, i, &dentry);
  if (dentry->type == 0x85)
   break;

  if (need_delete & 1) {
   _ZN4chip7BitMaskINS_3app8Clusters10EnergyEvse7FeatureEjEC2IJS4_EEES4_DpOT__0(chip::BitMask<chip::app::Clusters::EnergyEvse::Feature,uint> * __restrict this, chip::app::Clusters::EnergyEvse::Feature && __restrict __args)
# 170 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/AmazfitTicino/chip-tool/refs/heads/master/src/platform/Zephyr/CHIPDevicePlatform.h"
                     ;
   dentry->type &= ~0x80;
  } else {
   i++;
  }
 }

 *num_entries = i;
 *new_inode = NULL;
 exfat_free_inode(inode);

 ret = (need_delete & 1) ? 1 : -22;

out:
 return ret;
}