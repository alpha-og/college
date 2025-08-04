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

def create_table(table_name, columns, primary_key=None):
    columns_formatted = ""
    for column_name, column_info in columns.items():
        column_type = column_info["type"]
        
        # Identity for single-column primary keys
        if "primary_key" in column_info and len(primary_key or []) == 0:
            column_type = f"{column_type} GENERATED ALWAYS AS IDENTITY"
        
        # Not null constraint
        if "not_null" in column_info and column_info["not_null"]:
            column_type += " NOT NULL"

        # Unique constraint
        if "unique" in column_info and column_info["unique"]:
            column_type += " UNIQUE"
            
        columns_formatted += f"\t{column_name} {column_type},\n"

    # Add foreign key constraints separately for clarity and correctness
    foreign_keys = []
    for column_name, column_info in columns.items():
        if "foreign_key" in column_info:
            foreign_key_ref = column_info['foreign_key']['references'].split('.')
            foreign_keys.append(f"\tFOREIGN KEY ({column_name}) REFERENCES {foreign_key_ref[0]} ({foreign_key_ref[1]}),")

    if primary_key:
        columns_formatted += f"\tPRIMARY KEY ({', '.join(primary_key)}),\n"
    elif any(col.get("primary_key") for col in columns.values()):
        columns_formatted += f"\tPRIMARY KEY ({[col for col, info in columns.items() if info.get('primary_key')][0]}),\n"

    all_constraints = "".join(foreign_keys) + columns_formatted
    # Remove trailing comma and newline
    all_constraints = all_constraints.strip().rstrip(',')

    template = f"""CREATE TABLE IF NOT EXISTS {table_name}(
{all_constraints}
);"""
    return template

