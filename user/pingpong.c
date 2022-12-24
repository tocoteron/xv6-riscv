#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  int parent_fds[2], child_fds[2];
  char buf[5];

  pipe(parent_fds);
  pipe(child_fds);

  pid = fork();
  if (pid < 0) {
    printf("fork failed");
    exit(1);
  }

  if (pid == 0) {
    read(child_fds[0], buf, 4);
    printf("%s\n", buf);
    write(parent_fds[1], "pong", 4);
  } else {
    write(child_fds[1], "ping", 4);
    read(parent_fds[0], buf, 4);
    printf("%s\n", buf);
  }

  exit(0);
}
