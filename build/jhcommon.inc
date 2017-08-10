# -*- makefile -*-
ifdef RMCH_CONFIG_LOADED

DEPS_$(DIR) := $(DEPS_$(DIR)) $(TOPSRCDIR)/build/jhcommon.inc

# Force variables to be immediate
CFLAGS_KERNEL_$(DIR) := $(CFLAGS_KERNEL_$(DIR))
CFLAGS_PROG_$(DIR) := $(CFLAGS_PROG_$(DIR))
CFLAGS_KERNEL_$(DIR) += -I$(TOPDIR)/jhkernel/include
# kernel builds always use local copy of jhcommon/include for test progs
ifneq (,$(strip $(JH_BUILD_KERNEL)))
CFLAGS_PROG_$(DIR) += -I$(TOPDIR)/jhcommon/include
else
ifneq (,$(strip $(MASTERBUILD_BUILD_DIR)))
CFLAGS_PROG_$(DIR) += -I$(MASTERBUILD_BUILD_CDITOOLS_INCLUDE_PATH)
else
CFLAGS_PROG_$(DIR) += -I$(TOPDIR)/jhcommon/include
endif
endif

ifdef USE_STATIC_LIBJHCOMMON
LIBS_$(DIR) := $(LIBS_$(DIR)) jhcommon
else
SHLIBS_$(DIR) := $(SHLIBS_$(DIR)) jhcommon
endif

else

KERNINCDIR += $(TOPDIR)/jhkernel/include

# kernel builds always use local copy of jhcommon/include for test progs
ifneq (,$(strip $(JH_BUILD_KERNEL)))
# XXX: Use CFLAGS_PROG instead of INCDIRS so that dependencies are set 
# XXX: correctly for the code that matters (ie. kernel modules, not test progs)
CFLAGS_PROG += -I$(TOPDIR)/jhcommon/include
else
ifneq (,$(strip $(MASTERBUILD_BUILD_DIR)))
INCDIRS	+= $(MASTERBUILD_BUILD_CDITOOLS_INCLUDE_PATH)
else
INCDIRS += $(TOPDIR)/jhcommon/include
endif
endif

ifdef USE_STATIC_LIBJHCOMMON
LIBS += jhcommon
else
SHLIBS += jhcommon
endif

ifdef JH_BUILD_DEBUG
LDFLAGS_tad += -Wl,-rpath,/mnt/jethead/lib/$(ARCH)
endif

endif # RMCH_CONFIG_LOADED
