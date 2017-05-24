%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%THIS MODULE IS COMPLETE%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


-module(gui).
-export([newControl/0]).

% This cabin module is where the simulation work is done and the
% GUI is managed. This version only displays the lift cabins, showing them
% as yellow when the doors are closed and blue when the doors are open.

% To use: call newGui, which sets up the window for the GUI with the background
% information and returns a function (the fun at the end of newGui) that can 
% be used to create each of the rectangles representing the lifts as well as 
% process to manage that cabin.



-define(WaitTime, 1).
-define(StopTime, 5).
-define(Delta, 5).
-define(StepTime, 0.05).

-define(WidthLift, 80).
-define(HeightFloor, 100).
-define(Gap, 8).
-define(TextSize, 32).

-define(NormalColor, yellow).
-define(StopColor, blue).

% Call once to create the window layout.
newControl() ->
	{[L1, L2, L3], [F1, F2, F3, F4, F5]} = simulation:newScenario(3,5),
    	Width = 500, 
    	Height = 50,
    	Win = gs:window(gs:start(), [{width, Width+?TextSize},
			             {height, Height+?TextSize},
				     {bg, white},
				     {title, "Lift Controller"}]),
	%floor controls up	
	gs:create(button, {F1,up}, Win, [{label, {text, "F1 up"}}, {x, 0}]),    	    	
	gs:create(button, {F2,up}, Win, [{label, {text, "F2 up"}}, {x, 100}]),
    	gs:create(button, {F3,up}, Win, [{label, {text, "F3 up"}}, {x, 200}]),
    	gs:create(button, {F4,up}, Win, [{label, {text, "F4 up"}}, {x, 300}]),
    	gs:create(button, {F5,up}, Win, [{label, {text, "F5 up"}}, {x, 400}]),
    	
    gs:config(Win, {map, true}),
    % return a function to create new cabin processes and their images
    loop().

loop() ->
    receive
        {gs, {Floor,up}, click, _, _} ->
            Floor ! up,
	    loop();
	{gs, {Floor,down}, click, _, _} ->
            Floor ! down,
	    loop()
    end.
    

