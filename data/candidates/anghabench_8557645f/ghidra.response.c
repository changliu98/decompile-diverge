char * ata_err_string(uint err_mask)

{
  uint err_mask_local;
  char *local_10;
  
  if ((err_mask & AC_ERR_HOST_BUS) == 0) {
    if ((err_mask & AC_ERR_ATA_BUS) == 0) {
      if ((err_mask & AC_ERR_TIMEOUT) == 0) {
        if ((err_mask & AC_ERR_HSM) == 0) {
          if ((err_mask & AC_ERR_SYSTEM) == 0) {
            if ((err_mask & AC_ERR_MEDIA) == 0) {
              if ((err_mask & AC_ERR_INVALID) == 0) {
                if ((err_mask & AC_ERR_DEV) == 0) {
                  if ((err_mask & AC_ERR_NCQ) == 0) {
                    if ((err_mask & AC_ERR_NODEV_HINT) == 0) {
                      local_10 = "unknown error";
                    }
                    else {
                      local_10 = "Polling detection error";
                    }
                  }
                  else {
                    local_10 = "NCQ error";
                  }
                }
                else {
                  local_10 = "device error";
                }
              }
              else {
                local_10 = "invalid argument";
              }
            }
            else {
              local_10 = "media error";
            }
          }
          else {
            local_10 = "internal error";
          }
        }
        else {
          local_10 = "HSM violation";
        }
      }
      else {
        local_10 = "timeout";
      }
    }
    else {
      local_10 = "ATA bus error";
    }
  }
  else {
    local_10 = "host bus error";
  }
  return local_10;
}