# Minishell - Proyecto 42

## Descripción
Este proyecto que consiste en crear una versión simplificada de un shell de Unix, similar a *bash*. Debe soportar la ejecución de comandos, redirecciones, pipes y gestionar señales, entre otras funcionalidades.

## Funcionalidades principales

### Shell interactivo
- Mostrar un *prompt* esperando un comando.
- Mantener un historial de comandos.
- Ejecutar programas y comandos ingresados por el usuario.

### Ejecución de comandos
- Buscar el ejecutable en `$PATH` o usar rutas absolutas/relativas.
- Manejar correctamente la ejecución de procesos con `execve`.

### Manejo de señales
- `CTRL+C` → Cancela el comando actual y muestra un nuevo *prompt*.
- `CTRL+D` → Cierra el shell.
- `CTRL+\` → No hace nada.

### Manejo de comillas
- Comillas simples `'` → Todo dentro se trata como un string literal.
- Comillas dobles `"` → Se respetan los caracteres especiales, excepto `$`.

### Redirecciones
- `<`  → Redirige input desde un archivo.
- `>`  → Redirige output a un archivo (sobreescribiéndolo).
- `>>` → Redirige output en modo *append*.
- `<<` → *Heredoc*: leer hasta encontrar un delimitador específico.

### Pipes (`|`)
- Conectar la salida de un comando con la entrada del siguiente (`ls | grep txt`).

### Variables de entorno
- Expandir `$VAR` con su valor correspondiente.
- `$?` → Estado de salida del último comando ejecutado.

### Built-ins a implementar
- `echo` (con opción `-n`).
- `cd` (solo con rutas absolutas/relativas).
- `pwd` (sin opciones).
- `export`, `unset`, `env`, `exit` (sin opciones).

## Restricciones
- No usar más de una variable global para manejar señales.
- No interpretar caracteres especiales como `\` o `;` fuera de lo especificado.
- No es necesario manejar *wildcards* (`*`, `?`, etc.).

## Recomendaciones para el desarrollo
### Dividir el proyecto en módulos:
1. **Parser:** Analiza la entrada del usuario.
2. **Ejecutor:** Ejecuta comandos, maneja `execve` y `fork`.
3. **Gestor de señales:** Controla `CTRL+C`, `CTRL+D`, etc.
4. **Built-ins:** Implementa `cd`, `echo`, `pwd`, etc.

### Otras consideraciones
- Usar `readline` y `add_history` para manejar la entrada del usuario.
- Gestionar procesos correctamente con `fork`, `wait`, `pipe`, `dup2`.
