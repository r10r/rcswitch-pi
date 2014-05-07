CXXFLAGS=-O2 -fPIC

all: send

rcswitch_wrap.cxx: RCSwitch.h rcswitch.i
	swig -c++ -python rcswitch.i

rcswitch_wrap.o: rcswitch_wrap.cxx
	$(CXX) $(CXXFLAGS) -c $+ -o $@ -I/usr/include/python2.7

_rcswitch.so: rcswitch_wrap.o RCSwitch.o
	$(CXX) -shared $(LDFLAGS) $+ -o $@ -lwiringPi

send: RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o *.so *.pyc *.cxx send

install:
	mkdir -p /usr/lib/python2.7/dist-packages
	cp rcswitch.py /usr/lib/python2.7/dist-packages
	cp _rcswitch.so /usr/lib/python2.7/dist-packages