#!/bin/sh
# Program2 Demo

# Currently this program only demonstrates the Alice and Bob programs

./bob -p 12345 &

bob1_PID=$!

./alice -h localhost -p 12345 -m "Happy Birthday to You!"

./bob --port 98765 --generateKeys &

bob2_PID=$!

./alice -h localhost -p 12345 -m "One year older"
./alice -h localhost -p 98765 -m "and wiser too."

sleep 1

kill $bob1_PID
kill $bob2_PID
