static struct sctp_auth_bytes *func0(size_t len)
{
	struct sctp_auth_bytes *key;

	
	if (len > (size_t) 0x7F)
		len = (size_t) 0x7F;

	key = kmalloc(sizeof(*key), GFP_KERNEL);
	if (key) {
		key->len = len;
		key->data = kmalloc(len, GFP_KERNEL);
		key->hmac = kmalloc(len, GFP_KERNEL);
		key->key = kmalloc(sizeof(struct sctp_auth_bytes_key),
				   GFP_KERNEL);

		if (key->data && key->hmac && key->key)
			goto out;

		kfree(key->data);
		kfree(key->hmac);
		kfree(key->key);
		kfree(key);
		key = NULL;
	}
out:
	return key;
}