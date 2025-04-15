# Minishell - Proyecto 42

# Funciones permitidas

## `char *readline(const char *prompt);`

### 📌 Prototipo
```c
char *readline(const char *prompt);
```

### 🔁 Retorno
- Devuelve un puntero a una cadena de caracteres que contiene la línea ingresada por el usuario (debe ser liberada con `free`).
- Devuelve `NULL` si se encuentra EOF (por ejemplo, al presionar `CTRL+D`).

### ⚙️ Funcionamiento
- Muestra un `prompt` personalizado.
- Permite al usuario editar la línea con teclas como flechas, suprimir, etc.
- Espera hasta que el usuario presione `Enter`.

### 🧠 Importancia en Minishell
- Se utiliza como entrada principal del shell.
- Permite una experiencia de usuario similar a Bash.
- Es compatible con el historial y edición avanzada de líneas.

---

## `void rl_clear_history(void);`

### 📌 Prototipo
```c
void rl_clear_history(void);
```

### 🔁 Retorno
- No retorna nada.

### ⚙️ Funcionamiento
- Borra todo el historial de comandos actual almacenado en memoria.

### 🧠 Importancia en Minishell
- Útil si quieres limpiar el historial de comandos manualmente.
- Aunque no es estrictamente necesario, puede usarse como parte de una función de limpieza.

---

## `void rl_on_new_line(void);`

### 📌 Prototipo
```c
void rl_on_new_line(void);
```

### 🔁 Retorno
- No retorna nada.

### ⚙️ Funcionamiento
- Notifica a la biblioteca Readline que se ha iniciado una nueva línea.
- Esencial para una actualización correcta del estado interno de Readline.

### 🧠 Importancia en Minishell
- Se usa especialmente después de una señal como `CTRL+C` para que Readline sepa que se debe mostrar un nuevo prompt limpio.

---

## `void rl_replace_line(const char *text, int clear_undo);`

### 📌 Prototipo
```c
void rl_replace_line(const char *text, int clear_undo);
```

### 🔁 Retorno
- No retorna nada.

### ⚙️ Funcionamiento
- Reemplaza el contenido actual de la línea por el texto proporcionado.
- `clear_undo = 1` borra el historial de deshacer (undo), `0` lo mantiene.

### 🧠 Importancia en Minishell
- Se utiliza tras manejar señales como `SIGINT` para borrar la línea incompleta.
- Asegura que el shell no muestre comandos a medio escribir después de interrupciones.

---

## `void rl_redisplay(void);`

### 📌 Prototipo
```c
void rl_redisplay(void);
```

### 🔁 Retorno
- No retorna nada.

### ⚙️ Funcionamiento
- Reescribe la línea de entrada en pantalla con el contenido actual.
- Se usa para forzar que el prompt y la línea de entrada se muestren correctamente.

### 🧠 Importancia en Minishell
- Muy útil después de manejar señales (como `SIGINT`) para refrescar la interfaz del usuario.

---

## `void add_history(const char *line);`

### 📌 Prototipo
```c
void add_history(const char *line);
```

### 🔁 Retorno
- No retorna nada.

### ⚙️ Funcionamiento
- Añade la línea pasada como argumento al historial de Readline.
- Permite que se pueda acceder con las flechas ↑ ↓ posteriormente.

### 🧠 Importancia en Minishell
- Hace que el shell recuerde los comandos anteriores, lo cual es fundamental para una buena experiencia de usuario.

---

## `ssize_t write(int fd, const void *buf, size_t count);`

### 🔁 Retorno
- Devuelve el número de bytes escritos.
- Devuelve `-1` en caso de error (por ejemplo, si `fd` no es válido).

### ⚙️ Funcionamiento
- Escribe hasta `count` bytes desde el búfer `buf` en el descriptor de archivo `fd`.

