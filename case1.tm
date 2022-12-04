; the finite set of states
#Q = {0,1,2,3,4,5,accept}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {accept}

; the number of tapes
#N = 1

; the transition functions

; State 0: start state
0 0 _ r 1
0 1 _ r 2
0 _ _ * accept

; State 1: write '0'
1 0 0 r 1
1 1 0 r 2
1 _ 0 * 3

; State 2: write '1'
2 0 1 r 1
2 1 1 r 2
2 _ 1 * 3

; State 3: choose
3 1 _ l 4
3 0 _ l 5


; State 4: carry '1'
4 0 0 l 4
4 1 1 l 4
4 _ 1 * accept


; State 5: carry '0'
5 0 0 l 5
5 1 1 l 5
5 _ 0 * accept

