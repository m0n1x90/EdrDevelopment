#include "DriverHeader.h"
#include "DriverCallbacks.h"

VOID DriverUnload(
    _In_ PDRIVER_OBJECT DriverObject
)
{
    UNREFERENCED_PARAMETER(DriverObject);

    PsSetCreateProcessNotifyRoutine(EdrCreateProcessNotifyRoutine, TRUE);
    PsRemoveLoadImageNotifyRoutine(EdrLoadImageNotifyRoutine);
    PsRemoveCreateThreadNotifyRoutine(EdrCreateThreadNotifyRoutine);

    DbgPrint("[+] Driver Unloaded\n");
}


NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = DriverUnload;

    NTSTATUS status;

    DbgPrint("[+] Loading Driver\n");

    status = PsSetLoadImageNotifyRoutine(EdrLoadImageNotifyRoutine);
    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] Failed to register PspLoadImageNotifyRoutine : %08X\n", status);
        return status;
    }
    DbgPrint("[+] Loaded Image Notify Routine\n");

    status = PsSetCreateThreadNotifyRoutine(EdrCreateThreadNotifyRoutine);
    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] Failed to register PspCreateThreadNotifyRoutine : %08X\n", status);
        return status;
    }

    DbgPrint("[+] Loaded Thread Notify Routine\n");

    status = PsSetCreateProcessNotifyRoutine(EdrCreateProcessNotifyRoutine, FALSE);
    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] Failed to register PspCreateProcessNotifyRoutine : %08X\n", status);
        return status;
    }

    DbgPrint("[+] Loaded Process Notify Routine\n");

    DbgPrint("[+] Driver Loaded Successfully\n");
    return STATUS_SUCCESS;
}

