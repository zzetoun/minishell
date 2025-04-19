Below is a breakdown of the key “cases” and edge‑conditions you’ll need to handle when you implement these built‑in commands in C.  In each case the shell has already parsed quotes and split on whitespace (and handled unescaped semicolons as command separators), so your code will simply see an array of C‑strings.

---

## 1. `cd`

1. **No arguments**  
   - Lookup `HOME` in your shell’s environment table.  
   - If unset or empty → error: `cd: HOME not set` and return non‑zero.  
   - Otherwise, `chdir(HOME)`.

2. **Exactly one argument**  
   1. **`"-"`**  
      - Lookup `OLDPWD`.  
      - If unset → error: `cd: OLDPWD not set`.  
      - Else `chdir(OLDPWD)`, then print the new directory to stdout followed by “\n”.  
   2. **Begins with `~`** (tilde expansion)  
      - If exactly `"~"` → treat as `HOME`.  
      - Else if `"~/…"` → replace leading `~` with `HOME`.  
      - Else if `"~user"` or `"~user/…"` → look up that user’s home via `getpwnam()`.  
      - If user not found → error: `cd: no such user: user`.  
   3. **Relative vs absolute path**  
      - If it does **not** start with `/`, and you have a `CDPATH` variable → split `CDPATH` on `:` and for each entry try `chdir(CDPATH[i] + "/" + arg)`.  
        - On first success, if the chosen path didn’t match `.` or begin with `/`, print the actual path you changed to.  
        - If none succeed, fall back to plain `chdir(arg)`.  
      - If it **does** start with `/` or begins with `.` → `chdir(arg)` directly.
   4. **Error conditions from `chdir()`**  
      - Not found: `ENOTDIR` or `ENOENT` → “`cd: %s: No such file or directory`”  
      - Not a directory: `ENOTDIR` → “`cd: %s: Not a directory`”  
      - Permission denied: `EACCES` → “`cd: %s: Permission denied`”  
      - Others: print strerror(errno).
   5. **On success**  
      - Update your shell’s `OLDPWD = previous PWD`  
      - Update `PWD = getcwd()` (or, if you want “logical” behavior, manipulate the old PWD string with `..` and symlinks).  

3. **Too many arguments**  
   - If `argc > 2` → error: `cd: too many arguments`, return non‑zero.

---

## 2. `echo`

- **Supported option**: only `-n`.  
  - If the very first argument is exactly `-n`, suppress the trailing `\n`.  
  - Everything else (including `-nn` or `--n`) is treated as data.  
- **Zero arguments** → just print `\n`.  
- **Multiple arguments** → print them separated by single spaces, then `\n` (if not suppressed).  
- **Quoting / semicolons**: already stripped by parser.

---

## 3. `pwd`

- **No arguments** → call `getcwd()` and print the result plus `\n`. 
- **senstive case no arguments** → able to check all cases (`PWD`, `pWd`, `PwD`, `pwd  `... etc) and with space after.
- **Any arguments** → error: `pwd: too many arguments`, return non‑zero.  
- **`getcwd()` failure** → print `pwd: error retrieving current directory: %s\n` with `strerror(errno)`.

---

## 4. `export`

- **Takes one or more arguments** of the form `NAME` or `NAME=VALUE`.  
- For each argument:  
  1. Validate identifier: must begin with letter or `_`, then letters, digits, or `_`.  
     - On invalid → error: `export: '%s': not a valid identifier`.  
  2. If contains `=` → split and set `NAME` to `VALUE` in your env table, and mark it exported.  
  3. If no `=` → look up `NAME` in the shell’s private vars; if found, mark exported; if not found, create it with empty value and mark exported.  
- **No arguments** → typically shells list all exported variables; you can choose to do the same or treat as NOP.

---

## 5. `unset`

- **Takes one or more arguments** (variable names).  
- For each argument:  
  1. Validate identifier (same rules as `export`).  
     - On invalid → error: `unset: '%s': not a valid identifier`.  
  2. Remove from environment table (and from exported set).  
- **No arguments** → error: `unset: not enough arguments`.

---

## 6. `env`

- **No arguments** → iterate over environment table and print `NAME=VALUE\n` for each.  
- **Any arguments** → error: `env: too many arguments` (since no options or command execution is supported).

---

## 7. `exit`

- **No arguments** → terminate the shell process with exit code equal to the last command’s status.  
- **Any arguments** → error: `exit: too many arguments` (per your spec) and do **not** exit.

---

### Quoting and Semicolons

- Your built‑in handlers never see raw quotes or unescaped semicolons.  The shell parser has already:
  1. Removed matching `"…"` and `‘…’` or backslashes, producing literal C‑strings.
  2. Split commands on unescaped `;` into separate invocations.
- If the user backslashes or quotes a semicolon (`"\;"`), the parser will feed you a string containing `;`—you treat it like any other character in a filename or variable name.

---

### Effects on the Shell

- **`cd`** changes the **process’s** current directory (via `chdir()`), and then you must update the `PWD`/`OLDPWD` environment entries so that subsequent commands and prompts reflect the new directory.  
- **`export`/`unset`** modify your in‑memory environment table; exported vars will be inherited by any child processes you later `fork()/exec()`.  
- **`env`** and **`pwd`** simply read state and print it.  
- **`exit`** causes the shell’s main loop to break and the process to terminate.