#pragma once

#include <stdlib.h>

#include "jsanchez_shared.h"

struct memory_arena
{
    u8 *Base;
    u8 *Marker;
    u64 CurrentSize;
    u64 TotalSize;
};

#define PushArray(Arena, Type, Count) (Type*)PushSize(Arena, (sizeof(Type) * (Count)), alignof(Type))
#define PushStruct(Arena, Type) (Type*)PushSize(Arena, sizeof(Type), alignof(Type))
void    ArenaInit(memory_arena *Arena, u64 TotalSize);
u8     *PushSize(memory_arena *Arena, u64 Size, u64 Alignment = 8);
void    ArenaFree(memory_arena *Arena);

void ArenaInit(memory_arena *Arena, u64 TotalSize)
{
    *Arena = {0};
    Arena->Base = (u8*)malloc(TotalSize); // TODO: Handle malloc failure
    Arena->Marker = Arena->Base;
    Arena->TotalSize = TotalSize;
}

void ArenaFree(memory_arena *Arena)
{
    free(Arena->Base);
    Arena->Base = nullptr;
    Arena->Marker = nullptr;
    Arena->CurrentSize = 0;
    Arena->TotalSize = 0;
}

u8 *PushSize(memory_arena *Arena, u64 Size, u64 Alignment)
{
    Assert(Alignment != 0 && (Alignment & (Alignment - 1)) == 0 && "Alignment must be a power of two");

    // NOTE: Bytes needed to move Marker up to the next Alignment boundary (0 if already aligned)
    u64 Padding = (Alignment - ((uintptr_t)Arena->Marker & (Alignment - 1))) & (Alignment - 1);

    // NOTE: Written as a subtraction so a huge Size can't wrap around and pass the check
    if(Padding > Arena->TotalSize - Arena->CurrentSize ||
       Size > Arena->TotalSize - Arena->CurrentSize - Padding)
    {
        Assert(false && "Arena out of memory");
        return nullptr;
    }

    u8 *Result = Arena->Marker + Padding;
    Arena->CurrentSize += Padding + Size;
    Arena->Marker = Result + Size;
    return Result;
}
