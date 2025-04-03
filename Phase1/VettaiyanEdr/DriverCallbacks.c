#include "DriverCallbacks.h"

VOID EdrLoadImageNotifyRoutine(
    _In_ PUNICODE_STRING FullImageName,
    _In_ HANDLE ProcessId,
    _In_ PIMAGE_INFO ImageInfo
) {
    UNREFERENCED_PARAMETER(ImageInfo);
    PEPROCESS Process = NULL;
    PUNICODE_STRING ProcessName = NULL;

    PsLookupProcessByProcessId(ProcessId, &Process);
    SeLocateProcessImageName(Process, &ProcessName);

    DbgPrint(
        "[+] Image Loaded: ProcessName = %wZ, ProcessID = %d, ImageName = %wZ\n",
        ProcessName,
        (ULONG)(ULONG_PTR)ProcessId,
        FullImageName
    );
}

VOID EdrCreateProcessNotifyRoutine(
    _In_ HANDLE ParentProcessId,
    _In_ HANDLE ProcessId,
    _In_ BOOLEAN Create
) {
    if (Create) {
        PEPROCESS process = NULL;
        PUNICODE_STRING parentProcessName = NULL, processName = NULL;

        PsLookupProcessByProcessId(ParentProcessId, &process);
        SeLocateProcessImageName(process, &parentProcessName);

        PsLookupProcessByProcessId(ProcessId, &process);
        SeLocateProcessImageName(process, &processName);

        DbgPrint(
            "[+] Process spawned : PPID = %d, Parent Process Name = %wZ\n\t\tChild Process : PIDD = %d, Process Name = %wZ",
            ParentProcessId,
            parentProcessName,
            ProcessId,
            processName
        );
    }
    else {
        DbgPrint(
            "[+] Process Deleted: PPID = %d, PID = %d\n",
            ParentProcessId,
            ProcessId
        );
    }
}

VOID EdrCreateThreadNotifyRoutine(
    _In_ HANDLE ProcessId,
    _In_ HANDLE ThreadId,
    _In_ BOOLEAN Create
) {
    if (Create) {
        DbgPrint(
            "[+] Thread Created: ID = %d, ProcessID = %d\n",
            ThreadId,
            ProcessId
        );
    }
    else {
        DbgPrint(
            "[+] Thread Terminated: ID = %d, ProcessID = %d\n",
            ThreadId,
            ProcessId
        );
    }
}