# Implementación de Builtins en Minishell

Este documento describe el comportamiento esperado y los requisitos para implementar los comandos *built-in* solicitados en el proyecto `minishell`. Incluye validaciones necesarias y comportamientos específicos requeridos por el enunciado.

---

## 1. `echo` con la opción `-n`

### Comportamiento:

- Imprime los argumentos separados por espacios.
- Finaliza con salto de línea, a menos que se pase `-n`.

### Requisitos:

- Soportar múltiples `-n` (como `echo -n -n hola`).
- No interpretar secuencias como `\n`, `\t`, etc.

### Ejemplos:

```bash
echo hola mundo       # hola mundo\n
echo -n hola mundo    # hola mundo
```

---

## 2. `cd` con ruta absoluta o relativa

### Comportamiento:

- Cambia el directorio de trabajo al especificado.

### Requisitos:

- Usar `chdir(path)`.
- Actualizar las variables `PWD` y `OLDPWD`.
- Si la ruta no existe, imprimir error:

```bash
minishell: cd: no such file or directory: ruta
```

### Restricciones:

- No soportar `cd` sin argumentos (sin uso de `HOME`).

---

## 3. `pwd` sin opciones

### Comportamiento:

- Imprime la ruta absoluta del directorio actual.

### Requisitos:

- Usar `getcwd()`.
- Finalizar con salto de línea.

### Restricciones:

- No aceptar ninguna opción (`-L`, `-P`, etc).

---

## 4. `export` sin opciones

### Comportamiento:

- Asigna o modifica variables de entorno.
- Sin argumentos: imprime variables exportadas.

### Requisitos:

- Validar que el nombre cumpla:
  ```regex
  ^[a-zA-Z_][a-zA-Z0-9_]*$
  ```
- Al imprimir, usar formato:

```bash
declare -x VAR="valor"
```

### Restricciones:

- No soportar opciones como `-p` ni argumentos con comandos.

---

## 5. `unset` sin opciones

### Comportamiento:

- Elimina una variable de entorno.

### Requisitos:

- Validar nombres como en `export`.
- No imprimir nada al eliminar.

### Restricciones:

- No aceptar opciones ni flags.

---

## 6. `env` sin opciones o argumentos

### Comportamiento:

- Imprime todas las variables de entorno, una por línea.

### Requisitos:

- Usar formato `VAR=valor`.

### Restricciones:

- No soportar ningún argumento ni opción.

---

## 7. `exit` sin opciones

### Comportamiento:

- Termina la ejecución de minishell.

### Requisitos:

- Si se pasa un número, usarlo como `exit status` (`% 256`).
- Si se pasa un valor no numérico:

```bash
minishell: exit: valor: numeric argument required
exit status = 2
```

- Si se pasan más de un argumento:

```bash
minishell: exit: too many arguments
(no termina)
```

---

## Tabla Resumen

| Builtin  | Argumentos     | Requiere validación   | Acción principal        |
| -------- | -------------- | --------------------- | ----------------------- |
| `echo`   | `-n` y strings | No                    | Imprime con/sin newline |
| `cd`     | ruta           | Sí (existencia)       | Cambia directorio       |
| `pwd`    | ninguno        | No                    | Muestra path actual     |
| `export` | `VAR=VAL`      | Sí (regex)            | Modifica entorno        |
| `unset`  | `VAR`          | Sí (regex)            | Borra variable          |
| `env`    | ninguno        | No                    | Muestra entorno         |
| `exit`   | `[status]`     | Sí (número, cantidad) | Termina minishell       |

---
