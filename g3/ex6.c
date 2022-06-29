#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  char *path = "/home/jmartins/Documents/MIEI/SO/guiao-3/";
  char str[100];

  pid_t pid1, pid2;
  int pids[3];
  int codSaida = 1;
  int count = 0;
  int status;
  int bw;
  int i;
  for (i = 1; i < argc; i++)
  {

    pid1 = fork();
    pids[i - 1] = pid1;
    if (pid1 == 0)
    {

      bw = snprintf(str, 100, "%s%s", path, argv[i]);
      if (bw <= 0)
        perror("snprintf");

      while (codSaida > 0)
      {
        count++;

        pid2 = fork();
        if (pid2 == 0)
        {
          int r = execl(str, str, NULL);
          _exit(r);
        }

        waitpid(pid2, &status, 0);
        codSaida = WEXITSTATUS(status);
      }

      _exit(count);
    }
  }

  for (i = 1; i < argc; i++)
  {
    waitpid(pids[i - 1], &status, 0);
    if (WIFEXITED(status))
      printf("%s %d\n", argv[i], WEXITSTATUS(status));
  }

  return 0;
}