# Minishell Project Documentation

This document outlines the requirements and guidelines for the Minishell project. 
It covers the allowed external functions, detailed functional requirements (both mandatory and bonus features), 
and a comprehensive list of edge cases to consider for robust implementation.

---

## I. Submission Requirements

- **Executable Name:**  
  The final shell executable must be named `minishell`.

- **Files to Turn In:**  
  - A Makefile  
  - All header files (`*.h`)  
  - All C source files (`*.c`)

- **Makefile Targets:**  
  Your Makefile must support at least the following targets:
  - **NAME:** Creates the final executable (`minishell`).
  - **all:** Builds the entire project.
  - **clean:** Removes all object files and intermediate build files.
  - **fclean:** Removes the binary file along with the intermediate files.
  - **re:** Performs a full rebuild by executing `fclean` and then `all`.

---

## II. Allowed External Functions and Their Uses

The following functions are permitted in the project. Understanding their purposes and usage is essential for proper implementation:

### A. Input and History Management
- **`readline()`**  
  - **Purpose:** Reads a line of input from the user, providing line-editing features and a customizable prompt.
  - **Usage:** Use it to obtain user commands.
  
- **`rl_clear_history()`**  
  - **Purpose:** Clears the command history list maintained by readline.
  - **Usage:** Call this function on exit or when you need to reset the history.
  
- **`rl_on_new_line()`**  
  - **Purpose:** Prepares readline for a new input line.
  - **Usage:** Use this after processing a command to update readline’s state.
  
- **`rl_replace_line()`**  
  - **Purpose:** Replaces the current contents of the input buffer with a new string.
  - **Usage:** Use this when you need to programmatically modify the current input.
  
- **`rl_redisplay()`**  
  - **Purpose:** Forces readline to update the display.
  - **Usage:** Use this after any modifications that affect what is displayed.
  
- **`add_history()`**  
  - **Purpose:** Adds a command to the history list.
  - **Usage:** Call this after successfully reading and processing a command.

### B. Standard I/O and Memory Management
- **`printf()`**  
  - **Purpose:** Outputs formatted strings to stdout.
  - **Usage:** Use for displaying messages and debugging output.
  
- **`malloc()` and `free()`**  
  - **Purpose:** Allocate and deallocate dynamic memory.
  - **Usage:** Ensure proper memory management to avoid		leaks (excluding acceptable leaks in `readline()`).
  
- **`write()`**  
  - **Purpose:** Writes data to a file descriptor.
  - **Usage:** Use this for low-level output operations.

### C. File Operations and Process Control
- **File Handling Functions:**  
  - **`access()`**: Checks file access permissions.  
  - **`open()`, `read()`, `close()`**: Manage file input and output.
  
- **Process Management Functions:**  
  - **`fork()`**: Creates a new (child) process.  
  - **`wait()`, `waitpid()`, `wait3()`, `wait4()`**: Wait for child process(es) to finish.
  - **Usage:** Launch and manage external commands, handle pipelines, and perform I/O redirection correctly.

### D. Signal Handling
- **Signal Functions:**  
  - **`signal()` and `sigaction()`**: Set up custom signal handlers.
  - **`sigemptyset()` and `sigaddset()`**: Manage signal sets.
  - **`kill()`**: Send a signal to a process.
- **Usage:**  
  - Implement correct behavior for signals such as ctrl-C, ctrl-D, and ctrl+\\.
  - **Global Variable Restriction:** Only one global variable is allowed to track the signal number, and it must not store any additional data.

### E. Directory and File Status
- **Directory Functions:**  
  - **`getcwd()` and `chdir()`**: Get and change the current working directory.
- **File Status Functions:**  
  - **`stat()`, `lstat()`, `fstat()`**: Retrieve file information.
  - **`unlink()`**: Delete a file.
- **Usage:**  
  - These functions support built-ins (like `pwd` and `cd`) and manage file redirection operations.

### F. Command Execution and I/O Redirection
- **`execve()`**  
  - **Purpose:** Executes an external command by replacing the current process image.
- **`dup()` and `dup2()`**  
  - **Purpose:** Duplicate file descriptors to support redirection.
- **`pipe()`**  
  - **Purpose:** Creates a communication channel between processes.
- **Usage:**  
  - Essential for implementing piping between commands and setting up I/O redirections.

### G. Directory Traversal
- **Directory Traversal Functions:**  
  - **`opendir()`, `readdir()`, `closedir()`**  
  - **Usage:** Use these to search for executables in directories or implement file system commands.

### H. Error Handling and Terminal I/O
- **Error Handling Functions:**  
  - **`strerror()`, `perror()`**: Retrieve and display error messages.
