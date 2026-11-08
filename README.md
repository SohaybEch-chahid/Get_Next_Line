*This project has been created as part of the 42 curriculum by sech-cha.*

# get_next_line

## Description

**get_next_line** is a project from the 42 curriculum that introduces file handling, static variables, memory management, and the use of system calls in C.

The goal of this project is to write a function that reads and returns a file one line at a time.

The function must return one line per call, including the newline character (`\n`) when it exists. When the end of the file is reached, it returns the remaining content if there is any, even if it does not end with a newline. Once all content has been read, the function returns `NULL`.

The project also introduces the concept of persistent data between function calls. Since `read()` may retrieve more data than is needed for the current line, the program must temporarily store the remaining content for the next call.

### Main objectives

- Understand and use the `read()` system call.
- Work with file descriptors.
- Understand static variables and persistent storage.
- Manage dynamically allocated memory using `malloc()` and `free()`.
- Manipulate strings and buffers.
- Handle multiple file descriptors independently.
- Avoid memory leaks and invalid memory accesses.

## Instructions

### Compilation

The project is written in C and requires a C compiler such as `cc` or `gcc`.

Compile the project with a chosen buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c -o gnl
```

You can change `BUFFER_SIZE` to test different reading sizes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c -o gnl
```

### Execution

Run the compiled program:

```bash
./gnl
```

The function can also be tested with a file by opening it with `open()` and passing its file descriptor to `get_next_line()`.

### Function prototype

```c
char *get_next_line(int fd);
```

### Return values

| Situation | Return value |
|---|---|
| A line is successfully read | The allocated line |
| The last line has no newline | The remaining content |
| End of file with no remaining content | `NULL` |
| Invalid file descriptor | `NULL` |
| Reading or allocation error | `NULL` |

## Algorithm

### 1. General approach

The main idea is to maintain a temporary storage area called `stash`.

The stash stores all characters read from the file that have not yet been returned to the caller.

The algorithm follows these steps:

1. Find or create the storage associated with the file descriptor.
2. Read data from the file until a newline is found or the end of the file is reached.
3. Append the newly read data to the existing stash.
4. Extract the first line from the stash.
5. Update the stash by removing the line that was just returned.
6. Return the extracted line.

This process is repeated every time `get_next_line()` is called.

### 2. Reading and storing data

The `read_and_store()` function reads data using the `read()` system call.

It continues reading while the stash does not contain a newline character.

Each time data is read, it is appended to the existing stash using `ft_strjoin()`.

For example, suppose the file contains:

```text
Hello
World
42
```

And `BUFFER_SIZE` is 8.

The first read might return:

```text
Hello
Wo
```

The stash now contains:

```text
Hello\nWo
```

Since a newline has been found, reading stops.

### 3. Extracting a line

The `extract_line()` function searches for the first newline character in the stash.

It allocates enough memory for the first line and copies the characters into a new string.

For example:

```text
Stash:  Hello\nWorld\n42
```

The returned line is:

```text
Hello\n
```

The original stash is not modified by this operation.

This separation is important because the returned line and the remaining stash have different responsibilities.

### 4. Updating the stash

After extracting a line, the `update_stash()` function removes the returned line from the stash.

It creates a new string containing only the remaining characters.

For example:

```text
Before:
Hello\nWorld\n42

Returned line:
Hello\n

After:
World\n42
```

The old stash is freed after the remaining content has been copied.

If there is no remaining content, the stash is freed and `NULL` is returned.

### 5. Handling multiple file descriptors

A common approach to this project is to use a static array indexed by the file descriptor.

However, this implementation uses a **linked list** to manage the storage of multiple file descriptors.

Each node contains:

- `fd`: the file descriptor associated with the node.
- `stash`: the remaining unread content for that file descriptor.
- `next`: a pointer to the next node.

The structure is defined as:

```c
typedef struct s_fd
{
    int             fd;
    char            *stash;
    struct s_fd     *next;
} t_fd;
```

The linked list allows each file descriptor to maintain its own independent stash.

For example, if two files are opened simultaneously:

```text
HEAD
 |
 v
+------+----------------+------+
| fd 3 | stash: "Hello" | next | ----+
+------+----------------+------+     |
                                      v
                              +------+----------------+------+
                              | fd 4 | stash: "World" | NULL |
                              +------+----------------+------+
```

When `get_next_line()` is called with a file descriptor, `find_fd()` searches for the corresponding node.

### 6. Why use a linked list?

A linked list was chosen instead of a fixed-size array because:

- It does not require a predefined maximum number of file descriptors.
- Memory is allocated only when a new file descriptor is used.
- Each file descriptor has its own independent storage.
- Nodes can be removed individually when they are no longer needed.

The trade-off is that searching for a file descriptor requires traversing the list, which takes O(n) time in the number of stored file descriptors.

## Project Structure

```text
get_next_line/
|
|-- get_next_line.c
|-- get_next_line_utils.c
|-- get_next_line.h
|
|-- get_next_line_bonus.c
|-- get_next_line_utils_bonus.c
|-- get_next_line_bonus.h
|-- README.md
```

## Resources

### Documentation

- [read() — Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)
- [open() — Linux manual page](https://man7.org/linux/man-pages/man2/open.2.html)
- [close() — Linux manual page](https://man7.org/linux/man-pages/man2/close.2.html)
- [malloc() — Linux manual page](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [free() — Linux manual page](https://man7.org/linux/man-pages/man3/free.3.html)
- [Static variables in C](https://en.cppreference.com/w/c/language/static_storage_duration.html)
- [Linked lists — GeeksforGeeks](https://www.geeksforgeeks.org/data-structures/linked-list/)

### AI Usage

AI tools were used as learning during the development of this project.

They were used for:

- Understanding the behavior of the `read()` system call and file descriptors.
- Learning how static variables preserve data between function calls.
- Understanding dynamic memory allocation and memory ownership.
- Exploring different approaches to handling multiple file descriptors.
- Reviewing algorithm logic and identifying potential edge cases.
