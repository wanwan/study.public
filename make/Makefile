
.PHONY: all test1 test2 test3 run

all: test1 test2 

test1:
	gcc -o test1 -DVALUE=1 test.c

test2:
	gcc -o test2  test.c

test3:
	make header > values.h
	gcc -o test3  test3.c

run:
	./test1
	./test2

.ONESHELL
header:
	echo << EOF

MAKEFILEDEFVALUE := 10

define FORMAT :=
echo << EOF
#ifndef __VALUES_H__
#define __VALUES_H__

int ARG1=$${MAKEFILEDEFVALUE};

#endif /* __VALUES_H__ */
endef

	EOF
