#include "sighandlers.h"
#include <stdio.h>

void child_interupt(int sig) { printf("\n"); }

void catch_interupt(int sig) { printf("\n\n"); }