- **Terminal I/O Functions:**  
  - **`isatty()`, `ttyname()`, `ttyslot()`, `ioctl()`**: Retrieve and control terminal information.
- **Usage:**  
  - Manage errors effectively and ensure correct shell interaction with the terminal.

### I. Environment and Terminal Settings
- **`getenv()`**  
  - **Purpose:** Retrieves environment variable values.
- **Terminal Attribute Functions:**  
  - **`tcsetattr()`, `tcgetattr()`**: Modify or retrieve terminal settings.
- **Usage:**  
  - Critical for managing shell behavior across different terminal modes and for variable expansion.

### J. Termcap Library Functions
- **Termcap Functions:**  
  - **`tgetent()`, `tgetflag()`, `tgetnum()`, `tgetstr()`, `tgoto()`, `tputs()`**  
  - **Usage:**  
	- Used for low-level terminal control, such as cursor movement or display attribute manipulation.

---

## III. Functional Requirements of the Minishell

### A. User Interface and Input Handling
- **Prompt Display:**  
  - The shell must display a prompt and wait for user input.
- **History Management:**  
  - Maintain a command history (accessible via up/down arrow keys) using readline’s history functions.

### B. Command Parsing and Execution
- **Executable Search:**  
  - Locate the correct executable either by searching the `PATH` or using a provided relative/absolute path.
- **Quoting Rules:**  
  - **Single Quotes (`'`):** Treat contents literally, with no interpretation of metacharacters.
  - **Double Quotes (`"`):** Treat contents literally except for variable expansion (e.g., `$VAR`).

### C. Redirections and Pipelines
- **Redirection Operators:**  
  - **Input (`<`):** Redirect standard input.
  - **Output (`>`):** Redirect standard output in overwrite mode.
  - **Append (`>>`):** Redirect standard output in append mode.
  - **Here-Document (`<<`):** Read input until a delimiter is encountered (without updating history).
- **Pipes (`|`):**  
  - Connect the output of one command as the input to another.

### D. Environment Variable Expansion
- **Basic Expansion:**  
  - Replace `$VARIABLE` with its corresponding value from the environment.
- **Special Variable:**  
  - **`$?`** should expand to the exit status of the last executed foreground command.

### E. Signal Handling
- **Interactive Mode Behavior:**  
  - **ctrl-C:** Interrupts the current command and displays a new prompt on a fresh line.
  - **ctrl-D:** Exits the shell.
  - **ctrl+\\:** Has no effect.
- **Global Variable Requirement:**  
  - Only one global variable is permitted for storing the signal number (no extra data).

### F. Built-In Commands
The shell must implement the following built-in commands with specified restrictions:
- **echo:**  
  - Supports the `-n` option (omit the trailing newline).
- **cd:**  
  - Changes the directory using a relative or absolute path (no additional options).
- **pwd:**  
  - Displays the current working directory (no options).
- **export:**  
  - Sets environment variables (without additional options).
- **unset:**  
  - Removes environment variables (without additional options).
- **env:**  
  - Displays all environment variables (no options or arguments).
- **exit:**  
  - Terminates the shell without extra options.

### G. Memory Management
- **Memory Leaks:**  
  - While memory leaks from `readline()` are acceptable, ensure that all memory allocated by your own code (e.g., for tokenization and building ASTs) is properly freed.

---

## IV. Bonus Features

### A. Wildcard Expansion (Globbing)
- **Wildcard Character (`*`):**  
  - Matches zero or more characters in file or directory names within the current working directory.
  - **Example:**  
	The command `ls *.c` should expand to all files ending with `.c`.
- **Implementation Steps:**
  - After tokenizing input, check arguments containing `*`.
  - Use directory functions (such as `opendir()`, `readdir()`, and `closedir()`) to scan for matching files.
  - Implement a matching function to compare filenames against the wildcard pattern.
  - Consider the behavior when:
	- No matches are found (either leave the pattern unchanged or notify the user).
	- Hidden files (those starting with a dot) should typically be excluded, unless explicitly required.
	- More complex patterns (e.g., `pre*fix*`) are provided.

---

## V. Edge Cases and Robustness Considerations

To ensure the Minishell is robust and error‑free, consider the following edge cases and handling strategies:

### 1. Input Parsing and Tokenization
- **Empty or Whitespace-Only Input:**  
  - **Situation:** User presses Enter on a blank line.  
  - **Action:** Redisplay prompt; do not add to history.  
- **Mixed Whitespace Delimiters:**  
  - **Situation:** Tabs and spaces intermixed.  
  - **Action:** Treat any sequence of whitespace as a single separator.  
- **Unclosed Quotes:**  
  - **Situation:** Single (`'`) or double (`"`) quotes not balanced.  
  - **Action:** Print	syntax error and discard input.  
