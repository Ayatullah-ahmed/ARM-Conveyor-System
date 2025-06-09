//
// Created by Marcilino on 6/9/2025.
//
#include <errno.h>
#include <sys/types.h>

// Minimal implementation for _sbrk
void* _sbrk(int incr) {
    extern char _end;          // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

    // Simple heap implementation - no checking!
    heap_end += incr;
    return (void*)prev_heap_end;
}
