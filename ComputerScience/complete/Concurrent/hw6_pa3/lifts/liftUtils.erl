-module(liftUtils).
-export([insert/4,waitTime/4,stopAt/3,count/2]).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%	2 Inserting Floors into the Stoplist
%Implement a function insert(Stoplist, Now, Dir, Floor} that returns a new stoplist. Here Stoplist
%is the current stoplist, Now is the floor where the lift agent is currently located, Dir is either up or down de-
%pending on which button has been pressed at floor Floor.
%It is important to compute a new stoplist that minimizes time until the lift arrives at the desired floor. Take the
%following possibilities into account:
%     • Floor is already contained in the stoplist.
%     • The lift is already at Floor.
%     • If the lift moves from floor A to B with A<Floor<B and Dir is up, insert between A and B.
%     • If the lift moves down from floor A to B with A>Floor>B and Dir is down, insert between A and B.
%     • Insert Floor as much to the front of the stoplist as possible while following the above rules.
%
%	For example,
%       	liftUtils:insert([], 3, up, 6).
%	returns [6], whereas
%       	liftUtils:insert([5, 7, 9, 3], 4, up, 6).
%	returns [5, 6, 7, 9, 3], and
%       	liftUtils:insert([5, 7, 9, 3], 4, down, 6).
%	returns [5, 7, 9, 6, 3].
%
%Store the function in the file liftUtils.erl.
%
%Hint. In order to test your scenario you might want to consider a simple implementation of insert first.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	Arguments				%
%Stoplist = current stoplist			%
%Now = floor where list agent is located	%
%Dir = button either up or down			%
%Floor = what floor pressed it			%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
insert([],Now,Dir,Floor) -> [Floor]; %if the list is empty cons Floor onto the list
insert(Stoplist, Now, Dir, Floor) 
	when Now==Floor -> Stoplist; %if the lift is already at the floor return stoplst 
insert([HD | [FW | TL] ] , Now, Dir, Floor) 
	when HD==Floor -> [HD] ++ [FW] ++ TL; %recursively calls in an attempt to find a properspace for an up press
insert([HD | [FW | TL] ] , Now, Dir, Floor) 
	when HD<Floor,Floor<FW ,Dir==up -> [HD] ++ [Floor] ++ [FW] ++ TL; %recursively calls in an attempt to find a properspace for an up press
insert([HD | [FW | TL] ] , Now, Dir, Floor) 
	when HD>Floor,Floor>FW ,Dir==down -> [HD] ++ [Floor] ++ [FW] ++ TL;%recursively calls in an attempt to find a properspace for an up press  
insert([Head|Tail], Now, Dir, Floor) -> [Head]++insert(Tail,Now,Dir,Floor).%neither of the other conditions were met so this is called

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%
%	3 Computing the Waittime
%
% Implement a function waitTime(Stoplist, Now, Dir, Floor} that returns the waittime before a
% request can be served. Here Stoplist is the current stoplist, Now is where the lift is currently located, Dir
% is either up or down depending on which button has been pressed at floor Floor.
% As mentioned above, stopping the lift takes five time units whereas moving the lift by one floor takes one time
% unit. The waittime must be computed with the same rules as for insertion into the stoplist (do NOT duplicate
% the code!).
%
% 	For example,
%       	liftUtils:waitTime([5, 7, 9, 3], 4, up, 6).
% 	returns 7, and
%       	liftUtils:waitTime([5, 7, 9, 3], 4, down, 6).
% 	returns 23.
%
% Store the function in the file liftUtils.erl.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	Arguments				%
%Stoplist = current stoplist			%
%Now = floor where lift is located		%
%Dir = button either up or down			%
%Floor = what floor pressed it			%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
count([HD | [FW | TL] ],Floor)-> 
	if
		TL == [] -> 0;
		HD == Floor -> 0;
		HD < FW -> FW-HD + 5 + count([FW]++TL,Floor);
		HD > FW -> HD-FW + 5 + count([FW]++TL,Floor)
	end.
waitTime([],Now, Dir,Floor)when Floor > Now -> Floor - Now;
waitTime([],Now, Dir,Floor)when Floor < Now -> Now - Floor;
waitTime([],Now, Dir,Floor)when Floor == Now -> Now - Floor;
waitTime(Stoplist,Now, Dir,Floor)when [Floor] > [Now] -> Floor - Now;
waitTime(Stoplist,Now, Dir,Floor)when [Floor] < [Now] -> Now - Floor;
waitTime(Stoplist,Now, Dir,Floor)when [Floor] == [Now] -> Now - Floor;

waitTime(Stoplist, Now, Dir, Floor)-> 1+count(insert(Stoplist, Now, Dir, Floor),Floor).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%	4 Pressing a Lift Button
% Implement a function stopAt(Stoplist, Now, Floor) that returns a new stoplist when a button for
% Floor is pressed inside the lift. Here Stoplist is the current stoplist, and Now is the floor where the lift
% agent is currently located. Follow the same rules to insert Floor into the stoplist as for Insert.
% Store the function in the file liftUtils.erl.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	Arguments				%
%Stoplist = current stoplist			%
%Now = floor where lift is located		%
%Floor = what floor was pressed			%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
stopAt(Stoplist,Now,Floor)-> 
	if
		Stoplist == [] -> [Floor];
		Now == Floor -> Stoplist;
		Now < Floor -> insert(Stoplist,Now,up,Floor);
		Now > Floor -> insert(Stoplist,Now,down,Floor)
	end.

