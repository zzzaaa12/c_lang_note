#include <stdio.h>
#include <stdlib.h>
#include <string.h>

strchr_replace_once(char *input, char old, char new)
{
	char *target = strchr(input, old);
	if (target)
		*target = new;
}

/*
str_replace(): replace a old string by new string
	XXX: the return value need call free()!!
*/
char *str_replace(char *str, const char *old, const char *new)
{
	int len, len_old, len_new;
	int count = 0;
	char *pos, *ptr, *next, *new_str;

	if (str == NULL || old == NULL || new == NULL)
		return NULL;

	len = strlen(str);
	len_old = strlen(old);
	len_new = strlen(new);

	/* count old string */
	ptr = str;
	while (ptr) {
		ptr = strstr(ptr, old);
		if (!ptr)
			break;
		count++;
		ptr++;
	}

	/* allocate enough space to store the result string */
	new_str = malloc(len + (len_new - len_old) * count + 1);
	if (new_str == NULL)
		return NULL;

	memset(new_str, 0, len + (len_new - len_old) * count + 1);
	pos = new_str;

	/* copy the first part before first old string */
	ptr = strstr(str, old);
	if (ptr && ptr != str) {
		strncpy(new_str, str, ptr - str);
		pos = new_str + (ptr - str);
	}

	while (ptr) {

		/* copy new string to replace old string */
		strncpy(pos, new, len_new); // copy new string
		pos = pos + len_new;
		next = strstr(ptr + len_old, old);

		/* copy last string */
		if (next == NULL) {
			strcpy(pos, ptr + len_old);
			break;
		}

		/* copy other string */
		strncpy(pos, ptr + len_old, next - (ptr + len_old));
		pos += next - (ptr + len_old);
		ptr = next;
	}

	return new_str;
}

int strchr_count(const char *str, int c)
{
	int count = 0;
	const char *ptr;

	if (str == NULL || c == 0)
		return -1;

	ptr = str;
	while (ptr) {
		ptr = strchr(ptr, c);
		if (!ptr)
			break;
		count++;
		ptr++;
	}

	return count;
}

int strstr_count(const char *str, const char *find)
{
	int count = 0;
	const char *ptr;

	if (str == NULL || find == NULL)
		return -1;

	ptr = str;
	while (ptr) {
		ptr = strstr(ptr, find);
		if (!ptr)
			break;
		count++;
		ptr++;
	}

	return count;
}


int main(void)
{
	char aa[] = "11xxxxx11xxxxx11aaaaa11211";
	char *test;

	printf("%d\n", strstr_count("123456123456312313143425346123456", "123"));
	printf("%d\n", strchr_count("aaa12345612345a6312a31314a34253461a23456a", 'a'));

	printf("old=%s\n", aa);
	test = str_replace(aa, "11", "!!!!!!!!");
	if (test) {
		printf("new=%s\n", test);
		free(test);
	}

	return 0;
}


