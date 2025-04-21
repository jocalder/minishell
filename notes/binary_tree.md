# Concepto de árbol binario

## 1. Tokenizar o tokens
Tokenizar significa dividir una cadena de texto en partes significativas, llamadas tokens. Es el primer paso del análisis de una entrada.
Token como identificador de la entrada para posteriormente tratarlo segun su comportamiento en el programa. 
## 2. Estructura de un árbol binario
- **Línea de comandos**: ls -l | grep "file" | wc -l
                                      |
                                    /   \
                                    |    wc -l
                                  /   \
                               ls -l grep "file"
Divide la entrada en tokens separados por pipes, por ejemplo:
- **Tokenizado**: ["ls -l", "grep txt", "wc -l"].
Una vez tokenizado se debería guardar cada bloque en un char ** .. para poder pasarselo a **execve**.
