CC=cl65
CFLAGS=-ttelestrat
PROGRAM=file
SOURCE=src/file.c

ASFLAGS=-C -W -e error.txt -l xa_labels.txt


ifeq ($(CC65_HOME),)
        CC = cl65
        AS = ca65
        LD = ld65
        AR = ar65
else
        CC = $(CC65_HOME)/bin/cl65
        AS = $(CC65_HOME)/bin/ca65
        LD = $(CC65_HOME)/bin/ld65
        AR = $(CC65_HOME)/bin/ar65
endif


$(PROGRAM): $(SOURCE)
	$(CC) -o build/file $(CFLAGS) $(LDFILES) $(SOURCE)
	#$(CC) -o 800 $(CFLAGS) $(LDFILES) $(SOURCE)
	#$(CC) -o 900 $(CFLAGS) --config deps/orix-sdk/cfg/telestrat_900.cfg $(LDFILES) $(SOURCE)

	# Reloc
	#python deps/orix-sdk/bin/relocbin.py3 800 900 $(PROGRAM) 3

