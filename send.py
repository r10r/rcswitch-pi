#!/usr/bin/python

import sys
import rcswitch

PIN = 3

def main(argv):
  switch = rcswitch.RCSwitch()
  switch.enableTransmit(PIN)

  system_code = argv[1]
  unit_code = int(argv[2])
  command = int(argv[3])

  print 'sending systemCode[%s] unitCode[%i] command[%i]' % (system_code, unit_code, command)

  if command == 0:
      switch.switchOff(system_code, unit_code)
  elif command == 1:
      switch.switchOn(system_code, unit_code)

if __name__ == '__main__':
  main(sys.argv)
