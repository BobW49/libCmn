# Generated file - Edits will be discarded by next generation!
# vi:nu:sts=4 ts=4 sw=4
# ( 6/30/2025  0:19:47.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

PGMNAM=prep
SYS=macos64
ARCH=arm64
BUILD=./.build
BASE_OBJ = $(BUILD)/$(PGMNAM)/$(SYS)/$(ARCH)
SRCDIR = ./src
TEST_SRC = ./tests
INSTALL_BASE = $(HOME)/Support/bin/$(ARCH)
LIB_BASE = $(HOME)/git/lib/$(SYS)/$(ARCH)

CFLAGS += -g -Werror -I$(SRCDIR)
ifdef  NDEBUG
CFLAGS += -DNDEBUG
else   #DEBUG
CFLAGS += -D_DEBUG
endif  #NDEBUG
CFLAGS += -D__MACOS64_ENV__
CFLAGS_LIBS = 
# libCmn
LIBCMN_BASE = $(LIB_BASE)/libCmn
CFLAGS += -I$(LIBCMN_BASE)/include
CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)
CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3

LIBOBJ = $(BASE_OBJ)
ifdef  NDEBUG
LIB_FILENAME=$(PGMNAM)R.a
OBJDIR = $(LIBOBJ)/o/r
else   #DEBUG
LIB_FILENAME=$(PGMNAM)D.a
OBJDIR = $(LIBOBJ)/o/d
endif  #NDEBUG
TEST_OBJ = $(OBJDIR)/obj
TEST_BIN = $(OBJDIR)/bin
LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)

.SUFFIXES:
.SUFFIXES: .asm .c .cpp .o

OBJS =

TESTS =






#------------------------------------------------
#         Compile Objects and Routines
#------------------------------------------------


OBJS += $(OBJDIR)/Dict.o

$(OBJDIR)/Dict.o: $(SRCDIR)/Dict.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dict_object.o

$(OBJDIR)/Dict_object.o: $(SRCDIR)/Dict_object.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumFile.o

$(OBJDIR)/EnumFile.o: $(SRCDIR)/EnumFile.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumFile_object.o

$(OBJDIR)/EnumFile_object.o: $(SRCDIR)/EnumFile_object.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem.o

$(OBJDIR)/EnumItem.o: $(SRCDIR)/EnumItem.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem_json.o

$(OBJDIR)/EnumItem_json.o: $(SRCDIR)/EnumItem_json.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItem_object.o

$(OBJDIR)/EnumItem_object.o: $(SRCDIR)/EnumItem_object.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems.o

$(OBJDIR)/EnumItems.o: $(SRCDIR)/EnumItems.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems_json.o

$(OBJDIR)/EnumItems_json.o: $(SRCDIR)/EnumItems_json.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/EnumItems_object.o

$(OBJDIR)/EnumItems_object.o: $(SRCDIR)/EnumItems_object.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Gen.o

$(OBJDIR)/Gen.o: $(SRCDIR)/Gen.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Gen_object.o

$(OBJDIR)/Gen_object.o: $(SRCDIR)/Gen_object.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main.o

$(OBJDIR)/Main.o: $(SRCDIR)/Main.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Main_object.o

$(OBJDIR)/Main_object.o: $(SRCDIR)/Main_object.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<





#------------------------------------------------
#      Compile and execute Tests
#------------------------------------------------


TESTS += Dict_test

Dict_test: $(TEST_SRC)/Dict_test.c $(SRCDIR)/Dict.h $(SRCDIR)/Dict_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumFile_test

EnumFile_test: $(TEST_SRC)/EnumFile_test.c $(SRCDIR)/EnumFile.h $(SRCDIR)/EnumFile_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumItem_test

EnumItem_test: $(TEST_SRC)/EnumItem_test.c $(SRCDIR)/EnumItem.h $(SRCDIR)/EnumItem_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += EnumItems_test

EnumItems_test: $(TEST_SRC)/EnumItems_test.c $(SRCDIR)/EnumItems.h $(SRCDIR)/EnumItems_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Gen_test

Gen_test: $(TEST_SRC)/Gen_test.c $(SRCDIR)/Gen.h $(SRCDIR)/Gen_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3

TESTS += Main_test

Main_test: $(TEST_SRC)/Main_test.c $(SRCDIR)/Main.h $(SRCDIR)/Main_internal.h $(SRCDIR)/prep_defs.h $(LIBCMN_BASE)/include/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F) --no_int3





#------------------------------------------------
#              Phony Targets
#------------------------------------------------


.PHONY: all
all:  create_dirs link


.PHONY: build
build:  create_dirs link


.PHONY: check
check: $(TESTS)


.PHONY: clean
clean:
	-rm -fr $(BUILD)/$(PGMNAM)/$(SYS)/$(ARCH)


.PHONY: create_dirs
create_dirs:
	-mkdir -p $(BUILD)
	-mkdir -p $(TEST_OBJ)
	-mkdir -p $(TEST_BIN)


.PHONY: install
install:
	cp $(OBJDIR)/bin/$(PGMNAM) $(HOME)/bin/$(ARCH)/$(PGMNAM)


.PHONY: link
link: $(OBJS) $(SRCDIR)/mainProgram.c
	CC -o $(OBJDIR)/bin/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^


.PHONY: test
test: $(TESTS)


