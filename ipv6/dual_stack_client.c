/*
Reference:
	1. http://blog.chinaunix.net/uid-26583794-id-3167485.html
	2. http://pubs.opengroup.org/onlinepubs/7908799/xns/netdb.h.html
	3. http://owend.corp.he.net/ipv6/sample_application/c/v6_client.c

struct hostent {
    char  *h_name;            // official name of host
    char  **h_aliases;        // alias list
    int   h_addrtype;         // host address type
    int   h_length;           // length of address
    char  **h_addr_list;      // list of addresses
};

struct addrinfo {
    int              ai_flags;        // customize behavior
    int              ai_family;       // address family
    int              ai_socktype;     // socket type
    int              ai_protocol;     // protocol
    socklen_t        ai_addrlen;      // length in bytes of address
    struct sockaddr *ai_addr;         // address
    char            *ai_canonname;    // canonical name of host
    struct addrinfo *ai_next;         // next in list
};
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
	int sock = -1;
	int ret = -1;
	char buffer[1024] = {};
	char *result = NULL;
	struct timeval timeval;
	struct addrinfo addrinfo, *res, *r;
	fd_set afdset;

	if (argc < 3 || atoi(argv[2]) <= 0) {
		fprintf(stderr, "please input [hostname] and [port]\n");
		fprintf(stderr, "ex: %s %s %s\n", argv[0], "www.google.com", "80");
		exit(-1);
	}

	memset(&addrinfo, 0, sizeof(addrinfo));
	addrinfo.ai_family = AF_UNSPEC;
	addrinfo.ai_socktype = SOCK_STREAM;
	addrinfo.ai_protocol = IPPROTO_TCP;

	ret = getaddrinfo(argv[1], argv[2], &addrinfo, &res);
	if (ret != 0) {
		fprintf(stderr, "Failed to resolve address information\n");
		goto out;
	}

	for (r = res; r != NULL; r = r->ai_next) {
		sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		ret = connect(sock, r->ai_addr, r->ai_addrlen);
		if (ret == 0) {
		if (r->ai_family == AF_INET6)
		printf("connected via IPv4\n")
			else if (r->ai_family == AF_INET6)
		printf("connected via IPv6\n")
			break;
	}
	}

	if (ret < 0) {
		fprintf(stderr, "connect() fail\n");
		freeaddrinfo(res);
		goto out;
	}

	snprintf(buffer, sizeof(buffer), "messages");

	if (send(sock, buffer, strlen(buffer), 0) < 0) {
		fprintf(stderr, "send() fail");
		goto out;
	}

	FD_ZERO(&afdset);
	FD_SET(sock, &afdset);
	timeval.tv_sec = 3;
//  timeval.tv_usec = 0;
	printf("%f" ,timeval.tv_usec);

	ret = select(sock + 1, &afdset, NULL, NULL, &timeval);
	if (ret == -1) {
		fprintf(stderr, "select() fail\n");
		goto out;
	}

	memset(buffer, 0, sizeof(buffer));
	if(FD_ISSET(sock, &afdset)) {
		read(sock, buffer, sizeof(buffer));
	} else {
		fprintf(stderr, "recv_buf = NULL\n");
		goto out;
	}

	printf("recv: %s \n", buffer);

out:
	return 0;
}
