# Debug Log - External Command Lookup

## Problem

The following commands failed:

```bash
echo hello | cat
cat out.txt
```

Output:

```text
cat: command not found
```

However:

```bash
/bin/cat out.txt
```

worked correctly.

---

## Initial Hypothesis

Possible causes:

* PATH environment variable missing
* PATH parsing failure
* argv[0] corrupted by parser
* exec path resolution bug
* execve failure

---

## Investigation

### 1. Verify PATH

Inside minishell:

```bash
env
echo $PATH
```

Result:

PATH exists and contains `/bin`.

---

### 2. Verify executable exists

```bash
which cat
```

Result:

```text
/bin/cat
```

---

### 3. Verify parser output

Added debug:

```c
fprintf(stderr, "argv[0]=[%s]\n", args[0]);
```

Result:

```text
argv[0]=[cat]
```

Parser was not the problem.

---

### 4. Verify PATH extraction

Added debug to print directories returned by:

```c
extract_path_from_envp()
```

Result:

```text
...
/usr/bin
/bin
...
```

PATH extraction worked correctly.

---

### 5. Verify executable path generation

Added debug inside:

```c
exec_path_finder()
```

Unexpected result:

```text
/bin//bin
```

Expected:

```text
/bin/cat
```

The generated executable path was incorrect.

---

## Possible Root Cause

The original implementation used:

```c
ft_asprintf(&exec_path, "%s/%s", *dirs_iter, cmd);
```
`ft_asprintf` / `ft_printf` may not handle this case correctly.

---

## Fix

Replaced path construction using:

```c
ft_asprintf()
```

with explicit string joins:

```c
tmp = ft_strjoin(*dirs_iter, "/");
exec_path = ft_strjoin(tmp, cmd);
free(tmp);
```

---

## Result

Commands now work:

```bash
echo hello | cat
cat out.txt
```

Output:

```text
hello
```

---

## Concepts Learned

### envp

Environment variables passed to the process.

Example:

```text
PATH=/usr/bin:/bin
```

---

### dirs_path

Array produced from PATH.

Example:

```c
[
 "/usr/bin",
 "/bin",
 NULL
]
```

---

### exec_path

Full executable path.

Example:

```text
/bin/cat
```

---

### execve

Executes an external program.

Example:

```c
execve("/bin/cat", argv, envp);
```

---

## Takeaway

The parser was correct.

The failure occurred during executable path resolution inside the executor.

Suggest possible issue in `ft_asprintf` / `ft_printf` buffer-mode formatting.
