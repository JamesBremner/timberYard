#source file search paths
VPATH = ./src ../pack2/src

# compiler include search paths
INCS = -I./include \
	-I../pack2/src \

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

OPT = -O2
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJ_timber = \
	$(ODIR)/TimberAllocation.o \
	$(ODIR)/taTimber.o \
	$(ODIR)/taInstance.o \
	$(ODIR)/taLevel.o \
	$(ODIR)/taCutter.o \
	$(ODIR)/taSpace.o \
	$(ODIR)/pack2.o \
	$(ODIR)/cCut.o \

### COMPILE

$(ODIR)/%.o: %.cpp  
	g++ -c $< \
	-o $@  $(CCflags) $(INCS)

timber: $(OBJ_timber)
	g++ $(OPT) \
	-o bin/timber.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