- **Escaped Newline Continuation:**  
  - **Situation:** Line ends with `\` to join with next line.  
  - **Action:** Read next line, strip backslash, concatenate before parsing.  
- **Line Comments (`#`):**  
  - **Situation:** `#` outside quotes starts a comment.  
  - **Action:** Ignore `#` and rest of line; continue parsing preceding tokens.  
- **Unbalanced Parentheses/Braces:**  
  - **Situation:** `( cmd1 && cmd2` or `${VAR`.  
  - **Action:** Detect at parse time; report syntax error.

### 2. Quoting, Escaping, and Comments
- **Nested Quotes:**  
  - **Situation:** `"a 'b' c"` or `'a "b" c'`.  
  - **Action:** Allow literal inner quotes if opposite type.  
- **Backslash in Quotes:**  
  - **Situation:** `echo "a \"b\""` or `echo 'a \'b\''`.  
  - **Action:** Honor backslash only in double quotes; in single quotes treat literally.  
- **Here‑Document Delimiter Quoting:**  
  - **Situation:** Delimiter in `<< 'EOF'` vs `<< EOF`.  
  - **Action:** If quoted, disable variable expansion within the here‑doc.

### 3. Parameter, Command, and Arithmetic Expansion
- **Undefined Variables:**  
  - **Situation:** `$FOO` not set.  
  - **Action:** Expand to empty string.  
- **Special Variables:**  
  - **Situation:** `$?`, `$$`, `$!` before any processes.  
  - **Action:** `$?` → `0`, `$$` → shell PID, `$!` → empty or last background PID.  
- **Invalid `$` Usage:**  
  - **Situation:** `$1var` or `$-`.  
  - **Action:** Treat as literal text or report syntax error.  
- **Brace Expansion Errors:**  
  - **Situation:** `${VAR:-default}`, `${VAR:=default}`, missing `}`.  
  - **Action:** Perform correct default/assign semantics; on missing `}`, syntax error.  
- **Command Substitution:**  
  - **Situation:** `` `cmd` `` or `$(cmd)`.  
  - **Action:** Execute `cmd`, capture stdout (stripping trailing newline), then re‑tokenize.  
- **Arithmetic Expansion:**  
  - **Situation:** `$(( 2+3 ))` or division by zero.  
  - **Action:** Evaluate integer expression; on error, print	message and return nonzero status.

### 4. Globbing and Pathname Expansion
- **No Matches:**  
  - **Situation:** `*.xyz` matches nothing.  
  - **Action:** Leave pattern unexpanded (or as user preference).  
- **Hidden Files:**  
  - **Situation:** `.*` or `*.c` matching `.foo`.  
  - **Action:** Exclude files starting with `.` unless pattern explicitly begins with `.`.  
- **Complex Patterns:**  
  - **Situation:** `pre*fix*suffix`.  
  - **Action:** Match greedily; sort results lexicographically.  
- **Directory Slash in Pattern:**  
  - **Situation:** `dir/*.c`.  
  - **Action:** Only expand within specified directory, not recursive.

### 5. Redirections and File Descriptor Manipulation
- **Simple Redirections:**  
  - **Situation:** `cmd >out`, `cmd <in`.  
  - **Action:** Open files with correct flags; on error, print	and abort execution.  
- **Append vs Overwrite:**  
  - **Situation:** `>>out` vs `>out`.  
  - **Action:** Use `O_APPEND` or `O_TRUNC` accordingly.  
- **Multiple Redirections:**  
  - **Situation:** `cmd >o1 >o2`, `cmd 2>&1`.  
  - **Action:** Apply left‑to‑right; duplicate or close FDs as specified.  
- **Here‑Document EOF Before Delimiter:**  
  - **Situation:** EOF (Ctrl‑D) before matching delimiter.  
  - **Action:** Abort the here‑doc; do not add to history.  
- **Ambiguous Redirect Without Space:**  
  - **Situation:** `cmd>file`.  
  - **Action:** Recognize `>` token and filename even without spacing.

### 6. Pipelines and Process Execution
- **Non‑existent Commands in Pipeline:**  
  - **Situation:** `false | cmd`.  
  - **Action:** `access()` check each; report for the failing stage but still run others.  
- **SIGPIPE Handling:**  
  - **Situation:** Downstream process exits early.  
  - **Action:** Parent or writer sees `SIGPIPE`; ignore or catch and propagate error.  
- **Maximum Pipe Depth:**  
  - **Situation:** Excessive chained pipes (`a|b|c|…`).  
  - **Action:** Dynamically allocate FD arrays; detect `EMFILE` and report “too many open files.”  
