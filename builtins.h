#ifndef BUILTINS_H_INCLUDED
#define BUILTINS_H_INCLUDED

int mysh_cd(char **args);
int mysh_help(char **args);
int mysh_exit(char **args);

extern char *builtin_cmds[];

extern int (*builtin_func[])(char **);

int cnt_builtins();

#endif
