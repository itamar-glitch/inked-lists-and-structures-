
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structures
typedef struct student {
    char* name;
    int  id;
    struct clist* courses;
} student;

typedef struct course {
    char* title;
    int  number;
    struct slist* students;
} course;

typedef struct slist {
    student* info;
    struct slist* next;
} slist;

typedef struct clist {
    course* info;
    struct clist* next;
} clist;

// prototypes
slist* add_student(slist* students, char* name, int id);
clist* add_course(clist* courses, char* title, int number);
void reg_student(slist* students, clist* courses, int id, int number);
void unreg_student(slist* students, int id, int number);
void print_students(slist* students);
void print_courses(clist* courses);
void free_all(slist* sl, clist* cl);

//DO NOT TOUCH THIS FUNCTION
static void getstring(char* buf, int length) {
    int len;
    buf = fgets(buf, length, stdin);
    len = (int)strlen(buf);
    if (buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}
//DO NOT TOUCH THIS FUNCTION 
int main() {
    slist* students = 0;
    clist* courses = 0;
    char  c;
    char  buf[100];
    int   id, num;

    do {
        printf("Choose:\n"
            "    add (s)tudent\n"
            "    add (c)ourse\n"
            "    (r)egister student\n"
            "    (u)nregister student\n"
            "    (p)rint lists\n"
            "    (q)uit\n");

        while ((c = (char)getchar()) == '\n');
        getchar();
        switch (c) {
        case 's':
            printf("Adding new student.\n");

            printf("Student name: ");
            getstring(buf, 100);
            printf("Student ID: ");
            scanf("%d", &id);

            students = add_student(students, buf, id);

            break;

        case 'c':
            printf("Adding new course.\n");

            printf("Course name: ");
            getstring(buf, 100);

            printf("Course number: ");
            scanf("%d", &num);

            courses = add_course(courses, buf, num);

            break;

        case 'r':
            printf("Registering a student to a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            reg_student(students, courses, id, num);

            break;

        case 'u':
            printf("Unregistering a student from a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            unreg_student(students, id, num);

            break;

            case 'p':
            printf("Printing Information.\n");

            print_students(students);
            print_courses(courses);

            break;

        case 'q':
            printf("Quitting...\n");
            break;
        }

        if (c != 'q')
            printf("\n");
    } while (c != 'q');

    free_all(students, courses);
    return 0;

}
//----------------------------------------------------------------------------------------------------remove---------------------------------------------------------
slist* remove_s(int value, slist* head) {
    slist* temp;
    if (!head) {
        return NULL;
    }
    if (head->info->id == value) {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    head->next = remove_s(value, head->next);
    return head;
}


clist* remove_c(int value, clist* head) {
    clist* temp;
    if (!head) {
        return NULL;
    }
    if (head->info->number == value) {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    head->next = remove_c(value, head->next);
    return head;
}



//-----------------------------------------------------------------------------------------------------------
// searches for an item with passed key.
//returns NULL if didn't find it.
slist* search_s(slist * head, int key) {
    while (head) { //loop through the list
        if (head->info->id == key) {
            return head;
        }
        head = head->next;
    }
    //didn't find the item with the requested key
    return NULL;
}

// searches for an item with passed key.
//returns NULL if didn't find it.
clist* search_c(clist* head, int key) {
    while (head) { //loop through the list
        if (head->info->number == key) {
            return head;
        }
        head = head->next;
    }
    //didn't find the item with the requested key
    return NULL;
}

//------------------------------------------------------------------------------------------------------------
// while keeping it sorted ascending by key
clist* insert_c(clist* head, clist* newNode) {
    if (!head)
        return newNode;
    //check if newNode's key is smaller than all keys and should be first
    if (newNode->info->number < head->info->number) {
        newNode->next = head;
        return newNode;
    }
    head->next = insert_c(head->next, newNode);
    return head;
}
slist* insert_st(slist* head, slist* newNode) {
    if (!head)
        return newNode;
    //check if newNode's key is smaller than all keys and should be first
    if (newNode->info->id < head->info->id) {
        newNode->next = head;
        return newNode;
    }
    head->next = insert_st(head->next, newNode);//breakpoint conditons 
    return head;
}
//-------------------------------------------------------------------------------------------------------
slist* add(slist* students, char* name, int id) {
    struct student* new_stud = (struct student*)malloc(sizeof(struct student));
    struct slist* place = (struct slist*)malloc(sizeof(struct slist));
    char* name_student = malloc(strlen(name) + 1);
    
    if (new_stud == NULL) {// making sure that there arnt problom with the memory allocating
        exit(1);
    }
    strcpy(name_student, name);//copy the content of title
    new_stud->id = id;// new item
    new_stud->name = name_student;
    new_stud->courses = NULL;
    if (students == NULL) {//empty list case 
        struct slist* students = (struct slist*)malloc(sizeof(struct slist));
        students->info = new_stud;
        students->next = NULL;
		free(place);
        return students;
    }
    place->info = new_stud;
    place->next = NULL;
    students = insert_st(students, place);
    return students;
    }
slist* add_student(slist* students, char* name, int id) {
    students = add(students, name, id);
    return students;
}
//-----------------------------------------------------------------------------------------------------------
clist* add_c(clist* courses, char* title, int number) {
    struct course* new_course = (struct course*)malloc(sizeof(struct course));
    char* name_course = malloc(sizeof(title) + 1);// pointer for the title 
    //students *pointer
    if (new_course == NULL || name_course == NULL) {
        exit(1);
    }
    strcpy(name_course, title);//copy the value of the title to the new adress
    new_course->title = name_course;//making the course "card"
    new_course->number = number;
    new_course->students = NULL;
    if (courses == NULL) {
        courses = malloc(sizeof(struct course));//making space for for the new course
        if (courses == NULL) {
            exit(1);
        }
        courses->info = new_course;
        courses->next = NULL;
        //free(pointer);
        return courses;
    }
    struct clist* pointer = (struct clist*)malloc(sizeof(struct clist));
    pointer->info = new_course;
    pointer->next = NULL;
    courses =insert_c(courses, pointer);//sorted insert
    return courses;
}
clist* add_course(clist* courses, char* title, int number) {
    courses = add_c(courses,title,number);
    return courses;
}
//--------------------------------------------------------------------------------------------------------------
void reg_student(slist* students, clist* courses, int id, int number) {
	clist* pointer_c = courses;
	slist* pointer_s = students;
	while (students->info->id != id) {// search for the students by id
		students = students->next;
	}
	while (courses->info->number != number) {//search for course by number
		courses = courses->next;
	}
	clist* new_course = (clist*)malloc(sizeof(struct clist));
	new_course->info = courses->info;
	new_course->next = NULL;
	students->info->courses=insert_c(students->info->courses, new_course);//update the list with the added course and update it in student courses
	slist* new_student = (slist*)malloc(sizeof(struct slist));
	new_student->info = students->info;
	new_student->next = NULL;
	courses->info->students = insert_st(courses->info->students, new_student);//update the list with the new student to course students
	students = pointer_s;//return students head
	courses = pointer_c;//return the courses head
}
//--------------------------------------------------------  delete student in courses list  ----------------------------------------------------------
void unreg_student(slist* students, int id, int number) {
    slist* pointer_s = students;
    pointer_s = search_s(pointer_s, id);//search for student
    clist* pointer_sc = pointer_s->info->courses;
    pointer_sc = search_c(pointer_s->info->courses, number);//search for courses
    pointer_sc->info->students=remove_s(id,pointer_sc->info->students);//remove student from courses list
    pointer_s->info->courses=remove_c(number,pointer_s->info->courses);//remove courses from student list
}

//--------------------------------------------------------------------------------------------------------------------------------
void print_students(slist* students) {
    int flag = 0;
    if (students == NULL || students->info == NULL) {//empty lists conditons
        printf("STUDENT LIST: EMPTY!\n");
        return;
    }
    printf("STUDENT LIST:\n");
    while (students) {
        clist* crs_head = students->info->courses;
        printf("%d:%s\n", students->info->id, students->info->name);
        if (!students->info->courses) {
            printf("student is not registered for courses.\n");
            students = students->next;
            continue;
        }
        printf("courses: ");
        while (students->info->courses) {
            if (flag == 0) {//print it only once
                printf("%d-%s", students->info->courses->info->number, students->info->courses->info->title);//print student title and name
                students->info->courses = students->info->courses->next;
                flag = 1;
            }
            else {
                printf(", %d-%s", students->info->courses->info->number, students->info->courses->info->title);
                students->info->courses = students->info->courses->next;
            }
        }
        students->info->courses = crs_head;
        printf("\n");
        flag = 0;
        students = students->next;
    }
}
// ---------------------------------------------------------------------------------------------------------------------

void print_courses(clist* courses) {
    int flag = 0;
    if (courses == NULL || courses->info == NULL) {//empty option
        printf("COURSE LIST: EMPTY!\n");
        return;
    }
    printf("COURSE LIST:\n");
    while (courses) {//run on courses
        slist* student_head = courses->info->students;
        printf("%d:%s\n", courses->info->number, courses->info->title);
        if (!courses->info->students) {
            printf("course has no students.\n");
            courses = courses->next;
            continue;
        }
        printf("students: ");
        while (courses->info->students) {//run on courses students list
            if (flag == 0) {
                printf("%d-%s", courses->info->students->info->id, courses->info->students->info->name);
                courses->info->students = courses->info->students->next;
                flag = 1;
            }
            else {
                printf(", %d-%s", courses->info->students->info->id, courses->info->students->info->name);
                courses->info->students = courses->info->students->next;
            }
        }
        courses->info->students = student_head;
        printf("\n");
        flag = 0;
        courses = courses->next;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------

void free_clhelp(clist* cl) {//free the students courses
	if (cl == NULL) {//breakpoint condition
		return;
	}
	free_clhelp(cl->next);
	free(cl);//no need to delete more then cl specific course its call 
}

void free_sl(slist* sl) {//free the courses 
	if(sl == NULL) {//break point condition
		return;
	}
	free_sl(sl->next);//recursive call
    free_clhelp(sl->info->courses);//call for another func that delete student courses
    free((sl->info->name));//delete name becuse he char* type
    free(sl->info);
	free(sl);
}

void free_slhelp(slist* sl) {//free the students in courses linked list
	if (sl == NULL) {//breakpoint condtion
		return;
	}
	free_slhelp(sl->next);//recursive call
	free(sl);//no need to free more than that becuse free sl take care of that
}



void free_cl(clist* cl) {//free all courses
	if (cl == NULL) {//breakpoint condition
		return;
	}
	free_cl(cl->next);//recursive call
    free_slhelp(cl->info->students);// call for function that free al students in course (of courses list)
    free(cl->info->title);//delete title becuse is type is char*
    free(cl->info);
	free(cl);
}



void free_all(slist* sl, clist* cl) {
	if (cl==NULL && sl==NULL){
		return;
	}
	free_sl( sl);
	free_cl(cl);
}
//---------------------------------------------------------------------the end------------------------------------------------------------------------------
