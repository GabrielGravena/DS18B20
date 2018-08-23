#include "precompiled.hpp"

#include "ds18b20.hpp"

INITCODE
EXTERN_C
DRIVER_INITIALIZE
    DriverEntry;

PAGED
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
PAGED
NTSTATUS
EvtDriverDeviceAdd(
    WDFDRIVER Driver,
    WDFDEVICE_INIT * DeviceInit)
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(Driver);

    RETURN_IF_NOT_SUCCESS(CreateDS18B20Device(DeviceInit));

    return STATUS_SUCCESS;
}
