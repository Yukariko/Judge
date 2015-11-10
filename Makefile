INCLUDEDIRS = \

LIBDIRS = \

LIBS = \

CPPFLAGS = -Wall -O2 -std=c++11 -g 
LDFLAGS =  $(LIBDIRS) $(LIBS)

bin = judge

t1 = main
t2 = judge
t3 = execute
t4 = compile
t5 = language
t6 = address

obj = $(t1).o $(t2).o $(t3).o $(t4).o $(t5).o

all: $(bin)
$(bin): $(obj)
		$(CXX) $(CPPFLAGS) $(obj) $(LDFLAGS) -o $@

clean:
		rm -f $(bin) *.o
