; the finite set of states
#Q = {0,1,2,3,4,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject1,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1}

; the complete set of tape symbols
#G = {1,_}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2

; the transition functions

; State 0: start state
0 1_ 11 rr 1
0 __ __ ** accept

; State 1: check end
1 __ __ ll accept
1 1_ 1_ ll 2

; State 2: move n steps to left
2 11 11 rl 2
2 1_ 1_ *r 3
2 _1 _1 l* reject
2 __ __ l* reject

; State 3: move n steps to right
3 11 11 rr 3
3 1_ 11 rr 4
3 _1 _1 l* reject
3 __ __ l* reject


; State 4: move one step to right
4 1_ 1_ r* 1
4 __ __ l* reject


; State accept
accept 1* _* l* accept
accept _* _* r* accept1
accept1 ** t* r* accept2
accept2 ** r* r* accept3
accept3 ** u* r* accept4
accept4 ** e* ** halt_accept

; State reject
reject 1* _* l* reject
reject _* _* r* reject1
reject1 ** f* r* reject2
reject2 ** a* r* reject3
reject3 ** l* r* reject4
reject4 ** s* r* reject5
reject5 ** e* ** halt_reject



