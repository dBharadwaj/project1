TOPDIR          =$(PWD)
SUBDIRS         =$(TOPDIR)/src/
OBJDIR          =$(TOPDIR)/objects
INCLUDES        =-I$(TOPDIR)/include/

LDFLAGS         =-lglut -lGL


LIBDIR          =$(TOPDIR)/lib/
TESTDIRS        =$(TOPDIR)/tests
CPP             =g++
CPPFLAGS        =-c -Wall 
all: hello

hello: object.o change.o
	$(CPP) object.o change.o -o hello $(LDFLAGS)		


object.o: $(SUBDIRS)/object.cpp 
	$(CPP) $(CPPFLAGS) -g $(INCLUDES) $(SUBDIRS)/object.cpp 

change.o: $(SUBDIRS)/change.cpp $(SUBDIRS)/object.cpp $(SUBDIRS)/3dinp.txt
	$(CPP) $(CPPFLAGS) -g $(INCLUDES) $(SUBDIRS)/object.cpp  $(SUBDIRS)/change.cpp $(SUBDIRS)/3dinp.txt $(LDFLAGS)	

clear: 
	rm -rf *o hello
	rm -f $(TOPDIR)/objects/*.o
