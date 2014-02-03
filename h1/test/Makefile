SOURCES		= TestRunner.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
DEPS		= $(SOURCES:.cpp=.d)
CXX 		= @clang++
CXXFLAGS 	= -g -DDEBUG -std=c++11 -stdlib=libc++
NAME 		= test

all: $(NAME)

$(NAME): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
	@echo 'Done!'

%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $^ > $@

clean:
	@rm -f $(NAME)
	@rm -f *.o
	@rm -f *.d
	@rm -rf *.dSYM/
	@echo 'All clean!'

-include $(DEPS)
