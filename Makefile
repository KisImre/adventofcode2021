# Copyright (c) 2021, Kis Imre. All rights reserved.
# SPDX-License-Identifier: MIT

ifeq ($(DAY),)
$(error DAY variable is not set)
endif

include day$(DAY)/day.mk

BINARY_NAME := adventofcode_day$(DAY)
BINARY := day$(DAY)/$(BINARY_NAME)

BUILDDIR := build/day_$(DAY)

objs := $(addprefix $(BUILDDIR)/day$(DAY)/,$(objs))
deps := $(objs:%.o=%.d)

CXXFLAGS += -I. -O2 -Wall -Werror
LDFLAGS +=

CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)g++
MKDIR := mkdir -p

.PHONY: all clean

all: $(BINARY)
	@echo "Build finished"

run: all
	@echo Day $(DAY) results:
	@cd day$(DAY) && ./$(BINARY_NAME)

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
