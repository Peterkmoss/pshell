#ifndef BUILTINS_H_INCLUDED
#define BUILTINS_H_INCLUDED

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

extern char *builtin_cmds[];

extern int (*builtin_func[])(char **);

int cnt_builtins();

#endif
