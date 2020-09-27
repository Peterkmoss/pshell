#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *builtin_cmds[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&sh_cd, &sh_help, &sh_exit};

int cnt_builtins() { return sizeof(builtin_cmds) / sizeof(char *); }

int sh_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "sh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sh");
    }
  }
  return 0;
}

int sh_help(char **args) {
  int i;
  printf("Peter Moss' pshell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < cnt_builtins(); i++) {
    printf("  %s\n", builtin_cmds[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int sh_exit(char **args) { exit(0); }
