DefinitionBlock ("ACPITABL.dat", "SSDT", 0x01, "MSFT", "DS18B20", 0x1)
{
    Scope(\_SB)
    {
        Device(GPOT)
        {
            Name(_HID, "ds18b20")
            Name(_CID, "ds18b20")
            Name(_UID, 1)
            Name(_CRS, ResourceTemplate()
            {
                GpioIO(Shared, PullDefault, 0, 0, IoRestrictionNoneAndPreserve, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 18 }
            })
        }
    }
}
