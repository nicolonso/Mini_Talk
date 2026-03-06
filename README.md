# Mini_Talk
*This project has been created as part of the 42 curriculum by nalfonso.*

# minitalk

## Description

**minitalk** is a communication program written in C that allows a **client** and a **server** to exchange messages using **UNIX signals**.

The client sends a string to the server **bit by bit** using signals.
The server reconstructs the message and prints it.

This project focuses on:

* UNIX signals
* Interprocess communication
* Bitwise operations
* Signal handling using `sigaction`
* Process management in Linux

---

## Instructions

### Compilation

Compile the project using:

```bash
make
```

This will generate two programs:

```
server
client
```

---

### Start the server

```bash
./server
```

Example output:

```
Server PID: 12345
```

---

### Run the client

```bash
./client <server_pid> "message"
```

Example:

```bash
./client 12345 "Hello World"
```

The server will display the received message.

---

## Communication Protocol

Communication happens using only two signals:

| Signal  | Meaning |
| ------- | ------- |
| SIGUSR1 | Bit 1   |
| SIGUSR2 | Bit 0   |

Each character is sent **bit by bit** (8 bits per character).

Example flow:

```
Client → send bits
Server → reconstruct character
Server → print message
```

---

## Project Structure

```
minitalk/
│
├── Makefile
├── README.md
├── server.c
├── client.c
├── hdr/
└── libft/
```

---

## Resources

UNIX Signals documentation
https://man7.org/linux/man-pages/man7/signal.7.html

sigaction manual
https://man7.org/linux/man-pages/man2/sigaction.2.html

Bitwise operations in C
https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/

---

## AI Usage

AI tools were used during the development of this project for:

* Understanding UNIX signal behaviour
* Reviewing signal handling strategies
* Debugging synchronization issues
* Improving testing strategies

All explanations were reviewed and the final code was written and understood by the author.
