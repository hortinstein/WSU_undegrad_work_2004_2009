#!/bin/sh
qemu -fda mtximage -serial stdio -serial pty -boot a -no-fd-bootchk

#qemu -fda mtximage -serial pty -serial pty -boot a -no-fd-bootchk

# This command opens minicom as a terminal on the pty:
# minicom -o -p /dev/pty/6
#
#   -o              prevents minicom from sending modem initialization info
#   -p [device]     specifices the pseudo-terminal to hook up to
#


