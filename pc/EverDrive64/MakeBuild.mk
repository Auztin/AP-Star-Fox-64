OBJS = $(patsubst %.cpp,%-$(PLATFORM).o,$(SOURCE))
DEPS = $(shell find $(SRCDIR)/ -type f -name '*.d')

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

include $(DEPS)

%-$(PLATFORM).o: %.cpp Makefile
	$(CXX) -o $@ -c $< $(CXXFLAGS) -MMD
