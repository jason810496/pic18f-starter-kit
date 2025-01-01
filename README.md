# PIC18F4520

## Usage

- `template.c` 

## Connect to Serial Port

1. `ls -al /dev/tty.usbserial*`
```
crw-rw-rw-  1 root  wheel  0x9000004  1  1 21:16 /dev/tty.usbserial-1120
```
2. `screen /dev/tty.usbserial-1120 1200` ( `1200` is the baud rate)
3. Press `Ctrl + A` then `Ctrl + K` to exit screen
