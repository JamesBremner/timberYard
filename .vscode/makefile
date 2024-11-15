#source file search paths
VPATH = ./src ../windex/include ../pack2/src

# compiler include search paths
INCS =  \
	-I../windex/include \
	-I../pack2/src \

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs -lComctl32 \

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj

OPT = -g
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

OBJ_timberGUI = \
	$(ODIR)/timberGUI.o \
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

timberGUI: $(OBJ_timberGUI)
	g++ $(OPT) \
	-o bin/timberGUI.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

