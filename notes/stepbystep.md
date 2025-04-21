# 42-Minishell

## Index
[Funciones](#funciones)
.
- [Gestión de memoria](#1-gestión-de-memoria-️)

- [Salida estandar](#2-salida-estándar-️)

- [Manejo de archivos](#3-manejo-de-archivos-)

- [Manejo de errores](#4-manejo-de-errores-️)

- [Gestión de procesos](#5-gestión-de-procesos-)

- [Señales](#6-señales-)

- [Manejo de entrada de usuario](#7-manejo-de-entrada-de-usuario-)

- [Directorios](#8-directorios-)

- [Información de archivos](#9-información-de-archivos-️)

- [Duplicación de descriptores de archivo](#10-duplicación-de-descriptores-de-archivo-)

- [Terminal y TTY](#11-terminal-y-tty-)

- [Variables de entorno](#12-variables-de-entorno-)

<!-- - [Configuracion de la terminal](#13-configuración-de-la-terminal-termcapterminfo-️) -->


## Funciones

### 1. Gestión de memoria 🗂️ 

**`malloc(size_t size)`***: Reserva `size` bytes de memoria y devuelve un puntero al bloque reservado.

**`free(void *ptr)`**: Libera el bloque de memoria reservado previamente por `malloc`.

```c
#include <stdlib.h>
#include <stdio.h>

int main() 
{
	char	*buffer;

	buffer = (char *)malloc(20);
	if (!buffer)
		free(buffer);
	return (0);
}
```

### 2. Salida Estándar 🖨️ 
**`write`**(int fd, const void *buf, size_t count): Escribe `count` bytes desde `buf` hacia el descriptor de archivo `fd`.

```c
#include <unistd.h>

int main() 
{
    write(1, "Hello from write!\n", 18); 
    return 0;
}

```
**`printf(const char *format, ...)`**: Imprime texto formateado en la salida estándar.

```c
#include <stdio.h>

int main() 
{
    printf("Hello world with printf!\n");
    return 0;
}
```

### 3. Manejo de Archivos 🔐
**`access(const char *pathname, int mode)`**: Verifica permisos de acceso a un archivo (lectura, escritura, ejecución).

```c
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	if (access("file.txt", F_OK) == 0)
		write(STDOUT_FILENO, "file.txt exist\n", 16);
	else
		write (STDERR_FILENO, "Error: Not exist file.txt\n", 37);
	return (0);
}
```
**`open(const char *pathname, int flags)`**: Abre un archivo y devuelve su descriptor.

**`close(int fd)`**: Cierra un descriptor de archivo abierto.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	close(fd);
	write(STDOUT_FILENO, "file.txt is closed\n", 17);
	return (0);
}
```

**`read(int fd, void *buf, size_t count)`**: Lee `count` bytes del descriptor de archivo `fd` en `buf`.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_readed;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	bytes_readed = read(fd, buffer, 1024);
	if (bytes_readed != -1)
		write (STDOUT_FILENO, buffer, bytes_readed);
	else
		write (STDERR_FILENO, "Error: Failed read\n", 20);
	close(fd);
	write(STDOUT_FILENO, "\nfile.txt is closed\n", 18);
	return (0);
}
```
**`unlink(const char *pathname)`**: Elimina un archivo del sistema de archivos.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_readed;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	bytes_readed = read(fd, buffer, 1024);
	if (bytes_readed != -1)
		write (STDOUT_FILENO, buffer, bytes_readed);
	else
		write (STDERR_FILENO, "Error: Failed read\n", 20);
	close(fd);
	write(STDOUT_FILENO, "\nfile.txt is closed\n", 18);
	unlink("source/file.txt");
	write(STDOUT_FILENO, "\nfile.txt is deleted\n", 22);
	return (0);
}
```

### 4. Manejo de Errores ⚠️
**`strerror(int errnum)`**: Devuelve una cadena descriptiva del error asociado con 
`errnum`.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
	int fd;
	
	fd = open("not_found.txt", O_RDONLY);
	if (fd == -1)
		printf("Error: Cannot open file: %s\n", strerror(errno));
	return (0);
}
```
**`perror(const char *s)`**: Imprime un mensaje de error en la salida estándar de errores.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
	int fd;
	
	fd = open("not_found.txt", O_RDONLY);
	if (fd == -1)
		perror("Error: Cannot open file");
	return (0);
}
```

### 5. Gestión de procesos 👥
**`fork()`**: Crea un nuevo proceso `(hijo)` duplicando el proceso actual.
```c
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	__pid_t pid;

	pid = fork();
	if (pid == 0)
		printf("Children process (PID: %d)\n", getpid());
	else
		printf("Parent process(PID: %d)\n", getpid());
	return (0);
}
```

**`wait(int *status)`**: Espera a que termine un proceso hijo.

**`waitpid(pid_t pid, int *status, int options)`**: Espera de forma selectiva por un proceso hijo específico.

**`wait3(int *status, int options, struct rusage *rusage) / wait4(pid_t pid, int *status, int options, struct rusage *rusage)`**: Variantes de waitpid con información de uso de recursos.

```c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	__pid_t pid;

	pid = fork();
	if (pid == 0)
		printf("Children process (PID: %d)\n", getpid());
	else
	{
		wait(NULL); // Wait for all process to be finished
		waitpid(pid, NULL, 0); // Wait only the pid process
		write(STDOUT_FILENO, "Children process finished.\n", 28);
	}
	return (0);
}
```

**`execve(const char *pathname, char *const argv[], char *const envp[])`**: Reemplaza el proceso actual con uno nuevo.
```c
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	char *args[] = {"/bin/ls", "-l", NULL};
	execve("/bin/ls", args, NULL);
	write(STDERR, "execve failed", 15);
	return (1);
}
```
**`exit(int status)`**: Termina el proceso actual devolviendo status al sistema operativo.
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void) 
{
	while (1)
	{
		write(STDOUT_FILENO, "Exit after this write\n", 23);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
```

### 6. Señales 🚦

**`signal(int signum, void (*handler)(int))`**: Establece un manejador para una señal específica.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int sig)
{
	printf("Signal %d received!\n", sig);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	signal(SIGINT, handler);
	while (1)
		;
	return (0);
}
```

**`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**: Configura el comportamiento detallado para señales.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int sig)
{
	printf("Signal %d received!\n", sig);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	struct	sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror ("Error: falied sigaction");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for signal SIGINT (Ctrl+C)...\n");
	while (1)
		sleep(1);
	return (0);
}

```

**`kill(pid_t pid, int sig)`**: Envía una señal sig a un proceso pid.
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <signal.h>

int main() 
{
    pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Falied in fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Children process (PID: %d)\n", getpid());
		while (1)
			sleep(1);
	}
	else
	{
		printf("Parent process(PID: %d)\n", getpid());
		sleep(2);
		printf("Parent sendig SIGKILL to children.\n");
		kill(pid, SIGKILL);
		printf("Children process finished\n");
	}
	return (0);
}
```

### 7. Manejo de entrada de usuario 📚./

**`readline(const char *prompt)`**: Lee una línea desde la entrada estándar con una interfaz interactiva (permite edición de línea, historial, etc.).

```c
#include <unistd.h> 
#include <readline/readline.h>

int main(void) 
{
	char	*line;
	line = readline("Input line> ");
	if (!line)
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	free(line);
	return (0);
}
```

**`add_history(const char *line)`**: Añade la línea leída al historial de comandos.

```c
#include <unistd.h> 
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) 
{
	char	*input;

	input = readline("History> ");
	if (input) 
	{
		add_history(input);
		printf("Added to history: %s\n", input);
	}
	else
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	free(input);
	return (0);
}
```

**`rl_clear_history()`**: Limpia el historial de comandos almacenado en la sesión actual.

```c
#include <unistd.h> 
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) 
{
	char	*input

	input = readline("History> ");
	if (input) 
	{
		add_history(input);
		printf("Added to history: %s\n", input);
	}
	else
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	rl_clear_history();
	free(line);
	return (0);
}
```

**`rl_on_new_line()`**: Informa a readline que se ha iniciado una nueva línea.

**`rl_replace_line(const char *text, int clear_undo)`**: Reemplaza el contenido actual de la línea por `text`.

**`rl_redisplay()`**: Vuelve a mostrar la línea actual en el terminal.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	input = readline("Input: ");
	if (!input)
	{
		write(STDERR_FILENO, "Error: failed to read the line.\n", 34);
		exit(EXIT_FAILURE);
	}
	if (*line != '\0')
		add_history(input);
	printf("Input readed: %s\nNew input: ", input);
	rl_replace_line(readline(""), 0);
	rl_on_new_line();
	rl_redisplay();
	rl_clear_history();
	free(input);
	return (0);
}
```

### 8. Directorios 📁
**`getcwd(char *buf, size_t size)`**: Obtiene el directorio de trabajo actual.

```c
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("Actual directory: %s\n", cwd);
	else
		perror("Error: failed getcwd");
	return (0);
}
```
**`chdir(const char *path)`**: Cambia el directorio de trabajo actual.

```c
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("Actual directory: %s\n", cwd);
	else
		perror("Error: failed getcwd");
		
	chdir("/home/");
	printf("New directory: %s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}
```

**`opendir(const char *name)`**: Abre un directorio y devuelve un puntero al mismo.

**`readdir(DIR *dirp)`**: Lee la siguiente entrada de un directorio abierto.

**`closedir(DIR *dirp)`**: Cierra un directorio abierto.

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int	main(void)
{
	DIR				*dir;
	struct dirent	*ent;
	
	dir = opendir(".");
	if (!dir)
	{
		perror("Error: failed opendir");
		return(EXIT_FAILURE);
	}
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		printf("%s\n", ent->d_name);
	}
	closedir(dir);
	return (0);
}
```

### 9. Información de Archivos 🗃️

**`stat(const char *path, struct stat *buf)`**: Obtiene información del archivo.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>  

int	main(void)
{
	struct stat info;

	if (stat("file.txt", &info) == 0)
		printf("Size: %ld bytes\n", info.st_size);
	else
		perror("Error stat failed");
	return (0);
}
```

**`lstat(const char *path, struct stat *buf)`**: Igual que `stat`, pero sigue enlaces simbólicos.
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>  

int	main(void)
{
	struct stat info;

	if (lstat("file.txt", &info) == 0)
		printf("Size: %ld bytes\n", info.st_size);
	else
		perror("Error stat failed");
	return (0);
}
```
**`fstat(int fd, struct stat *buf)`**: Obtiene información del archivo usando su descriptor de archivo.

```c
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>  

int	main(void)
{
	int			fd;
	struct stat info;
	
	fd = open("file.txt", O_RDONLY);
	if (fstat(0, &info) == 0)
		printf("Size: %ld bytes\n", info.st_size);
	else
		perror("Error stat failed");
	close(fd);
	return (0);
}
```

### 10. Duplicación de Descriptores de Archivo 🔗

**`dup(int oldfd)`**: Duplica un descriptor de archivo.

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() 
{
	int fd_original;

	fd_original = open("original_file.txt", O_WRONLY | O_CREAT, 0644);
	printf("Duplicated fd\n");
	close(fd_original);
	return 0;
}
```

**`dup2(int oldfd, int newfd)`**: Duplica `oldfd` en `newfd`, cerrando `newfd` si está abierto.

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() 
{
	int fd_new;
	int fd_original;

	fd_original = open("original_file.txt", O_WRONLY | O_CREAT, 0644);
	fd_new = open("new_file.txt", O_WRONLY | O_CREAT, 0644);
	printf("Duplicated fd\n");
	if (!dup2(fd_new, fd_original))
		perror("Error: failed dup2");
	close(fd_original);
	close(fd_new);
	return (0);
}
```

### 11. Terminal y TTY 📞

**`isatty(int fd)`**: Verifica si un descriptor de archivo es un terminal.

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	if (isatty(STDIN_FILENO))
		printf("STDIN is a terminal.\n");
	else
		printf("STDIN is not a terminal.\n");
	return (0);
}
```

**`ttyname(int fd)`**: Devuelve el nombre del terminal asociado al descriptor `fd`.

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	if (isatty(STDIN_FILENO))
		printf("%s is a terminal.\n", ttyname(STDIN_FILENO));
	else
		printf("STDIN is not a terminal.\n");
	return (0);
}
```

**`ttyslot()`**: Devuelve el número de terminal de la sesión actual.

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	printf("%d is a terminal.\n", ttyslot());
	return (0);
}
```

**`ioctl(int fd, unsigned long request, ...):`** Controla dispositivos I/O.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int	main(void)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
	{
		perror("Error: failed ioctl");
		return(1);
	}
	printf("Size of terminal: %d rows, %d colums\n", w.ws_row, w.ws_col);
	return (0);
}
```

### 12. Variables de Entorno 🌍

**`getenv(const char *name)`**: Obtiene el valor de una variable de entorno.
```c
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*path;

	path = getenv("HOME");
	if (path!= NULL)
		printf("System HOME: %s\n", path);
	else
		printf("Variable HOME not defined\n");
	return(0);
}
```
<!-- 
### 13. Configuración de la Terminal (termcap/terminfo) 🎛️

**`tcgetattr(int fd, struct termios *termios_p)`**: Obtiene los atributos de la terminal.

**`tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`**: Configura los atributos de la terminal.

**`tgetent(char *bp, const char *name)`**: Inicializa la base de datos de capacidades de la terminal.

**`tgetflag(char *id)`**, **`tgetnum(char *id)`**, **`tgetstr(char *id, char **area)`**: Obtienen diferentes tipos de capacidades de la terminal.

**`tgoto(const char *cap, int col, int row)`**: Calcula la secuencia de control para moverse en la terminal.

**`tputs(const char *str, int affcnt, int (*putc)(int))`**: Imprime cadenas de control en la terminal. -->