CXX=g++ 
LD=ld

OPENCV_PATH=e:/USIT/opencv/build/install/
OPENCV_VERSIONTAG=2413
BOOST_PATH=c:/msys64/mingw32/lib/
BOOST_TARGET=mgw53
BOOST_VERSIONTAG=1_59
MINGW_PATH=c:/msys64/mingw64/

# Windows
CXXFLAGS=-O3 -Wall -D__NO_INLINE__ -fmessage-length=0 -std=c++11 \
    -static-libstdc++ -static-libgcc -static -Os -s \
    -I${OPENCV_PATH}/include \
    -I${OPENCV_PATH}/include/opencv \
    -I${BOOST_PATH}/include/boost-${BOOST_VERSIONTAG}


##
## Use this to utilize the default version of the opencv
## This could lead to an access vioalation error 0xc000007b
## If this happens the dlls of the opencv are faulty, compile them by hand.
##
#LINK_OPENCV= \
#    ${OPENCV_PATH}/build/lib/x86/mingw/libopencv_core${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/lib/x86/mingw/libopencv_highgui${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/lib/x86/mingw/libopencv_imgproc${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/lib/x86/mingw/libopencv_objdetect${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/x86/mingw/lib/x86/mingw/libopencv_contrib${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/x86/mingw/lib/x86/mingw/libopencv_featuers2d${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/x86/mingw/lib/x86/mingw/libopencv_nonfree${OPENCV_VERSIONTAG}.dll.a \
#    ${OPENCV_PATH}/build/x86/mingw/lib/x86/mingw/libopencv_photo${OPENCV_VERSIONTAG}.dll.a 

## 
## Use this for hand compiled opencv 32bit libs.
## In a mingw shell: 
## $ cd ${OPENCV_PATH}
## $ mkdir build2 ; cd build2
## $ cmake -G "MSYS Makefiles" -DCMAKE_CXX_FLAGS:STRING=-m32 ..
## $ make
##
#try .a#LINK_OPENCV= \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_core${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_highgui${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_imgproc${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_objdetect${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_contrib${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_nonfree${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_features2d${OPENCV_VERSIONTAG}.dll \
#try .a#    ${OPENCV_PATH}/x86/mingw/bin/libopencv_photo${OPENCV_VERSIONTAG}.dll 

LINK_OPENCV= \
	-L${OPENCV_PATH}/x86/mingw/staticlib \
	-lopencv_contrib${OPENCV_VERSIONTAG} \
	-lopencv_stitching${OPENCV_VERSIONTAG} \
	-lopencv_nonfree${OPENCV_VERSIONTAG} \
	-lopencv_superres${OPENCV_VERSIONTAG} \
	-lopencv_ts${OPENCV_VERSIONTAG} \
	-lopencv_videostab${OPENCV_VERSIONTAG} \
	-lopencv_gpu${OPENCV_VERSIONTAG} \
	-lopencv_photo${OPENCV_VERSIONTAG} \
	-lopencv_objdetect${OPENCV_VERSIONTAG} \
	-lopencv_legacy${OPENCV_VERSIONTAG} \
	-lopencv_video${OPENCV_VERSIONTAG} \
	-lopencv_ml${OPENCV_VERSIONTAG} \
	-lopencv_calib3d${OPENCV_VERSIONTAG} \
	-lopencv_features2d${OPENCV_VERSIONTAG} \
	-lopencv_highgui${OPENCV_VERSIONTAG} \
	-lIlmImf \
	-llibjasper \
	-llibtiff \
	-llibpng \
	-llibjpeg \
	-lopencv_imgproc${OPENCV_VERSIONTAG} \
	-lopencv_flann${OPENCV_VERSIONTAG} \
	-lopencv_core${OPENCV_VERSIONTAG} \
	-lzlib \
	-lwinmm \
	-lvfw32 \
	-lws2_32 \
	-lsetupapi \
	-lole32 \
	-lgdi32 \
	-lcomctl32 \
	-lwinpthread 
	
LINKFLAGS= ${LINK_OPENCV} \
    -lboost_regex-mt \
    -lboost_filesystem-mt \
    -lboost_system-mt
	

bin/%.exe: %.cpp version.h
	$(CXX) $< -o $@ $(CXXFLAGS) $(LINKFLAGS)

all: bin/lbp.exe bin/lbpc.exe bin/surf.exe bin/surfc.exe bin/sift.exe bin/siftc.exe bin/caht.exe bin/wahet.exe bin/gfcf.exe bin/lg.exe bin/cg.exe bin/hd.exe bin/hdverify.exe bin/qsw.exe bin/ko.exe bin/koc.exe bin/cb.exe bin/cbc.exe bin/cr.exe bin/dct.exe bin/dctc.exe bin/maskcmp.exe bin/ifpp.exe bin/manuseg.exe bin/cahtlog2manuseg.exe bin/wahetlog2manuseg.exe bin/cahtvis.exe


