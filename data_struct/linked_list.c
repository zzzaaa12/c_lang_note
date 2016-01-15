
/* The first node has no data, just save the next pointer */
struct mylist {
	int id;
	char *str;
	struct mylist *next;
} MY_LIST;

/* add a item after last node */
int mylist_add(struct mylist *list, int id, char *str, int str_len)
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
	ptr->next->str = malloc(str_len + 1);
	ptr->next->next = NULL;

	if (ptr->next->str == NULL) {
		cprintf("malloc fail: ptr->next->str\n");
		free(ptr->next);
		ptr->next = NULL;
		goto out;
	}


	memset(ptr->next->str, 0, str_len);
	strncpy(ptr->next->str, str, str_len + 1);
	ret = 0;
out:
	return ret;
}

/* read string in node by id */
char *mylist_read(struct mylist *list, int id)
{
	char *str = NULL;
	struct mylist *ptr = list;

	if (ptr == NULL)
		goto out;

	while (ptr->next) {
		if (ptr->next->id == id) {
			str = strdup(ptr->next->str);
			break;
		}
		ptr = ptr->next;
	}

out:
	return str;
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
			free(ptr->next->str);
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
		free(ptr->str);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}

	list->next = NULL;
	ret = 0;
out:
	return ret;
}
