# Pseudocode

1. ```
   structure Student{
        register_number // student's register number
        name // student's name
        cgpa // student's cgpa
        next // next node pointer
   }
   ```
2. ```
   FUNCTION create_student(register_number,name,cgpa,head)
        Student * student = new (Student)
        *student = {
            .register_number=register_number,
            .name=name,
            .cgpa=cgpa,
            .next=head
        }
        IF head == NULL THEN
            head = student
        ELSE
            head->next=NULL
            head = student
        END IF
        RETURN head
   }
   ```
3. ```
    FUNCTION read_student_data(filename)
        open filename as file // file handle
        DECLARE variables register_number, name, cgpa, head
        WHILE (fscanf(file,"%10c%20c%f",register_number,name,&cgpa)) DO
            head = create_student(register_number,name,cgpa)
        END WHILE
        RETURN head
   ```
4. ```
   FUNCTION swap(current)
        Student * tmp = current
        current = current->next
        tmp->next = current->next
        current->next = tmp
   ```
5. ```
   FUNCTION bubble_sort_pass(head)
        IF head->next == NULL THEN
            RETURN
        ELSE IF head->register_number > head->next->register_number THEN
            Student * tmp = head
            head = head->next
            tmp->next = head->next
            head->next = tmp
        END IF
        RETURN bubble_sort_pass(head->next)
   ```
6. ```
   FUNCTION bubble_sort(head)
       bubble_sort_pass(head)
       IF head->next == NULL THEN
           RETURN
       END IF
       RETURN bubble_sort(head->next)
   ```
7. ```
   FUNCTION linear_search(key, head)
       IF head->next == NULL THEN
           RETURN head
       ELSE IF head->key == key THEN
           RETURN head
       END IF
       RETURN linear_search(key, head->next)
   ```
8. ```
   FUNCTION display_student_list(head)
       OUTPUT head->register_number, head->name, head->cgpa
       IF head->next == null THEN
           RETURN
       RETURN display_student_list(head->next)
   ```
9. ```
   FUNCTION display_menu()
       OUTPUT "1. Show sorted students list"
       OUTPUT "2. Find student using register_number and show name and cgpa"
       OUTPUT "3. Quit"
       OUTPUT "Choice: "
   ```
10. ```
    FUNCTION handle_choice(head)
        INPUT choice
        IF choice == 1 THEN
            display_student_list(bubble_sort(head))
        ELSE IF choice == 2 THEN
            OUTPUT "Provide the register_number: "
            INPUT register_number
            Student * result = linear_search(register_number, head)
            OUTPUT result->register_number, result->name, result->cgpa
        ELSE IF choice == 3 THEN
            OUTPUT "Exiting..."
            exit(0)
        ELSE
            OUTPUT "Choose a valid option"
        RETURN
    ```
11. ```
    WHILE (1) DO
        display_menu()
        Student * head = read_student_data("example.txt")
        handle_choice(head)
    ```
