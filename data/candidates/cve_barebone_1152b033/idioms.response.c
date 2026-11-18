int hci_req_sync(struct hci_dev *dev, int (*req)(struct hci_request *req, unsigned long opt), unsigned long opt, unsigned int timeout, unsigned char *status)
{
 int ret = 0;
 if (!test_bit(0, &dev->flags))
  return -100;
 hci_lock_req(&dev->req_lock);
 ret = __hci_req_sync(dev, req, opt, timeout, status);
 hci_unlock_req(&dev->req_lock);
 return ret;
}