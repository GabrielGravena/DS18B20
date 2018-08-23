#include "precompiled.hpp"

#include "ds18b20.hpp"

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
