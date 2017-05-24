(* mlfunctions.sml
 * Alex Hortin
 * 10732085
 * 10/22/2007
 * CPTS355
 * containsl; in_list, intersection, filter, quicksort, Practice with datatypes, treeToString, perms
 *)
load "Int";

(* *************************************************** *)
(* * in_list 5% ************************************** *)
(* *************************************************** *)


(* 
	*	in_list
	*	This function determines whether or not a value is in a list
	*	Parameter:	Tuple
				1)  item to search for
				2)	list of items of same time as argument 1
	*	Return:		Boolean
				1)	a boolean value whether or not it is part of the list
 *)
fun in_list(x,[]) = 				false
	|   in_list(x,b::y) = 			if x=b then true else in_list(x,y);


(* *************************************************** *)
(* * intersection 10%********************************* *)
(* *************************************************** *)


(* 
	*	intersection
	*	This function determines common members between 2 lists of values
	*	Parameter:	Tuple
				1)  a list
				2)	a list
	*	Return:		List
				1)	list of the intersected values
 *)
fun intersection([],[]) = 			[]
	|	intersection(x,[]) = 		[]
	|	intersection([],y) = 		[]	
	|	intersection(int::x,y) = 	if ( in_list(int,y) andalso ( not ( in_list(int,x)) ) ) then int::(intersection(x,y)) else intersection(x,y); 


(* *************************************************** *)
(* * filter 10%*************************************** *)
(* *************************************************** *)


(* 
	*	filter
	*	This function generates a list of items in a list that satisfy a predicate
	*	Parameter:	Predicate and a List
				1)  predicate to test values
				2)	a list
	*	Return:		List
				1)	list of the values that satisfy the predicate
 *) 
fun filter pred l = let
	fun loop ([], l) = rev l
	|	loop (x::r, l) = if ( pred x ) then loop(r, x::l) else loop(r,l);          
	in
		loop (l, [])
	end


(* *************************************************** *)
(* * quicksort 20%************************************ *)
(* *************************************************** *)


(* 
	*	partition
	*	This function is a helper to quicksort that partitions a list into two halves based on a boolean comparitor
	*	Parameter:	Predicate and a List
				1)  predicate to test values
				2)	a list to partition
	*	Return:		List
				1)	the list will be partitioned by the predicate
 *)
fun partition pred l = let
	fun loop ([],trueList,falseList) = (rev trueList, rev falseList)
	|	loop (h::t,trueList,falseList) = if pred h then loop(t, h::trueList, falseList) else loop(t, trueList, h::falseList)
    in 
		loop (l,[],[]) 
	end


(* 
	*	quicksort
	*	This function sorts a list of parameters based on a given predicate it used the helper function partition
	*	Parameter:	Predicate and a List
				1)  predicate to test values
				2)	a list to sort
	*	Return:		List
				1)	the list will be sorted by the predicate
 *)
fun quicksort comp l = let
	fun sort [] = []
	|	sort (x::xs) = let 
			val (left, right) = partition (fn y => comp (y, x)) xs ;
		in
			sort left @ x :: sort right
		end 	
	in
		sort l
	end

(* *************************************************** *)
(* * Practice with datatypes 20%********************** *)
(* *************************************************** *)

(*
	*	either
	*	datatype containing values of string or int
	*	for use in eitherTree
*)
datatype either = STRING of string | INT of int;


(*
	*	eitherTree
	*	datatype containing values of string or int
	*	for use in eitherTree
*)
datatype eitherTree = LEAF of either | BRANCH of eitherTree * eitherTree	

(* 
	*	eitherSearch
	*	This function recursively searchs a binary tree for a value
	*	Parameter:	tree value
				1)  a value to search for
				2)	a tree to search in
	*	Return:		bool
				1)	true or false based on whether or not the value is there.
 *)
fun eitherSearch (BRANCH (left,right)) p = (eitherSearch left p) orelse (eitherSearch right p)
	|	eitherSearch (LEAF i ) p = (i = INT(p))  

