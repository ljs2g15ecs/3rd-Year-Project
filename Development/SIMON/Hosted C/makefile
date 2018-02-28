CC 		= gcc
CFLAGS	= -D $(S)
LFLAGS	= 

src_dir	= source
build	= build
PROG	= $(build)/SIMON_host.exe
src		= $(wildcard $(src_dir)/*.c)
obj		= $(patsubst $(src_dir)/%.c,$(build)/%.o,$(src))

S = S32_64

all: $(build) $(PROG)

$(build):
	mkdir $(build)

$(PROG): $(obj)
	$(CC) $^ -o $@


$(build)/%.o: $(src_dir)/%.c FORCE
	$(CC) $(CFLAGS) -c $< -o $@
FORCE:

.PHONY: run
run:
	$(PROG)
	
.PHONY: clean
clean:
	del /Q $(build)