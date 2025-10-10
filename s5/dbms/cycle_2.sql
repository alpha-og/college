-- data inserted using seed.sql

INSERT INTO staff (stffirstname, stflastname, stfstreetadress, stfcity, stfstate, stfzipcode, stfareacode, stfphonenumber, joiningdate, salary, position) VALUES
    ('Meera', 'Warrier', '99 Street', 'Palakkad', 'Kerala', 681537, 471, '9847144854', '2018-08-04', 4000, 'Lecturer');
SELECT * FROM staff;

INSERT INTO faculty (staffid, title, status, tenured) VALUES (1, 'Prof.', 'Part-time', '2019-08-05');
SELECT * FROM faculty;

INSERT INTO categories (categorydescription, departmentid) VALUES ('Computer Science', 101);
SELECT * FROM categories;

INSERT INTO subjects (categoryid, subjectcode, subjectname) VALUES (1, 101, 'Digital Logic Design');
SELECT * FROM subjects;

INSERT INTO faculty_subjects (staffid, subjectid, proficiencyrating) VALUES (1, 1, 9);
SELECT * FROM faculty_subjects;

INSERT INTO buildings (buildingname, numberoffloorts) VALUES ('Computer Science Block', 4);
SELECT * FROM buildings;

INSERT INTO classrooms (buildingcode, phoneavailable) VALUES (1, FALSE);
SELECT * FROM classrooms;

INSERT INTO classes (subjectid, classroomid, starttime, duration) VALUES (1, 1, '08:00:00', 30);
SELECT * FROM classes;

INSERT INTO faculty_classes (staffid, classid) VALUES (1, 1);
SELECT * FROM faculty_classes;

INSERT INTO students (studfirstname, studlastname, studstreetadress, studcity, studstate, studzipcode, studareacode, studphonenumber) VALUES ('Arjun', 'Yadav', '19 Street', 'Lucknow', 'Uttar Pradesh', 681537, 581, '9588840556');
SELECT * FROM students;

INSERT INTO student_class_status (classdescription) VALUES ('Enrolled');
SELECT * FROM student_class_status;

INSERT INTO student_schedules (classid, studentid, classstatus, grade) VALUES (1, 1, 1, 68);
SELECT * FROM student_schedules;

INSERT INTO faculty_categories (staffid, categoryid) VALUES (1, 1);
SELECT * FROM faculty_categories;

---

SELECT * FROM staff, faculty WHERE staff.staffid = faculty.staffid AND EXTRACT(ISOYEAR FROM DATE (tenured)) - EXTRACT(ISOYEAR FROM DATE (joiningdate)) > 5;

SELECT staff.staffid, (tenured - CURRENT_DATE)/365 as "Remaining Tenure", tenured FROM staff, faculty WHERE staff.staffid = faculty.staffid;

SELECT * FROM staff WHERE salary BETWEEN 10000 AND 50000;

SELECT position, COUNT(*) FROM staff GROUP BY position;

SELECT stfareacode, COUNT(*) FROM staff GROUP BY stfareacode;
