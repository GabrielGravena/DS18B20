DefinitionBlock ("DSDT.AML", "DSDT", 0x02, "MSFT", "SAMPLE", 0x1)
{
	Score(\_SB)
	{
		Device(GPIO)
		{
			Name(_ADR, 0)
			Name(_HID, "TEST0001")
			Name(_CID, "TEST0001")
			Name(_UID, 4)

			Method (_CRS, 0x0, NotSerialized)
			{
				Name (RBUF, ResourceTemplate()
				{
					GpioIo(Exclusive, PullUp, 0, 0, , "\\_SB_GPIO", 0, ResourceConsumer, , RawDataBuffer() {1}) {18}
				})

				return RBUF;
			}
		}
	}
}
