# Casos de Prueba para Minishell

Este documento contiene una lista de comandos para probar el comportamiento esperado de un shell tipo Bash, incluyendo tanto casos correctos como errores intencionales. Esto te ayudará a validar tu `minishell`, especialmente en el parseo.

---

echo asd$PWD

echo "$PWD asd $USER"
vgoyzuet

echo $1PWD

echo asd$1PWD

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
banana			OK
```
Status = OK
### ❌ Redirección mal usada
```bash
echo hola >		OK
```
Status = OK
### ❌ Comillas sin cerrar
```bash
echo "hola //I think this is in the parser
```
The program exit inmediately
### ❌ Pipe mal formado
```bash
| ls			OK
ls |			//I think this in the parser (DONE, but still running the command)
ls || grep .c	//The same (DONE, but still running the command)
```

### ❌ Heredoc sin delimitador
```bash
cat <<				OK
```
Update status = 2(syntax error)
### ❌ Variable no existente
```bash
echo $NOEXISTE		OK
```
Status = OK
### ❌ Acceso sin permisos
```bash
echo hola > /root/test.txt
```
Print message// minishell: /root/test.txt: permission denied Update status = 1(generic error)
### ❌ Redirección sin comando
```bash
> archivo.txt	//i think this in the parser (DONE, but make redir without command)
```
Update status = 0 because the first value you give me like a command and print in stdout "command not found".
### ❌ Error de ejecución
```bash
/bin/ls noexiste	OK
```
Update status = 2(syntax error)
---

## 🧪 Otros Casos Curiosos

```bash
echo $?						OK
sleep 1 | echo terminado	OK
cd && pwd		NOT TO HANDLE
```
Status = OK
I must to update the status in case the program works it, after of an error
---

## 🔁 Casos con Redirecciones en Posiciones Intermedias

### ✅ Redirección de salida en medio
```bash
ls -l > out.txt | wc -l		OK
```
Status = OK
### ✅ Heredoc antes del pipe
```bash
cat << EOF | grep hola		OK
línea 1
hola mundo
EOF
```
Status = OK
### ❌ Redirección sin comando después del pipe
```bash
echo hola | > archivo.txt		//Parsing needs to know what type it is whitout a first valid command and creates the file (DONE, but same other similar cases)
```
update status = 0
### ❌ Uso confuso de heredoc con redirección
```bash
ls -l | cat << EOF | > output | wc -l
línea
EOF							//The same as the previous case and the program continues in an infinite loop
```
expected status = 0
### ✅ Redirección combinada con pipes válidos
```bash
echo hola > archivo.txt | cat archivo.txt										OK
```
Status = OK
---


### Casos avanzados de Input invalidos

```bash
| ls					Update status = 2
ls |					//Parser
< archivo.txt ls		//Parser Message: "minishell: archivo.txt: No such file or directory"
> out.txt echo hola		//Parser
echo hola >				OK // update status = 2
cat << 					OK // update status = 2
ls || grep foo			//Parser
echo hola && ls			//Parser
echo 'hola				//Parser
echo "hola				//Parser
```

---

### Casos de Inputs raros, pero validos

```bash
ls|wc						OK Status = OK	
ls   |   wc -l				OK Status = OK
ls | | wc   doble pipe		//Parser Expected status = 2
cd / | ls -a				Still incompleted cd
grep '' archivo.txt			If exists the file and  the command doesn´t work Status = 1 else Status = 0, if doesn´t exist the file Message: grep: archivo.txt: No such file or directory Status = 2
echo "\\\\\\\\\\"			OK Status = OK
````

---

### Caso de input inválido especial

```bash
$?  (DONE)
Show the next message:

AddressSanitizer:DEADLYSIGNAL
=================================================================
==4404==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000008 (pc 0x5b364c939164 bp 0x7ffcb53de7b0 sp 0x7ffcb53de6c0 T0)
==4404==The signal is caused by a READ memory access.
==4404==Hint: address points to the zero page.
    #0 0x5b364c939164 in split_cmd src/set_input.c:49
    #1 0x5b364c939ca6 in split_input src/set_input.c:98
    #2 0x5b364c93a0eb in set_input src/set_input.c:116
    #3 0x5b364c9377bb in main src/main.c:18
    #4 0x71e4b542a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #5 0x71e4b542a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #6 0x5b364c937584 in _start (/home/jocalder/42cursus/mini-chela/minishell+0x4584) (BuildId: 19b5b55715924203ae8131c3aef927739d8fe725)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV src/set_input.c:49 in split_cmd
==4404==ABORTING
```

---
