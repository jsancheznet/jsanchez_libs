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

#define PushArray(Arena, Type, Count) (Type*)PushSize(Arena, (sizeof(Type) * Count))
#define PushStruct(Arena, Type) (Type*)PushSize(Arena, sizeof(Type))
void    ArenaInit(memory_arena *Arena, u64 TotalSize);
u8     *PushSize(memory_arena *Arena, u64 Size);
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

u8 *PushSize(memory_arena *Arena, u64 Size)
{
    if(Arena->CurrentSize + Size >= Arena->TotalSize)
    {
        Assert(false && "Arena->CurrentSize + Size >= Arena->TotalSize");
    }

    u8 *Result = Arena->Marker;
    Arena->CurrentSize += Size;
    Arena->Marker += Size; // TODO: Align allocations to a 4 byte boundary, https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/
    return Result;
}
