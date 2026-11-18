struct bee_file *bee_file_by_handle(struct bee_handle *handle, char *path, unsigned long long size)
{
    struct bee_file *file;
    struct bee_user *user;
    struct bee_priv *priv = handle->priv;

    user = bee_user_by_handle(priv, handle);
    if(priv->func->open){
        file = priv->func->open(priv, user, path, size);
    }else{
        file = NULL;
    }
    return file;
}