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
	
	free_all(students,courses);
    return 0;
}
