CXXFLAGS=-O2 -fPIC

call: send

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
