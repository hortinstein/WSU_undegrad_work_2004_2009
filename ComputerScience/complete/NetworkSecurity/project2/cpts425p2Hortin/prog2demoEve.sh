#!/bin/sh
# Program2 Demo Eve

# This program demonstrates the Alice, Bob, and Eve programs
# This demo assumes that Alice is sending confidential messages to Bob.
# (Note: Another set of commands would be needed for testing if Alice 
# (were sending high integrity messages to Bob.)

./bob -p 10001 -g &
bob1_PID=$!
sleep 1

./alice -h localhost -p 10001 -m "First--thumb"
sleep 1

./bob -p 10002 -g &
bob2_PID=$!
sleep 1

./alice -h localhost -p 10001 -m "Second--shoe"
sleep 1

./alice -h localhost -p 10002 -g -m "Third--tree"
sleep 1

./eve -i 10003 -h localhost -p 10002 &
eve1_PID=$!
sleep 1

./alice -h localhost -p 10003 -m "Fourth--door"
sleep 1

./alice -h localhost -p 10002 -m "Fifth--dive"
sleep 1

./eve -i 10004 -h localhost -p 10002 -m "**MITM**" &
eve2_PID=$!
sleep 1

./alice -h localhost -p 10004 -m "Fifth--dive"
sleep 1

./alice -h localhost -p 10003 -m "Sixth--sticks"
sleep 1


kill $bob1_PID
kill $bob2_PID
kill $eve1_PID
kill $eve2_PID
