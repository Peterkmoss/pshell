#include "builtins.h"
#include "sighandlers.h"
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SPLIT_BUFSIZE 64
#define SPLIT_DELIM " \t\r\n\a"
#define MAX_CWD INT_MAX

char *sh_read_line() {
  char *line = NULL;
  size_t len = 0;
  if (getline(&line, &len, stdin) == -1) {
    if (feof(stdin))
      exit(EXIT_SUCCESS);

    perror("readline");
    exit(EXIT_FAILURE);
  }
  return line;
}

char **sh_split_line(char *line) {
  int bufsize = SPLIT_BUFSIZE;
  char **args = malloc(bufsize * sizeof(char *));
  char *arg;

  if (!args) {
    fprintf(stderr, "sh: error in allocating memory");
    exit(EXIT_FAILURE);
  }

  arg = strtok(line, SPLIT_DELIM);
  int pos = 0;
  while (arg != NULL) {
    args[pos++] = arg;

    if (pos >= bufsize) {
      bufsize += SPLIT_BUFSIZE;
      args = realloc(args, bufsize * sizeof(char *));
      if (!args) {
        fprintf(stderr, "sh: error in allocating memory");
        exit(EXIT_FAILURE);
      }
    }
    // To get rid of the end-line char
    arg = strtok(NULL, SPLIT_DELIM);
  }
  args[pos] = NULL;
  return args;
}

int sh_launch(char **args) {
  pid_t pid;
  int status;

  // Handle interrupts of process
  signal(SIGINT, child_interupt);

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1)
      perror("sh");
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("sh");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return status;
}

int sh_exec(char **args) {
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 0;
  }

  for (i = 0; i < cnt_builtins(); i++) {
    if (strcmp(args[0], builtin_cmds[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return sh_launch(args);
}

void sh_loop(void) {
  char *line, *cwd, *promt;
  char **args;
  int status = 0;

  do {
    signal(SIGINT, SIG_IGN);

    cwd = getcwd(NULL, 0);
    if (status)
      promt = "\033[32m> \033[0m";
    else
      promt = "\033[0m> ";

    printf("%s %s", cwd, promt);
    line = sh_read_line();
    args = sh_split_line(line);
    status = sh_exec(args);

    free(line);
    free(args);
  } while (1);
}

int main(int argc, char *argv[]) {
  sh_loop();

  return EXIT_SUCCESS;
}
