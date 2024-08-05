1. 
```
   Structure Term
       coefficient // coefficient of the term
       exponent // variable exponent
```
2. 
```
   Structure Polynomial
       degree // highest power of polynomial
       terms // pointer to array of terms
```
3. 
```
    DECLARE variables polynomials, result, termsR
```
4. 
```
    Polynomial polynomials[2]
```
5.
```
    FOR i=0...1 DO
        OUTPUT "---- Polynomial "+i+" ----"
        INPUT degree
        Term terms[degree+1]
        polynomials[i].degree = degree
        polynomials[i].terms = terms
        FOR j=0,1...degree DO
            INPUT coefficient
            polynomials[i].terms[j].coefficient = coefficient
            polynomials[i].terms[j].exponent = degree-i
        END FOR
    END FOR
```
6. 
```
    Term termsR[MAX_TERMS]
```
7. 
```
    result = {
        .degree = MAX_DEGREE
        .terms = termsR
    }
```
8. 
```
    FOR i=0...1 DO
        FOR j=0,1...polynomials[i].degree DO
            FOR k=0,1...MAX_TERMS DO
                IF result.terms[k].exponent == polynomials[i].terms[j].exponent THEN
                    result.terms[k].coefficient += polynomials[i].terms[j].coefficient
                END IF
            END FOR
        END FOR
    END FOR         
```
9. 
```
    FOR i=0,1...MAX_TERMS DO
        IF result.terms[i].coefficient == 0 THEN
            CONTINUE
        END IF
        OUTPUT result.terms[i].coefficient + "x^" + result.terms[i].exponent+" + "
    END FOR
```
