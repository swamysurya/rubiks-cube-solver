
# Learning Notes — Rubik's Cube Solver

These notes record the concepts learned while building
the Rubik's Cube Solver in C++.

## Day 2 — C++ Compilation and Compiler Warnings

### 1. Source Code and Executable

- Source code is the human-readable C++ code stored in `.cpp` files.
- The compiler translates source code into an executable.
- On Windows, our executable can use the `.exe` extension.

### 2. Compilation Command

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic src/main.cpp -o rubiks_solver.exe
```

- `g++`: invokes the C++ compiler.
- `-std=c++20`: selects the C++20 language standard.
- `-Wall`: enables a broad set of useful warnings.
- `-Wextra`: enables additional warnings.
- `-Wpedantic`: warns about certain non-standard extensions.
- `src/main.cpp`: specifies the source file.
- `-o rubiks_solver.exe`: names the output executable.

### 3. Why Compiler Warnings Matter

Warnings can identify suspicious or potentially incorrect code.
They do not guarantee that a program is bug-free.

We should understand each warning and fix genuine issues
rather than suppress warnings without investigation.

### 4. Commands Learned

```powershell
g++ --version
git --version
g++ -std=c++20 -Wall -Wextra -Wpedantic src/main.cpp -o rubiks_solver.exe
.\rubiks_solver.exe
```

### 5. Questions to Revisit

- What happens during compilation?
- How is a source file different from an executable?
- Why do we enable compiler warnings?
- Does successful compilation guarantee correct program behavior?

### 6. Practical Exercise

Create a small C++ program with an unused variable.
Compile it with and without warning flags and compare the output.
Record what you observe.



## Day 2 — Git Inspection and PowerShell Commands

### 1. Check Git Repository Status

```powershell
git status
```

Shows the current branch, untracked files, staged changes,
and modifications that have not been committed.

### 2. Display a File's Contents

```powershell
Get-Content src/main.cpp
```

Displays the contents of the specified file in PowerShell.
Useful for inspecting source code directly from the terminal.

### 3. Check Whether a File Exists

```powershell
Test-Path docs/learning-notes.md
```

Returns `True` if the specified path exists, or `False`
if it does not.

### 4. Navigate to the Project Directory

```powershell
cd "C:\Users\swamy\Desktop\ReactProjects-dont delete\rubiks-cube-solver"
```

Changes the current working directory to the project folder.
Quotes are necessary here because the path contains spaces.

### 5. Inspect Changes Before Committing

```powershell
git diff
```

Displays changes to tracked files that have not been staged.

```powershell
git diff --cached
```

Displays changes that have already been staged for the next commit.

Note: A newly created, untracked file will not appear in
`git diff` until it is staged.

### 6. Development Practice

Before committing code, inspect the repository status,
review the relevant changes, and ensure that only the intended
files are included in the commit.
