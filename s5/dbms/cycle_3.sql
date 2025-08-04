-- 1. Display the count of teachers teaching either two or three different subjects
SELECT COUNT(*) FROM faculty_subjects GROUP BY staffid HAVING COUNT(*) in (2,3);

-- 2. Display the maximum of average salary from Staff table based on their positions
SELECT MAX(avg_salary) FROM (SELECT position, AVG(salary) avg_salary FROM staff GROUP BY position) AS tmp;

-- 3. Display the minimum grade of students for each subject from each class
SELECT subjectname, classid, MIN(grade) FROM subjects, classes, student_schedules WHERE subjects.subjectid = classes.subjectid AND classes.classid = student_schedules.classid GROUP BY subjects.subjectname, classes.classid;

-- 4. Display subject name which contains character ‘a’
SELECT subjectname FROM subjects WHERE subjectname LIKE '%a%';

-- 5. Display the name of students having mobile no starting with ‘95’
SELECT studfirstname, studlastname FROM students WHERE studphonenumber LIKE '95%';

-- 6. Retrieve Class ID and maximum duration available in Classes where maximum duration is less than 45 minutes
SELECT classid, MAX(duration) FROM classes GROUP BY classid HAVING MAX(duration) < 45;

-- 7. Display the list of students based on Student ID in ascending order and Student Name in descending order, Group by Subject Name
-- incomplete solution
SELECT students.* FROM students, student_schedules, classes, subjects where students.studentid = student_schedules.studentid AND student_schedules.classid = classes.classid AND subjects.subjectid = classes.subjectid GROUP BY students.studentid ORDER BY students.studentid ASC, students.studfirstname DESC;

-- 8. Display position and average salary of staff belonging to state “Kerala” or “Tamil Nadu” where salary is more than 10000 and average salary is less than 25000
SELECT position, AVG(salary) FROM staff WHERE stfstate in ('Kerala', 'Tamil Nadu') AND salary > 10000 GROUP BY position HAVING AVG(salary) < 25000;
