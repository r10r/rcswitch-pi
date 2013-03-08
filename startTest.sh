#!/bin/bash
#
# 

#Rev Typ B:
#sudo ./sendTriState F1FF1FF00001
sudo ./sendRev B 1 0
sleep 1
#sudo ./sendTriState F1FF1FF00010
sudo ./sendRev B 1 1
sleep 1

#sudo ./sendTriState F1FFF1F00001
sudo ./sendRev B 2 0
sleep 1
#sudo ./sendTriState F1FFF1F00010
sudo ./sendRev B 2 1
sleep 1

#sudo ./sendTriState F1FFFF100001
sudo ./sendRev B 3 0
sleep 1
#sudo ./sendTriState F1FFFF100010
sudo ./sendRev B 3 1
sleep 1

