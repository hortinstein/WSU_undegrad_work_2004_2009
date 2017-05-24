(* mltests.sml
 * Alex Hortin
 * 10732085
 * 10/22/2007
 * CPTS355
 * contains; test functions for all ML problems
 *)

use "mlfunctions.sml";

print "\n(* Testing for in_list *)\n";
in_list (1,[]);
in_list (1,[1,2,3]);
in_list ([1],[[1]]); 
in_list ([1],[[3],[5]]); 
in_list ("c",["b","c","z"]);
print "\n(* Testing for intersection *)\n";
intersection ([1],[1]); 
intersection ([1,2,3],[1,2]); 
intersection ([[2,3],[1,2],[2,3]], [[1],[2,3]]); 
print "\n(* Testing for filter *)\n";
filter (fn (x) => (x = 1)) [1,2,3];
filter (fn (x) => (x <= 3))[1,2,3,4]; 
print "\n(*Testing for Quicksort *)\n";
quicksort (fn (x,y) => (x <= y)) [1];
quicksort (fn (x,y) => (x <= y)) [3,2,1,2]; 
quicksort (fn (x,y) => (x >= y)) [3,2,1,2]; 
print "\n(*Testing Practice with datatypes *)\n";
eitherTest;	
print "\n(*Testing treeToString *)\n";
val L1a = LEAF "a"
val L1b = LEAF "b"
val L1c = LEAF "c"
val L2a = NODE [L1a, L1b, L1c];
val L2b = NODE [L1b, L1c, L1a];
val L3 = NODE [L2a, L2b, L1a, L1b];
val L4 = NODE [L1c, L1b, L3];
val L5 = NODE [L4];
val iL1a = LEAF 1
val iL1b = LEAF 2
val iL1c = LEAF 3
val iL2a = NODE [iL1a, iL1b, iL1c];
val iL2b = NODE [iL1b, iL1c, iL1a];
val iL3 = NODE [iL2a, iL2b, iL1a, iL1b];
val iL4 = NODE [iL1c, iL1b, iL3];
val iL5 = NODE [iL4];

treeToString String.toString L5;  
treeToString Int.toString iL5; 

print "\n(*Testing perms *)\n";
perms[1,2,3]
