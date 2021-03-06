#include "precompiled.hpp"

#include "ds18b20.hpp"

PAGED
static
EVT_WDF_DEVICE_PREPARE_HARDWARE
    EvtDevicePrepareHardware;

_Use_decl_annotations_
PAGED
NTSTATUS
EvtDevicePrepareHardware(
    WDFDEVICE Device,
    WDFCMRESLIST ResourcesRaw,
    WDFCMRESLIST ResourcesTranslated)
{
    PAGED_CODE();

    auto deviceContext = GetDeviceContext(Device);

    return deviceContext->PrepareHardware(
        ResourcesRaw,
        ResourcesTranslated);
}

_Use_decl_annotations_
PAGED
NTSTATUS
CreateDS18B20Device(WDFDEVICE_INIT * DeviceInit)
{
    PAGED_CODE();

    WDF_PNPPOWER_EVENT_CALLBACKS pnpPowerCallbacks;
    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);
    pnpPowerCallbacks.EvtDevicePrepareHardware = EvtDevicePrepareHardware;

    WdfDeviceInitSetPnpPowerEventCallbacks(
        DeviceInit,
        &pnpPowerCallbacks);

    WDF_OBJECT_ATTRIBUTES deviceAttributes;
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(
        &deviceAttributes,
        DS18B20);

    WDFDEVICE device;
    RETURN_IF_NOT_SUCCESS(
        WdfDeviceCreate(
            &DeviceInit,
            &deviceAttributes,
            &device));

    new (device) DS18B20(device);

    return STATUS_SUCCESS;
}

_Use_decl_annotations_
void *
DS18B20::operator new(
    size_t Size,
    WDFDEVICE Device)
{
    UNREFERENCED_PARAMETER(Size);

    return GetDeviceContext(Device);
}

_Use_decl_annotations_
PAGED
DS18B20::DS18B20(WDFDEVICE Device)
    : m_device(Device)
{
    PAGED_CODE();
}
_Use_decl_annotations_
PAGED
NTSTATUS
DS18B20::PrepareHardware(
    WDFCMRESLIST ResourcesRaw,
    WDFCMRESLIST ResourcesTranslated)
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER((ResourcesRaw, ResourcesTranslated));
    return STATUS_SUCCESS;
}
