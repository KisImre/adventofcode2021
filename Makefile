# Copyright (c) 2021, Kis Imre. All rights reserved.
# SPDX-License-Identifier: MIT

BINARY := adventofcode

BUILDDIR ?= build

objs += main.o

objs := $(addprefix $(BUILDDIR)/,$(objs))
deps := $(objs:%.o=%.d)

CXXFLAGS += -I. -O2 -Wall -Werror
LDFLAGS +=

CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++
MKDIR := mkdir -p

.PHONY: all clean

all: $(BINARY)
	@echo "Build finished"

clean:
	@echo "Cleaning"
	@rm -rf $(BUILDDIR) $(BINARY)

$(BINARY): $(objs)
	@echo "LD   	$@"
	@$(LD) $(LDFLAGS) $(objs) -o $@

$(BUILDDIR)/%.o: %.cpp
	@echo "CXX  	$@"
	@$(MKDIR) $(dir $(@))
	@$(CXX) $(CXXFLAGS) -MMD -MP -MF$(@:%.o=%.d) -MT$@ -c $< -o $@

-include $(deps)
