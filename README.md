# BÅBÅL
Bättre än COBOL iallafall
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
Integer : 0000! <br>
Operator : 0001! <br>
Set-To Operator : 0010! <br>
Boolean Operator : 0011! <br>
If Statement : 0100! <br> 
NIf statement : 0101! <br>
Variable : 0110! <br>
Print : 0111! <br>
Go-To : 1000! <br>  
Numeric Separator ( '(' och ')' ) : 1001! <br>
While-Loop : 1010! <br>
End-Of-File-Line : 1111! <br>
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
<br>
While: <br>
linje-id 1010! VARVISKAGÅOMFALSKT 0000! VADVISKAJÄMFÖRA 0010! BOOLEAN-OPERATOR-ID VADVISKAJÄMFÖRA2 1000! LINJE-ID-VI-GÅR-TILL\\
<br>
skriv b innan integer för att hantera som bas10,  bas10 -> bas2 <br>
skriv d innan integer för att få bas2 -> bas10 <br>
<br>
Operator: <br>
0000 -> + <br>
0001 -> - <br>
0010 -> * <br>
0011 -> / <br>
0100 -> ^ <br>
<br>
Boolean Operator: <br>
0000 -> == <br>
0001 -> > <br>
0010 -> < + <br>
0011 -> >= <br>
0100 -> <= <br>
1000 -> != <br>

##De första 20 fibonaccitalen i BÅBÅL

```
b1  1111! b13 1000! 0
b2  0110! 00000001 0010! 0 0000! 0 1000! 0
b3  0110! 00000010 0010! 0 0000! 1 1000! 0
b4  0110! 00000100 0010! 0 0000! 0 1000! 0
b5  1010! b12 0110! 00000100 0011! 0010 0000! b20 1000! 0
b6  0110! 00000011 0010! 0 0110! 00000010 0001! 0000 0110! 00000001 1000! 0
b7  0111! 0110! 00000011 1000! 0
b8  0110! 00000001 0010! 0 0110! 00000010 1000! 0
b9  0110! 00000010 0010! 0 0110! 00000011 1000! 0
b10 0110! 00000100 0010! 0 0110! 00000100 0001! 0000 0000! 1 1000! 0
b11 1000! b5
b12 1000! 0
b13
```
