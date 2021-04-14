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