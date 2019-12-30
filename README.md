# CPSC 323 Project

Build this program using the concepts I learned in CPSC 323 Compilers and Languages. First, I used Finite State Machine for Lexical Analyzer. Then, I used a table driven predictive parser for Syntax Analyzer. Lastly, I used the machine codes provided by the professor for Semantic Analyzer

# Lexical Analyzer
State 1: Initial state

State 2: Identifier 

State 3: Space

State 4: Numbers

State 5: Float numbers

State 6: Start of comment

State 7: End of comment

M = {Σ, q, q₀, F, N}

Σ = { i, d, $, . , o, ! }

q = {1, 2, 3, 4, 5, 6, 7}

q₀ = 1

F = 1, 2, 3, 4, 5, 7

N = ![FSM](https://user-images.githubusercontent.com/48542636/71569416-cc023300-2a83-11ea-90cf-393b6d784489.png) 

![FSMDiagram](https://user-images.githubusercontent.com/48542636/71569524-8db94380-2a84-11ea-95da-57b69078ae5c.png)

# Syntax Analyzer
G = { N, T , S , R}

N = {S, A, E, E’, T, T’, F, C, R, D, TY, M}

T = {id, +, -, *, /, (, ), @, ; if, while, do, int, flow, bool, {, }, ,, <, <=, ==, >=, >}

S = S

first(S) = {id, if, while, do, int, float, bool, ε}	follow(S) = {@, }, ;}

first(A) = {id}						follow(A) = {@, }, ;}

first(E) = {(, id}					follow(E) = {;, ), <, <=, ==, >=, >, {, @, }}

first(E’) = {+, -, ε}				        follow(E’) = {;, ), <, <=, ==, >=, >, {, @, }}

first(T) = {(, id}				        follow(T) = {+, -, ;, ), <, <=, ==, >=, >, {, @, }}

first(T’) = {*, /, ε}			                follow(T’) = {+, -, ;, ), <, <=, ==, >=, >, {, @, }}

first(F) = {(, id}				        follow(F) = {*, /, +, -, ;, ), <, <=, ==, >=, >, {, @, }}

first(C) = {(}				                follow(C) = {{, @, }, ;}

first(R) = {<, <=, ==, >=, >}		                follow(R) = {{, id}

first(D) = {int, float, bool, ε}		        follow(D) = {@, }, ;}

first(TY) = {int, float, bool}		                follow(TY) = {id}

first(M) = {,, ε}				        follow(M) = {@, }, ;}

![Table](https://user-images.githubusercontent.com/48542636/71569672-96f6e000-2a85-11ea-82f3-0b99ae76bdc7.png)

# Semantic Analyzer
![Machine Code](https://user-images.githubusercontent.com/48542636/71569749-2603f800-2a86-11ea-9ea4-aad099b97b47.png)

# Restrictions:
        This program can't identify single letter identifers
        There must be space between each lexeme
        This program can only translate if else statement, it cannot translate if statement
        All the loops must be in single line format
