1.

```
Structure Size {
    rows,
    columns
}
```

2.

```
Structure Position{
    row,
    column
}
```

3.

```
Structure MatrixElement {
    position // Position of element in the matrix (row,column)
    value // valule of element
    next // pointer to next element
}
```

4.

```
Structure Matrix {
    size // size of the matrix (rows, columns)
    elements =// pointer to head of linked list of elements
}
```

5.

```
FUNCTION get_tail(current_element)
    IF current_element->next == NULL THEN
        RETURN current_element
    ELSE
        RETURN get_tail(current_element->next)
    END IF
```

6.

```
FUNCTION create_matrix_element(matrix, position, value)
    MatrixElement * matrix_element = new (MatrixElement)
    matrix_element->next = NULL;
    matrix_element->position = position;
    matrix_element->value = value;
    IF matrix->elements == NULL THEN
        matrix->elements = matrix_element
    ELSE
        MatrixElement * tail = get_tail(matrix->elements)
        tail->next = matrix_element
    END IF
```

7.

```
FUNCTION create_matrix(size)
    Matrix * matrix = new (Matrix)
    matrix->size = size
    matrix->elements = NULL
    RETURN matrix
```

8.

```
FUNCTION read_size(){
    Size size = {.columns = 0, .rows = 0}
    OUTPUT "Matrix size (NxM): "
    INPUT size.rows, size.columns
    RETURN size
}
```

9.

```
FUNCTION read_elements(matrix)
    FOR i=0,1...matrix->size.rows DO
        FOR j=0,1...matrix-size.columns DO
            INPUT element
            IF element !=0 THEN
                Position position = {.row = row, .column = column}
                create_matrix_element(matrix, position, element)
            END IF
        END FOR
    END FOR
```

10.

```
FUNCTION display_matrix_elements(current_element)
    OUTPUT "("+current_element->value+"("current_element->position.row+","+current_element->position.column")), "
    IF current_element->next == NULL THEN
        RETURN
    ELSE
        RETURN display_matrix_elements(current_element->next)
    END IF
```

11.

```
FUNCTION display_matrix_in_tuple_form(matrix)
    OUTPUT "["
    display_matrix_elements(matrix)
    OUTPUT "]"
```

12.

```
FUNCTION transpose_matrix_elements(current_element)
    Position new_position = {.row=current_element->position.column,.column=current_element->position.row}
    current_element->position = new_position
    IF current_element->next == NULL THEN
RETURN
    ELSE
        RETURN transpose_matrix_elements(current_element->next)
    END IF
```

13.

```
FUNCTION transpose_matrix(matrix)
    transpose_matrix_elements(matrix->elements)
    Size size = {.rows=matrix->size.rows, .columns=matrix->size.columns}
```

14.

```
FUNCTION search_matrix_elements(current_element, query)
    IF current_element->position.row -- query.row && current_element->position.column == query.column THEN
        RETURN current_element
    END IF
    IF current_element->next == NULL THEN
        RETURN current_element
    ELSE
        RETURN search_matrix_elements(current_element->next, query)
    END IF
```

15.

```
FUNCTION traverse_and_add_elements(result, result_element)
    MatrixElement * element = search_matrix_elements(result_element,matrixB_element->position)
    IF element->position.row == matrixB_element->position.row && element->position.column == matrixB_element->position.column THEN
        element->value += matrixB_element->value
    ELSE
    create_matrix_element(result, matrixB_element->position,
                          matrixB_element->value)
    END IF
    IF matrixB_element->next == NULL
        RETURN
    END IF
    RETURN traverse_and_add_elements(result, result_element,
                                   matrixB_element->next)
```

16.

```
FUNCTION add_matrix(matrixA, matrixB)
    IF matrixA->size.rows != matrixB->size.rows || matrixA->size.columns != matrixB->size.columns THEN
        OUTPUT "Incompatible dimensions! Exiting..."
        EXIT(1);
    Matrix result = *matrixA
    traverse_and_add_elements(&result, result.elements, matrixB->elements)
    RETURN result
```

17.

```
FUNCTION display_menu()
    OUTPUT "1. Show Matrices"
    OUTPUT "2. Tranpose matrix"
    OUTPUT "3. Add matrices"
    OUTPUT "4. Quit"
    OUTPUT "Choice: "
```

18.

```
FUNCTION handle_choice(matrixA, matrixB)
    INPUT choice
    IF choice == 1 THEN
        INPUT matrixNumber
        IF matrixNumber == 1 THEN
            display_matrix_in_tuple_form(matrixA)
        ELSE IF matrixNumber == 2 THEN
            display_matrix_in_tuple_form(matrixB)
    ELSE IF choice == 2 THEN
        INPUT matrixNumber
        IF matrixNumber == 1 THEN
            transpose_matrix(matrixA)
            display_matrix_in_tuple_form(matrixA)
        ELSE IF matrixNumber == 2 THEN
            transpose_matrix(matrixB)
            display_matrix_in_tuple_form(matrixB)
    ELSE IF choice == 3 THEN
        Matrix result = add_matrix(matrixA, matrixB)
        display_matrix_in_tuple_form(&result)
    ELSE IF choice == 4 THEN
        OUTPUT "Exiting..."
        EXIT(0)
    ELSE
        OUTPUT "Invalid choice!"
    END IF
```

19.

```
Matrix * matrixA = create_matrix(read_size())
read_elements(matrixA)
display_matrix_in_tuple_form(matrixA)
```

20.

```
Matrix * matrixB = create_matrix(read_size())
read_elements(matrixB)
display_matrix_in_tuple_form(matrixB)
```

21.

```
WHILE (1) DO
    display_menu()
    handle_choice(matrixA, matrixB)
END WHILE
```
