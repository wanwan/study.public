
EDK2_ROOT=/home/waka/repos/edk2

.PHONY: make_edk_project hello

default: hello

make_edk_project:
	cp hello.c $(EDK2_ROOT)

hello:
	pushd $(EDK_ROOT)
	source edk_setup.sh
	make -C /home/waka/repos/edk2/BaseTools/Source/C
	build