def generate_create_tables():
    queries = ""
    # Define a specific order for table creation to satisfy foreign key constraints
    ordered_tables = [
        "staff", "categories", "subjects", "buildings", "classrooms",
        "students", "student_class_status", "faculty", "faculty_categories",
        "faculty_subjects", "classes", "faculty_classes", "student_schedules"
    ]
    for table_name in ordered_tables:
        table_info = database_schema[table_name]
        query = create_table(table_name, table_info["columns"], table_info.get("primary_key"))
        queries += f"{query}\n"
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

    # --- 1. Generate STAFF data and simulate IDs ---
    staff_data = []
    staff_ids = []
    
    primary_states = ['Kerala', 'Tamil Nadu'] if ensure_kerala_tamilnadu else []
    other_states = [s for s in city_state_mapping.keys() if s not in primary_states]
    selected_states = primary_states + random.sample(other_states, min(num_staff - len(primary_states), len(other_states)))
    
    shared_zip = get_zip_for_state(selected_states[0] if selected_states else 'Kerala')
    
    salaries_for_query = [4000, 8000, 12000, 20000, 30000, 45000, 55000, 60000, 80000]
    positions_for_query = ['Assistant Professor', 'Associate Professor', 'Professor', 'Lecturer']
    
    for i in range(num_staff):
        staff_id = i + 1
        staff_ids.append(staff_id)
        
        state = selected_states[i] if i < len(selected_states) else random.choice(list(city_state_mapping.keys()))
        city = get_city_for_state(state)
        zipcode = shared_zip if ensure_shared_zip and i == 0 else get_zip_for_state(state)
        area_code = get_area_code_for_state(state)
        
        salary = random.choice(salaries_for_query)
        position = random.choice(positions_for_query)

        if i == 0:
            salary = 4000
        elif i == 1:
            salary = 12000
        if i > 1 and i % 3 == 0:
            position = staff_data[0]['position'] if staff_data else random.choice(positions_for_query)
        
        staff_data.append({
            "staffid": staff_id, # Simulated ID
            "stffirstname": random.choice(first_names),
            "stflastname": random.choice(last_names),
            "stfstreetadress": f"{random.randint(1, 100)} {random.choice(['Street', 'Road', 'Avenue', 'Lane'])}",
            "stfcity": city,
            "stfstate": state,
            "stfzipcode": zipcode,
            "stfareacode": area_code,
            "stfphonenumber": f"9{random.randint(100000000, 999999999)}",
            "joiningdate": random_date(12, 1),
            "salary": salary,
            "position": position
        })
    
    # Generate insert query for staff
    staff_insert_data = [
        {k: v for k, v in row.items() if k != 'staffid'} 
        for row in staff_data
    ]
    queries += insert_query(
        "staff", 
        [k for k in staff_insert_data[0].keys()], 
        staff_insert_data
    )

    # --- 2. Generate FACULTY data, referencing staff IDs ---
    faculty_data = []
    faculty_staff_ids = sorted(random.sample(staff_ids, min(len(staff_ids), 6)))
    for i, staff_id in enumerate(faculty_staff_ids):
        # Find the joining date for this faculty from the staff data
        staff_record = next(s for s in staff_data if s['staffid'] == staff_id)
        hire_date = staff_record["joiningdate"]
        
        if ensure_tenured:
            if i == 0:
                tenure_date = hire_date + timedelta(days=365 * random.randint(2, 4))
                if (date.today() - tenure_date).days < 365 * 6:
                    tenure_date = date.today() - timedelta(days=365 * 6)
            else:
                tenure_date = random_date(5, 1)
        else:
            tenure_date = random_date(3, 1)
        
        faculty_data.append({
            "staffid": staff_id,
            "title": random.choice(['Dr.', 'Prof.']),
            "status": random.choice(['Full-time', 'Part-time']),
            "tenured": tenure_date
        })
    
    queries += insert_query(
        "faculty", 
        list(faculty_data[0].keys()), 
        faculty_data
    )

    # --- 3. Generate CATEGORIES data and simulate IDs ---
    categories_data = []
    category_ids = []
    category_names = list(academic_categories.keys())
    for i in range(num_categories):
        category_id = i + 1
        category_ids.append(category_id)
        categories_data.append({
            "categoryid": category_id, # Simulated ID
            "categorydescription": category_names[i],
            "departmentid": 100 + i + 1
        })
    
    category_insert_data = [
        {k: v for k, v in row.items() if k != 'categoryid'}
        for row in categories_data
    ]
    queries += insert_query(
        "categories",
        list(category_insert_data[0].keys()),
        category_insert_data
    )
    
    # --- 4. Generate SUBJECTS data, referencing category IDs and simulating subject IDs ---
    subjects_data = []
    subject_ids = []
    all_subjects = [sub for cat in academic_categories.values() for sub in cat]
    
    # Ensure one subject name contains 'a'
    if ensure_subject_contains_a:
        subject_with_a = random.choice([s for s in all_subjects if 'a' in s.lower()])
        subjects_data.append({
            "subjectid": 1,
            "categoryid": random.choice(category_ids),
            "subjectcode": 101,
            "subjectname": subject_with_a
        })
        all_subjects.remove(subject_with_a)
        subject_ids.append(1)
    
    for i in range(num_subjects - len(subjects_data)):
        subject_id = len(subjects_data) + 1
        subject_ids.append(subject_id)
        subject = random.choice(all_subjects)
        
        subjects_data.append({
            "subjectid": subject_id, # Simulated ID
            "categoryid": random.choice(category_ids),
            "subjectcode": 101 + i,
            "subjectname": subject
        })
        all_subjects.remove(subject)
        
    subject_insert_data = [
        {k: v for k, v in row.items() if k != 'subjectid'}
        for row in subjects_data
    ]
    queries += insert_query(
        "subjects",
        list(subject_insert_data[0].keys()),
        subject_insert_data
    )

    # --- 5. Generate FACULTY_SUBJECTS with varied subject counts ---
    faculty_subjects_data = []
    
    # Ensure some faculty teach exactly 2 or 3 subjects
    if ensure_teacher_subject_counts and len(faculty_data) >= 2 and len(subjects_data) >= 3:
        # Faculty 1 teaches 2 subjects
        subjects_to_assign = random.sample(subject_ids, 2)
        for s_id in subjects_to_assign:
            faculty_subjects_data.append({
                "staffid": faculty_data[0]['staffid'],
                "subjectid": s_id,
                "proficiencyrating": random.randint(7, 10)
            })
        
        # Faculty 2 teaches 3 subjects
        subjects_to_assign = random.sample(subject_ids, 3)
        for s_id in subjects_to_assign:
            faculty_subjects_data.append({
                "staffid": faculty_data[1]['staffid'],
                "subjectid": s_id,
                "proficiencyrating": random.randint(7, 10)
            })
    
    # Assign subjects to other faculty with random counts
    assigned_faculty_ids = [fs['staffid'] for fs in faculty_subjects_data]
    for f in faculty_data:
        if f['staffid'] in assigned_faculty_ids:
            continue
        
        num_subjects_assigned = random.randint(1, min(3, len(subjects_data)))
        subjects_to_assign = random.sample(subject_ids, num_subjects_assigned)
        for s_id in subjects_to_assign:
            faculty_subjects_data.append({
                "staffid": f["staffid"],
                "subjectid": s_id,
                "proficiencyrating": random.randint(5, 10)
            })

    queries += insert_query(
        "faculty_subjects",
        list(faculty_subjects_data[0].keys()),
        faculty_subjects_data
    )

    # --- 6. Generate BUILDINGS and CLASSROOMS data with simulated IDs ---
    buildings_data = [
        {"buildingname": "Computer Science Block", "numberoffloorts": 4},
        {"buildingname": "Engineering Block", "numberoffloorts": 5},
        {"buildingname": "Mathematics Block", "numberoffloorts": 3}
    ]
    building_ids = [b + 1 for b in range(len(buildings_data))]
    
    buildings_insert_data = [
        {k: v for k, v in row.items()}
        for row in buildings_data
    ]
    queries += insert_query(
        "buildings",
        list(buildings_insert_data[0].keys()),
        buildings_insert_data
    )
    
    classrooms_data = []
    classroom_ids = []
    for i, building_id in enumerate(building_ids):
        for floor in range(1, buildings_data[i]["numberoffloorts"] + 1):
            classroom_id = len(classrooms_data) + 1
            classroom_ids.append(classroom_id)
            classrooms_data.append({
                "classroomid": classroom_id, # Simulated ID
                "buildingcode": building_id,
                "phoneavailable": random.choice([True, False])
            })
            
    classrooms_insert_data = [
        {k: v for k, v in row.items() if k != 'classroomid'}
        for row in classrooms_data
    ]
    queries += insert_query(
        "classrooms",
        list(classrooms_insert_data[0].keys()),
        classrooms_insert_data
    )

    # --- 7. Generate CLASSES data, referencing subject and classroom IDs, and simulating class IDs ---
    classes_data = []
    class_ids = []
    class_times = ["08:00:00", "09:30:00", "11:00:00", "14:00:00", "15:30:00"]
    durations = [30, 45, 60, 90]
    
    for i in range(num_classes):
        class_id = i + 1
        class_ids.append(class_id)
        
        duration = random.choice(durations)
        if ensure_class_duration_short and i == 0:
            duration = random.choice([25, 30, 40])
            
        classes_data.append({
            "classid": class_id, # Simulated ID
            "subjectid": random.choice(subject_ids),
            "classroomid": random.choice(classroom_ids),
            "starttime": random.choice(class_times),
            "duration": duration
        })
    
    classes_insert_data = [
        {k: v for k, v in row.items() if k != 'classid'}
        for row in classes_data
    ]
    queries += insert_query(
        "classes",
        list(classes_insert_data[0].keys()),
        classes_insert_data
    )

    # --- 8. Generate FACULTY_CLASSES data (many-to-many relationship) ---
    faculty_classes_data = []
    for staff_id in faculty_staff_ids:
        assigned_classes = random.sample(class_ids, random.randint(1, min(3, len(class_ids))))
        for class_id in assigned_classes:
            faculty_classes_data.append({"staffid": staff_id, "classid": class_id})

    queries += insert_query(
        "faculty_classes",
        list(faculty_classes_data[0].keys()),
        faculty_classes_data
    )
    
    # --- 9. Generate STUDENTS data with a shared zip code and phone number pattern and simulated IDs ---
    students_data = []
    student_ids = []
    for i in range(num_students):
        student_id = i + 1
        student_ids.append(student_id)
        
        state = random.choice(list(city_state_mapping.keys()))
        city = get_city_for_state(state)
        zipcode = shared_zip if ensure_shared_zip and i == 0 else get_zip_for_state(state)
        area_code = get_area_code_for_state(state)
        
        if ensure_student_phone_95 and i == 0:
            phone = f"95{random.randint(10000000, 99999999)}"
        else:
            phone = f"9{random.randint(100000000, 999999999)}"
            
        students_data.append({
            "studentid": student_id, # Simulated ID
            "studfirstname": random.choice(first_names),
            "studlastname": random.choice(last_names),
            "studstreetadress": f"{random.randint(10, 99)} {random.choice(['Lane', 'Street', 'Road', 'Colony'])}",
            "studcity": city,
            "studstate": state,
            "studzipcode": zipcode,
            "studareacode": area_code,
            "studphonenumber": phone
        })
    
    students_insert_data = [
        {k: v for k, v in row.items() if k != 'studentid'}
        for row in students_data
    ]
    queries += insert_query(
        "students",
        list(students_insert_data[0].keys()),
        students_insert_data
    )

    # --- 10. Generate STUDENT_CLASS_STATUS and STUDENT_SCHEDULES with simulated IDs and varied grades ---
    student_class_status_data = [
        {"classdescription": "Enrolled"},
        {"classdescription": "Completed"},
        {"classdescription": "Dropped"},
        {"classdescription": "Withdrawn"}
    ]
    queries += insert_query(
        "student_class_status",
        list(student_class_status_data[0].keys()),
        student_class_status_data
    )
    
    student_schedules_data = []
    pass_grade_threshold = 50 
    
    for s_id in student_ids:
        enrolled_classes = random.sample(class_ids, random.randint(2, min(4, len(class_ids))))
        for class_id in enrolled_classes:
            status = random.choices([1, 2, 3], weights=[70, 25, 5])[0]
            grade = None
            if status == 1:
                grade = random.randint(60, 95) if random.random() < 0.8 else None
            elif status == 2:
                if random.random() < 0.7:
                    grade = random.randint(pass_grade_threshold, 100)
                else:
                    grade = random.randint(0, pass_grade_threshold - 1)
            else:
                grade = random.randint(30, 60) if random.random() < 0.5 else None
                
            student_schedules_data.append({
                "classid": class_id,
                "studentid": s_id,
                "classstatus": status,
                "grade": grade
            })

    queries += insert_query(
        "student_schedules",
        list(student_schedules_data[0].keys()),
        student_schedules_data
    )

    # --- 11. Generate FACULTY_CATEGORIES data (many-to-many relationship) ---
    faculty_categories_data = []
    for staff_id in faculty_staff_ids:
        num_categories_assigned = random.randint(1, min(2, num_categories))
        assigned_categories = random.sample(category_ids, num_categories_assigned)
        for category_id in assigned_categories:
            faculty_categories_data.append({
                "staffid": staff_id,
                "categoryid": category_id
            })

    queries += insert_query(
        "faculty_categories",
        list(faculty_categories_data[0].keys()),
        faculty_categories_data
    )

    return queries

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate SQL seed data for DB schema with improved cohesiveness.")
    parser.add_argument("--seed", type=int, default=None, help="Random seed for reproducible data generation")
    parser.add_argument("--output", type=str, default="seed.sql", help="Output SQL file name")
    parser.add_argument("--num_staff", type=int, default=15, help="Number of staff members to generate")
    parser.add_argument("--num_students", type=int, default=20, help="Number of students to generate")
    parser.add_argument("--num_categories", type=int, default=3, help="Number of academic categories")
    parser.add_argument("--num_subjects", type=int, default=10, help="Number of subjects")
    parser.add_argument("--num_classes", type=int, default=10, help="Number of classes")

    parser.add_argument("--ensure_kerala_tamilnadu", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure Kerala and Tamil Nadu states are included")
    parser.add_argument("--ensure_salary_cases", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure diverse salary ranges for testing")
    parser.add_argument("--ensure_tenured", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure realistic tenure dates")
    parser.add_argument("--ensure_subject_contains_a", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure at least one subject contains 'a'")
    parser.add_argument("--ensure_student_phone_95", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure at least one student phone starts with '95'")
    parser.add_argument("--ensure_class_duration_short", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure at least one class with duration < 45 minutes")
    parser.add_argument("--ensure_shared_zip", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure some shared zip codes between staff and students")
    parser.add_argument("--ensure_teacher_subject_counts", type=lambda s: s.lower() in ['true', '1'], default=True, help="Ensure teachers teach 2-3 subjects for count queries")
    
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
