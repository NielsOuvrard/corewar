# Corewar README

## Overview

Corewar is a virtual machine game where programs, known as "warriors," battle for control of a shared memory space. This README provides an overview of how to use the Corewar executable and its command-line options.

## Usage

```shell
./corewar [-dump nbr_cycle] [-infos] [-wait] [[-n prog_number] [-aload_address] prog_name] ...
```
## Command-line Options

- `-dump nbr_cycle`: Dumps the memory after the specified number of cycles (default is 100). The memory is displayed in hexadecimal format, with 64 bytes per line (e.g., A0BCDEFE1DD3...).

- `-infos`: Prints additional information about the commands used during the execution.

- `-wait`: Listens for input from the standard input. You can enter 'a' to advance to the next command or 'd' to display the memory.

- `-n prog_number`: Sets the program number for the next program. If not specified, the first available number in the order of parameters will be assigned.

- `-a load_address`: Sets the loading address for the next program. If no address is specified, Corewar will optimize the addresses to ensure that processes are as far away from each other as possible. The addresses are calculated using MEM_SIZE modulo.

## Example

Here is an example of how to run Corewar with command-line options:

```shell
./corewar -dump 500 -infos -wait -n 1 -a 100 warrior1.cor -n 2 warrior2.cor
```

This command will run Corewar with a memory dump after 500 cycles, additional information printing, a wait mode, and two programs (warrior1.cor and warrior2.cor) with program numbers 1 and 2, respectively. The loading address of the first program is set to 100.

Enjoy the battle of the warriors in Corewar!
