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

## 4. Git Releases & Version Tagging (`git tag`)

### What is a Git Tag?
A **Git tag** is a permanent, immutable marker (or bookmark) attached to a specific commit in the repository's history. 

Unlike branches — which are dynamic and move forward automatically with every new commit — **tags never move**. Once attached to a commit, a tag marks that exact snapshot in time forever.

### Branch vs. Tag: Key Differences
| Characteristic | Git Branch (e.g. `main`, `feat/...`) | Git Tag (e.g. `v0.1.0`) |
| :--- | :--- | :--- |
| **Mutability** | **Dynamic**: Moves automatically with every commit. | **Static / Immutable**: Glued to one commit forever. |
| **Purpose** | In-progress work and active development. | Marking releases, milestones, or deployment versions. |
| **Checkout** | Leaves you on an active branch to write code. | Enters a "detached HEAD" state (read-only time-travel). |

---

### Lightweight Tags vs. Annotated Tags

1. **Lightweight Tag**:
   A simple pointer to a commit (just a named bookmark with no extra data):
   ```powershell
   git tag v0.1.0-lightweight
   ```

2. **Annotated Tag (Industry Standard for Releases)**:
   Stored as a full Git object containing:
   - Tag creator's name and email
   - Creation date and timestamp
   - Descriptive release message
   - Optional cryptographic GPG signature
   ```powershell
   git tag -a v0.1.0 -m "Milestone 1: Complete 18-move 3x3 Rubik's Cube simulation engine"
   ```

---

### Semantic Versioning (SemVer)
Version tags standardly follow the `vMAJOR.MINOR.PATCH` pattern:
* **MAJOR (`1.0.0`)**: Incompatible API changes or complete architectural overhauls.
* **MINOR (`0.1.0`)**: Major functional milestone added in a backwards-compatible manner (e.g., our full 18-move cube model!).
* **PATCH (`0.1.1`)**: Small bug fixes and documentation corrections.

---

### Essential Git Tagging Commands

```powershell
# 1. Create an annotated release tag on the current commit
git tag -a v0.1.0 -m "Milestone 1: Complete 18-move Rubik's Cube simulator"

# 2. List all existing tags in alphabetical order
git tag

# 3. List tags along with their annotation messages
git tag -n1

# 4. View full metadata and commit details of a tag
git show v0.1.0

# 5. Push a specific tag to GitHub
# Note: 'git push origin main' does NOT push tags automatically!
git push origin v0.1.0

# 6. Push ALL local tags to GitHub in one command
git push origin --tags

# 7. Time-travel: checkout the code exactly as it existed at v0.1.0
git checkout v0.1.0

# 8. Delete a local tag (if made by mistake)
git tag -d v0.1.0

# 9. Delete a tag on the remote GitHub repository
git push origin --delete v0.1.0
```

---

## 5. Git Productivity Aliases

Developers set up short aliases in `~/.gitconfig` to save repetitive typing:

```powershell
# Configure global shortcuts
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.cob "checkout -b"
git config --global alias.cm "commit -m"
git config --global alias.br branch
git config --global alias.lg "log --oneline --graph --decorate -n 10"

# Now you can use:
git st            # runs 'git status'
git co main       # runs 'git checkout main'
git cob feat/xyz  # runs 'git checkout -b feat/xyz'
git cm "feat: ..." # runs 'git commit -m "feat: ..."'
git lg            # runs pretty one-line graph log
```

---

## 6. Helpful Terminal Commands (PowerShell)
```powershell
# View file contents directly in terminal
Get-Content src/main.cpp

# Check whether a file or path exists
Test-Path docs/learning-notes.md

# List all files recursively
Get-ChildItem -Recurse -File
```

