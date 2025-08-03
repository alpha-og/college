CREATE TABLE IF NOT EXISTS staff(
	staffid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	stffirstname text,
	stflastname text,
	stfstreetadress text,
	stfcity text,
	stfstate text,
	stfzipcode int,
	stfareacode int,
	stfphonenumber text,
	joiningdate date,
	salary bigint,
	position text
);
CREATE TABLE IF NOT EXISTS faculty(
	staffid bigint REFERENCES staff (staffid),
	title text,
	status text,
	tenured date
);
CREATE TABLE IF NOT EXISTS categories(
	categoryid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	categorydescription text,
	departmentid bigint
);
CREATE TABLE IF NOT EXISTS faculty_categories(
	staffid bigint REFERENCES staff (staffid),
	categoryid bigint REFERENCES categories (categoryid),
	PRIMARY KEY (staffid, categoryid)
);
CREATE TABLE IF NOT EXISTS subjects(
	subjectid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	categoryid bigint REFERENCES categories (categoryid),
	subjectcode int,
	subjectname text
);
CREATE TABLE IF NOT EXISTS faculty_subjects(
	staffid bigint REFERENCES staff (staffid),
	subjectid bigint REFERENCES subjects (subjectid),
	proficiencyrating int,
	PRIMARY KEY (staffid, subjectid)
);
CREATE TABLE IF NOT EXISTS buildings(
	buildingcode bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	buildingname text,
	numberoffloorts int
);
CREATE TABLE IF NOT EXISTS classrooms(
	classroomid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	buildingcode bigint REFERENCES buildings (buildingcode),
	phoneavailable boolean
);
CREATE TABLE IF NOT EXISTS classes(
	classid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	subjectid bigint REFERENCES subjects (subjectid),
	classroomid bigint REFERENCES classrooms (classroomid),
	starttime time,
	duration int
);
CREATE TABLE IF NOT EXISTS faculty_classes(
	staffid bigint REFERENCES staff (staffid),
	classid bigint REFERENCES classes (classid),
	PRIMARY KEY (staffid, classid)
);
CREATE TABLE IF NOT EXISTS students(
	studentid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	studfirstname text,
	studlastname text,
	studstreetadress text,
	studcity text,
	studstate text,
	studzipcode int,
	studareacode int,
	studphonenumber text
);
CREATE TABLE IF NOT EXISTS student_class_status(
	classstatus bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	classdescription text
);
CREATE TABLE IF NOT EXISTS student_schedules(
	classid bigint REFERENCES classes (classid),
	studentid bigint REFERENCES students (studentid),
	classstatus bigint REFERENCES student_class_status (classstatus),
	grade int,
	PRIMARY KEY (classid, studentid)
);
INSERT INTO staff (stfFirstName, stfLastName, stfStreetAdress, stfCity, stfState, stfZipCode, stfAreaCode, stfPhoneNumber, joiningDate, salary, position) VALUES
    ('Eliza', 'Patel', '49 Road', 'Palakkad', 'Kerala', 681931, 495, '9200780963', '2019-01-25', 4000, 'Assistant Professor'),
    ('Yash', 'Zehra', '1 Lane', 'Tirupati', 'Tamil Nadu', 628361, 431, '9385970256', '2021-09-08', 8000, 'Guest Lecturer'),
    ('Bob', 'Babu', '4 Street', 'Nizamabad', 'Telangana', 501674, 870, '9509314931', '2021-04-17', 12000, 'Adjunct Professor'),
    ('Hari', 'Oberoi', '98 Lane', 'Gaya', 'Bihar', 847569, 612, '9632374341', '2019-10-18', 20000, 'Guest Lecturer'),
    ('Oscar', 'Warrier', '59 Avenue', 'Dharamshala', 'Himachal Pradesh', 171891, 189, '9123074397', '2018-04-06', 30000, 'Lab Instructor'),
    ('Om', 'Ullah', '38 Street', 'Panipat', 'Haryana', 123276, 129, '9897947650', '2017-04-29', 15000, 'Teaching Fellow'),
    ('Gita', 'Prasad', '86 Road', 'Solapur', 'Maharashtra', 432820, 240, '9425739463', '2016-10-12', 25000, 'Senior Faculty'),
    ('Lakshman', 'Chacko', '62 Road', 'Dibrugarh', 'Assam', 788278, 376, '9898574707', '2022-07-16', 18000, 'Academic Coordinator');

INSERT INTO faculty (staffID, title, status, tenured) VALUES
    (1, 'Mr.', 'Part-time', '2024-01-24'),
    (2, 'Ms.', 'Full-time', '2027-09-07'),
    (3, 'Dr.', 'Full-time', '2026-04-16'),
    (4, 'Prof.', 'Part-time', '2025-10-16'),
    (5, 'Dr.', 'Part-time', '2023-04-05'),
    (6, 'Ms.', 'Visiting', '2019-04-29');

