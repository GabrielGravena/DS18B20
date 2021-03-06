#pragma once

_IRQL_requires_max_(PASSIVE_LEVEL)
PAGED
NTSTATUS
CreateDS18B20Device(_In_ WDFDEVICE_INIT * DeviceInit);

class DS18B20
{
public:

    _IRQL_requires_max_(PASSIVE_LEVEL)
    PAGED
    DS18B20(
        _In_ WDFDEVICE Device);

    void *
    operator new(
        _In_ size_t Size,
        _In_ WDFDEVICE Device);

    _IRQL_requires_max_(PASSIVE_LEVEL)
    PAGED
    NTSTATUS
    PrepareHardware(
        _In_ WDFCMRESLIST ResourcesRaw,
        _In_ WDFCMRESLIST ResourcesTranslated);

private:

    WDFDEVICE
        m_device = WDF_NO_HANDLE;

};
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DS18B20, GetDeviceContext);
