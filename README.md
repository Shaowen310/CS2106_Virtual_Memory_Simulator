# OS Basics

Implementation of simulators to understand the basic concepts in operating system.

## Projects

* Virtual memory management
* Process management
* Process scheduling

## Spin Lock

Spin lock can be implemented by compare-and-swap (cas) atomic instruction.

Illustration:

```c
#include "spin_lock.h"
#include "cas.h"

void spin_lock(int *lock) {
    while (1) {
        if (cas(lock, 0, 1)) {
            return;
        }
    }
}

void spin_unlock(int *lock) {
    cas(lock, 1, 0);
}
```
