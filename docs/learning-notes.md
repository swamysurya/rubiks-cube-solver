


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


### git commands
```powershell
git status
```
```powershell
Get-Content src/main.cpp
```
```powershell
Test-Path docs/learning-notes.md
```
```powershell
git diff --cached
```
```powershell
git diff
```
```powershell
git ls-files
```

### Terminal commands

```powershell
Get-ChildItem -Recurse -File
```

### git commit msg formats

<type>: <short description>

Common types:
Type	When to use	Example
feat	New functionality	feat: add cube rotation logic
fix	Bug fix	fix: correct cube move validation
docs	Documentation changes	docs: add project requirements
build	Build system changes	build: configure CMake
test	Adding or updating tests	test: add cube initialization tests
refactor	Restructure code without changing behavior	refactor: simplify cube state representation
chore	Maintenance tasks	chore: add executable to gitignore