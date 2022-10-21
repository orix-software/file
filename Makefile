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
	mkdir build/bin -p
	mkdir build/usr/share/man -p
	$(CC) -o 1000 $(CFLAGS) $(LDFILES) $(SOURCE) --start-addr \$800
	$(CC) -o 1256 $(CFLAGS) $(LDFILES) $(SOURCE) --start-addr \$900
	# Reloc
	chmod +x deps/orix-sdk/bin/relocbin.py3
	deps/orix-sdk/bin/relocbin.py3 -o build/bin/file -2 1000 1256
	cd docs && ../../md2hlp/src/md2hlp.py3 --file file.md --output ../build/usr/share/man/file.hlp && cd ..

