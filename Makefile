##
# ft_nm
#
# @file
# @version 1.0

# Set the project, sources and build directory
SOURCEDIR=sources
INCDIR=includes
BUILDDIR=build

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
VERBOSE=FALSE


# Define verbose for compilation
ifeq ($(VERBOSE), TRUE)
	HIDE =
else
	HIDE = @
endif


# Create a list of *.c sources in SOURCEDIR
SOURCES = $(wildcard $(SOURCEDIR)/*.c)

# Define objects for all sources
OBJS := $(patsubst ${SOURCEDIR}/%.c,${BUILDDIR}/%.o,${SOURCES})

# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)

# Remove space after separator


# Creation of object files
${BUILDDIR}/%.o: ${SOURCEDIR}/%.c
	$(HIDE)${CC} -c ${CFLAGS} -o $@ $<

all: directories ${EXEC}

# Creation of the executable
$(EXEC): $(OBJS)
	@echo Linking $@
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Include dependencies
-include $(DEPS)


# Rule for sanitize the memory
asan: CFLAGS += -g3 -fsanitize=address
asan: all

directories:
	$(HIDE)$(MKDIR) $(BUILDDIR)

# Remove all objects
clean:
	$(HIDE)$(RM) $(wildcard $(BUILDDIR)/*.o)

# Remove all objects, dependencies and executable files generated during the build
fclean:
	$(HIDE)$(RM) $(BUILDDIR) $(EXEC) $(EXEC).dSYM
	@echo Cleaning done !

.PHONY: re clean fclean
# end
