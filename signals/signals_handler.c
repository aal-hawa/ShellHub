#include "../minishell.h"
// I need to put this one in cmd be ls
void execute_command(char *cmd)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) // Child Process
    {
        signal(SIGINT, SIG_DFL);  // Restore default Ctrl-C behavior
        signal(SIGQUIT, SIG_DFL); // Restore default Ctrl-\ behavior
        execlp(cmd, cmd, NULL);
        perror("exec failed");
        exit(1);
    }
    else if (pid > 0) // Parent Process
    {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) // Child terminated by signal
        {
            if (WTERMSIG(status) == SIGINT) // Ctrl-C
                write(1, "\n", 1);
            else if (WTERMSIG(status) == SIGQUIT) // Ctrl-\-
                write(1, "Quit (core dumped)\n", 19);
        }
    }
    else
    {
        perror("fork failed");
    }
}
