#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <errno.h>

#define MAXEVENT 64
#define READBUF  512
static int create_and_bind(char* address, char* port) {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; /* RETURN IPv4 and IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* only tcp */
	hints.ai_flags = AI_PASSIVE;   /* ALL interface */
	s = getaddrinfo(address, port, &hints, &result);
	if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }
  for (rp = result; rp != NULL; rp = rp->ai_next) {
  	sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
  	if (sfd == -1)
  		continue;
  	if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
  		break;
  	close(sfd);
  }

  if (rp == NULL) {
  	perror("bind fail");
  	return -1;
  }

  freeaddrinfo(result);

  return sfd;
}
static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

int handle_accept(int efd, int sfd) {
	struct sockaddr in_addr;
  socklen_t in_len = sizeof in_addr;
	int infd;
	int s = 0;
	char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];
	infd = accept4(sfd, &in_addr, &in_len, SOCK_NONBLOCK);
	if (infd == -1) {
		if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
			return -1;
		else {
			perror("accept");
			return -1;
		}
	}
	s = getnameinfo(&in_addr, in_len, 
									hbuf, sizeof hbuf, 
									sbuf, sizeof sbuf, 
									NI_NUMERICHOST | NI_NUMERICSERV);
	if (s == 0)
  {
    printf("Accepted connection on descriptor %d "
           "(host=%s, port=%s)\n", infd, hbuf, sbuf);
  }

  struct epoll_event event;

  event.data.fd = infd;
  event.events = EPOLLIN | EPOLLET;
  s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
  if (s == -1)
  {
    perror ("epoll_ctl");
    abort ();
  }
  return s;
}


void handle_read(struct epoll_event *events, int i) {
	int s;
	int done = 0;
	ssize_t count;
	char buf[READBUF];
	while (1) {
		count = read(events[i].data.fd, buf, sizeof(buf));
		if (count == -1) {
			if (errno != EAGAIN || errno != EWOULDBLOCK) {
				perror("read");
				done = 1;
			}
			break;
		}
		else if (count == 0) {
			done = 1;
			break;
		}

		s = write(events[i].data.fd, buf, count);

		if (s == -1) {
			perror("write");
			done = 1;
		}
		break;
	}
	if (done) {
		fprintf(stderr, "Closed connection on descriptor %d\n",
                          events[i].data.fd);
		close(events[i].data.fd);
	}
}



int main(int argc, char *argv[]) {
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s address port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	sfd = create_and_bind(argv[1], argv[2]);
	if (sfd == -1)
		exit(-1);

	s = listen(sfd, SOMAXCONN);
	if (s == -1) {
		perror("listen");
		exit(-1);
	}

	s = make_socket_non_blocking(sfd);
	if (s == -1) {
		exit(-1);
	}
	efd = epoll_create1(0);
	if (efd == -1) {
		perror("epoll create");
		exit(-1);
	}

	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1)
  {
    perror ("epoll_ctl");
    exit(-1);
  }

  events = calloc(MAXEVENT, sizeof event);

  while(1) {
  	int n, i;
  	n = epoll_wait(efd, events, MAXEVENT, -1);
  	for (i = 0; i < n; ++i) {
  		if ((events[i].events & EPOLLERR) ||
  				(events[i].events & EPOLLHUP) ||
  				(!(events[i].events & EPOLLIN))) {
  			perror("epoll error");
  			fprintf(stderr, "Closed connection on descriptor %d\n",
                events[i].data.fd);
  			close(events[i].data.fd);
  			continue;
  		}

  		else if (sfd == events[i].data.fd) {
  			while (1) {
  				s = handle_accept(efd, sfd);
  				if (s == -1) // we are done or on error
  					break;
	  		}
	  		continue;
  		} else {
  			handle_read(events, i);
  		}
  	}
  }
  free(events);
  close(sfd);
  return 0;
}