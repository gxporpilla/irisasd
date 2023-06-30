-include Makefileextra.local
CXX=g++

# Linux
#CXXFLAGS=-O3 -Wall -fmessage-length=0  -s
DEBUGFLAGS=
#DEBUGFLAGS=-rdynamic -DDEBUG
CXXFLAGS=${EXTRAFLAGS} ${DEBUGFLAGS} -gdwarf-3 -Wall -std=c++11 -Wformat
LINKFLAGS=-L/opt/local/lib \
		  -lopencv_core \
		  -lopencv_highgui \
		  -lopencv_imgproc \
		  -lopencv_objdetect \
		  -lopencv_contrib \
		  -lopencv_nonfree \
		  -lopencv_features2d \
		  -lboost_filesystem \
		  -lboost_system \
		  -lboost_regex \
		  -lopencv_photo \

COMPILETARGETS=lbp lbpc sift siftc surf surfc cg caht wahet gfcf lg hd hdverify qsw ko koc cb cbc cr dct dctc maskcmp ifpp manuseg cahtlog2manuseg wahetlog2manuseg cahtvis

ALLTARGETS= ${COMPILETARGETS} gen_stats_np.py

%:%.cpp version.h
	$(CXX) -o $@ $(CXXFLAGS) $< $(LINKFLAGS)

all: ${ALLTARGETS}
install: all
	mkdir -p ${HOME}/bin
	@echo "installing"
	@install -v ${ALLTARGETS} ${HOME}/bin/ | grep -e '->' | sed "s/.*->\s*'\(.*\)'/\1/" > INSTALL.LOG
	@cat INSTALL.LOG
	@echo "information stored in INSTALL.LOG"
uninstall: INSTALL.LOG
	@echo "uninstalling"
	@$(eval RMLIST:=`cat $< | xargs echo` )
	@echo "The following files will be removed"
	@cat $< | sed 's/^/    /'
	@rm -I ${RMLIST} $<
clean:
	rm ${COMPILETARGETS}

gen_stats_np.py:
	@:
