##
# ft_nm
#
# @file
# @version 0.1

# Set the project, sources and build directory
PROJDIR := $(realpath $(CURDIR))
SOURCEDIR := $(PROJDIR)/sources
INCDIR := $(PROJDIR)/includes
BUILDDIR := $(PROJDIR)/build


# Set command for OS
MKDIR=mkdir -p
RM=rm -rf


# Set variables of compilations
CC=gcc
CFLAGS= -Wall -Wextra -Werror
LDFLAGS=
EXEC=ft_nm
DEBUG=yes
VERBOSE=FALSE

# Add flag for debugging
ifeq ($(DEBUG), yes)
	CFLAGS += -g3 -fsanitize=address
endif

# Define verbose for compilation
ifeq ($(VERBOSE), TRUE)
	HIDE =
else
	HIDE = @
endif

# Define include directory
INCLUDES = $(addprefix -I, $(INCDIR))

# Create a alist of *.c sources in SOURCEDIR
SOURCES = $(wildcard $(SOURCEDIR)/*.c)

# Define objects for all sources
OBJS := $(subst $(SOURCEDIR), $(BUILDDIR), $(SOURCES:.c=.o))

# Define dependencies files for all objects

DEPS = $(OBJS:.o=.d)a

# Remove space after separator

PSEP = $(strip $(SEP))

# Define the function that will generate each rule

define generateRules
$(1)/%.o: %.c
	@echo Building $$@
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef

all: directories $(EXEC)

$(EXEC) : $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC)$(OBJS) -o $(EXEC)

# Include dependencies
-include $(DEPS)

# Generate rules
$(eval $(call generateRules, $(TARGETDIR)))

directories:
	$(HIDE)$(MKDIR)$(subst /,$(PSEP),$(TARGETDIR))

# Remove all objects

clean:
	$(HIDE)$(RM)$(wildcard $(BULDDIR)/*.o)
# Remove all objects, dependencies and executable files generated during the build
fclean:
	$(HIDE)(RM)$(subst /,$(BUILDDIR))
	@echo Cleaning done !

.PHONY: re clean fclean
# end
