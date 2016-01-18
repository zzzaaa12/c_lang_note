/*
Reference:
  http://my.oschina.net/u/158589/blog/62896
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	struct addrinfo hints, *result;
	char hostname[1024] = "";
	int ret;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s host msg...\n", argv[0]);
		goto fail;
	}

	memset(&hints, 0, sizeof(hints));
	memset(result, 0, sizeof(result));
	hints.ai_family = AF_UNSPEC;    // AF_UNSPEC, AF_INET, and AF_INET6
	hints.ai_socktype = SOCK_DGRAM;

	ret = getaddrinfo(argv[1], NULL, &hints, &result);

	if (ret != 0) {
		fprintf(stderr, "%s.\n", gai_strerror(ret));
		goto fail;
	}

	while (result != NULL) {
		memset(hostname, 0, sizeof(hostname));
		ret = getnameinfo(result->ai_addr,
				result->ai_addrlen,
				hostname,
				sizeof(hostname),
				NULL,
				0,
				NI_NUMERICHOST);

		if (ret == 0) {
			if (result->ai_family == AF_INET)
				printf("IPv4 ---> %s\n", hostname);
			else if (result->ai_family == AF_INET6)
				printf("IPv6 ---> %s\n", hostname);
		}

		result = result->ai_next;
	}

	return 0;

fail:
	return -1;
}
