import random
import argparse
from datetime import date, timedelta

# Improved city-state mappings for better geographical cohesiveness
city_state_mapping = {
    'Kerala': ['Kochi', 'Thiruvananthapuram', 'Thrissur', 'Alappuzha', 'Ernakulam', 'Kozhikode', 'Kollam', 'Palakkad'],
    'Tamil Nadu': ['Chennai', 'Coimbatore', 'Madurai', 'Salem', 'Tirunelveli', 'Vellore', 'Tirupati', 'Tiruchirappalli'],
    'Karnataka': ['Bangalore', 'Mysore', 'Mangalore', 'Hubli', 'Belgaum', 'Davangere'],
    'Maharashtra': ['Mumbai', 'Pune', 'Nashik', 'Nagpur', 'Aurangabad', 'Solapur'],
    'Delhi': ['Delhi', 'New Delhi'],
    'Andhra Pradesh': ['Vijayawada', 'Guntur', 'Visakhapatnam', 'Tirupati'],
    'Telangana': ['Hyderabad', 'Warangal', 'Nizamabad'],
    'West Bengal': ['Kolkata', 'Durgapur', 'Asansol'],
    'Punjab': ['Amritsar', 'Ludhiana', 'Jalandhar'],
    'Rajasthan': ['Jaipur', 'Jodhpur', 'Udaipur', 'Kota'],
    'Uttar Pradesh': ['Lucknow', 'Kanpur', 'Agra', 'Varanasi', 'Noida', 'Ghaziabad'],
    'Bihar': ['Patna', 'Gaya', 'Muzaffarpur'],
    'Madhya Pradesh': ['Bhopal', 'Indore', 'Jabalpur'],
    'Gujarat': ['Ahmedabad', 'Surat', 'Vadodara', 'Rajkot'],
    'Haryana': ['Gurgaon', 'Faridabad', 'Panipat'],
    'Himachal Pradesh': ['Shimla', 'Dharamshala', 'Manali'],
    'Uttarakhand': ['Dehradun', 'Haridwar', 'Nainital'],
    'Assam': ['Guwahati', 'Dibrugarh', 'Silchar']
}

# Enhanced name pools with better cultural representation
first_names = [
    'Alice', 'Bob', 'Cathy', 'David', 'Eve', 'Frank', 'Grace', 'Hank',
    'Irene', 'Jack', 'Karen', 'Leo', 'Maria', 'Nina', 'Oscar', 'Paul', 'Quincy', 'Rachel',
    'Steve', 'Tina', 'Uma', 'Victor', 'Wendy', 'Xander', 'Yvonne', 'Zack',
    'Anita', 'Brian', 'Chitra', 'Deepak', 'Eliza', 'Farhan', 'Gita', 'Hari', 'Indu',
    'Jatin', 'Kavya', 'Lakshman', 'Meera', 'Nikhil', 'Om', 'Pooja', 'Rohit', 'Sana',
    'Tarun', 'Usha', 'Varun', 'Waqar', 'Yash', 'Zoya', 'Arjun', 'Priya', 'Ravi', 'Sunita'
]

last_names = [
    'Antony', 'Babu', 'Chacko', 'Dinesh', 'Elena', 'Fernandez',
    'George', 'Hussain', 'Iyer', 'Jain', 'Kapoor', 'Lal', 'Menon', 'Nair', 'Oberoi',
    'Pillai', 'Qureshi', 'Reddy', 'Sarma', 'Tiwari', 'Upadhyay', 'Verma', 'Wadhwa',
    'Xavier', 'Yadav', 'Zaman', 'Aggarwal', 'Bhatt', 'Choudhary', 'Deshmukh',
    'Eswaran', 'Fazal', 'Gupta', 'Harikrishnan', 'Inamdar', 'Joshi', 'Khan', 'Lobo',
    'Mishra', 'Naidu', 'Ojha', 'Patel', 'Quazi', 'Rana', 'Singh', 'Thakur',
    'Ullah', 'Venkatesh', 'Warrier', 'Zehra', 'Kumar', 'Sharma', 'Devi', 'Prasad'
]

