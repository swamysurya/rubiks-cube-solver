# Git & Version Control — Learning Notes

## 1. Git Commit Message Conventions
We follow the **Conventional Commits** specification to keep git history clear, structured, and searchable:

```text
<type>: <short description>
```

| Type | When to Use | Example |
| :--- | :--- | :--- |
| **feat** | Adding new application functionality | `feat: implement front face rotation and tests` |
| **fix** | Fixing a bug or logic flaw | `fix: correct adjacent sticker mapping in F move` |
| **docs** | Documentation changes | `docs: add project architecture notes` |
| **build** | Changes to build configuration or tools | `build: configure project with CMake` |
| **test** | Adding, refactoring, or updating tests | `test: add cube initialization checks` |
| **refactor**| Restructuring code without changing behavior | `refactor: simplify sticker indexing calculation` |
| **chore** | Routine maintenance tasks | `chore: add build directory to gitignore` |

### Multi-line Commit Format (Title + Body)
For major features, provide a short summary followed by bullet points:
```bash
git commit -m "feat: implement front face rotation and tests" \
           -m "- Add rotateFaceClockwise() helper using 2D matrix transformation" \
           -m "- Implement rotateFrontClockwise() with adjacent rim permutations across U, R, D, L" \
           -m "- Add unit tests verifying 1-turn state change and 4-turn cyclic identity (F^4 = I)"
```

---

## 2. Essential Git Workflow Commands

### Inspecting Repository State
```powershell
# Check modified, staged, and untracked files
git status

# Inspect unstaged changes in working copy
git diff

# Inspect changes already staged for commit
git diff --cached
git diff --staged

# List all files tracked by Git
git ls-files
```

### Staging, Committing, and Syncing
```powershell
# Stage specific files
git add CMakeLists.txt tests/CubeTests.cpp docs/learning-notes.md

# Stage all tracked modifications
git add -u

# Commit with message
git commit -m "feat: your message here"

# Push to remote GitHub repository
git push origin main
```

---

## 3. Helpful Terminal Commands (PowerShell)
```powershell
# View file contents directly in terminal
Get-Content src/main.cpp

# Check whether a file or path exists
Test-Path docs/learning-notes.md

# List all files recursively
Get-ChildItem -Recurse -File
```