### 🧠 Importancia en Minishell
- Se utiliza para imprimir en la salida estándar (`STDOUT_FILENO`) o en errores (`STDERR_FILENO`).
- Es crucial para mostrar el prompt, errores o resultados.

---

## `int access(const char *pathname, int mode);`

### 🔁 Retorno
- Devuelve `0` si el acceso está permitido.
- Devuelve `-1` si hay error (por ejemplo, si no existe el archivo o no se tienen permisos).

### ⚙️ Funcionamiento
- Comprueba si el proceso actual tiene permisos para acceder a un archivo o directorio.
- El parámetro `mode` puede ser `R_OK`, `W_OK`, `X_OK` o `F_OK`.

### 🧠 Importancia en Minishell
- Permite verificar si un ejecutable existe y es ejecutable antes de llamar a `execve`.

---

## `int open(const char *pathname, int flags, mode_t mode);`

### 🔁 Retorno
- Devuelve un descriptor de archivo no negativo si tiene éxito.
- Devuelve `-1` en caso de error.

### ⚙️ Funcionamiento
- Abre un archivo y devuelve su descriptor de archivo.
- `flags` determina cómo se abre (ej. `O_RDONLY`, `O_WRONLY`, `O_CREAT`, `O_APPEND`, etc.).
- `mode` se usa si se crea el archivo, para definir permisos.

### 🧠 Importancia en Minishell
- Se utiliza para redirecciones (`<`, `>`, `>>`).
- Permite manejar archivos como entrada o salida de comandos.

---

## `ssize_t read(int fd, void *buf, size_t count);`

### 🔁 Retorno
- Devuelve el número de bytes leídos.
- Devuelve `0` en EOF.
- Devuelve `-1` si ocurre un error.

### ⚙️ Funcionamiento
- Lee hasta `count` bytes desde el descriptor `fd` al búfer `buf`.

### 🧠 Importancia en Minishell
- Se puede usar para leer archivos durante redirecciones de entrada o heredocs.

---

## `int close(int fd);`

### 🔁 Retorno
- Devuelve `0` si se cierra correctamente.
- Devuelve `-1` si ocurre un error.

### ⚙️ Funcionamiento
- Cierra el descriptor de archivo especificado.
- Libera recursos del sistema asociados al descriptor.

### 🧠 Importancia en Minishell
- Es vital cerrar descriptores después de redirecciones o ejecución de comandos.
- Previene fugas de descriptores que pueden agotar los recursos del sistema.

---
# Funciones de Gestión de Procesos y Señales - Minishell

Estas funciones permiten crear procesos hijos, esperar su finalización y gestionar señales. Son fundamentales para construir un shell que pueda ejecutar múltiples comandos y reaccionar a interrupciones del usuario.

---

## `pid_t fork(void);`

### 🔁 Retorno
- `0` en el proceso hijo.
- El PID del hijo en el proceso padre.
- `-1` en caso de error.

### ⚙️ Funcionamiento
- Crea un nuevo proceso duplicando el proceso actual.
- El hijo obtiene una copia del espacio de memoria del padre.

### 🧠 Importancia en Minishell
- Es esencial para ejecutar comandos externos sin bloquear el shell principal.

---

## `pid_t wait(int *wstatus);`

### 🔁 Retorno
- El PID del hijo que terminó.
- `-1` si no hay hijos o error.

### ⚙️ Funcionamiento
- Espera a que cualquier hijo termine y recoge su estado de salida.

### 🧠 Importancia en Minishell
- Permite sincronizar el padre con la terminación de los comandos ejecutados.

---

## `pid_t waitpid(pid_t pid, int *wstatus, int options);`

### 🔁 Retorno
- El PID del hijo esperado.
- `-1` si falla.

### ⚙️ Funcionamiento
- Espera a que un hijo específico termine.
- `options` permite modificar el comportamiento (ej. `WNOHANG`).

### 🧠 Importancia en Minishell
- Da más control sobre qué proceso esperar, útil en ejecuciones múltiples o pipes.

