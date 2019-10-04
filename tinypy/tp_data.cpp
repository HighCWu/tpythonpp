
/* Function: tp_data
 * Creates a new data object.
 * 
 * Parameters:
 * magic - An integer number associated with the data type. This can be used
 *         to check the type of data objects.
 * v     - A pointer to user data. Only the pointer is stored in the object,
 *         you keep all responsibility for the data it points to.
 *
 * 
 * Returns:
 * The new data object.
 * 
 * Public fields:
 * The following fields can be access in a data object:
 * 
 * magic      - An integer number stored in the object.
 * val        - The data pointer of the object.
 * info->free - If not NULL, a callback function called when the object gets
 *              destroyed.
 * 
 * Example:
 * > void *__free__(TP, tp_obj self)
 * > {
 * >     free(self.data.val);
 * > }
 * >
 * > tp_obj my_obj = tp_data(TP, 0, my_ptr);
 * > my_obj.data.info->free = __free__;
 */
tp_obj tp_data_t(TP, int magic, void *v) {
	tp_obj r = {TP_DATA};
	r.data.info = (tpd_data*)tp_malloc(tp, sizeof(tpd_data));
	r.data.val = v;
	r.type.magic = magic;
	return tp_track(tp,r);
}

tp_obj tp_data(TP, int magic, void *v) {
	return tp_data_t(tp, magic, v);
}

/* creates an untracked tp_data */
tp_obj tp_data_nt(TP, int magic, void *v) {
	tp_obj r = {TP_DATA};
	r.data.info = NULL;
	r.data.val = v;
	r.type.magic = magic;
	return r;
}
