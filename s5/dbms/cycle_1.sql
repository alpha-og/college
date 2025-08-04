-- DDL

CREATE TABLE staff (
	staffID bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	stfFirstName text,
	stfLastName text,
	stfStreetAdress text,
	stfCity text,
	stfState text,
	stfZipCode int,
	stfAreaCode int,
	stfPhoneNumber text,
	dateHired date,
	salary bigint,
	position text
);

CREATE TABLE faculty(
	staffID bigint REFERENCES staff (staffID) UNIQUE NOT NULL,
	title text,
	status text,
	tenured date 
);

CREATE TABLE categories(
	categoryid bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	categoryDescription text,
	departmentID bigint
);

CREATE TABLE faculty_categories(
	staffID bigint REFERENCES staff (staffID),
	categoryID bigint REFERENCES categories (categoryID),
    PRIMARY KEY (staffID, categoryID)
);

CREATE TABLE subjects(
	subjectID bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	categoryID bigint REFERENCES categories (categoryID),
	subjectCode int,
	subjectName text,
	subjectDescription text
);

CREATE TABLE faculty_subjects(
	staffID bigint REFERENCES staff (staffID),
	subjectID bigint REFERENCES subjects (subjectID),
	proficiencyRating int,
    PRIMARY KEY (staffID, subjectID)
);

CREATE TABLE buildings(
	buildingCode bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	buildingName text,
	numberOfFloorts int
);

CREATE TABLE classrooms(
	classroomID bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	buildingCode bigint REFERENCES buildings (buildingCode),
	phoneAvailable text
);

CREATE TABLE classes(
	classID bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	subjectID bigint REFERENCES subjects (subjectID),
	classroomID bigint REFERENCES classrooms (classroomID),
	startTime time,
	duration int
);

CREATE TABLE faculty_classes(
	staffID bigint REFERENCES staff (staffID),
	classID bigint REFERENCES classes (classID),
    PRIMARY KEY (staffID, classID)
);

CREATE TABLE students(
	studentID bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	studFirstName text,
	studLastName text,
	studStreetAdress text,
	studCity text,
	studState text,
	studZipCode int,
	studAreaCode int,
	studPhoneNumber text
);

CREATE TABLE student_class_status(
	classStatus bigint GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	classDescription text
);

CREATE TABLE student_schedules(
	classID bigint REFERENCES classes (classID),
	studentID bigint REFERENCES students (studentID),
	classStatus bigint REFERENCES student_class_status (classStatus),
	grade int,
    PRIMARY KEY (classID, studentID)
);

ALTER TABLE staff RENAME COLUMN dateHired TO joiningDate;
ALTER TABLE subjects DROP COLUMN subjectDescription;
