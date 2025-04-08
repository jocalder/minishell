#include "minishell.h"

static char *path_empty(char *path, char *home)
{
    char    *new_path;

    new_path = NULL;
    if (path[ft_strlen(home)] == '\0')
    {
        new_path = malloc(2);
        if (!new_path)
            return (NULL);
        new_path[0] = '~';
        new_path[1] = '\0';
    }
    return (new_path);
}

static char *replace_home(char *path)
{
    char    *home;
    char    *new_path;

    home = getenv("HOME");
    if (!home)
        return (ft_strdup(path));
    if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
    {
        path_empty(path, home);
        if (path[ft_strlen(home)] == '/')
        {
            new_path = malloc(ft_strlen(path) - ft_strlen(home) + 2);
            if (!new_path)
                return (path);
            new_path[0] = '~';
            ft_strcpy(new_path + 1, path + ft_strlen(home));
            return (new_path);
        }
    }
    return (ft_strdup(path));
}

static void join_prompt(char *ptr, char *user, char *display_cwd)
{
    ft_strcpy(ptr, RED);
    ptr += ft_strlen(RED);
    ft_strcpy(ptr, user);
    ptr += ft_strlen(user);
    ft_strcpy(ptr, "@minishell");
    ptr += ft_strlen("@minishell");
    ft_strcpy(ptr, WHITE);
    ptr += ft_strlen(WHITE);
    ft_strcpy(ptr, ":");
    ptr += ft_strlen(":");
    ft_strcpy(ptr, BLUE);
    ptr += ft_strlen(BLUE);
    ft_strcpy(ptr, display_cwd);
    ptr += ft_strlen(display_cwd);
    ft_strcpy(ptr, WHITE);
    ptr += ft_strlen(WHITE);
    ft_strcpy(ptr, "$ ");
    free(display_cwd);
}

char    *display_prompt(void)
{
    char    *user;
    char    cwd[1024];
    char    *prompt;
    char    *ptr;
    char    *display_cwd;
    int     len;

    len = 0;
    user = getenv("USER");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (NULL);
    display_cwd = replace_home(cwd);
    len = ft_strlen(RED) + ft_strlen(user) + ft_strlen("@minishell")
        + ft_strlen(WHITE) + ft_strlen(":") + ft_strlen(BLUE)
        + ft_strlen(display_cwd) + ft_strlen(WHITE) + ft_strlen("$ ") + 1;
    prompt = (char *)malloc(len);
    if (!prompt)
        return (free(display_cwd), NULL);
    ptr = prompt;
    join_prompt(ptr, user, display_cwd);
    return (prompt);
}
