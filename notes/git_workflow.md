
# 🧪 Flujo de trabajo en GitHub con Git para proyectos grupales

## 1. ⚙️ Configuración inicial
- **Crear repositorio**: Un miembro crea el repositorio en GitHub.
- **Agregar colaboradores**: Añadir al equipo como colaboradores.
- **Clonar el repositorio**: Cada miembro clona el repositorio con:
  ```bash
  git clone <URL_DEL_REPO>
  ```

## 2. 🌱 Uso de ramas y desarrollo colaborativo
- **Actualizar referencias remotas (opcional pero recomendado)**  
  Antes de empezar trabajo nuevo, actualiza el estado del repositorio remoto:
  ```bash
  git fetch origin
  ```

- **Crear una nueva rama desde `main`**:
  ```bash
  git checkout main
  git pull origin main
  git checkout -b nombre-de-la-rama
  ```

- **Hacer cambios y confirmarlos**:
  ```bash
  git add .
  git commit -m "Descripción de los cambios"
  ```

- **Subir la rama al repositorio remoto**:
  ```bash
  git push origin nombre-de-la-rama
  ```

- **Abrir un Pull Request (PR)** en GitHub y solicitar revisión.

- **Mergear tras aprobación** (usualmente en GitHub) y luego:
  ```bash
  git checkout main
  git pull origin main
  git branch -d nombre-de-la-rama
  git push origin --delete nombre-de-la-rama
  ```

## 3. 🔄 Mantener el repositorio y ramas sincronizadas
- **Mantener la rama `main` actualizada**:
  ```bash
  git checkout main
  git fetch origin
  git pull origin main
  ```

- **Actualizar tu rama con los últimos cambios de `main`**:
  ```bash
  git checkout nombre-de-la-rama
  git merge main
  # o si prefieres rebase:
  # git rebase main
  ```

- **Resolver conflictos** si los hay y hacer `commit`.

## 4. ✅ Buenas prácticas
- Usar mensajes de commit claros y descriptivos.
- Hacer Pull Requests pequeños, frecuentes y enfocados.
- Nunca trabajar directamente sobre `main` o `develop`.
- Revisar y comentar PRs de compañeros antes de mergear.
- Ejecutar `git fetch` regularmente para ver ramas nuevas y cambios remotos.
- Sincronizar con `main` antes de empezar a trabajar y antes de hacer push final.

---