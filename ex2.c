#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* structures */
typedef struct student {
    char *name;
    int  id;
    struct clist *courses;
} student;

typedef struct course {
    char *title;
    int  number;
    struct slist *students;
} course;

typedef struct slist {
    student      *info;
    struct slist *next;
} slist;

typedef struct clist {
    course       *info;
    struct clist *next;
} clist;


/* prototypes */
slist* add_student(slist *students, char *name, int id);
clist* add_course(clist *courses, char *title, int number);
void reg_student(slist *students, clist *courses, int id, int number);
void unreg_student(slist *students, int id, int number);
void print_students(slist *students);
void print_courses(clist *courses);
void free_all(slist *sl, clist *cl);

/*DO NOT TOUCH THIS FUNCTION */
static void getstring(char *buf, int length) {
    int len;
    buf = fgets(buf, length, stdin);
    len = (int) strlen(buf);
    if (buf[len-1] == '\n')
        buf[len-1] = '\0';
}

/*DO NOT TOUCH THIS FUNCTION */
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

        while ((c = (char) getchar()) == '\n');
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

                printf("Course number: ");\
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

    free_all(students,courses);
    return 0;
}
slist* add_student(slist *students, char *name, int id){
    slist *Last_Student;
    slist *temp_student;
    slist *final_student = students;
    Last_Student = (slist*)malloc(sizeof(slist));
    if (Last_Student == NULL){
        exit(1);
    }
    Last_Student->info = (student*)malloc(sizeof(student));
    Last_Student->info->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    Last_Student->info->courses = (clist*)malloc(sizeof(clist));
    Last_Student->info->courses = NULL;
    strcpy(Last_Student->info->name, name);
    Last_Student->info->id = id;
    if(!students){
        Last_Student->next = NULL;
        return Last_Student;
    }
    if(students->info->id>id){
        Last_Student->next = students;
        return Last_Student;
    }
    while(students!=NULL&&students->info->id<id){
        temp_student = students;
        students = students->next;
    }
    Last_Student->next = students;
    temp_student->next = Last_Student;
    return final_student;

}

clist* add_course(clist *courses, char *title, int number){
    clist *last_course;
    clist *temp_course;
    clist *final_courses = courses;
    last_course = (clist*)malloc(sizeof(clist));
    if (last_course == NULL){
        exit(1);
    }
    last_course->info = (course*)malloc(sizeof(course));
    last_course->info->title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
    last_course->info->students = (slist*)malloc(sizeof(slist));
    last_course->info->students = NULL;
    strcpy(last_course->info->title, title);
    last_course->info->number = number;
    if(!courses){
        last_course->next =  NULL;
        return last_course;
    }
    if(courses->info->number>number){
        last_course->next = courses;
        return last_course;
    }
    while(courses!=NULL&&courses->info->number<number){
        temp_course = courses;
        courses = courses->next;
    }
    last_course->next = courses;
    temp_course->next = last_course;
    return final_courses;

}

void reg_student(slist *students, clist *courses, int id, int number){
    clist *course_register , *temp_course , *temp2_course;
    slist *student_register , *temp_student, *temp2_student;
    course_register = (clist*) malloc(sizeof(clist));
    student_register = (slist*) malloc(sizeof(slist));
    while(courses){
        if(courses->info->number == number){
            break;
        }
        courses = courses->next;
    }
    while(students){
        if(students->info->id == id){
            break;
        }
        students = students->next;
    }
    temp_course = students->info->courses;
    course_register->info = courses->info;
    course_register->next = (clist*) malloc(sizeof(clist));
    course_register->next = NULL;
    if(!temp_course){
        students->info->courses = course_register;
    }
    else if(course_register->info->number < temp_course->info->number){
        course_register->next = students->info->courses;
        students->info->courses = course_register;
    }
    else{
        while(temp_course !=NULL && (course_register->info->number > temp_course->info->number)){
            temp2_course = temp_course;
            temp_course = temp_course->next;
        }

        course_register->next = temp_course;
        temp2_course->next = course_register;
    }
    temp_student = courses->info->students;
    student_register->info = students->info;
    student_register->next = (slist*) malloc(sizeof(slist));
    student_register->next = NULL;
    if(!temp_student){
        courses->info->students = student_register;
    }
    else if(student_register->info->id < temp_student->info->id){
        student_register->next = courses->info->students;
        courses->info->students = student_register;
    }
    else{
        while(temp_student !=NULL && (student_register->info->id > temp_student->info->id)){
            temp2_student = temp_student;
            temp_student = temp_student->next;
        }

        student_register->next = temp_student;
        temp2_student->next = student_register;
    }
}



void unreg_student(slist *students, int id, int number) {
    slist *sl = students , *sl2;
    clist *cl, *cl2;

    // Find the student in the list
    while (sl != NULL && sl->info->id != id) {
        sl = sl->next;
    }

    if (sl == NULL) {
        return;
    }

    // Find the course in the student's list of courses
    cl = sl->info->courses;
    while (cl != NULL && cl->info->number != number) {
        cl = cl->next;
    }

    if (cl == NULL) {
        return;
    }

    // Remove the course from the student's list of courses
    if (cl == sl->info->courses) {
        sl->info->courses = cl->next;
    } else {
        clist *prev = sl->info->courses;
        while (prev->next != cl) {
            prev = prev->next;
        }
        prev->next = cl->next;
    }
    sl2 = cl->info->students;
    slist *prev2;
    if (sl2->info->id == id){
        prev2 = sl2;
        cl->info->students = cl->info->students->next;
    } else {
        while(sl2->info->id != id){
            prev2 = sl2;
            sl2 = sl2 ->next;
        }
        prev2->next = sl2->next;
    }

    free (cl);
    free(sl2);

}

void print_students(slist *students){
    printf("STUDENT LIST:\n");
    slist* current_student = students;
    while (current_student != NULL) {
        printf("%d:%s\n", current_student->info->id, current_student->info->name);
        clist* enrolled_courses = current_student->info->courses;
        if(enrolled_courses == NULL){
            printf("student is not registered for courses.\n");
        }else{
            printf("courses: ");
            while (enrolled_courses != NULL) {
                printf("%d-%s", enrolled_courses->info->number,enrolled_courses->info->title);
                enrolled_courses = enrolled_courses->next;
                if(enrolled_courses != NULL){
                    printf(", ");
                }
            }
            printf("\n");
        }
        current_student = current_student->next;
    }
}
void print_courses(clist *courses) {
    printf("COURSE LIST:\n");
    clist *current_courses = courses;
    while (current_courses != NULL) {
        printf("%d:%s\n", current_courses->info->number, current_courses->info->title);
        slist* enrolled_students = current_courses->info->students;
        if(enrolled_students == NULL){
            printf("course has no students.\n");
        }else{
            printf("students: ");
            while (enrolled_students != NULL) {
                printf("%d-%s", enrolled_students->info->id,enrolled_students->info->name);
                enrolled_students = enrolled_students->next;
                if(enrolled_students != NULL){
                    printf(", ");
                }
            }
            printf("\n");
        }
        current_courses = current_courses->next;
    }
}
void free_all(slist *sl, clist *cl){
    free(sl);
    free(cl);
}


