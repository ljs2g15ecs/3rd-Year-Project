CC 		= g++
CFLAGS	= -D $(S) -std=c++11
LFLAGS	= 

S = S3264

src_dir	= source
build	= build\$(S)
PROG	= $(build)/SIMON_$(S).exe
src		= $(wildcard $(src_dir)/*.cpp)
obj		= $(patsubst $(src_dir)/%.cpp,$(build)/%.o,$(src))

all: $(build) $(PROG)
	$(PROG)

$(build):
	mkdir $(build)

$(PROG): $(obj)
	$(CC) $^ -o $@

$(build)/%.o: $(src_dir)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run:
	$(PROG)
	
.PHONY: clean
clean:
	del /Q build\S3264 build\S4872
	del /Q build\S4896 build\S6496
	del /Q build\S64128 build\S9696
	del /Q build\S96144 build\S128128
	del /Q build\S128192 build\S128256