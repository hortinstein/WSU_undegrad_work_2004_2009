-module(lift).
-export([newLift/1]).

% Code for the lift agents. Things to think about:
% Challenge: does the process always have sufficient information
% e.g. about the floor agents so it can send the messages it needs to send.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This is the function of the list process where compute a request from a floor
%
%			FLOOR ------> Request --------> LIFT (Compute Wait Time)
%	 (find best bid)FLOOR <------   Bid   <-------- LIFT 
%			FLOOR ------> Reply   --------> LIFT (Stay with same list
%							      or compute new based
%							      based on reply)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
liftProcess({request, FloorNum, FloorAgent, Direction}, {Now, Stoplist}) ->
    	FloorAgent ! {propose,self(),liftUtils:waitTime(Stoplist,Now, Direction, FloorNum)},%sending the bid than waiting for the accept/reject atoms
	receive
		accept -> NewStoplist = liftUtils:insert(Stoplist,Now, Direction, FloorNum), % accepted so computing new list
    			  {Now, NewStoplist};
		reject -> {Now, Stoplist}%reject so it keeps the old list
	end;

% stop messages are received from the buttons inside the lift
% for our simulation they will be sent directly from the command line to the lift process
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This is the function of the list process where a cabin requests a stop (comes from command line)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

liftProcess({stop, FloorNum}, {Now, Stoplist}) ->
 	NewStoplist = liftUtils:stopAt(Stoplist,Now,FloorNum), % getting the new stoplist
	{Now, NewStoplist}%resetting state
;
% arrived messages come from the Cabin agent that runs the lift cabin up and 
% down in its shaft. The lift agent should respond with an up, down, stop or wait message
% depending on what the lift needs to do next. Send stop if the lift should stop on this floor,
% send wait if the lift has nothing to do.
%liftProcess({Cabin, arrived, FloorNum}, {Now, Stoplist}) -> 
    % for demonstration purposes the following controller is included so the GUI does something interesting
    % in the absence of actual control logic. Replace it with your own controller logic.
    % Note that the state for this controller is just an atom -- yours will really use a
    % list as the value of Stoplist.
    % Note also that you can have a different type of state if you need it -- the
    % generic agent code that is calling this is perfectly happy to manage whatever
    % kind of state you specify provided you use it consistently -- i.e. pass it as the
    % initial state and return it from each possible action of this function.
%    case {FloorNum, Stoplist} of
%	{FloorNum, stopUp} -> Cabin ! {self(), stop}, {FloorNum, up};
%	{FloorNum, stopDown} -> Cabin ! {self(), stop}, {FloorNum, down};
%	{FloorNum, up} when FloorNum < 5 -> Cabin ! {self(), up}, {FloorNum, stopUp};
%	{FloorNum, _} when FloorNum == 5 -> Cabin ! {self(), down}, {FloorNum, stopDown};
%	{FloorNum, down} when FloorNum > 1 -> Cabin ! {self(), down}, {FloorNum, stopDown};
%	{FloorNum, _} when FloorNum == 1 -> Cabin ! {self(), up}, {FloorNum, stopUp}
%    end
%.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%	5 The Lift Agent
% Implement a function liftProcess(Message, State) for the lift agent which returns a new state.
% The file lift.erl already contains code fragments to give you a start.
%    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
liftProcess({Cabin, arrived, FloorNum}, {Now, Stoplist}) -> 
    case {FloorNum, Stoplist} of
	{_,[]} -> Cabin ! {self(), wait}, {FloorNum,[]};%if the stoplist is empty dont even move 	
	{FloorNum, [H|T]} -> 
		if
			H == FloorNum-> Cabin ! {self(), stop},{FloorNum,T};
			H < FloorNum -> Cabin ! {self(), down},{FloorNum,Stoplist};
			H > FloorNum -> Cabin ! {self(), up},{FloorNum,Stoplist}
		end
    end.

% Create a new lift agent with an empty stop list and located on Floor 1.
% Takes lift number as parameter but not used.
newLift(_N) ->
     agent:newAgent(fun liftProcess/2,  {1, []}).
