#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./include \
	-I../ravencode/pub/src \
	-I../raven-set \
	-I../pack2/src \
	-I../boost/boost1_78 

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	-L../boost/boost1_78/lib \
		-lboost_system-mgw11-mt-x64-1_78 \
		-lboost_program_options-mgw11-mt-x64-1_78 \
		# -lboost_thread-mgw11-mt-x64-1_7 \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

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

### COMPILE

$(ODIR)/pack2.o: ../pack2/src/pack2.cpp
	g++ -c $< \
	-o $@  $(CCflags) $(INCS)
$(ODIR)/cCut.o: ../pack2/src/cCut.cpp
	g++ -c $< \
	-o $@  $(CCflags) $(INCS)

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

