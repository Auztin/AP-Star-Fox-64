PLATFORM:= windows
CXX:=x86_64-w64-mingw32-g++
TARGET:=$(TARGET).exe
CXXFLAGS+= -D_WIN32_WINNT=0x0601
LDFLAGS+= -static
LDFLAGS+= -l ws2_32
LDFLAGS+= -l wsock32
export

build:
	@$(BUILD)
