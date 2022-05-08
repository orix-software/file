CC=cl65
CFLAGS=-ttelestrat
PROGRAM=file
SOURCE=src/file.c

ASFLAGS=-C -W -e error.txt -l xa_labels.txt

ifdef TRAVIS_BRANCH
ifeq ($(TRAVIS_BRANCH), main)
RELEASE:=$(shell cat VERSION)
else
RELEASE=alpha
endif
endif

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
	$(CC) -o 800 $(CFLAGS) $(LDFILES) $(SOURCE)
	$(CC) -o 900 $(CFLAGS) --config deps/orix-sdk/cfg/telestrat_900.cfg $(LDFILES) $(SOURCE)

	# Reloc
	python deps/orix-sdk/bin/relocbin.py3 800 900 $(PROGRAM) 3

test:
	mkdir -p build/bin/
	mkdir -p build/usr/share/man
	mkdir -p build/usr/share/ipkg  
	cp $(PROGRAM) build/bin/
	cp src/man/$(PROGRAM).hlp build/usr/share/man
	cp src/ipkg/$(PROGRAM).csv build/usr/share/ipkg
	cd build &&	tar -c * > ../$(PROGRAM).tar && cd ..
	gzip $(PROGRAM).tar
	mv $(PROGRAM).tar.gz $(PROGRAM).tgz
	php buildTestAndRelease/publish/publish2repo.php $(PROGRAM).tgz ${hash} 6502 tgz alpha 
	echo nothing