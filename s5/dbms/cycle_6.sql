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
$$ LANGUAGE plpgsql

CREATE OR REPLACE TRIGGER restrict_trigger
BEFORE DELETE OR UPDATE OR INSERT
ON students
FOR EACH ROW
  EXECUTE FUNCTION restrict()

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
$$ LANGUAGE plpgsql

CREATE OR REPLACE TRIGGER salary_restrict_trigger
BEFORE UPDATE
ON staff
FOR EACH ROW
  EXECUTE FUNCTION salary_restrict()

-- Cursors:

-- 1. Write a PL/SQL block to display the details of Staff living in a particular
-- city


-- 2. Using parameterized cursors list the name of staff who work in the same
-- department in which ‘xyz’ works
-- 3. Write a PL/SQL block to display Staff_ID and salary of two highest paid
-- staffs using cursors

