
TOPDIR := ../..

TARGET_LIBS = libjhcommon 
# libjhcomserver libjhcomclient
TARGET_SHLIBS = libjhcommon

INCDIRS += ../include


#Only if JH_GCHEAP is not no should we enable GCHEAP
ifneq ($(JH_GCHEAP), no)
CFLAGS_PROG += -DGCHEAP_ENABLED
endif

JH_COMMON_SRCS = Thread.cpp \
	gh_memory.cpp \
	Mutex.cpp 


SRCS_libjhcommon = $(JH_COMMON_SRCS)

SRCS_libjhcommonmd = $(JH_COMMON_SRCS)
CFLAGS_libjhcommonmd = -DUSE_WRAPPERS

SRCS_libjhcommongb = $(JH_COMMON_SRCS)
CFLAGS_libjhcommongb = -DUSE_GUARD_BANDS -DUSE_WRAPPERS

SRCS_libjhcomserver = ComponentManager.cpp ComponentManagerUtils.cpp
CFLAGS_libjhcomserver =

SRCS_libjhcomclient = ComponentManagerClient.cpp ComponentManagerUtils.cpp
CFLAGS_libjhcomclient =

include $(TOPDIR)/jhbuild/Make.Defaults
include $(TOPDIR)/jhbuild/Make.Rules


