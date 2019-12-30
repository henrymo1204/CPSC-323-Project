# CPSC 323 Project

Build this program using the concepts I learned in CPSC 323 Compilers and Languages. First, I used Finite State Machine for Lexical Analyzer. Then, I used a table driven predictive parser for Syntax Analyzer. Lastly, I used the machine codes provided by the professor for Semantic Analyzer

# Finite State Machine
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



# Restrictions:
        This program can't identify single letter identifers
        There must be space between each lexeme
        This program can only translate if else statement, it cannot translate if statement
        All the loops must be in single line format
