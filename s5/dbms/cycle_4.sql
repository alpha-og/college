-- 1. a) Revoke insert privilege for a user on table Students and check whether you are able to insert a row in to the table
--    b) Grant the permission to the user for inserting values in to students table and check whether insertion is possible or not
REVOKE INSERT ON students FROM s23b25;
INSERT INTO students (studfirstname, studlastname, studstreetadress, studcity, studstate, studzipcode, studareacode, studphonenumber) VALUES ('Vijay', 'Kumar', 'elm Street', 'Lucknow', 'Uttar Pradesh', 861537, 851, '5988804556');
GRANT INSERT ON students TO s23b25;


-- 2. a) Start a new transaction and insert a row into the Staff table. Commit the transaction and display the changes to the table
-- b) Start a new transaction and insert a row into the Staff table.Undo the transaction and display the changes to the table
START TRANSACTION;
INSERT INTO staff (	
	stfFirstName,	
	stfLastName,	
	stfStreetAdress,	
	stfCity,	
	stfState,	
	stfZipCode,	
	stfAreaCode,	
	stfPhoneNumber,	
	joiningdate,	
	salary,	
	position
) VALUES ('Ajay', 'Kumar', 'elm street', 'Chennai', 'Tamilnadu', 618800, 02, '1234567790', '2024-06-17', 70000, 'Professor');
COMMIT;

START TRANSACTION;
INSERT INTO staff (	
	stfFirstName,	
	stfLastName,	
	stfStreetAdress,	
	stfCity,	
	stfState,	
	stfZipCode,	
	stfAreaCode,	
	stfPhoneNumber,	
	joiningdate,	
	salary,	
	position
) VALUES	
('Ravi', 'Shankar', 'hay street', 'Chennai', 'Tamilnadu', 618800, 02, '1234567890', '2024-01-27', 40000, 'Teaching Assistant');
ROLLBACK;

-- 3. Display the staffid and title for Faculty along with staffid and position for Staff in a single table. Indicate the source of the row in the result by adding an additional column EMPLOYEE with possible values as ‘F’ (Faculties) and ‘S’ (Staff). Display all rows (Using UNION ALL)
SELECT 'F' as Source, faculty.staffid, title FROM faculty UNION ALL (SELECT 'S' as Source, staff.staffid, position FROM staff);

-- 4. Find the pass percentage of a particular subject (using grade)
SELECT 
    S.SubjectName,
    ROUND(
        100.0 * SUM(CASE WHEN SS.Grade > 30  THEN 1 ELSE 0 END) / COUNT(*), 2
    ) AS PassPercentage
FROM STUDENT_SCHEDULES SS
JOIN CLASSES C ON SS.ClassID = C.ClassID
JOIN SUBJECTS S ON C.SubjectID = S.SubjectID
WHERE S.SubjectName = 'VLSI Design'
group by s.subjectname;

-- 5. Display the number of students in each classroom on a particular building using JOINS
SELECT buildings.buildingcode, classes.classroomid, COUNT(DISTINCT student_schedules.studentid) FROM buildings JOIN classrooms ON buildings.buildingcode = classrooms.buildingcode JOIN classes ON classrooms.classroomid = classes.classroomid JOIN student_schedules ON classes.classid = student_schedules.classid GROUP BY buildings.buildingcode, classes.classroomid;

-- 6. Display the list of students and staff who have the same zip code
SELECT S1.StudFirstName, S1.StudLastName, ST1.StfFirstName, ST1.StfLastName, S1.StudZipCode
FROM STUDENTS S1
JOIN STAFF ST1 ON S1.StudZipCode = ST1.stfzipcode;

-- 7. Display the list of faculty who engage same subject (for any particular subject name)
SELECT F.StaffID, F.Title, S.SubjectName
FROM FACULTY_SUBJECTS FS
JOIN SUBJECTS S ON FS.SubjectID = S.SubjectID
JOIN FACULTY F ON FS.StaffID = F.StaffID
WHERE S.SubjectName = 'VLSI Design';

