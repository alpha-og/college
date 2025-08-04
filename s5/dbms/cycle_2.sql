-- data inserted using seed.sql

SELECT * FROM staff, faculty WHERE staff.staffid = faculty.staffid AND EXTRACT(ISOYEAR FROM DATE (tenured)) - EXTRACT(ISOYEAR FROM DATE (joiningdate)) > 5;

SELECT staff.staffid, (tenured - CURRENT_DATE)/365 as "Remaining Tenure", tenured FROM staff, faculty WHERE staff.staffid = faculty.staffid;

SELECT * FROM staff WHERE salary BETWEEN 10000 AND 50000;

SELECT position, COUNT(*) FROM staff GROUP BY position;

SELECT stfareacode, COUNT(*) FROM staff GROUP BY stfareacode;
