CC 		= g++
CFLAGS	= -D S3264 -std=c++11
LFLAGS	= 

S = S3264

src_dir	= source
build	= build
PROG	= $(build)/SIMON_s3264.exe
src		= $(wildcard $(src_dir)/*.cpp)
obj		= $(patsubst $(src_dir)/%.cpp,$(build)/%.o,$(src))

all: $(build) $(PROG)

$(build):
	mkdir $(build)

$(PROG): $(obj)
	$(CC) $^ -o $@
	$(PROG)

$(build)/%.o: $(src_dir)/%.cpp FORCE
	$(CC) $(CFLAGS) -c $< -o $@
FORCE:

.PHONY: run
run:
	$(PROG)
	
.PHONY: clean
clean:
	del /Q $(build)