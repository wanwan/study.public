#!/bin/sh

fdisk $1 << __EOF__
n
p
1
1
2879
t
1
p
w
__EOF__