---

## `pid_t wait3(int *wstatus, int options, struct rusage *rusage);`

### 🔁 Retorno
- El PID del hijo terminado.
- `-1` si falla.

### ⚙️ Funcionamiento
- Como `waitpid`, pero permite recoger estadísticas de uso del sistema (`rusage`).

### 🧠 Importancia en Minishell
- Menos común, pero útil para monitorear recursos usados por procesos hijos.

---

## `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);`

### 🔁 Retorno
- El PID del hijo terminado.
- `-1` si falla.

### ⚙️ Funcionamiento
- Combina `waitpid` y `wait3` para esperar un proceso específico y obtener estadísticas.

### 🧠 Importancia en Minishell
- Similar a `waitpid`, pero con métricas adicionales.

---

## `__sighandler_t signal(int signum, __sighandler_t handler);`

### 🔁 Retorno
- El manejador anterior, o `SIG_ERR` si falla.

### ⚙️ Funcionamiento
- Establece un manejador para una señal específica (`SIGINT`, `SIGQUIT`, etc.).

### 🧠 Importancia en Minishell
- Permite capturar señales como `CTRL+C` y actuar apropiadamente (por ejemplo, mostrar un nuevo prompt).

---

## `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si ocurre un error.

### ⚙️ Funcionamiento
- Proporciona una interfaz más robusta y flexible que `signal` para manejar señales.
- Permite definir cómo reaccionar ante señales.

### 🧠 Importancia en Minishell
- Usado para una gestión segura y precisa de señales.

---

## `int kill(pid_t pid, int sig);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` en caso de error.

### ⚙️ Funcionamiento
- Envía una señal al proceso con PID `pid`.
- Por ejemplo, `SIGKILL`, `SIGINT`, etc.

### 🧠 Importancia en Minishell
- Puede usarse para terminar procesos hijos manualmente o gestionar señales entre procesos.

---

## `void exit(int status);`

### 🔁 Retorno
- No retorna. Termina el proceso actual.

### ⚙️ Funcionamiento
- Finaliza el proceso y devuelve el código `status` al sistema operativo.

### 🧠 Importancia en Minishell
- Usado por el built-in `exit` y para cerrar el shell correctamente.

---

## `char *getcwd(char *buf, size_t size);`

### 🔁 Retorno
- Puntero a `buf` con el path actual, o `NULL` si falla.

### ⚙️ Funcionamiento
- Llena el buffer `buf` con el directorio de trabajo actual del proceso.

### 🧠 Importancia en Minishell
- Usado por el built-in `pwd` para mostrar el path actual.

---

## `int chdir(const char *path);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Cambia el directorio de trabajo actual al especificado por `path`.

### 🧠 Importancia en Minishell
- Necesario para implementar el built-in `cd`.

---

## `int stat(const char *pathname, struct stat *statbuf);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Obtiene información sobre el archivo especificado y la guarda en `statbuf`.
- Sigue enlaces simbólicos.

### 🧠 Importancia en Minishell
- Útil para verificar existencia, tipo y permisos de archivos antes de ejecutar.

---

## `int lstat(const char *pathname, struct stat *statbuf);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Similar a `stat`, pero si el archivo es un enlace simbólico, devuelve info del enlace, no del destino.

### 🧠 Importancia en Minishell
- Útil para distinguir entre archivos reales y enlaces simbólicos.

---

## `int fstat(int fd, struct stat *statbuf);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Como `stat`, pero actúa sobre un descriptor de archivo abierto.

### 🧠 Importancia en Minishell
- Útil para redirecciones y manejo de archivos ya abiertos.

---

## `int unlink(const char *pathname);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Elimina el archivo especificado por `pathname`.
- No borra el contenido hasta que no haya más referencias.

### 🧠 Importancia en Minishell
- Puede usarse para limpieza temporal de archivos (como en `heredoc`).

---

