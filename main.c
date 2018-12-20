#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

void attrs(int procc, FILE *file)
{
    char *name;
    switch (procc)
    {

        case 0:
            name = "Предок";
            break;
        case 1:
            name = "Потомок1";
            break;
        case 2:
            name = "Потомок2";
            break;
        default:
            printf("ошибка вывода атрибутов");
            return;


    }
    fprintf(file, "%s %s %d %s %d\n",name, " идентификатор процесса: ", getpid(), "Процесс № ", procc);
    fprintf(file, "%s %s %d %s %d\n",name, " идентификатор группы процессов: ", getpgid(getpid()), "Процесс № ", procc);
    fprintf(file, "%s %s %d %s %d\n",name, " идентификатор сеанса процесса: ", getsid(getpid()), "Процесс № ", procc);
    fprintf(file, "%s %s %d %s %d\n",name, " идентификатор предка: ", getppid(), "Процесс № ", procc);



}

int main(int argc, char * argv[]) {

    char *arg[] = { "lab3_1_1", "file1.txt", argv[3], (char *) 0 };

    if (fork() == 0)
    {
        printf("Дочерний процесс 1:\n");
        sleep(atoi(argv[2]));
        FILE *f1 = fopen("file1.txt", "a");
        attrs(1, f1);
        fclose(f1);
        return 0;
    }
    else
    {
        if (vfork() == 0)
        {
            printf("Дочерний процесс 2:\nЗапускаю exec....\n");
            if (execv(arg[0], arg) == -1)
            {
                printf("ошибка\n");
                printf("%d\n", errno);
            }
            printf("Это никогда не выведется!\n");
            return 0;
        }
        sleep(atoi(argv[1]));
        FILE *f = fopen("file1.txt", "a");
        attrs(0, f);
        fclose(f);
    }
    printf("конец\n");
    return 0;
}