# Enhanced position hierarchy for better academic structure
academic_positions = [
    'Assistant Professor', 'Associate Professor', 'Professor', 'Lecturer', 'Senior Lecturer',
    'Visiting Faculty', 'Adjunct Professor', 'Guest Lecturer', 'Teaching Assistant',
    'Research Associate', 'Head of Department', 'Dean', 'Academic Coordinator',
    'Postdoctoral Fellow', 'Instructor', 'Visiting Scholar', 'Research Scientist',
    'Lab Instructor', 'Senior Faculty', 'Assistant Lecturer', 'Junior Research Fellow',
    'Senior Research Fellow', 'Program Director', 'Teaching Fellow', 'Emeritus Professor'
]

# Enhanced subject pools with realistic academic categories
cs_subjects = [
    'Database Systems', 'Computer Networks', 'Operating Systems', 'Data Structures and Algorithms',
    'Machine Learning', 'Artificial Intelligence', 'Software Engineering', 'Computer Architecture',
    'Compiler Design', 'Digital Logic Design', 'Computer Graphics', 'Cybersecurity',
    'Web Technologies', 'Mobile Computing', 'Cloud Computing', 'Distributed Systems'
]

mathematics_subjects = [
    'Discrete Mathematics', 'Linear Algebra', 'Calculus', 'Statistics',
    'Numerical Analysis', 'Mathematical Modeling', 'Graph Theory', 'Probability Theory'
]

electronics_subjects = [
    'Digital Electronics', 'Analog Electronics', 'VLSI Design', 'Signal Processing',
    'Communication Systems', 'Microprocessors', 'Control Systems', 'Power Electronics'
]

# Academic categories with realistic department mappings
academic_categories = {
    'Computer Science': cs_subjects,
    'Mathematics': mathematics_subjects,
    'Electronics': electronics_subjects
}

# database schema (unchanged)
database_schema = {
    "staff": {
        "columns": {
            "staffid": {"type": "bigint", "primary_key": True, "identity": True},
            "stffirstname": {"type": "text"},
            "stflastname": {"type": "text"},
            "stfstreetadress": {"type": "text"},
            "stfcity": {"type": "text"},
            "stfstate": {"type": "text"},
            "stfzipcode": {"type": "int"},
            "stfareacode": {"type": "int"},
            "stfphonenumber": {"type": "text"},
            "joiningdate": {"type": "date"},
            "salary": {"type": "bigint"},
            "position": {"type": "text"}
        }
    },
    "faculty": {
        "columns": {
            "staffid": {
                "type": "bigint",
                "not_null": True,
                "unique": True,
                "foreign_key": {"references": "staff.staffid"}
            },
            "title": {"type": "text"},
            "status": {"type": "text"},
            "tenured": {"type": "date"}
        }
    },
    "categories": {
        "columns": {
            "categoryid": {"type": "bigint", "primary_key": True, "identity": True},
            "categorydescription": {"type": "text"},
            "departmentid": {"type": "bigint"}
        }
    },
    "faculty_categories": {
        "columns": {
            "staffid": {
                "type": "bigint",
                "foreign_key": {"references": "staff.staffid"}
            },
            "categoryid": {
                "type": "bigint",
                "foreign_key": {"references": "categories.categoryid"}
            }
        },
        "primary_key": ["staffid", "categoryid"]
    },
    "subjects": {
        "columns": {
            "subjectid": {"type": "bigint", "primary_key": True, "identity": True},
            "categoryid": {
                "type": "bigint",
                "foreign_key": {"references": "categories.categoryid"}
            },
            "subjectcode": {"type": "int"},
            "subjectname": {"type": "text"}
        }
    },
    "faculty_subjects": {
        "columns": {
            "staffid": {
                "type": "bigint",
                "foreign_key": {"references": "staff.staffid"}
            },
            "subjectid": {
                "type": "bigint",
                "foreign_key": {"references": "subjects.subjectid"}
            },
            "proficiencyrating": {"type": "int"}
        },
        "primary_key": ["staffid", "subjectid"]
    },
    "buildings": {
        "columns": {
            "buildingcode": {"type": "bigint", "primary_key": True, "identity": True},
            "buildingname": {"type": "text"},
            "numberoffloorts": {"type": "int"}
        }
    },
    "classrooms": {
        "columns": {
            "classroomid": {"type": "bigint", "primary_key": True, "identity": True},
            "buildingcode": {
                "type": "bigint",
                "foreign_key": {"references": "buildings.buildingcode"}
            },
            "phoneavailable": {"type": "boolean"}
        }
    },
    "classes": {
        "columns": {
            "classid": {"type": "bigint", "primary_key": True, "identity": True},
            "subjectid": {
                "type": "bigint",
                "foreign_key": {"references": "subjects.subjectid"}
            },
            "classroomid": {
                "type": "bigint",
                "foreign_key": {"references": "classrooms.classroomid"}
            },
            "starttime": {"type": "time"},
            "duration": {"type": "int"}
        }
    },
    "faculty_classes": {
        "columns": {
            "staffid": {
                "type": "bigint",
                "foreign_key": {"references": "staff.staffid"}
            },
            "classid": {
                "type": "bigint",
                "foreign_key": {"references": "classes.classid"}
            }
        },
        "primary_key": ["staffid", "classid"]
    },
    "students": {
        "columns": {
            "studentid": {"type": "bigint", "primary_key": True, "identity": True},
            "studfirstname": {"type": "text"},
            "studlastname": {"type": "text"},
            "studstreetadress": {"type": "text"},
            "studcity": {"type": "text"},
            "studstate": {"type": "text"},
            "studzipcode": {"type": "int"},
            "studareacode": {"type": "int"},
            "studphonenumber": {"type": "text"}
        }
    },
    "student_class_status": {
        "columns": {
            "classstatus": {"type": "bigint", "primary_key": True, "identity": True},
            "classdescription": {"type": "text"}
        }
    },
    "student_schedules": {
        "columns": {
            "classid": {
                "type": "bigint",
                "foreign_key": {"references": "classes.classid"}
            },
            "studentid": {
                "type": "bigint",
                "foreign_key": {"references": "students.studentid"}
            },
            "classstatus": {
                "type": "bigint",
                "foreign_key": {"references": "student_class_status.classstatus"}
            },
            "grade": {"type": "int"}
        },
        "primary_key": ["classid", "studentid"]
    }
}

