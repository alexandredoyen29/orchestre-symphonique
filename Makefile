# Makefile pour générer le logiciel "Orchestre symphonique"

CC=gcc
OPTIONS=-Wall -Werror -Wpedantic -Wconversion -ansi -std=c11 -O3 -pthread -lopenal -lalut -lm
BIBLIOTHEQUES_COMMUNES_SOURCES=$(wildcard src/commun/*.c)
BIBLIOTHEQUES_COMMUNES_DESTINATION=$(addprefix build/obj/,$(notdir $(BIBLIOTHEQUES_COMMUNES_SOURCES:.c=.o)))

generation-build:
	mkdir build
	mkdir build/obj
	mkdir build/sons
	cp -r sons/sons-mono/* build/sons/

build-commun: generation-build
	${CC} -c $(word 1,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 1,${BIBLIOTHEQUES_COMMUNES_DESTINATION})
	${CC} -c $(word 2,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 2,${BIBLIOTHEQUES_COMMUNES_DESTINATION})
	${CC} -c $(word 3,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 3,${BIBLIOTHEQUES_COMMUNES_DESTINATION})

build-commun-debug: generation-build
	${CC} -c $(word 1,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 1,${BIBLIOTHEQUES_COMMUNES_DESTINATION}) -g
	${CC} -c $(word 2,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 2,${BIBLIOTHEQUES_COMMUNES_DESTINATION}) -g
	${CC} -c $(word 3,${BIBLIOTHEQUES_COMMUNES_SOURCES}) ${OPTIONS} -o $(word 3,${BIBLIOTHEQUES_COMMUNES_DESTINATION}) -g

build-orchestre: build-commun
	${CC} src/orchestre/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -o build/orchestre

build-debug-orchestre: build-commun-debug
	${CC} src/orchestre/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -DDEBUG -o build/orchestre -g

build-instrument: build-commun
	${CC} src/instrument/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -o build/instrument

build-debug-instrument: build-commun-debug
	${CC} src/instrument/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -DDEBUG -o build/instrument -g

build-instrument-script: build-commun
	${CC} src/instrument-script/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -o build/instrument-script

build-debug-instrument-script: build-commun-debug
	${CC} src/instrument-script/*.c ${BIBLIOTHEQUES_COMMUNES_DESTINATION} ${OPTIONS} -DDEBUG -o build/instrument-script -g

build-all: build-orchestre build-instrument build-instrument-script

build-debug-all: build-debug-orchestre build-debug-instrument build-deug-instrument-script

clean:
	rm -rf build
