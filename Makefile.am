## Process this file with automake to produce Makefile.in

if USE_GMAKE
  MAKE = gmake
endif

# build subdirectories
SUBDIRS = include/HepPDT include/HepPID src/HepPDT src/HepPID data \
         tests/HepPID tests/HepPDT doc/HepPID doc/HepPDT \
         examples/HepPDT examples/HepPID examples/data 
# list all subdirectories - for distribution and cleaning
DIST_SUBDIRS = include/HepPDT src/HepPDT data tests doc \
               examples/HepPDT examples/HepPID examples/data

docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS)

install-docs:
	cd doc; $(MAKE) $(AM_MAKEFLAGS) install-docs
