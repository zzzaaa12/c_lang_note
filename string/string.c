#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
str_replace(): replace a old string by new string
	XXX: the return value need call free()!!
*/
char *str_replace(char *str, const char *old, const char *new)
{
	int len, len_old, len_new;
	int count = 0;
	char *ptr, *next, *new_str;

	if (str == NULL || old == NULL || new == NULL)
		return NULL;

	len = strlen(str);
	len_old = strlen(old);
	len_new = strlen(new);

	ptr = str;
	while (ptr) {
		ptr = strstr(ptr, old);
		if (!ptr)
			break;
		count++;
		ptr++;
	}

	new_str = malloc(len + (len_new-len_old) * count + 1);
	if (new_str == NULL)
		return NULL;

	memset(new_str, 0, len + (len_new-len_old) * count + 1);

	ptr = strstr(str, old);

	if (ptr != str)
		strncat(new_str, str, ptr - str);


	while (ptr) {
		strncat(new_str, new, len_new); // copy new string
		next = strstr(ptr + 1, old);
		if (next == NULL) { // copy last old string
			strcat(new_str, ptr + len_old);
			break;
		}

		strncat(new_str, ptr+len_old, next - (ptr+len_old));
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
	char aa[] = "xxxxx11xxxxx11aaaaa112";
	printf("%d\n", strstr_count("123456123456312313143425346123456", "123"));
	printf("%d\n", strchr_count("aaa12345612345a6312a31314a34253461a23456a", 'a'));
	printf("old=%s\n", aa);
	printf("new=%s\n", str_replace(aa, "11", "!!!!!!!!!!!!!!!"));
	return 0;
}


