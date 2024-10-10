# BNF
```<program> ::= <line> | <line> "\n" <program>
<line> ::= <lineid> <whitespace> <eofdef> <whitespace> <goto> | <lineid> <whitespace> <assignment> <whitespace> <goto> | <lineid> <whitespace> <loop> <whitespace> <goto> | <lineid> <whitespace> <if> <whitespace> <goto> | <lineid> <whitespace> <nif> <whitespace> <goto> | <lineid> <whitespace> <output> <whitespace> <goto>
<eofdef> ::= <classification> <whitespace> <lineid>
<loop> ::= <classification> <whitespace> <lineid> <whitespace> <condition> 
<if> ::= <classification> <whitespace> <lineid> <whitespace> <condition> 
<nif> ::= <classification> <whitespace> <lineid> <whitespace> <condition> 
<assignment> ::= <classification> <whitespace> <variable> <whitespace> <classification> <whitespace> <number> <whitespace> 
<output> ::= "print" <whitespace> <number> 

<lineid> ::= <number>
<goto> ::= <classification> <whitespace> <number>

<classification> ::= <digit> <digit> <digit> <digit> "!"

<condition> ::= <number> <boperator> <number>
<expression> ::= <number> | <expression> <operator> <expression>

<variable> ::= <number>
<number> ::= <letter> <digit> <number> | <digit> | <digit> <number> | <letter> <digit>

<whitespace> ::= " " <whitespace> | " "

<boperator> ::= "==" | ">" | "<" | ">=" | "<=" | "!="
<operator> ::= "+" | "-" | "*" | "/" | "^"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter> ::= "b" | "d"
