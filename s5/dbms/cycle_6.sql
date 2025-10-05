-- Triggers:

-- 1. Create a trigger such that before a row is deleted from Student_Schedules
-- table, it is inserted into another table

CREATE TABLE student_schedules_archive (LIKE student_schedules INCLUDING ALL);

CREATE OR REPLACE FUNCTION archive_student_schedules()
RETURNS TRIGGER AS $$
BEGIN
  INSERT INTO student_schedules_archive
  SELECT *;
  RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER archive_student_schedules_trigger
BEFORE DELETE
ON student_schedules
FOR EACH ROW
  EXECUTE FUNCTION archive_student_schedules();

-- 2. Create a trigger on Students table in which it stops deletion and updation on
-- Sundays and allows insertion only on Fridays
CREATE OR REPLACE FUNCTION restrict()
RETURNS TRIGGER AS $$
DECLARE
  today TEXT;
BEGIN
  today := TRIM(TO_CHAR(CURRENT_DATE, 'Day'));
  IF TG_OP IN ('DELETE', 'UPDATE') AND today = 'Sunday' THEN
    RAISE EXCEPTION 'Deletion and Updation on Sundays is restricted';
  ELSIF TG_OP = 'INSERT' AND today <> 'Friday' THEN
    RAISE EXCEPTION 'Insertion is permitted only on Fridays';
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER restrict_trigger
BEFORE DELETE OR UPDATE OR INSERT
ON students
FOR EACH ROW
  EXECUTE FUNCTION restrict();

-- 3. Write a trigger on Staff table such that updation is not possible if new salary
-- is greater than old salary
CREATE OR REPLACE FUNCTION salary_restrict()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.salary > OLD.salary THEN
    RAISE EXCEPTION 'New salary cannot be greater than old salary';
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER salary_restrict_trigger
BEFORE UPDATE
ON staff
FOR EACH ROW
  EXECUTE FUNCTION salary_restrict();

-- Cursors:

-- 1. Write a PL/SQL block to display the details of Staff living in a particular
-- city
DO $$
  DECLARE
    city TEXT := 'Chennai';
    rec RECORD;
  BEGIN
    RAISE NOTICE 'Staff living in %', city;
    FOR rec IN
      SELECT * FROM staff
      WHERE stfcity = city
    LOOP
      RAISE NOTICE 'ID: %, Name: %, Salary: %, City: %', rec.staffid, rec.stffirstname || ' ' || rec.stflastname, rec.salary, rec.stfcity;
    END LOOP;
END $$;

-- 2. Using parameterized cursors list the name of staff who work in the same
-- department in which ‘xyz’ works
DO $$
  DECLARE
    dept BIGINT;
    rec RECORD;
  BEGIN
    SELECT c.departmentid INTO dept
    FROM staff s
    JOIN faculty_subjects fs ON s.staffid = fs.staffid
    JOIN subjects sub ON fs.subjectid = sub.subjectid
    JOIN categories c ON sub.categoryid = c.categoryid
    WHERE s.stffirstname = 'Yash';

    RAISE NOTICE 'Staff in the same department as Yash';

    FOR rec IN 
      SELECT s.stffirstname, s.stflastname
      FROM staff s
      JOIN faculty_subjects fs ON s.staffid = fs.staffid
      JOIN subjects sub ON fs.subjectid = sub.subjectid
      JOIN categories c ON sub.categoryid = c.categoryid
      WHERE c.departmentid = dept AND s.stffirstname <> 'Yash'
    LOOP
      RAISE NOTICE '% %', rec.stffirstname, rec.stflastname;
    END LOOP;
END $$;

-- 3. Write a PL/SQL block to display Staff_ID and salary of two highest paid
-- staffs using cursors

DO $$
  DECLARE
    rec RECORD;
    stf_cursor CURSOR FOR
      SELECT staffid, salary
      FROM staff
      ORDER BY salary DESC
      LIMIT 2;
  BEGIN
    OPEN stf_cursor;
    LOOP
      FETCH stf_cursor INTO rec;
      EXIT WHEN NOT FOUND;
      RAISE NOTICE 'StaffID: %, Salary: %', rec.staffid, rec.salary;
    END LOOP;
END $$;
