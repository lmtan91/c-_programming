
TOPDIR := ../..

TARGET_PROGS =
TARGET_PROGS += mainStack 
TARGET_PROGS += stack3test
TARGET_PROGS += maxtest
TARGET_PROGS += max3test
TARGET_PROGS += stack4test 
TARGET_PROGS += stack5test 
TARGET_PROGS += stack7test 
TARGET_PROGS += stack8test 
TARGET_PROGS += refnonref 

INCDIRS =
INCDIRS += .

CFLAGS_PROG += -DBIT_IS_DEBUG -DBIT_HAS_DEBUG_COLORS
CFLAGS_PROG += -DBIT_IS_STB -std=c++11


BIT_SRCS =
BIT_SRCS += mainStack.cpp
STACK3_SRCS += stack3test.cpp
STACK4_SRCS += stack4test.cpp
STACK5_SRCS += stack5test.cpp
STACK7_SRCS += stack7test.cpp
STACK8_SRCS += stack8test.cpp
MAX_SRCS += maxtest.cpp
MAX3_SRCS += max3test.cpp
REFNONREF_SRCS += refnonref.cpp

SRCS_mainStack = $(BIT_SRCS)
SRCS_stack3test = $(STACK3_SRCS)
SRCS_stack4test = $(STACK4_SRCS)
SRCS_stack5test = $(STACK5_SRCS)
SRCS_stack7test = $(STACK7_SRCS)
SRCS_stack8test = $(STACK8_SRCS)
SRCS_maxtest = $(MAX_SRCS)
SRCS_max3test = $(MAX3_SRCS)
SRCS_refnonref = $(REFNONREF_SRCS)

include $(TOPDIR)/jhbuild/Make.Defaults
include $(TOPDIR)/jhbuild/Make.Rules


