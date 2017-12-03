
# Building and Running in Simplicity Studio

## Create and Import Project

From the checkout directory:

```bash
> mkdir ../FreeRtosExamplesBuild
> cd ../FreeRtosExamplesBuild
> cmake -G "Eclipse CDT4 - Unix Makefiles" ../FreeRtosExamples
```

In "Simplicity Studio":

*File > Import > Existing Projects into Workspace*

Select the *FreeRtosExamplesBuild* folder.


## Running and Debugging

After building, the examples can be run:

*Run > Debug Configuration*

In *Main > Executable*: select the binary

The binary file should be an ELF executable. This can be checked
with the `file` command:

```bash
> file <binaryName>
<binaryName>: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), statically linked, not stripped
```

In *Connection*:

- Disable *Auto-select compatible device*
- *Boards*: Select used board (e.g EFM32 Tiny Gecko Starter Kit board (BRD2100A Rev A05))


In *Tracing*:

- Activate *Enable tracing*
- *Core clock* 14.000000 *MHz*
- *SWO clock*:
    - disable *Auto*
    - 875 *kHz*

> If breakpoints don't work, check if the binaries contain debug symbols