(* 
	*	eitherTest
	*	This function is a helper mainly for testing that:     
		* constructs an eitherTree with at least 5 int-containing leaves, at least 5 string-containing leaves, and at least 4 levels;
	    * searches the tree using your eitherSearch function for a value that is present in the tree;
	    * and, searches the tree using your eitherSearch function for a value that is notpresent in the tree. 			
													
															node1
														/			\
													node2			node3
												  /		\			/	  \
											node4		node5	node6	  node7
											/	\		/	\	/	\	  /	   \
										node8	node9	a	b	c	1	 2		node10
										/	\	/	\							/	\
										6	d	3	4							5	node11
																					/	\
																					e	f
	*	Parameter:	N/A
	*	Return:		N/A
*)
fun eitherTest () = let
	val L1a = LEAF(STRING( "a"))
	val L1b = LEAF(STRING( "b"))
	val L1c = LEAF(STRING( "c"))
	val L1d = LEAF(STRING( "d"))
	val L1e = LEAF(STRING( "e"))
	val L1f = LEAF(STRING( "f"))
	val iL1a = LEAF(INT 1)
	val iL1b = LEAF(INT 2)
	val iL1c = LEAF(INT 3)
	val iL1d = LEAF(INT 4)
	val iL1e = LEAF(INT 5)
	val iL1f = LEAF(INT 6) 
	val node11 = BRANCH(L1e,L1f) ;
	val node10 = BRANCH(iL1e,node11);
	val node9 = BRANCH(iL1c,iL1d);
 	val node8 = BRANCH(iL1f,L1d);
	val node7 = BRANCH(iL1b,node10);
	val node6 = BRANCH(L1c,iL1a);
	val node5 = BRANCH(L1a,L1b);
	val node4 = BRANCH(node8,node9);
	val node3 = BRANCH(node6,node7);
	val node2 = BRANCH(node4,node5);
	val node1 = BRANCH( node2 , node3 ); 
	val res = 	eitherSearch node1 2;
	val res2 =	eitherSearch node1 9;	
	in
		print "\n Test complete 2: true, 9:false \n "
	end

	
(* *************************************************** *)
(* * treeToString 20%********************************* *)
(* *************************************************** *)

(*
	*	Tree
	*	polymorphic datatype used to build a tre
	*	for use use in treeToString
*)
datatype 'a Tree = LEAF of 'a | NODE of ('a Tree) list

(* 
	*	treeToString
	*	This function recursively prints out a tree in a string format
	*	Parameter:	a tree
				1)  a tree to search through and print out data
	*	Return:		a string
				1)	a string that represents the data of the tree
 *)

fun treeToString pfun t = let
	fun loop (NODE (x::xs)) =   treeToString pfun(x) ^ loop(NODE xs)  
	|	loop (LEAF l) = pfun(l)
	|	loop (NODE []) = ")"	
	in
		"(" ^ loop t
	end  



(* *************************************************** *)
(* * perms 15%**************************************** *)
(* *************************************************** *)


(* 
	*	perms
	*	This function is given a list and returns a list of lists being one of the permutations of the original list
	*	Parameter:	List
				1)  list to permutate
	*	Return:		List of Lists
				1)	a list of all the permutations of that original list 
 *)
fun perms [] = [[]]
	|	perms l = let
		fun cycle _ [] = []
		|	cycle needtocycle (x::xs) = (x,needtocycle@xs) :: (cycle (needtocycle@[x]) xs); (* This function cycles the head all the way to the tail *)
		fun cons a b = a::b; (* Function for attaching the new perumatations *)
		fun attachToPerms (head, otherPerms) = map (cons head) (perms otherPerms)
		fun buildList [] = []
		| 	buildList (x::xs) = x @ (buildList xs);
	in
		buildList (map attachToPerms (cycle [] l))
	end; 









 

