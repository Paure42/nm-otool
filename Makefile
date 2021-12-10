##
# ft_nm
#
# @file
# @version 0.1

# Set the project, sources and build directory
SOURCEDIR=sources/
INCDIR=includes/
BUILDDIR=build/

# Define include directory
INCLUDES = $(addprefix -I, $(INCDIR))

# Set command for OS
MKDIR=mkdir -p
RM=rm -rf

# Set variables of compilations
CC=gcc
CFLAGS= -Wall -Wextra -Werror
LDFLAGS=
EXEC=ft_nm
DEBUG=yes
VERBOSE=TRUE

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


# Create a list of *.c sources in SOURCEDIR
SOURCES = $(wildcard $(SOURCEDIR)*.c)

# Define objects for all sources
OBJS = $(patsubst ${SOURCEDIR}%.c,${BUILDDIR}%.o,${SOURCES})

# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)

# Remove space after separator
PSEP = $(strip $(SEP))

# Creation of object files
${BUILDDIR}%.o:	${SOURCEDIR}%.c ${INCLUDES}
	$(HIDE)${CC} -c ${CFLAGS} -o $@ $<

# Creation of the executable
$(EXEC): ${OBJS}
	${CC} ${CFLAGS} -o ${EXEC} ${OBJS} ${LDFLAGS}

all: directories ${EXEC}

# Include dependencies
-include $(DEPS)

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILDDIR))

# Remove all objects
clean:
	$(HIDE)$(RM) $(wildcard $(BULDDIR)/*.o)

# Remove all objects, dependencies and executable files generated during the build
fclean:
	$(HIDE)(RM) $(subst /,$(PESP), $(BUILDDIR))
	@echo Cleaning done !

.PHONY: re clean fclean
# end
