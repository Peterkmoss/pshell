#include "builtins.h"
#include <stdio.h>
#include <unistd.h>

char *builtin_cmds[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&mysh_cd, &mysh_help, &mysh_exit};

int cnt_builtins() { return sizeof(builtin_cmds) / sizeof(char *); }

int mysh_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "mysh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("mysh");
    }
  }
  return 0;
}

int mysh_help(char **args) {
  int i;
  printf("Peter Moss' MYSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < cnt_builtins(); i++) {
    printf("  %s\n", builtin_cmds[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int mysh_exit(char **args) { return 0; }
