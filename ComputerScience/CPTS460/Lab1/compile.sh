echo comiling ......
bcc  -c main.c
as86 -o bs.o  bs.s
echo linking .......
ld86 -d bs.o  main.o  /usr/lib/bcc/libc.a
echo check a.out size
ls -l a.out
echo dumping a.out to floppy .......
dd if=a.out  of=mtximage  bs=1024 count=1 conv=notrunc