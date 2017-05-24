-module(floor).
-export([newFloor/2,selectBest/2]).

newFloor(N, Lifts) -> agent:newAgent(fun floor/2, {N, Lifts}).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% 	6 The Floor Agent
% Implement a function floor(Message, State) for the floor agent which returns a new state.
% The code for selecting the lift with shortest waittime (given that you know the waittime for each lift) is outlined
% in the selectBest function in this file.
% The file floor.erl contains code fragments to give you a start.
%
% Note this code does not change the floor state from one iteration to the next.
% Add information to the state to handle lights on the buttons.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
reciever(X) -> 
	receive 
		{propose,Lift,Time}-> {Lift,Time} 
	end. 
		  
floor(up, {N, Lifts}=State) -> 
	Sender = fun(E) -> E ! {request, N, self(),up} end,
	lists:foreach(Sender,Lifts),
	Waits = [reciever(X) || X <- Lifts],
	selectBest(Waits,{}),		
	% You fill in here: send a request message to all the lifts, 
	% gather all the responses, choose the best one, send an accept
	% to that lift and a reject to all the others.
        State
	;
floor(down, {N, Lifts}=State) ->
	Sender = fun(E) -> E ! {request, N, self(),down} end,
	lists:foreach(Sender,Lifts),
	Waits = [reciever(X) || X <- Lifts],
	selectBest(Waits,{}),		
	% You fill in here: consider, whether this needs to be different
	% code than the up code. (Probably not, so write a function
	% that can handle either.)
        State
	;

floor(arriveUp, State) -> State;
floor(arriveDown, State) -> State.


% Choose the best {Lift, Time} from a list of such.
%selectBest([], {Lift, Time}=Best) -> Lift ! accept, Best;
%selectBest([{Lift, Time}|Rest], {BLift, BTime}=Best) when Time<Best -> BLift! reject, selectBest(Rest, {Lift, Time});
%selectBest([{Lift, Time}|Rest], Best) -> Lift ! reject, selectBest(Rest, Best);

selectBest([], {Lift, Time}) -> Lift ! accept;
selectBest([{Lift, Time}|Rest], {BLift,Btime}) when Time==Btime -> Lift! reject, selectBest(Rest,{BLift,Btime});
selectBest([{Lift, Time}|Rest], {BLift,Btime}) when Time>Btime -> Lift! reject, selectBest(Rest,{BLift,Btime});
selectBest([{Lift, Time}|Rest], {BLift,Btime}) when Time<Btime -> BLift! reject, selectBest(Rest,{Lift,Time});
selectBest([{Lift, Time}|Rest], {}) -> selectBest(Rest,{Lift,Time}).










