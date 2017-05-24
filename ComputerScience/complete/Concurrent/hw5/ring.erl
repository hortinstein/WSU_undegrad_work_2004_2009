%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Alex Hortin
% Homework 5 
% Programming Assignment 2
% 3/29/2009

% Write a ring benchmark. Create N processes in a ring. Send a mes-
% sage round the ring M times so that a total of N * M messages get
% sent. Time how long this takes for different values of N and M.
% Write a similar program in some other programming language you
% are familiar with. Compare the results. Write a blog, and publish
% the results on the Internet!
%
%	Test Compile/Run in Erl:" c(ring), ring:ring({5,6}). "   
%
%
% My code simply works by creating a ring with a Pid0 than spawning all the other nodes, saving 
% their pid so you can later forward the message.  After all nodes are complete, the final node
% lets the initial node know its complete than all nodes go into wait send loops, and Pid0 goes
% into a special one that decrements m.  Each node waits till it recieves a message, than it 
% passes the message onto its neighbor, than goes back into the loop.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

-module(ring). %defining the name of the ring 
-export([ring/2]). %exporting the ring function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ring({N,M}) 
% This function exists to give the user information about the benchmark
% and then it will spawn the creation of the message passing ring.
% It will output information regarding the ring to the user, and it 
% will begin the ring by calling spawnRing, and it will also bring the 
% different time benchmarks into the program, finally outputting them after
% the ring algorithm is complete 
%
% input:
%	N :		The number of processes created within the ring
% 	M :		The number of times the messages are passed throughout
%			the ring   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

ring(N,M) ->
	io:format("...processes created:~p~n",[N]), %outputting information about execution to the user    
	io:format("...messages each process passes:~p~n",[M]),		
	io:format("...total messages passed:~p~n",[M*N]),			
	Pid0 = self(), %storing the self to pass on
	To = spawn(fun() -> spawnRing(N,Pid0) end), %calling the process that builds that ring saving it's child
	receive
		complete -> %recieves a message that the ring has been completed
			io:format("."),%indicates a message passed			
			To ! msg, %starts the first message pass
			waitSendCounter(To,M-1)%goes into the counter wait loop
		
	
	end.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% spawnRing(N,FirstPID) 
% This begins building the ring by creating the first node that will recieve
% a message, and this node is not connected to anything.   
%
% input:
%	N :		The number of processes created within the ring
%	FirstPID : 	This is the PID of the first process so the final ring can forward it 
%			the message that it's looking for
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

spawnRing(1,FirstPID) ->
	io:format("...creating final node, seding completion message to node first node( ~p ) ~n",[FirstPID]),
	FirstPID ! complete,%letting node 0 know that it can begin starting the message passing
	waitSend(FirstPID);%entering the waitsend loop for message reception
	
spawnRing(N,FirstPID) -> 
	To = spawn(fun() -> spawnRing(N-1,FirstPID) end), %creating the next node in the chain saving its PID
	waitSend(To). %entering waitsend and saving 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
% waitSend(toPID)
% This function is where each node in the ring, except for the starting node waits for a message.
% When it recieves a message, it forwards the message to it's partner (toPID) than resumes waiting.
%
% input:
% 	toPID :		This is the partner node that this node always passes messages to in the ring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

waitSend(ToPID) ->
	receive %waiting to recieve the next message
		msg -> 
			ToPID ! msg, %passing on the atom
			waitSend(ToPID) %going back into the wait loop
	end.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% waitSendCounter(toPID,M) 
% This function is like waitSend, but takes an additional counter that it used to keep track of the 
% m.  This is called by the very first node created, and everytime all of the nodes 
%
% input:
% 	toPID :		This is the partner node that this node always passes messages to in the ring
%	M:		The number of times remaining for the message to pass around the ring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

waitSendCounter( ToPID,0 ) ->%overload to handle zero meaning its done
	io:format("benchmark complete~n"),
	{_, Time1} = statistics(runtime),
	{_, Time2} = statistics(wall_clock),
    	io:format("runtime=~p (~p) microseconds~n",[Time1, Time2]);	
waitSendCounter( ToPID,M ) ->
	receive %waiting for the entire ring to complete
		msg -> 
			io:format("."),%indicates a message passed
			ToPID ! msg, %passing the message to the ring again
			waitSendCounter(ToPID,M-1) %calling again and decrementing the loop
	end.








