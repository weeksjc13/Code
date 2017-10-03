% name: Josh Weeks
% date: 11/15/16
% tabs: none

% There are three cannibals and three missionaries on one bank of a river. They want to get to the 
% other side. There is a rowboat, but it can only hold one or two people at a time.

% The boat will not go across the river by itself. It must be rowed. Either a missionary a cannibal
% can row the boat, but if it ever happens that cannibals outnumber missionaries on either bank of 
% the river, then the cannibals will eat the missionaries on that bank. (Note that it is okay for
% there to be some positive number of cannibals and no missionaries on a bank, since then there are 
% no missionaries to be eaten.) Someone who is in the boat on a given bank is considered to be on that 
% bank, so a missionary cannot hide in the boat.

% The problem is to develop a plan for getting everybody across the river without anybody being eaten. 





% predicate follows(S, T) is true if state T can immediately follow state S in the sequence of states

% KEY (reference for coder)
% MissionariesLeft - mercenaries on left bank
% MissionariesRight - mercenaries on right bank
% m - mercenary that is taking the boat
% CannibalsLeft - cannibals on left bank
% CannibalsRight - cannibals on right bank
% c - cannibal that is taking the boat



% A single missionary taking the boat from right to left.

follows(state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m | MissionariesRight], CannibalsRight, boat)),
        state(bank([m | MissionariesLeft], CannibalsLeft, boat), bank(MissionariesRight, CannibalsRight, noboat))).



% A single missionary taking the boat from left to right.

follows(state(bank([m | MissionariesLeft], CannibalsLeft, boat), bank(MissionariesRight, CannibalsRight, noboat)),
        state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m | MissionariesRight], CannibalsRight, boat))).



% A single cannibal taking the boat from right to left.

follows(state(bank(MissionariesLeft, CannibalsLeft, noboat), bank(MissionariesRight, [c | CannibalsRight], boat)),
        state(bank(MissionariesLeft, [c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat))).



% A single cannibal taking the boat from left to right.

follows(state(bank(MissionariesLeft, [c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat)),
        state(bank(MissionariesLeft, CannibalsLeft, noboat), bank(MissionariesRight, [c | CannibalsRight], boat))). 



% One missionary and one cannibal taking the boat from right to left.

follows(state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m | MissionariesRight], [c | CannibalsRight], boat)),
        state(bank([m | MissionariesLeft], [c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat))).



% One missionary and one cannibal taking the boat from left to right.

follows(state(bank([m | MissionariesLeft], [c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat)),
        state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m | MissionariesRight], [c | CannibalsRight], boat))).



% Two missionaries taking the boat from right to left.

follows(state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m, m | MissionariesRight], CannibalsRight, boat)),
        state(bank([m, m | MissionariesLeft], CannibalsLeft, boat), bank(MissionariesRight, CannibalsRight, noboat))).



% Two missionaries taking the boat from left to right.

follows(state(bank([m, m | MissionariesLeft], CannibalsLeft, boat), bank(MissionariesRight, CannibalsRight, noboat)),
        state(bank(MissionariesLeft, CannibalsLeft, noboat), bank([m, m | MissionariesRight], CannibalsRight, boat))).



% Two cannibals taking the boat from right to left.

follows(state(bank(MissionariesLeft, CannibalsLeft, noboat), bank(MissionariesRight, [c, c | CannibalsRight], boat)),
        state(bank(MissionariesLeft, [c, c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat))).



% Two cannibals taking the boat from left to right.

follows(state(bank(MissionariesLeft, [c, c | CannibalsLeft], boat), bank(MissionariesRight, CannibalsRight, noboat)),
        state(bank(MissionariesLeft, CannibalsLeft, noboat), bank(MissionariesRight, [c, c | CannibalsRight], boat))).



% admissableBank(M, C) checks to see if the banks state will not lead to the cannibals eating
% the mercenaries

admissibleBank(M, _) :- length(M, 0), !.
  % the length of list M (mercenaries) is less than the length of list C (cannibals)
admissibleBank(M, C) :- length(M, X), length(C, Y), not(X<Y). 



% admissible(S) is true if S is admissible state. An admissible state is one where 
% no missionary is being eaten on either bank of the river.

admissible(state(bank(MissionariesLeft, CannibalsLeft, _), bank(MissionariesRight, CannibalsRight, _))) :-
  admissibleBank(MissionariesLeft, CannibalsLeft),
  admissibleBank(MissionariesRight, CannibalsRight).



% validState(CurrentSolution, PossibleNewSolution) is true when PossibleNewSolution passes as a valid solution
% with the CurrentSolutions head being the previous step in the solution

validState([CurrentState | Rest], [NewState, CurrentState | Rest]) :-
  follows(CurrentState, NewState),
  admissible(NewState),
  not(member(NewState, [CurrentState | Rest])).



% plan(X, G, L) takes a list of states X, a goal state G, and a list of states L
% and is true if L is an extension of X that begins with state G

plan([Goal | Rest], Goal, [Goal | Rest]).
plan(CurrentSolution, Goal, FullSolution) :-
  validState(CurrentSolution, PossibleNewSolution),
  plan(PossibleNewSolution, Goal, FullSolution).



% Print the solution

showSolution([]).
showSolution([state(Left, Right) | Rest]) :-
  write(Left), write('	'), write(Right), nl, showSolution(Rest).



% Runs the program with starting point input (FullBank (3 missionaries and 3 cannabals) 
% that must make it to the EmptyBank (no mercenaries or cannabals) showing each step that 
% it takes to get the solution

run :-
  EmptyBank = bank([], [], noboat),
  FullBank = bank([m, m, m], [c, c, c], boat),
  BeginningState = state(FullBank, EmptyBank),
  GoalState = state(EmptyBank, FullBank),
  plan([BeginningState], GoalState, ReversedSolution),
  reverse(ReversedSolution, RegularSolution),
  showSolution(RegularSolution),
  nl.



