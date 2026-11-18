__attribute__((used)) static int do_buffer(struct callback *cb)
{
	int ret = 0;
	int err;

	switch (cb->type) {
	case CB_TYPE_NONE:
		break;
	case CB_TYPE_FUNC:
		ret = cb->func(cb->arg);
		if (ret)
			goto out;
		break;
	case CB_TYPE_FILE:
		ret = do_callback_withbuf(cb, cb->file);
		if (ret)
			goto out;
		break;
	case CB_TYPE_DIR:
		ret = do_callback_withbuf(cb, cb->dir);
		if (ret)
			goto out;
		break;
	case CB_TYPE_BLOB:
		ret = do_callback_withbuf(cb, cb->blob);
		if (ret)
			goto out;
		break;
	case CB_TYPE_TREE:
		ret = do_callback_withbuf(cb, cb->tree);
		if (ret)
			goto out;
		break;
	case CB_TYPE_COMMIT:
		ret = do_callback_withbuf(cb, cb->commit);
		if (ret)
			goto out;
		break;
	case CB_TYPE_TAG:
		ret = do_callback_withbuf(cb, cb->tag);
		if (ret)
			goto out;
		break;
	}

	cb->done = 0;
out:
	err = ret;
	return err;
}