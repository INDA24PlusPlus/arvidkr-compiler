# BÅBÅL
## BNF
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
<number> ::= <letter> <value> | <value>
<value> ::= <digit> <value> | <digit>

<whitespace> ::= " " <whitespace> | " "

<boperator> ::= "==" | ">" | "<" | ">=" | "<=" | "!="
<operator> ::= "+" | "-" | "*" | "/" | "^"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<letter> ::= "b" | "d"

```
## Syntax
Den börjar alltid köra på linje 1 <br>
Om EOF inte inträffar kommer den bara att köra sorterat efter linje-id <br>
<br>
<br>
fyra bitar ID -> <br> 
Integer, Operator, Set-To Operator, Boolean Operator, If Statement, NIf statement, <br>
0000!    0001!     0010!            0011!             0100!         0101! <br>
<br>
Variable,   Print,    Go-To,  Numeric Separator ( '(' och ')' )   While-Loop    End-Of-File-Line <br>
0110!       0111!,    1000!,  1001!                               1010!         1111! <br>
<br>
Go-To 0 ger nästa rad, döp ingen linje till 0 plz <br>
<br>
If statement: <br>
linje-id 0100! VARVISKAGÅOMSANT 0000! VADVISKAJÄMFÖRA (integer variable/integer/...) 0010! BOOLEAN-OPERATOR-ID VADVISKAJÄMFÖRA2 1000! LINJE-ID-VI-GÅR-TILL <br>
<br>
NIf statement: <br>
linje-id 0101! VARVISKAGÅOMSANT 0000! VADVISKAJÄMFÖRA 0010! BOOLEAN-OPERATOR-ID VADVISKAJÄMFÖRA2  1000! LINJE-ID-VI-GÅR-TILL <br>
<br>
Integer Variable assignment: <br>
linje-id 0110! VARIABLE-ID 0010! COPY/BORROW 0000! VALUE 1000! LINJE-ID-VI-GÅR-TILL <br>
<br>
EOF: <br>
linje-id 1111! LINJENSOMSKAVARAEOF 1000! LINJE-ID-VI-GÅR-TILL //Om linjen någonsin körs exitas programmet <br>
<br>
Print: <br>
linje-id 0111! VADVISKAPRINTA (integer variable/integer/...) 1000! LINJE-ID-VI-GÅR-TILL <br>
\\
While: \\
linje-id 1010! VARVISKAGÅOMFALSKT 0000! VADVISKAJÄMFÖRA 0010! BOOLEAN-OPERATOR-ID VADVISKAJÄMFÖRA2 1000! LINJE-ID-VI-GÅR-TILL\\
\\
skriv b innan integer för att hantera som bas10,  bas10 -> bas2 \\
skriv d innan integer för att få bas2 -> bas10 \\
\\
Operator: \\
0000 -> + \\
0001 -> - \\
0010 -> * \\
0011 -> / \\
0100 -> ^ \\
\\
Boolean Operator: \\
0000 -> == \\
0001 -> > \\
0010 -> < + \\
0011 -> >= \\
0100 -> <= \\
1000 -> != \\
