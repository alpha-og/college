-- 1. Create a view from faculty, staff and student relation to display faculty name,
-- classid, subject name based on schedule given.
CREATE VIEW view_faculty AS
  SELECT staff.stffirstname || ' ' || staff.stfLastName, faculty_classes.classid, subjects.subjectname
  FROM faculty
  JOIN staff ON faculty.staffid = staff.staffid
  JOIN faculty_classes ON faculty.staffid = faculty_classes.staffid
  JOIN faculty_subjects ON faculty.staffid = faculty_subjects.staffid
  JOIN subjects ON faculty_subjects.subjectid = subjects.subjectid;

-- 2. Use assert statement to check whether Classroom table has at least 1 data
DO $$
DECLARE
  count NUMERIC;
BEGIN
  SELECT count(*) INTO count FROM classrooms;
  ASSERT count > 0, 'Classrooms table is empty';
END $$;

-- 3. Write a PL/SQL block to do the following:
-- a. Using control structures, display the list of faculties who have been hired
-- between two dates
-- b. Using CASE statement, satisfy the following conditions
-- accepting Staff ID as input:
-- i. Case 1: if salary < 5000, give 50% increment
-- ii. Case 2: if salary between 5000 and 10000, give 10% increment 
-- iii. Case 3: if salary > 10000, display a message ‘No Increment’ 
-- c. Read the Faculty table row by row using WHILE loop and display the last name of
-- the faculty (Example: ‘Last Name: Antony’)

DO $$
DECLARE 
  v_start DATE:='2020-01-01';
  v_end DATE:='2022-12-31';
  rec RECORD;
BEGIN
  FOR rec IN SELECT stffirstname ||' '|| stflastname AS faculty_name
    FROM staff
    WHERE joiningdate BETWEEN v_start AND v_end
    loop raise notice 'Faculty:%',rec.faculty_name;
  END loop;
END $$;

DO $$
DECLARE 
  v_staffid int:=13;
  v_salary NUMERIC;
BEGIN
  SELECT salary INTO v_salary
  FROM staff 
  WHERE staffid=v_staffid;
  CASE WHEN v_salary<5000 THEN
    UPDATE staff
    SET salary=salary*1.5
    WHERE staffid=v_staffid;
    RAISE NOTICE 'salary incremented by 50%%';
    WHEN v_salary BETWEEN 5000 AND 10000 THEN
    UPDATE staff
    SET salary=salary*1.1
    WHERE staffid=v_staffid;
    RAISE NOTICE 'salary incremented by 10%%';
    ELSE raise notice 'no increment';
    END CASE;
END $$;

DO $$
DECLARE 
rec RECORD;
cur CURSOR FOR SELECT stflastname FROM faculty f
JOIN staff s ON f.staffid=s.staffid;
BEGIN
  OPEN cur;
  FETCH cur INTO rec;
  WHILE FOUND LOOP
    RAISE NOTICE 'Last Name: %', rec.stflastname;
    FETCH cur INTO rec;
  END LOOP;
  CLOSE cur;
END $$;