- **Zombie Processes:**  
  - **Situation:** Child exits but not waited on.  
  - **Action:** Use `waitpid(-1, …, WNOHANG)` in SIGCHLD handler to reap.

### 7. Built-In Commands and Environment Management
- **`cd -`:**  
  - **Situation:** Return to previous directory.  
  - **Action:** Save and swap `$OLDPWD`/`$PWD`.  
- **`export` Without Arguments:**  
  - **Situation:** `export` alone.  
  - **Action:** List all exported vars.  
- **`unset` Non‑existent Var:**  
  - **Situation:** `unset FOO` when FOO unset.  
  - **Action:** No error; no-op.  
- **`env` with Arguments:**  
  - **Situation:** `env VAR=val cmd`.  
  - **Action:** Temporarily set VAR for `cmd` only.  
- **Invalid Built‑in Syntax:**  
  - **Situation:** `exit foo`.  
  - **Action:** If `foo` non-numeric, print	error; exit with status `255`.

### 8. Signal and Job Control
- **Interactive Signals:**  
  - **Situation:** Ctrl‑C, Ctrl‑D, Ctrl+\\, Ctrl‑Z.  
  - **Action:**  
	- Ctrl‑C: interrupt foreground, redisplay prompt  
	- Ctrl‑D: exit if no input; EOF otherwise  
	- Ctrl+\\: ignore  
	- Ctrl‑Z: suspend foreground (optional job control)  
- **SIGWINCH (Window Resize):**  
  - **Situation:** Terminal dimensions change.  
  - **Action:** Recompute line lengths via `ioctl()`.  
- **Background Execution (`&`):**  
  - **Situation:** `sleep 10 &`.  
  - **Action:** Fork without wait; print	background PID; track status for `$!`.

### 9. Memory, Resource, and Error Handling
- **Allocation Failures:**  
  - **Situation:** `malloc()` returns `NULL`.  
  - **Action:** Clean up, print	“memory error,” return to prompt.  
- **File Descriptor Leaks:**  
  - **Situation:** `open()` or `pipe()` without `close()`.  
  - **Action:** Audit every code path; ensure matching `close()`/`closedir()`.  
- **Race in `access()` vs `open()`:**  
  - **Situation:** File removed between checks.  
  - **Action:** Prefer `open()` with proper flags; handle errors there.  
- **Signal‑Safe Functions:**  
  - **Situation:** Calling non‑async‑safe API in handler.  
  - **Action:** Restrict to `write()` and `sig_atomic_t`.  

### 10. I/O, Terminal, and Encoding
- **Non‑TTY I/O:**  
  - **Situation:** Input/output redirected from files or pipes.  
  - **Action:** Disable line editing; read raw lines until EOF.  
- **Invalid UTF‑8 Sequences:**  
  - **Situation:** Multi‑byte sequence broken.  
  - **Action:** Treat bytes literally; avoid		crashes.  
- **Carriage Return Handling:**  
  - **Situation:** CRLF input from Windows files.  
  - **Action:** Strip `\r` before processing.  

### 11. Non‑Interactive & Scripting Mode
- **Script File Execution:**  
  - **Situation:** `./minishell script.sh`.  
  - **Action:** Read and execute without prompt, exit at EOF.  
- **`exit` in Script:**  
  - **Situation:** `exit` inside a script.  
  - **Action:** Terminate shell immediately with given status.  

### 12. Miscellaneous
- **Excessively Long Argument Lists:**  
  - **Situation:** `execve()` fails with `E2BIG`.  
  - **Action:** Report “argument list too long.”  
- **Illegal Byte in Filename:**  
  - **Situation:** NUL or path separator in file name.  
  - **Action:** Reject or treat as not found.  
- **Environment Size Limits:**  
  - **Situation:** Too many or too-large variables.  
  - **Action:** Detect and report if `execve()` fails with `E2BIG`.  
- **Locale Changes at Runtime:**  
  - **Situation:** User sets `LANG` or `LC_*` during session.  
  - **Action:** Respect new locale for word splitting and display width.  
- **Circular Here‑Doc References:**  
  - **Situation:** Here‑doc delimiter equals a variable name.  
  - **Action:** No special handling; treat delimiter literally.  
- **Editor Key Sequences:**  
  - **Situation:** User inputs arrow or function keys.  
  - **Action:** Let `readline()` handle; avoid		interpreting raw codes.



---

## VI. Valgrind Test script

valgrind --trace-children=yes -s --suppressions=ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

## VII. Final Remarks

This documentation covers all aspects necessary for building a functional, robust Minishell. 
By adhering to the guidelines for allowed functions, functional requirements (both mandatory and bonus), 
and comprehensive edge case handling, you can develop a shell that behaves similarly to bash in interactive mode.

Happy coding!

--- 
