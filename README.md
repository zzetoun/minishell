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
  - **Usage:** Ensure proper memory management to avoid leaks (excluding acceptable leaks in `readline()`).
  
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

### A. Logical Operators with Parentheses (&& and ||)
- **Logical AND (`&&`):**  
  - Execute the command following `&&` only if the preceding command succeeds (returns 0).
- **Logical OR (`||`):**  
  - Execute the command following `||` only if the preceding command fails (nonzero exit status).
- **Parentheses for Grouping:**  
  - Use parentheses to override the default operator precedence, ensuring commands are evaluated as a single unit.
  - **Example without grouping:**
    ```bash
    cmd1 && cmd2 || cmd3
    ```
  - **Example with grouping:**
    ```bash
    (cmd1 && cmd2) || cmd3
    ```
- **Implementation Notes:**
  - Extend your parser to recognize `&&`, `||`, and grouping symbols `(` and `)`.
  - Construct an Abstract Syntax Tree (AST) or equivalent structure to enforce correct precedence.
  - Employ short-circuit evaluation to avoid unnecessary command executions.

### B. Wildcard Expansion (Globbing)
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

To ensure the Minishell is robust and error-free, consider the following edge cases and handling strategies:

### 1. Input Parsing and Tokenization
- **Empty or Whitespace-Only Input:**  
  - **Situation:** The user presses Enter without typing any command.
  - **Action:** Simply display a new prompt and do not add an empty command to history.
- **Unbalanced or Unclosed Quotes:**  
  - **Situation:** Input contains unclosed single (`'`) or double (`"`) quotes.
  - **Action:** Report a syntax error and prompt for a new command.
- **Unbalanced or Misplaced Parentheses:**  
  - **Situation:** Commands with missing or extra parentheses (e.g., `(cmd1 && cmd2` or `cmd1 && cmd2)`).
  - **Action:** Detect and report the error during parsing.
- **Misplaced Logical Operators:**  
  - **Situation:** Input begins or ends with `&&` or `||` (e.g., `&& cmd1`, `cmd1 ||`).
  - **Action:** Validate token order and provide a syntax error message.

### 2. Command Execution
- **Non-existent/Non-executable Commands:**  
  - **Situation:** The command does not exist or the file lacks execution permissions.
  - **Action:** Use `access()` for validation and report an appropriate error message.
- **Invalid Paths:**  
  - **Situation:** Commands provided with absolute or relative paths that are invalid.
  - **Action:** Validate paths and handle errors gracefully.

### 3. Redirections and Pipelines
- **Redirection Errors:**  
  - **Situation:** Input or output redirection fails (e.g., due to missing files or permission issues).
  - **Action:** Check file accessibility (using `open()`/`access()`) and prevent execution if redirection setup fails.
- **Here-Document (<<) Issues:**  
  - **Situation:** The delimiter is never encountered, or input is terminated by ctrl-D.
  - **Action:** Decide whether to abort the redirection or process the accumulated input, and do not update history if aborted.
- **Pipeline Problems:**  
  - **Situation:** A command within a pipeline fails.
  - **Action:** Propagate the correct exit status and determine if subsequent commands should be executed.

### 4. Environment Variable Expansion
- **Undefined Variables:**  
  - **Situation:** A referenced variable is not defined.
  - **Action:** Replace it with an empty string.
- **Invalid Syntax After `$`:**  
  - **Situation:** The `$` symbol is not immediately followed by a valid identifier.
  - **Action:** Treat the symbol as literal text or report a syntax error.
- **Special Variable `$?`:**  
  - **Situation:** No prior command has executed.
  - **Action:** Return a default or consistent exit status.

### 5. Wildcard Expansion
- **No Matching Files:**  
  - **Situation:** The wildcard pattern (e.g., `*.c`) does not match any files.
  - **Action:** Either leave the pattern unchanged or notify the user.
- **Hidden Files Matching:**  
  - **Situation:** Wildcard unintentionally matches hidden files.
  - **Action:** Exclude files starting with a dot unless explicitly required.
- **Multiple or Complex Patterns:**  
  - **Situation:** Patterns such as `pre*fix*` are encountered.
  - **Action:** Ensure robust matching even with overlapping or empty pattern segments.

### 6. Logical Operators and Grouping
- **Malformed Groupings:**  
  - **Situation:** Unbalanced parentheses or dangling operators (e.g., `cmd1 &&`).
  - **Action:** Validate during parsing and display syntax error messages.
- **Short-Circuit Evaluation:**  
  - **Situation:** A command’s result renders subsequent operators unnecessary.
  - **Action:** Implement short-circuiting to prevent redundant execution.

### 7. Built-In Commands and Special Cases
- **Invalid or Missing Arguments:**  
  - **Situation:** Built-ins like `cd`, `export`, or `unset` receive improper or missing arguments.
  - **Action:** Validate and provide clear, user-friendly error messages.
- **Extra Arguments for `exit`:**  
  - **Situation:** The `exit` command is given additional unsupported arguments.
  - **Action:** Follow the specifications—ignore extra arguments or warn the user.

### 8. Signal Handling
- **Rapid or Concurrent Signals:**  
  - **Situation:** Multiple signals (e.g., repeated ctrl-C) are received quickly.
  - **Action:** Use the single global variable to track the signal and handle it without disrupting the prompt.
- **Terminal Control Signals:**  
  - **Situation:** Differentiating between ctrl-C (interrupt), ctrl-D (exit), and ctrl+\\ (ignored).
  - **Action:** Implement each behavior exactly as specified.

### 9. Memory and Resource Management
- **Memory Allocation Failures:**  
  - **Situation:** `malloc()` returns `NULL`.
  - **Action:** Always check allocations and free any allocated memory before handling the error.
- **File Descriptor or Resource Leaks:**  
  - **Situation:** Files or directories are left open.
  - **Action:** Ensure every open operation (e.g., `open()`, `opendir()`) is paired with an appropriate close (`close()`, `closedir()`).
- **Custom Code Memory Leaks:**  
  - **Situation:** Memory leaks in the tokenization, parsing, or AST management.
  - **Action:** Regularly test with tools (e.g., Valgrind) and free all allocated resources.

### 10. Miscellaneous
- **Handling Extremely Long Commands:**  
  - **Situation:** The input exceeds typical buffer sizes.
  - **Action:** Use dynamic allocation and proper buffer management.
- **Preventing Buffer Overflows:**  
  - **Situation:** Large inputs or string operations might overrun buffers.
  - **Action:** Use safe string functions and perform bounds checking.
- **Concurrency and Race Conditions:**  
  - **Situation:** Multiple processes concurrently modifying shared resources.
  - **Action:** Apply proper synchronization, especially during signal handling.

---

## VI. Valgrind Test script

valgrind --trace-children=yes -s --suppressions=ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

## VII. Final Remarks

This documentation covers all aspects necessary for building a functional, robust Minishell. 
By adhering to the guidelines for allowed functions, functional requirements (both mandatory and bonus), 
and comprehensive edge case handling, you can develop a shell that behaves similarly to bash in interactive mode.

Happy coding!

--- 