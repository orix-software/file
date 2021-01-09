CC=cl65
CFLAGS=-ttelestrat
PROGRAM=file
SOURCE=src/file.c

ASFLAGS=-C -W -e error.txt -l xa_labels.txt -DTARGET_ORIX

ifdef TRAVIS_BRANCH
ifeq ($(TRAVIS_BRANCH), main)
RELEASE:=$(shell cat VERSION)
else
RELEASE=alpha
endif
endif


$(PROGRAM): $(SOURCE)
	$(CC) -o $(PROGRAM) $(CFLAGS) $(LDFILES) $(SOURCE)

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