def get_city_for_state(state):
    """Get a random city that belongs to the given state"""
    if state in city_state_mapping:
        return random.choice(city_state_mapping[state])
    # Fallback for states not in mapping
    all_cities = [city for cities in city_state_mapping.values() for city in cities]
    return random.choice(all_cities)

def get_zip_for_state(state):
    """Generate realistic zip codes based on state"""
    state_zip_ranges = {
        'Kerala': (680000, 695999),
        'Tamil Nadu': (600000, 643999),
        'Karnataka': (560000, 591999),
        'Maharashtra': (400000, 445999),
        'Delhi': (110000, 110099),
        'Andhra Pradesh': (500000, 535999),
        'Telangana': (500000, 509999),
        'West Bengal': (700000, 743999),
        'Punjab': (140000, 160999),
        'Rajasthan': (300000, 345999),
        'Uttar Pradesh': (200000, 285999),
        'Bihar': (800000, 855999),
        'Madhya Pradesh': (450000, 488999),
        'Gujarat': (360000, 396999),
        'Haryana': (120000, 136999),
        'Himachal Pradesh': (170000, 177999),
        'Uttarakhand': (240000, 263999),
        'Assam': (780000, 788999)
    }
    
    if state in state_zip_ranges:
        start, end = state_zip_ranges[state]
        return random.randint(start, end)
    return random.randint(600000, 699999)

def get_area_code_for_state(state):
    """Generate realistic area codes based on state"""
    state_area_codes = {
        'Kerala': [471, 484, 487, 495, 496, 497],
        'Tamil Nadu': [422, 423, 424, 427, 431, 432],
        'Karnataka': [80, 821, 824, 831, 836],
        'Maharashtra': [20, 22, 212, 240, 250],
        'Delhi': [11],
        'Andhra Pradesh': [40, 863, 866, 877],
        'Telangana': [40, 870, 878],
        'West Bengal': [33, 341, 342, 343],
        'Punjab': [161, 172, 181, 183],
        'Rajasthan': [141, 145, 151, 291, 294],
        'Uttar Pradesh': [512, 522, 542, 562, 581],
        'Bihar': [612, 621, 631, 641],
        'Madhya Pradesh': [731, 751, 755, 761],
        'Gujarat': [261, 265, 268, 278, 281],
        'Haryana': [124, 129, 130, 169],
        'Himachal Pradesh': [177, 186, 189],
        'Uttarakhand': [135, 136, 159],
        'Assam': [361, 366, 373, 376]
    }
    
    if state in state_area_codes:
        return random.choice(state_area_codes[state])
    return random.randint(40, 99)

