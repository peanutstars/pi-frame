
SUBDIRS	:= packages \
		   bin \
		   lib

#------------------------------------------------------------------------------
# DEFINE SUBDIR MACRO
#------------------------------------------------------------------------------
DISTCLEANSUBDIRS	:= $(patsubst %, %-distclean, $(SUBDIRS))
CLEANSUBDIRS		:= $(patsubst %, %-clean, $(SUBDIRS))
INSTALLSUBDIRS		:= $(patsubst %, %-install, $(SUBDIRS))

#------------------------------------------------------------------------------
# DEFINE SUBDIR RULES
#------------------------------------------------------------------------------
.PHONY: install install-subdirs clean clean-subdirs distclean distclean-subdirs $(SUBDIRS) $(INSTALLSUBDIRS) $(CLEANSUBDIRS) $(DISTCLEANSUBDIRS)

all:	$(SUBDIRS)

$(SUBDIRS):	
	$(MAKE) -C $@
	$(MAKE) -C $@ install

install:	install-subdirs
	#cp -a sbin misc $(VM_SYSTEM_BASE)/system

install-subdirs:	$(INSTALLSUBDIRS)

$(INSTALLSUBDIRS):
	$(MAKE) -C $(patsubst %-install,%,$@) install

clean:	clean-subdirs

clean-subdirs:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	$(MAKE) -C $(patsubst %-clean,%,$@) clean

distclean:	distclean-subdirs

distclean-subdirs:	$(DISTCLEANSUBDIRS)

$(DISTCLEANSUBDIRS):
	$(MAKE) -C $(patsubst %-distclean,%,$@) distclean

