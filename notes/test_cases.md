# Casos de Prueba para Minishell

Este documento contiene una lista de comandos para probar el comportamiento esperado de un shell tipo Bash, incluyendo tanto casos correctos como errores intencionales. Esto te ayudará a validar tu `minishell`, especialmente en el parseo.

---

## ✅ Comandos Válidos

```bash
echo hola mundo
pwd
cd ..
cd /
cd ./src
ls -l | grep .c
cat < Makefile
echo hola > file.txt
echo otra línea >> file.txt
cat file.txt | sort | uniq
export VAR=42
echo $VAR
echo "$VAR"
unset VAR
echo $VAR
```

---

## 🧪 Redirecciones Combinadas

```bash
ls > salida.txt
cat < salida.txt | wc -l
grep "main" < salida.txt > result.txt
```

---

## 🪄 Heredoc

```bash
cat << EOF
línea 1
línea 2
EOF
```

---

## 🚨 Casos con Errores o Comportamiento Extraño

### ❌ Comando no encontrado
```bash
banana
```

### ❌ Redirección mal usada
```bash
echo hola >
```

### ❌ Comillas sin cerrar
```bash
echo "hola
```

### ❌ Pipe mal formado
```bash
| ls
ls |
ls || grep .c
```

### ❌ Heredoc sin delimitador
```bash
cat <<
```

### ❌ Variable no existente
```bash
echo $NOEXISTE
```

### ❌ Acceso sin permisos
```bash
echo hola > /root/test.txt
```

### ❌ Redirección sin comando
```bash
> archivo.txt
```

### ❌ Error de ejecución
```bash
/bin/ls noexiste
```

---

## 🧪 Otros Casos Curiosos

```bash
echo $?
sleep 1 | echo terminado
cd && pwd
```

---

## 🔁 Casos con Redirecciones en Posiciones Intermedias

### ✅ Redirección de salida en medio
```bash
ls -l > out.txt | wc -l
```

### ✅ Heredoc antes del pipe
```bash
cat << EOF | grep hola
línea 1
hola mundo
EOF
```

### ❌ Redirección sin comando después del pipe
```bash
echo hola | > archivo.txt
```

### ❌ Uso confuso de heredoc con redirección
```bash
ls -l | cat << EOF | > output | wc -l
línea
EOF
```

### ✅ Redirección combinada con pipes válidos
```bash
echo hola > archivo.txt | cat archivo.txt
```

---


### Casos avanzados de Input invalidos

```bash
| ls
ls |
< archivo.txt ls
> out.txt echo hola
echo hola >
cat << 
ls || grep foo
echo hola && ls
echo 'hola
echo "hola
```

---

### Casos de Inputs raros, pero validos

```bash
ls|wc
ls   |   wc -l
ls | | wc   # doble pipe
cd / | ls -a
grep '' archivo.txt
echo "\\\\\\\\\\"
````

---