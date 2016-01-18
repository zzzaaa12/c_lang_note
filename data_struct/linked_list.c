
/* The first node has no data, just save the next pointer */
struct mylist {
	int id;
	char *data;
	struct mylist *next;
} MY_LIST;

/* add a item after last node */
int mylist_add(struct mylist *list, int id, char *data, int data_len)
{
	int ret = -1;
	struct mylist *ptr = list;

	if (ptr == NULL)
		goto out;

	while (ptr->next)
		ptr = ptr->next;

	ptr->next = malloc(sizeof(struct mylist));
	if (ptr->next == NULL)
		goto out;

	ptr->next->id = id;
	ptr->next->data = malloc(data_len + 1);
	ptr->next->next = NULL;

	if (ptr->next->data == NULL) {
		cprintf("malloc fail: ptr->next->data\n");
		free(ptr->next);
		ptr->next = NULL;
		goto out;
	}


	memset(ptr->next->data, 0, data_len);
	strncpy(ptr->next->data, data, data_len + 1);
	ret = 0;
out:
	return ret;
}

/* read data in node by id */
char *mylist_read(struct mylist *list, int id)
{
	char *data = NULL;
	struct mylist *ptr = list;

	if (ptr == NULL)
		goto out;

	while (ptr->next) {
		if (ptr->next->id == id) {
			data = strdup(ptr->next->data);
			break;
		}
		ptr = ptr->next;
	}

out:
	return data;
}

/* remove a node by id */
static int mylist_del(struct mylist *list, int id)
{
	int ret = -1;
	struct mylist *ptr, *tmp;

	ptr = list;
	if (ptr == NULL)
		goto out;

	while (ptr->next) {
		if (ptr->next->id == id) {
			tmp = ptr->next->next;
			free(ptr->next->data);
			free(ptr->next);
			ptr->next = tmp;
			ret = 0;
			goto out;
		}

		ptr = ptr->next;
	}
out:
	return ret;
}

/* clean all nodes */
int mylist_clean(struct mylist *list)
{
	int ret = -1;
	struct mylist *ptr, *tmp;

	if (list == NULL)
		goto out;

	ptr = list->next;
	while (ptr) {
		free(ptr->data);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}

	list->next = NULL;
	ret = 0;
out:
	return ret;
}
