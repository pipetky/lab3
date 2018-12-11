#include <stdio.h>
#include <unistd.h>

void attrs()
{
    printf ("%d\n",getpid());
    printf ("%d\n",getppid());
    printf ("%d\n",getsid(getpid()));
    printf ("%d\n",getpgid(getpid()));

}

int main() {
    char *arg[] = { "/usr/bin/ls",  0 };

    /* fork и exec в порожденном процессе */
    if (fork() == 0) {
        printf("Дочерницй процесс 1:\n");
        attrs();
        return 0;
    }
    else {
        if (vfork() == 0) {
            printf("Дочерний процесс 2:\nЗапускаю exec\n");
            execv(arg[0], arg);
            printf("I will never be called!\n");
            return 0;
        }
        printf("Execution continues in parent process\n");
    }


    return 0;
}