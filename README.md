# Non-Blocking / Interrupt based SPI writeBytes() function for ESP8266

Using `SPI.writeBytes(data, size)` of the official Arduino SDK blocks the CPU until all data is sent via SPI, wasting lots of CPU cycles.

Using `nbSPI_writeBytes(data, size)` instead will return almost immediatly and NOT block the CPU until all data is sent. CPU is only blocked to (re-)fill the SPI buffer when needed.

Execution time is independent of the actual SPI speed and is about ~6µs for every 64 Bytes of data.

<img src="examples/timing.png" />

The size of the SPI Hardware Buffer of the ESP8266 is 64 Bytes. Thus, only 64 Bytes of data can be sent at once. If more data needs to be sent out, an ISR is called to fill up the Buffer after 64 Bytes were sent.