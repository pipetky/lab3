#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void attrs(int procc)
{

    printf("%d %s %d\n",getpgid(getpid()), "Процесс № ", procc);
    printf("%d %s %d\n",getsid(getpid()), "Процесс № ", procc);
    printf("%d %s %d\n",getppid(), "Процесс № ", procc);
    printf("%d %s %d\n",getpgid(getpid()), "Процесс № ", procc);


}

int main() {
    char *arg[] = { "lab3_1", (char *) 0 };

    attrs(0);

    if (fork() == 0)
    {
        printf("Дочерний процесс 1:\n");
        attrs(1);
        return 0;
    }
    else
    {
        if (vfork() == 0)
        {
            printf("Дочерний процесс 2:\nЗапускаю exec...\n");
            if (execv(arg[0], arg) == -1)
            {
                printf("ошибка\n");
                printf("%d\n", errno);
            }
            printf("Это никогда не выведется!\n");
            return 0;
        }
    }
    printf("конец");
    return 0;
}