#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2
// redir -i /etc/passwd -o out.txt cat  == cat < /etc/passwd > out.txt

int main(int argc, char *argv[])
{

   char *args[10] = {};
   int icom;
   int iargs = 0;
   int i;

   if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0)
   {
      int fdin = open(argv[2], O_RDONLY);
      if (fdin < 0)
         perror("open");
      int fdout = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0640);
      if (fdout < 0)
         perror("open");
      int dup_1 = dup2(fdin, 0);
      if (dup_1 < 0)
         perror("dup2");
      int dup_2 = dup2(fdout, 1);
      if (dup_2 < 0)
         perror("dup2");
      close(fdin);
      close(fdout);

      icom = 5;
   }
   else if (strcmp(argv[1], "-i") == 0)
   {
      int fdin = open(argv[2], O_RDONLY);
      if (fdin < 0)
         perror("open");
      int dup_1 = dup2(fdin, 0);
      if (dup_1 < 0)
         perror("dup2");
      close(fdin);

      icom = 3;
   }
   else if (strcmp(argv[1], "-o") == 0)
   {
      int fdout = open(argv[2], O_CREAT | O_TRUNC | O_RDONLY, 0640);
      if (fdout < 0)
         perror("open");
      int dup_1 = dup2(fdout, 1);
      if (dup_1 < 0)
         perror("dup2");
      close(fdout);

      icom = 3;
   }
   else
      icom = 1;

   for (i = icom; i < argc; i++)
   {
      args[iargs++] = argv[i];
   }
   args[iargs] = NULL;

   if (fork() == 0)
   {
      int res = execvp(argv[icom], args);
      _exit(res);
   }
   wait(NULL);

   return 0;
}