# create table function (unchanged)
def create_table(table_name, columns, primary_key=None):
    columns_formatted = ""
    for column_name, column_info in columns.items():
        column_type = column_info["type"]
        if "primary_key" in column_info:
            column_type = f"{column_type} GENERATED ALWAYS AS IDENTITY PRIMARY KEY"
        elif "foreign_key" in column_info:
            foreign_key = column_info['foreign_key']['references'].split('.')
            foreign_key = f"{foreign_key[0]} ({foreign_key[1]})"
            column_type = f"{column_type} REFERENCES {foreign_key}"

        columns_formatted += f"\t{column_name} {column_type},\n"

    if primary_key:
        columns_formatted = columns_formatted[:-1]
        primary_key = f"\tPRIMARY KEY ({', '.join(primary_key)})"
        template = f"""CREATE TABLE IF NOT EXISTS {table_name}(
{columns_formatted}
{primary_key}
);"""
    else:
        columns_formatted = columns_formatted[:-2]
        template = f"""CREATE TABLE IF NOT EXISTS {table_name}(
{columns_formatted}
);"""
    return template

def generate_create_tables():
    queries = ""
    for table_name, table_info in database_schema.items():
        query = create_table(table_name, table_info["columns"], table_info.get("primary_key"))
        queries  += f"{query}\n"
    return queries  