## `int execve(const char *pathname, char *const argv[], char *const envp[]);`

### 🔁 Retorno
- No retorna si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Reemplaza el proceso actual con uno nuevo indicado por `pathname`.
- `argv[]` contiene los argumentos del nuevo programa.
- `envp[]` contiene las variables de entorno.

### 🧠 Importancia en Minishell
- Es la base para ejecutar comandos externos como `ls`, `cat`, etc.
- Se suele usar después de hacer `fork()`.

---

## `int dup(int oldfd);`

### 🔁 Retorno
- Nuevo descriptor de archivo que es una copia de `oldfd`, o `-1` si falla.

### ⚙️ Funcionamiento
- Duplica un descriptor de archivo existente.

### 🧠 Importancia en Minishell
- Útil para redirecciones. Permite guardar el descriptor original antes de redirigir.

---

## `int dup2(int oldfd, int newfd);`

### 🔁 Retorno
- `newfd` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Duplica `oldfd` en `newfd`. Si `newfd` está abierto, se cierra primero.

### 🧠 Importancia en Minishell
- Fundamental para implementar redirecciones (`<`, `>`, `>>`) y `pipes`.
- Por ejemplo, para redirigir stdout de un proceso a un archivo.

---

## `int pipe(int pipefd[2]);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Crea un canal unidireccional de comunicación (pipe).
- `pipefd[0]` es el extremo de lectura, `pipefd[1]` es el de escritura.

### 🧠 Importancia en Minishell
- Permite conectar la salida de un proceso con la entrada de otro (`ls | grep txt`).
- Se usa junto con `fork()` y `dup2()`.

---

## `DIR *opendir(const char *name);`

### 🔁 Retorno
- Puntero a un objeto `DIR` si tiene éxito.
- `NULL` si falla.

### ⚙️ Funcionamiento
- Abre el directorio indicado por `name` y devuelve un puntero para iterarlo.

### 🧠 Importancia en Minishell
- Aunque no siempre es necesario, puede ser útil si decides implementar un built-in como `ls` o necesitas verificar contenidos del directorio actual.

---

## `struct dirent *readdir(DIR *dirp);`

### 🔁 Retorno
- Puntero a una estructura `dirent` que describe la siguiente entrada del directorio.
- `NULL` si no hay más entradas o si ocurre un error.

### ⚙️ Funcionamiento
- Lee secuencialmente las entradas del directorio abierto por `opendir`.

### 🧠 Importancia en Minishell
- Útil si deseas listar archivos manualmente o implementar funcionalidades de exploración del sistema de archivos.

---

## `int closedir(DIR *dirp);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Cierra el directorio previamente abierto con `opendir`.

### 🧠 Importancia en Minishell
- Buena práctica liberar los recursos del sistema cuando terminas de trabajar con un directorio.

---

## `int isatty(int fd);`

### 🔁 Retorno
- `1` si el descriptor `fd` está asociado a un terminal.
- `0` si no lo está.
- `-1` si ocurre un error.

### ⚙️ Funcionamiento
- Verifica si el descriptor de archivo hace referencia a un terminal.

### 🧠 Importancia en Minishell
- Permite saber si el shell está en modo interactivo.

---

## `char *ttyname(int fd);`

### 🔁 Retorno
- Cadena con el nombre del terminal asociado al descriptor `fd`.
- `NULL` si ocurre un error.

### ⚙️ Funcionamiento
- Devuelve el nombre del dispositivo terminal para el descriptor dado.

### 🧠 Importancia en Minishell
- Puede utilizarse para depurar o para mostrar información del terminal.

---

## `int ttyslot(void);`

### 🔁 Retorno
- Número de la entrada en el archivo de terminales (/etc/ttys) que corresponde al terminal de control.
- `0` si no se encuentra.
- `-1` si hay error.

### ⚙️ Funcionamiento
- Determina el número de la terminal que está siendo usada.

