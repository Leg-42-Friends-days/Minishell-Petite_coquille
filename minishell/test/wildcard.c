# include <readline/history.h>
# include <readline/readline.h>
// readline rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay add_history

# include <dirent.h>
# include <signal.h>
// man 3 kill
// man 3 signal
# include <sys/types.h>
// opendir() readdir() closedir()

# include <sys/ioctl.h>
// ioctl()

# include <termios.h>
// tcsetattr() tcgetattr()

# include <curses.h>
# include <term.h>
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs

# include <sys/stat.h>
// stat() lstat() fstat()

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
// getenv()
# include <string.h>
# include <unistd.h>


int main()
{
    struct dirent *entry;
    char *str;
    DIR *dp;

    str = "/home/mickzhan/Exercice/Minishell/minishell/test";
    dp = opendir(str);
    if (!dp)
    {
        printf("Erreur d'ouverture de dossier");
        return (1);
    }

    while((entry = readdir(dp)))
    {
        printf("CONTENT : %s\n", entry->d_name);
    }
    closedir(dp);
    return (0);
}