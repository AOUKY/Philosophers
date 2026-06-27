# Philosophers

> “Thinking is good. Thinking forever while holding one fork is not.”

This project is my implementation of **Philosophers** at 42, focused on **threads, mutexes, timing, and deadlock prevention** in C.

---

## Why this project exists

The goal of Philosophers is to understand concurrency by implementing the classic **Dining Philosophers Problem**.

You simulate philosophers that repeatedly:

1. take forks
2. eat
3. sleep
4. think

But multiple threads accessing shared resources (forks) creates real synchronization problems:
- race conditions
- deadlocks
- starvation
- timing precision issues

This project teaches how to write deterministic-enough concurrent code in a nondeterministic world.

---

## 42 mindset / project constraints

- Language: **C**
- Build with **Makefile**
- Use **POSIX threads** (`pthread`)
- One thread per philosopher
- Shared forks protected by **mutexes**
- Accurate timestamped logging
- Stop simulation when:
  - one philosopher dies, or
  - all philosophers have eaten enough (optional argument)

---

## Program arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example
```bash
./philo 5 800 200 200
```

Meaning:
- 5 philosophers
- dies if no meal for 800 ms
- eats for 200 ms
- sleeps for 200 ms
- no meal limit (simulation ends on death)

---

## Project structure (example)

```text
.
├── Makefile
├── include/
│   └── philo.h
├── src/
│   ├── main.c
│   ├── init.c
│   ├── routine.c
│   ├── monitor.c
│   ├── utils.c
│   └── parsing.c
└── README.md
```

> Your actual file names may differ — adjust this tree to match your repo.

---

## Build & run

### Compile
```bash
make
```

### Run
```bash
./philo 5 800 200 200
```

### Clean objects
```bash
make clean
```

### Full clean
```bash
make fclean
```

### Rebuild
```bash
make re
```

---

## Core concepts used

- **Threads**: each philosopher runs independently
- **Mutexes**: protect fork access and shared state
- **Monitor loop/thread**: checks death condition and optional meal completion
- **Custom sleep strategy**: better timing control than raw `usleep` only
- **Synchronized printing**: prevents mixed log lines

---

## Concurrency strategy (high-level)

A common safe approach is:

- each philosopher has a left fork + right fork mutex
- fork pickup order is controlled (or staggered) to avoid circular wait
- only one thread prints at a time (print mutex)
- monitor frequently checks `last_meal_time` against `time_to_die`
- simulation stop flag is shared and protected

This keeps behavior stable and avoids undefined race-heavy output.

---

## Output format (expected)

Typical logs look like:

```text
timestamp_in_ms philosopher_id has taken a fork
timestamp_in_ms philosopher_id is eating
timestamp_in_ms philosopher_id is sleeping
timestamp_in_ms philosopher_id is thinking
timestamp_in_ms philosopher_id died
```

---

## What I learned (human part)

Philosophers changed how I debug code.

In single-thread programs, bugs are often “logical.”
In multithreaded programs, bugs are often “timing + ordering.”

I learned to:
- protect every shared read/write path
- think about lock scope and lock ordering
- reduce false assumptions about execution order
- use small reproducible test cases to catch edge cases

It’s one of the first 42 projects that really feels like systems programming.

---

## Common edge cases to test

- `1` philosopher (can take one fork, then dies)
- very small `time_to_die`
- many philosophers (e.g. 150–200)
- with and without `number_of_times_each_philosopher_must_eat`
- no data races under stress

---

## 42 evaluation quick-check (example)

- [x] No data races on shared state
- [x] No deadlock in normal scenarios
- [x] Correct death detection timing
- [x] Clean, readable logs
- [x] Handles 1 philosopher case
- [x] Proper memory cleanup
- [x] Makefile with required rules

---

## Final note

Philosophers is less about “making threads run” and more about **making them cooperate safely**.

If your program works 9 times out of 10, it’s not done yet 🙂
