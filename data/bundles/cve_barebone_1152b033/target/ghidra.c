int hci_req_sync(hci_dev *hdev,_func_int_hci_request_ptr_unsigned_long *req,unsigned_long opt,
                u32 timeout,u8 *hci_status)

{
  int iVar1;
  int ret;
  u8 *hci_status_local;
  u32 timeout_local;
  unsigned_long opt_local;
  _func_int_hci_request_ptr_unsigned_long *req_local;
  hci_dev *hdev_local;
  int local_c;
  
  iVar1 = test_bit(0,&hdev->flags);
  if (iVar1 == 0) {
    local_c = -100;
  }
  else {
    mutex_lock(&hdev->req_lock);
    local_c = __hci_req_sync(hdev,req,opt,timeout,hci_status);
    mutex_unlock(&hdev->req_lock);
  }
  return local_c;
}