#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Create a menu to interact with
void printmenu() 
{
    printf("======= Mini Shell by Knoah Bragg =========\n");
    printf("0. exit\n");
    printf("1. ls -l\n");
    printf("2. uname -r\n");
    printf("3. top\n");
    printf("4. date\n");
    printf("5. echo phrase\n");
    printf("6. hostname\n");
    printf("7. pwd\n");
    printf("8. ps\n");
    printf("9. whoami\n");
    printf("===== Select a command to run. ========\n");
}

int main() 
{
    //Local variables
    int choice;
    int status;

    //Ignore SIGINT for the shell
    signal(SIGINT, SIG_IGN);

    do {
        //Post the menue and check for an option
        printmenu();
        scanf("%d", &choice);

        //Exit case
        if (choice == 0) 
        {
            printf("Sayonara!...Exiting\n");
            break;
        }

        pid_t pid = fork();

        if (pid == 0) 
        {
            switch (choice) 
            {
                //ls -l
                case 1:
                    execl("/usr/bin/ls", "ls", "-l", NULL);
                    perror("execl");
                    break;

                //uname
                case 2:
                    execl("/usr/bin/uname", "uname", "-r", NULL);
                    perror("execl");
                    break;

                //top
                case 3:
                    execl("/usr/bin/top", "top", NULL);
                    perror("execl");
                    break;

                //date
                case 4:
                    execl("/usr/bin/date", "date", NULL);
                    perror("execl");
                    break;

                //echo
                case 5:
                    execl("/bin/echo", "echo", "Muwahahaha", NULL);
                    perror("execl");
                    break;

                //hostname
                case 6:
                    execl("/bin/hostname", "hostname", NULL);
                    perror("execl");
                    break;

                //pwd
                case 7:
                    execl("/bin/pwd", "pwd", NULL);
                    perror("execl");
                    break;

                //ps
                case 8:
                    execl("/bin/ps", "ps", NULL);
                    perror("execl");
                    break;

                //whoami
                case 9:
                    execl("/usr/bin/whoami", "whoami", NULL);
                    perror("execl");
                    break;

                //Not a choice
                default:
                    printf("Invalid choice. Try again.\n");
                    break;
            }

            //Avoid error
            exit(EXIT_FAILURE);  
        }

        if (pid > 0) 
        {
            pid = wait(&status);
            printf("End of process %d: ", pid);

            //Exit
            if (WIFEXITED(status)) 
            {
                printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
            }

            //Killed
            if (WIFSIGNALED(status)) 
            {
                printf("The process ended with kill -%d.\n", WTERMSIG(status));
            }
        }

    } while (choice != 0);

    return 0;
}