INSERT INTO categories (categoryDescription, departmentID) VALUES
    ('Computer Science', 101),
    ('Mathematics', 102),
    ('Electronics', 103);

INSERT INTO subjects (categoryID, subjectCode, subjectName) VALUES
    (1, 101, 'Data Analysis and Algorithms'),
    (1, 102, 'Computer Graphics'),
    (2, 103, 'Calculus'),
    (2, 104, 'Linear Algebra'),
    (3, 105, 'Signal Processing'),
    (3, 106, 'Digital Electronics');

INSERT INTO faculty_subjects (staffID, subjectID, proficiencyRating) VALUES
    (1, 3, 9),
    (1, 2, 10),
    (2, 5, 8),
    (2, 4, 10),
    (3, 3, 10),
    (3, 2, 10),
    (4, 5, 9),
    (4, 4, 10),
    (5, 6, 8),
    (5, 7, 7),
    (6, 6, 7),
    (6, 7, 7);

INSERT INTO buildings (buildingName, numberOfFloorts) VALUES
    ('Computer Science Block', 4),
    ('Engineering Block', 5),
    ('Mathematics Block', 3),
    ('Laboratory Block', 2);

INSERT INTO classrooms (buildingCode, phoneAvailable) VALUES
    (1, FALSE),
    (1, TRUE),
    (2, FALSE),
    (2, TRUE),
    (3, FALSE),
    (3, TRUE),
    (4, TRUE),
    (4, FALSE);

INSERT INTO classes (subjectID, classroomID, startTime, duration) VALUES
    (3, 2, '09:30:00', 40),
    (3, 3, '11:00:00', 45),
    (4, 6, '14:00:00', 60),
    (1, 1, '11:00:00', 90),
    (3, 7, '09:30:00', 90);

INSERT INTO faculty_classes (staffID, classID) VALUES
    (1, 1),
    (1, 3),
    (2, 5),
    (2, 4),
    (3, 2),
    (3, 1),
    (4, 2),
    (4, 1),
    (5, 4),
    (6, 5),
    (6, 2);

INSERT INTO students (studFirstName, studLastName, studStreetAdress, studCity, studState, studZipCode, studAreaCode, studPhoneNumber) VALUES
    ('Priya', 'Upadhyay', '94 Colony', 'Dehradun', 'Uttarakhand', 681931, 136, '9587288736'),
    ('David', 'Tiwari', '19 Lane', 'Gurgaon', 'Haryana', 129784, 129, '9327774671'),
    ('Kavya', 'Qureshi', '26 Lane', 'Durgapur', 'West Bengal', 719521, 341, '9546861563'),
    ('Deepak', 'Kapoor', '89 Lane', 'Jalandhar', 'Punjab', 141242, 172, '9712334103'),
    ('Nina', 'Khan', '96 Colony', 'Varanasi', 'Uttar Pradesh', 226267, 542, '9206327675'),
    ('Rohit', 'Yadav', '47 Colony', 'Nainital', 'Uttarakhand', 246360, 136, '9212124648'),
    ('Bob', 'Kapoor', '35 Road', 'Gurgaon', 'Haryana', 130660, 169, '9402099104'),
    ('Nina', 'Reddy', '96 Lane', 'Asansol', 'West Bengal', 708856, 342, '9560893390'),
    ('Sana', 'Inamdar', '72 Street', 'Ludhiana', 'Punjab', 157944, 181, '9999465742'),
    ('Karen', 'Kapoor', '78 Street', 'Lucknow', 'Uttar Pradesh', 205295, 512, '9242825930');

INSERT INTO student_class_status (classDescription) VALUES
    ('Enrolled'),
    ('Completed'),
    ('Dropped'),
    ('Withdrawn');

INSERT INTO student_schedules (classID, studentID, classStatus, grade) VALUES
    (3, 1, 1, 67),
    (5, 1, 2, 88),
    (2, 1, 2, 95),
    (2, 2, 1, 85),
    (1, 2, 1, 63),
    (1, 3, 1, 69),
    (3, 3, 1, 85),
    (3, 4, 1, 73),
    (2, 5, 2, 87),
    (5, 5, 1, 65),
    (5, 6, 2, 84),
    (3, 6, 2, 68),
    (1, 7, 1, 85),
    (2, 7, 3, 49),
    (5, 8, 1, 79),
    (2, 8, 2, 84),
    (3, 9, 1, 68),
    (2, 10, 1, 85),
    (4, 10, 2, 69),
    (5, 10, 1, 79);

INSERT INTO faculty_categories (staffID, categoryID) VALUES
    (1, 1),
    (2, 1),
    (3, 2),
    (4, 2),
    (5, 3),
    (6, 1);

