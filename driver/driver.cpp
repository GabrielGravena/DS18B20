#include "precompiled.hpp"

EXTERN_C
DRIVER_INITIALIZE
    DriverEntry;

static
EVT_WDF_DRIVER_DEVICE_ADD
    EvtDriverDeviceAdd;

_Use_decl_annotations_
NTSTATUS
DriverEntry(
    DRIVER_OBJECT * DriverObject,
    UNICODE_STRING * RegistryPath)
{
    WDF_DRIVER_CONFIG driverConfig;
    WDF_DRIVER_CONFIG_INIT(
        &driverConfig,
        EvtDriverDeviceAdd);

    RETURN_IF_NOT_SUCCESS(
        WdfDriverCreate(
            DriverObject,
            RegistryPath,
            WDF_NO_OBJECT_ATTRIBUTES,
            &driverConfig,
            nullptr));

    return STATUS_SUCCESS;
}

_Use_decl_annotations_
NTSTATUS
EvtDriverDeviceAdd(
    WDFDRIVER Driver,
    WDFDEVICE_INIT * DeviceInit)
{
    UNREFERENCED_PARAMETER((Driver, DeviceInit));

    return STATUS_NOT_IMPLEMENTED;
}
