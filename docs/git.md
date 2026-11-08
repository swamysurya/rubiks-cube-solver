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

## 2. Feature Branching Workflow (Standard Practice)

Working on isolated feature branches instead of committing directly to `main` is an industry standard practice (as mandated in `docs/requirements.md`).

### Why Use Feature Branches?
1. **Isolation**: Development and experimentation happen safely without risking the stability of `main`.
2. **Reviewable Chunks**: Each branch encapsulates one specific feature, bug fix, or task.
3. **Clean History**: Merges into `main` represent completed, fully tested milestones.

### Branch Naming Conventions
```text
feat/<feature-name>    # For new functionality (e.g., feat/down-face-rotation)
fix/<bug-name>         # For bug fixes (e.g., fix/sticker-index-mapping)
docs/<topic>           # For documentation updates (e.g., docs/branching-guide)
test/<scope>           # For test suite additions (e.g., test/solver-invariants)
```

### The Standard 6-Step Branch Lifecycle

```
1. main (clean) ──> 2. checkout -b feat/... ──> 3. Code, Test, Doc ──> 4. commit ──> 5. merge into main ──> 6. push
```

```powershell
# Step 1: Ensure main is clean and selected
git checkout main

# Step 2: Create and switch to a new feature branch
git checkout -b feat/down-face-rotation

# Step 3 & 4: Implement code, write tests, update docs, then commit on the branch
git add .
git commit -m "feat: implement Down face rotation and tests"

# Step 5: Switch back to main and merge the completed feature
git checkout main
git merge feat/down-face-rotation

# Step 6: Push updated main to GitHub and delete the merged local branch (optional)
git push origin main
git branch -d feat/down-face-rotation
```

---

## 3. Essential Git Workflow Commands

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

## 4. Git Stashing (`git stash`)

### What is Git Stash?
`git stash` temporarily shelves (or "stashes") uncommitted changes (both staged and unstaged) in your working directory, resetting your working tree to match `HEAD`. This allows you to work on something else or switch branches without losing your in-progress work or creating temporary "WIP" commits.

### When to Use It?
1. **Urgent Context Switching**: You are in the middle of implementing a feature on `feat/...`, but you need to switch to `main` or another branch to fix an urgent bug or review code.
2. **Pulling Upstream Changes**: Git refuses to `git pull` because your local changes would be overwritten. You can `git stash`, pull, and then `git stash pop`.
3. **Experimental Testing**: You want to test how the codebase compiles/runs without your current edits without deleting them.

### Essential Stash Commands
```powershell
# 1. Stash current tracked modifications
git stash

# 2. Stash including newly created (untracked) files
git stash -u

# 3. Stash with a descriptive note
git stash save "WIP: prime rotations"

# 4. View the list of all saved stashes
git stash list

# 5. Restore the most recent stash and remove it from the stash list
git stash pop

# 6. Restore the stash without removing it from the stash list
git stash apply

# 7. Discard the most recent stash (or a specific stash like stash@{0})
git stash drop
```

---

## 5. Helpful Terminal Commands (PowerShell)
```powershell
# View file contents directly in terminal
Get-Content src/main.cpp

# Check whether a file or path exists
Test-Path docs/learning-notes.md

# List all files recursively
Get-ChildItem -Recurse -File
```

