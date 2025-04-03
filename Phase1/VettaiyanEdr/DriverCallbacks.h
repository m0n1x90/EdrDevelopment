#ifndef DRIVER_CALLBACKS_H
#define DRIVER_CALLBACKS_H

#include "DriverHeader.h"

VOID EdrLoadImageNotifyRoutine(
    _In_ PUNICODE_STRING FullImageName,
    _In_ HANDLE ProcessId,
    _In_ PIMAGE_INFO ImageInfo
);

VOID EdrCreateProcessNotifyRoutine(
    _In_ HANDLE ParentProcessId,
    _In_ HANDLE ProcessId,
    _In_ BOOLEAN Create
);

VOID EdrCreateThreadNotifyRoutine(
    _In_ HANDLE ProcessId,
    _In_ HANDLE ThreadId,
    _In_ BOOLEAN Create
);

#endif // DRIVER_CALLBACKS_H