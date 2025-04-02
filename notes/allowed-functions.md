# Minishell - Proyecto 42

## Funciones permitidas en Minishell

A continuación se describen todas las funciones permitidas en el proyecto, incluyendo su prototipo, parámetros, valores de retorno, funcionamiento y usos.

### Entrada y gestión del historial
#### `char *readline(const char *prompt);`
#### `void rl_clear_history(void);`
#### `void rl_on_new_line(void);`
#### `void rl_replace_line(const char *text, int clear_undo);`
#### `void rl_redisplay(void);`
#### `void add_history(const char *line);`

### Gestión de memoria
#### `void *malloc(size_t size);`
#### `void free(void *ptr);`

### Entrada/Salida
#### `int write(int fd, const void *buf, size_t count);`
#### `int read(int fd, void *buf, size_t count);`

### Gestión de archivos
#### `int open(const char *pathname, int flags, mode_t mode);`
#### `int close(int fd);`
#### `int access(const char *pathname, int mode);`
#### `int unlink(const char *pathname);`

### Gestión de directorios
#### `int chdir(const char *path);`
#### `char *getcwd(char *buf, size_t size);`
#### `DIR *opendir(const char *name);`
#### `struct dirent *readdir(DIR *dirp);`
#### `int closedir(DIR *dirp);`

### Gestión de procesos
#### `pid_t fork(void);`
#### `pid_t wait(int *wstatus);`
#### `pid_t waitpid(pid_t pid, int *wstatus, int options);`
#### `int wait3(int *status, int options, struct rusage *rusage);`
#### `int wait4(pid_t pid, int *status, int options, struct rusage *rusage);`
#### `int execve(const char *filename, char *const argv[], char *const envp[]);`
#### `void exit(int status);`

### Gestión de señales
#### `int signal(int signum, void (*handler)(int));`
#### `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`
#### `int kill(pid_t pid, int sig);`

### Redirección y pipes
#### `int dup(int oldfd);`
#### `int dup2(int oldfd, int newfd);`
#### `int pipe(int pipefd[2]);`

### Gestión de terminal
#### `int isatty(int fd);`
#### `char *ttyname(int fd);`
#### `int ttyslot(void);`
#### `int ioctl(int fd, unsigned long request, ...);`

### Gestión de entorno
#### `char *getenv(const char *name);`

### Control de terminal
#### `int tcgetattr(int fd, struct termios *termios_p);`
#### `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`
#### `int tgetent(char *bp, const char *name);`
#### `int tgetflag(char *id);`
#### `int tgetnum(char *id);`
#### `char *tgetstr(char *id, char **area);`
#### `char *tgoto(const char *cap, int col, int row);`
#### `int tputs(const char *str, int affcnt, int (*putc)(int));`

### Manejo de errores
#### `char *strerror(int errnum);`
#### `void perror(const char *s);`
