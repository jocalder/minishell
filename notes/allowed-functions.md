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