def generate_seed_queries(
    num_staff=8,
    num_students=10,
    num_categories=3,
    num_subjects=6,
    num_classes=5,
    ensure_kerala_tamilnadu=True,
    ensure_salary_cases=True,
    ensure_tenured=True,
    ensure_subject_contains_a=True,
    ensure_student_phone_95=True,
    ensure_class_duration_short=True,
    ensure_shared_zip=True,
    ensure_teacher_subject_counts=True,
    seed=None
):
    def format_value(val):
        if isinstance(val, str):
            return f"'{val}'"
        elif isinstance(val, date):
            return f"'{val.isoformat()}'"
        elif isinstance(val, bool):
            return 'TRUE' if val else 'FALSE'
        elif val is None:
            return "NULL"
        return str(val)

    def insert_query(table, columns, data):
        if not data:
            return ""
        col_str = ", ".join(columns)
        values_str = ",\n    ".join(
            f"({', '.join(format_value(row[col]) for col in columns)})"
            for row in data
        )
        return f"INSERT INTO {table} ({col_str}) VALUES\n    {values_str};\n\n"

    if seed is not None:
        random.seed(seed)

    queries = ""

    def random_date(start_years_ago, end_years_ago):
        start = date.today() - timedelta(days=365 * start_years_ago)
        end = date.today() - timedelta(days=365 * end_years_ago)
        return start + timedelta(days=random.randint(0, (end - start).days))

    # Enhanced Staff generation with better geographical cohesiveness
    salaries = [4000, 8000, 12000, 20000, 30000, 15000, 25000, 18000]
    staff_data = []
    
    # Select primary states to ensure Kerala and Tamil Nadu are included
    primary_states = ['Kerala', 'Tamil Nadu'] if ensure_kerala_tamilnadu else []
    other_states = [s for s in city_state_mapping.keys() if s not in primary_states]
    selected_states = primary_states + random.sample(other_states, min(num_staff - len(primary_states), len(other_states)))
    
    # Generate shared zip code for the first staff member's state
    shared_zip_state = selected_states[0] if selected_states else 'Kerala'
    shared_zip = get_zip_for_state(shared_zip_state)
    
    for i in range(num_staff):
        # Select state ensuring Kerala and Tamil Nadu are first if required
        if i < len(selected_states):
            state = selected_states[i]
        else:
            state = random.choice(list(city_state_mapping.keys()))
        
        city = get_city_for_state(state)
        zipcode = shared_zip if ensure_shared_zip and i == 0 else get_zip_for_state(state)
        area_code = get_area_code_for_state(state)
        
        salary = salaries[i % len(salaries)] if ensure_salary_cases else random.choice(salaries)
        
        staff_data.append({
            "stfFirstName": random.choice(first_names),
            "stfLastName": random.choice(last_names),
            "stfStreetAdress": f"{random.randint(1, 100)} {random.choice(['Street', 'Road', 'Avenue', 'Lane'])}",
            "stfCity": city,
            "stfState": state,
            "stfZipCode": zipcode,
            "stfAreaCode": area_code,
            "stfPhoneNumber": f"9{random.randint(100000000, 999999999)}",
            "joiningDate": random_date(12, 1),
            "salary": salary,
            "position": random.choice(academic_positions)
        })

    # Enhanced Faculty generation with tenure considerations
    faculty_data = []
    for i in range(min(6, num_staff)):
        # Ensure realistic tenure dates (faculty must be hired before tenure)
        hire_date = staff_data[i]["joiningDate"]
        if ensure_tenured:
            # Tenure date should be after hire date by at least 2-6 years
            tenure_years_after_hire = random.randint(2, 6)
            tenured_date = hire_date + timedelta(days=365 * tenure_years_after_hire)
        else:
            tenured_date = random_date(3, 1)
        
        faculty_data.append({
            "staffID": i + 1,
            "title": random.choice(['Dr.', 'Mr.', 'Ms.', 'Prof.']),
            "status": random.choice(['Full-time', 'Part-time', 'Visiting']),
            "tenured": tenured_date
        })

    # Enhanced Categories with realistic academic departments
    categories_data = []
    category_names = list(academic_categories.keys())[:num_categories]
    for i, category_name in enumerate(category_names):
        categories_data.append({
            "categoryDescription": category_name,
            "departmentID": 100 + i + 1
        })

    # Enhanced Subjects with category-specific subjects
    subjects_data = []
    subject_id = 1
    for i, (category_name, category_subjects) in enumerate(list(academic_categories.items())[:num_categories]):
        # Distribute subjects across categories
        subjects_per_category = num_subjects // num_categories
        if i < num_subjects % num_categories:
            subjects_per_category += 1
        
        selected_subjects = random.sample(category_subjects, min(subjects_per_category, len(category_subjects)))
        
        for j, subject_name in enumerate(selected_subjects):
            # Ensure first subject contains 'a' for lab requirements
            if ensure_subject_contains_a and subject_id == 1:
                subject_name = "Data Analysis and Algorithms"
            
            subjects_data.append({
                "categoryID": i + 1,
                "subjectCode": 100 + subject_id,
                "subjectName": subject_name
            })
            subject_id += 1

    # Enhanced Faculty Subjects with realistic expertise patterns
    faculty_subjects_data = []
    for f in faculty_data:
        # Faculty should teach subjects from their category
        faculty_category = random.randint(1, num_categories)
        
        # Get subjects from faculty's category
        category_subjects = [s for s in subjects_data if s["categoryID"] == faculty_category]
        
        # Ensure teacher subject count requirements
        if ensure_teacher_subject_counts:
            subject_count = random.choice([2, 3])  # Exactly 2 or 3 for lab queries
        else:
            subject_count = random.randint(1, min(3, len(category_subjects)))
        
        selected_subjects = random.sample(category_subjects, min(subject_count, len(category_subjects)))
        
        for subject in selected_subjects:
            # Higher proficiency for subjects in faculty's expertise area
            proficiency = random.randint(7, 10) if len(selected_subjects) <= 2 else random.randint(5, 8)
            faculty_subjects_data.append({
                "staffID": f["staffID"],
                "subjectID": subject["subjectCode"] - 99,  # Convert back to subject ID
                "proficiencyRating": proficiency
            })

    # Enhanced Buildings with realistic academic structure
    buildings_data = [
        {"buildingName": "Computer Science Block", "numberOfFloorts": 4},
        {"buildingName": "Engineering Block", "numberOfFloorts": 5},
        {"buildingName": "Mathematics Block", "numberOfFloorts": 3},
        {"buildingName": "Laboratory Block", "numberOfFloorts": 2}
    ]

    # Enhanced Classrooms with better distribution
    classrooms_data = []
    for i, building in enumerate(buildings_data):
        # Multiple classrooms per building
        for floor in range(1, min(building["numberOfFloorts"] + 1, 3)):  # Limit for data size
            classrooms_data.append({
                "buildingCode": i + 1,
                "phoneAvailable": random.choice([True, False])
            })

    # Enhanced Classes with realistic scheduling
    classes_data = []
    class_times = ["08:00:00", "09:30:00", "11:00:00", "14:00:00", "15:30:00"]
    durations = [30, 45, 60, 90]
    
    for i in range(1, num_classes + 1):
        # Ensure short duration for lab requirements
        if ensure_class_duration_short and i == 1:
            duration = 40
        else:
            duration = random.choice(durations)
        
        classes_data.append({
            "subjectID": random.randint(1, len(subjects_data)),
            "classroomID": random.randint(1, len(classrooms_data)),
            "startTime": random.choice(class_times),
            "duration": duration
        })

    # Enhanced Faculty Classes with realistic teaching loads
    faculty_classes_data = []
    for f in faculty_data:
        # Faculty should teach 1-3 classes based on their status
        if f["status"] == "Full-time":
            class_count = random.randint(2, 3)
        else:
            class_count = random.randint(1, 2)
        
        assigned_classes = random.sample(range(1, num_classes + 1), min(class_count, num_classes))
        for class_id in assigned_classes:
            faculty_classes_data.append({
                "staffID": f["staffID"],
                "classID": class_id
            })

    # Enhanced Students with geographical diversity
    students_data = []
    student_states = random.sample(list(city_state_mapping.keys()), min(len(city_state_mapping), num_students // 2))
    
    for i in range(num_students):
        state = student_states[i % len(student_states)]
        city = get_city_for_state(state)
        zipcode = shared_zip if ensure_shared_zip and i == 0 else get_zip_for_state(state)
        area_code = get_area_code_for_state(state)
        
        # Ensure phone number starting with '95' for lab requirements
        if ensure_student_phone_95 and i == 0:
            phone = f"95{random.randint(10000000, 99999999)}"
        else:
            phone = f"9{random.randint(100000000, 999999999)}"
        
        students_data.append({
            "studFirstName": random.choice(first_names),
            "studLastName": random.choice(last_names),
            "studStreetAdress": f"{random.randint(10, 99)} {random.choice(['Lane', 'Street', 'Road', 'Colony'])}",
            "studCity": city,
            "studState": state,
            "studZipCode": zipcode,
            "studAreaCode": area_code,
            "studPhoneNumber": phone
        })

    # Student Class Status (unchanged)
    student_class_status_data = [
        {"classDescription": "Enrolled"},
        {"classDescription": "Completed"},
        {"classDescription": "Dropped"},
        {"classDescription": "Withdrawn"}
    ]

    # Enhanced Student Schedules with realistic grade distribution
    student_schedules_data = []
    for s_id in range(1, num_students + 1):
        # Students typically enroll in 2-4 classes
        enrolled_classes = random.sample(range(1, num_classes + 1), random.randint(2, min(4, num_classes)))
        
        for class_id in enrolled_classes:
            # Most students are enrolled, some completed, few dropped
            status_weights = [70, 25, 5]  # Enrolled, Completed, Dropped
            status = random.choices([1, 2, 3], weights=status_weights)[0]
            
            # Grade distribution based on status
            if status == 1:  # Enrolled - no grade yet or mid-term grade
                grade = random.randint(60, 85) if random.random() < 0.3 else None
            elif status == 2:  # Completed - full grade range
                grade = random.randint(50, 95)
            else:  # Dropped - lower grade or no grade
                grade = random.randint(30, 60) if random.random() < 0.5 else None
            
            if grade is not None:
                student_schedules_data.append({
                    "classID": class_id,
                    "studentID": s_id,
                    "classStatus": status,
                    "grade": grade
                })

    # Enhanced Faculty Categories with logical assignments
    faculty_categories_data = []
    for f in faculty_data:
        # Assign faculty to 1-2 categories based on their expertise
        num_categories_assigned = random.randint(1, min(2, num_categories))
        assigned_categories = random.sample(range(1, num_categories + 1), num_categories_assigned)
        
        for category_id in assigned_categories:
            faculty_categories_data.append({
                "staffID": f["staffID"],
                "categoryID": category_id
            })

    # Generate all insert queries
    table_data_map = {
        "staff": (list(staff_data[0].keys()), staff_data),
        "faculty": (list(faculty_data[0].keys()), faculty_data),
        "categories": (list(categories_data[0].keys()), categories_data),
        "subjects": (list(subjects_data[0].keys()), subjects_data),
        "faculty_subjects": (list(faculty_subjects_data[0].keys()), faculty_subjects_data),
        "buildings": (list(buildings_data[0].keys()), buildings_data),
        "classrooms": (list(classrooms_data[0].keys()), classrooms_data),
        "classes": (list(classes_data[0].keys()), classes_data),
        "faculty_classes": (list(faculty_classes_data[0].keys()), faculty_classes_data),
        "students": (list(students_data[0].keys()), students_data),
        "student_class_status": (list(student_class_status_data[0].keys()), student_class_status_data),
        "student_schedules": (list(student_schedules_data[0].keys()) if student_schedules_data else ["classID", "studentID", "classStatus", "grade"], student_schedules_data),
        "faculty_categories": (list(faculty_categories_data[0].keys()), faculty_categories_data),
    }

    for table, (columns, data) in table_data_map.items():
        queries += insert_query(table, columns, data)

    return queries

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate SQL seed data for DB schema with improved cohesiveness.")
    
    # Matching defaults with generate_seed_queries()
    parser.add_argument("--seed", type=int, default=None, help="Random seed for reproducible data generation")
    parser.add_argument("--output", type=str, default="seed.sql", help="Output SQL file name")
    parser.add_argument("--num_staff", type=int, default=8, help="Number of staff members to generate")
    parser.add_argument("--num_students", type=int, default=10, help="Number of students to generate")
    parser.add_argument("--num_categories", type=int, default=3, help="Number of academic categories")
    parser.add_argument("--num_subjects", type=int, default=6, help="Number of subjects")
    parser.add_argument("--num_classes", type=int, default=5, help="Number of classes")

    # Boolean feature flags (defaults match the function)
    parser.add_argument("--ensure_kerala_tamilnadu", type=lambda s: s.lower() in ['true', '1'], default=True, 
                       help="Ensure Kerala and Tamil Nadu states are included")
    parser.add_argument("--ensure_salary_cases", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure diverse salary ranges for testing")
    parser.add_argument("--ensure_tenured", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure realistic tenure dates")
    parser.add_argument("--ensure_subject_contains_a", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure at least one subject contains 'a'")
    parser.add_argument("--ensure_student_phone_95", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure at least one student phone starts with '95'")
    parser.add_argument("--ensure_class_duration_short", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure at least one class with duration < 45 minutes")
    parser.add_argument("--ensure_shared_zip", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure some shared zip codes between staff and students")
    parser.add_argument("--ensure_teacher_subject_counts", type=lambda s: s.lower() in ['true', '1'], default=True,
                       help="Ensure teachers teach 2-3 subjects for count queries")

    args = parser.parse_args() 
    
    print(f"- Staff members: {args.num_staff}")
    print(f"- Students: {args.num_students}")
    print(f"- Academic categories: {args.num_categories}")
    print(f"- Subjects: {args.num_subjects}")
    print(f"- Classes: {args.num_classes}")
    
    create_table_queries = generate_create_tables()  
    seed_queries = generate_seed_queries(
        num_staff=args.num_staff,
        num_students=args.num_students,
        num_categories=args.num_categories,
        num_subjects=args.num_subjects,
        num_classes=args.num_classes,
        ensure_kerala_tamilnadu=args.ensure_kerala_tamilnadu,
        ensure_salary_cases=args.ensure_salary_cases,
        ensure_tenured=args.ensure_tenured,
        ensure_subject_contains_a=args.ensure_subject_contains_a,
        ensure_student_phone_95=args.ensure_student_phone_95,
        ensure_class_duration_short=args.ensure_class_duration_short,
        ensure_shared_zip=args.ensure_shared_zip,
        ensure_teacher_subject_counts=args.ensure_teacher_subject_counts,
        seed=args.seed
    )

    print(f"Writing to {args.output}...")
    with open(args.output, "w") as sql_dump:
        sql_dump.write(create_table_queries)
        sql_dump.write(seed_queries)
    
    print("Completed successfully!")