### 🧠 Importancia en Minishell
- Poco común en shells básicos, pero útil para shells más complejos que manejan múltiples sesiones.

---

## `int ioctl(int fd, unsigned long request, ...);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Realiza operaciones de control específicas del dispositivo referenciado por `fd`.
- El tercer argumento depende de la operación (`request`).

### 🧠 Importancia en Minishell
- Utilizado para insertar caracteres en el buffer de entrada (por ejemplo, con `TIOCSTI`) o manipular atributos del terminal.

---

## `char *getenv(const char *name);`

### 🔁 Retorno
- Puntero a la cadena que contiene el valor de la variable de entorno.
- `NULL` si no existe.

### ⚙️ Funcionamiento
- Busca el valor de una variable de entorno.

### 🧠 Importancia en Minishell
- Esencial para implementar la expansión de variables (`$PATH`, `$HOME`, etc.) y para construir el entorno del proceso hijo antes de `execve`.

---

## `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Cambia los atributos del terminal asociado con `fd`.
- `optional_actions` puede ser `TCSANOW`, `TCSADRAIN` o `TCSAFLUSH`.

### 🧠 Importancia en Minishell
- Útil para modificar el modo de entrada del terminal, por ejemplo para desactivar el eco.

---

## `int tcgetattr(int fd, struct termios *termios_p);`

### 🔁 Retorno
- `0` si tiene éxito.
- `-1` si falla.

### ⚙️ Funcionamiento
- Obtiene los parámetros actuales del terminal referenciado por `fd` y los guarda en `termios_p`.

### 🧠 Importancia en Minishell
- Necesario para guardar el estado actual del terminal antes de modificarlo.

---

## `int tgetent(char *bp, const char *name);`

### 🔁 Retorno
- `1` si encuentra la entrada del terminal.
- `0` si no la encuentra.
- `-1` si no puede acceder a la base de datos termcap.

### ⚙️ Funcionamiento
- Carga la descripción del terminal desde la base de datos termcap.

### 🧠 Importancia en Minishell
- Prepara el entorno para usar otras funciones `tget*`.

---

## `int tgetflag(char *id);`

### 🔁 Retorno
- `1` si el flag está presente.
- `0` si no lo está.

### ⚙️ Funcionamiento
- Consulta un flag booleano de las capacidades del terminal.

### 🧠 Importancia en Minishell
- Útil para verificar comportamientos soportados por el terminal.

---

## `int tgetnum(char *id);`

### 🔁 Retorno
- Número asociado a la capacidad consultada.
- `-1` si no está definida.

### ⚙️ Funcionamiento
- Consulta una capacidad numérica del terminal.

### 🧠 Importancia en Minishell
- Permite conocer valores como el número de columnas o líneas.

---

## `char *tgetstr(char *id, char **area);`

### 🔁 Retorno
- Cadena que representa la capacidad del terminal.
- `NULL` si falla.

### ⚙️ Funcionamiento
- Devuelve una cadena que describe una secuencia de escape para una capacidad específica.

### 🧠 Importancia en Minishell
- Permite usar códigos especiales del terminal como limpiar la pantalla o mover el cursor.

---

## `char *tgoto(const char *cap, int col, int row);`

### 🔁 Retorno
- Cadena con secuencia de escape para posicionar el cursor.

### ⚙️ Funcionamiento
- Usa una cadena de `tgetstr` para calcular la secuencia que posiciona el cursor en `col`, `row`.

### 🧠 Importancia en Minishell
- Útil para tareas de manipulación avanzada del cursor.

---

## `int tputs(const char *str, int affcnt, int (*putc)(int));`

### 🔁 Retorno
- `OK` o `ERR`, según el resultado.

### ⚙️ Funcionamiento
- Imprime una cadena con posibles retardos controlados, usando la función `putc` para escribir cada carácter.

### 🧠 Importancia en Minishell
- Requerido para imprimir secuencias de escape de manera segura.

---
