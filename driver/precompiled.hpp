#pragma once

#include <ntddk.h>
#include <wdf.h>

#define RETURN_IF_NOT_SUCCESS(_status) { NTSTATUS __tmpStatus = (_status); if(__tmpStatus != STATUS_SUCCESS) { return __tmpStatus; } };
