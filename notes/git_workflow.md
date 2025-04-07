# Flujo de trabajo en GitHub con Git para proyectos grupales

## 1. Configuración inicial
- **Crear repositorio**: Un miembro crea el repositorio en GitHub.
- **Agregar colaboradores**: Añadir al equipo como colaboradores.
- **Clonar el repositorio**: Cada miembro clona el repositorio con `git clone <URL_DEL_REPO>`.

## 2. Uso de ramas y desarrollo colaborativo
- **Crear una rama** para cada nueva funcionalidad o corrección:
  ```bash
  git checkout -b nombre-de-la-rama
  ```
- **Realizar cambios** y confirmar:
  ```bash
  git add .
  git commit -m "Descripción de los cambios"
  ```
- **Subir la rama** al repositorio remoto:
  ```bash
  git push origin nombre-de-la-rama
  ```
- **Abrir un Pull Request (PR)** en GitHub y pedir revisión.
- **Hacer merge** después de la revisión y eliminar la rama:
  ```bash
  git branch -d nombre-de-la-rama
  git push origin --delete nombre-de-la-rama
  ```

## 3. Mantener el repositorio actualizado
- **Sincronizar con `main`** antes de hacer nuevos cambios:
  ```bash
  git checkout main
  git pull origin main
  git checkout nombre-de-la-rama
  git merge main
  ```
- **Resolver conflictos** y hacer commit de los cambios resueltos.

## 4. Buenas prácticas
- Usar mensajes de commit descriptivos.
- Hacer PR pequeños y frecuentes.
- No hacer cambios directamente en `main` o `develop`.
- Revisar código de otros antes de hacer merge.
- Sincronizar con `main` regularmente para evitar conflictos grandes.