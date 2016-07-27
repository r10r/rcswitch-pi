all: send send_bauhn

send: RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lpthread

send_bauhn: RCSwitch.o send_bauhn.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lpthread

clean:
	$(RM) *.o send
