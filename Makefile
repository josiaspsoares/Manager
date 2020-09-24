STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g

LIBRARIES = -lm

main : main.c ListaEstoque/ListaEstoque.c
	gcc $(STD) $(OPTIONS) main.c ListaEstoque/ListaEstoque.c -o main $(LIBRARIES)

