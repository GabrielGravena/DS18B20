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

    bool resourceFound = false;
    for (ULONG i = 0; i < WdfCmResourceListGetCount(ResourcesTranslated); i++)
    {
        auto descriptor = WdfCmResourceListGetDescriptor(
            ResourcesTranslated,
            i);

        if (descriptor->Type == CmResourceTypeConnection)
        {
            if (descriptor->u.Connection.Class == CM_RESOURCE_CONNECTION_CLASS_GPIO &&
                descriptor->u.Connection.Type == CM_RESOURCE_CONNECTION_TYPE_GPIO_IO)
            {
                m_gpioConnectionId.HighPart = descriptor->u.Connection.IdHighPart;
                m_gpioConnectionId.LowPart = descriptor->u.Connection.IdLowPart;

                resourceFound = true;
                break;
            }
        }
    }

    if (!resourceFound)
    {
        return STATUS_RESOURCE_TYPE_NOT_FOUND;
    }

    return STATUS_SUCCESS;
}

_Use_decl_annotations_
PAGED
NTSTATUS
DS18B20::SelfManagedIoInit(void)
{
    RETURN_IF_NOT_SUCCESS(
        WdfIoTargetCreate(
            m_device,
            WDF_NO_OBJECT_ATTRIBUTES,
            &m_ioTarget));

    DECLARE_UNICODE_STRING_SIZE(fileName, 256);

    RESOURCE_HUB_CREATE_PATH_FROM_ID(
        &fileName,
        m_gpioConnectionId.LowPart,
        m_gpioConnectionId.HighPart);

    WDF_IO_TARGET_OPEN_PARAMS openParams;
    WDF_IO_TARGET_OPEN_PARAMS_INIT_OPEN_BY_NAME(
        &openParams,
        &fileName,
        GENERIC_READ | GENERIC_WRITE);

    RETURN_IF_NOT_SUCCESS(
        WdfIoTargetOpen(
            m_ioTarget,
            &openParams));

    return STATUS_SUCCESS;
}
