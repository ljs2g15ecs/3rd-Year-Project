CC 		= g++
CFLAGS	= -D $(S) -D $(D) -std=c++11
LFLAGS	= 

S = S3264
D = BUILD

src_dir	= source
build	= $(D)\$(S)
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
	del /Q $(D)\S3264 $(D)\S4872
	del /Q $(D)\S4896 $(D)\S6496
	del /Q $(D)\S64128 $(D)\S9696
	del /Q $(D)\S96144 $(D)\S128128
	del /Q $(D)\S128192 $(D)\S128256