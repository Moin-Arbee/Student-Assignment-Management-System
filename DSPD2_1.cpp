#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {NOT_SUBMITTED, SUBMITTED} asg_sub_status;
typedef enum {NOT_DECLARED, DECLARED} asg_declare_status;
typedef enum {DUE_NOT_OVER, DUE_OVER} asg_due_status;
typedef enum {NOT_EVALUATED, EVALUATED} asg_eval_status;
typedef enum {NO,YES}isVivaTaken;
typedef enum{FAILURE,SUCCESS}status_code;

typedef struct Time_tag
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
}Time;

typedef struct Student_tag
{
	int stu_id;
	char name[30];
	int part_id;
	int grp_id;
	int asg_id;
	char asg_topic[30];
	Time _deadline;
	asg_sub_status a_sub_s;
	asg_eval_status a_eva_s;
	float off_marks;
	float viva_marks;
	struct Student_tag* next;
}Student;

typedef struct student_group_tag
{
	Student *student1, *student2;
	int grp_id;
	asg_declare_status a_dec_s;
	asg_sub_status a_sub_s;
	asg_eval_status a_eva_s;
	isVivaTaken viva;
	float marks_given;
	struct student_group_tag* next;
}Student_group;


typedef struct assg_tag
{
	int asg_id;
	char topic[30];
	asg_declare_status a_dec_s;
	asg_due_status a_due_s;
	asg_eval_status a_eva_s;
	Student_group* stu_group;
	struct assg_tag* next;
}Assignment;



// to check if student is present in the student list
status_code isStudentpresent(Student* student_lptr, int student_id)
{
	Student* student_ptr=student_lptr;
	status_code ret_val=FAILURE;
	int student_exists=0;
	while((student_ptr!=NULL)&&(student_exists==0))
	{
		if(student_ptr->stu_id==student_id)
		{
			student_exists=1;
		}
		else
		{
			student_ptr=student_ptr->next;
		}
	}
	if(student_exists==1)
	{
		ret_val=SUCCESS;
	}
	return ret_val;
}

Assignment* find_asg_ptr(Assignment* asg_lptr, int a_id)
{
	Assignment* ret_val;
	Assignment* asg_ptr=asg_lptr;
	int asg_found=0;
	while((asg_found==0)&&(asg_ptr!=NULL))
	{
		if(asg_ptr->asg_id==a_id)
		{
			ret_val=asg_ptr;
		}
		else
		{
			asg_ptr=asg_ptr->next;
		}
	}
	if(asg_found==0)
	{
		ret_val=NULL;
	}
	return ret_val;
}
void display_students(Student* student_lptr) {
    if (student_lptr == NULL)
	{
        printf("No students in the list.\n");
    } else 
	{
        Student* student_ptr = student_lptr;
        printf("Student ID\tName\t\tPartner\t\tGroup ID\tAssignment ID\tAssignment Topic\tDeadline\n");
        while (student_ptr != NULL) {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%s\t\t%d/%d/%d %d:%d\n", student_ptr->stu_id, student_ptr->name, student_ptr->part_id, student_ptr->grp_id, student_ptr->asg_id, student_ptr->asg_topic, student_ptr->_deadline.day, student_ptr->_deadline.month, student_ptr->_deadline.year, student_ptr->_deadline.hour, student_ptr->_deadline.minute);
            student_ptr = student_ptr->next;
        }
    }
}

void display_assignments(Assignment* asg_lptr) {
    if (asg_lptr == NULL) {
        printf("No assignments in the list.\n");
    } else {
        Assignment* asg_ptr = asg_lptr;
        printf("Assignment ID\tTopic\t\tDeclare Status\tDue Status\tEvaluation Status\tGroup ID\tSubmission Status\tEvaluation Status\n");
        while (asg_ptr != NULL) {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t", asg_ptr->asg_id, asg_ptr->topic, asg_ptr->a_dec_s, asg_ptr->a_due_s, asg_ptr->a_eva_s);
            Student_group* sgroup_ptr = asg_ptr->stu_group;
            while (sgroup_ptr != NULL) {
                printf("%d ", sgroup_ptr->grp_id);
                sgroup_ptr = sgroup_ptr->next;
            }
            printf("\t\t%d\t\t%d\n", asg_ptr->stu_group->a_sub_s, asg_ptr->stu_group->a_eva_s);
            asg_ptr = asg_ptr->next;
        }
    }
}

	
	//QUESTION 1:
	/* Insert a student record in the student-list. After every insertion of a student-record,
	appropriate changes/insertion needs to be done in the assignment-list also.*/ 



	//with the addition of a new student, we get thier assg_id, group_id. so we go to that assg
	//and add their group in the group list of that assignment. so, we actually need a add_group
	//auxilary function. 
	//when we are adding a group node, we are already in that assignment node, so we do not need
	//assignment's info in creating group node.
	//but we need assignment list pointer as its field, stu_group's head will change.


void ins_grp_list(Assignment** asg_mpptr, int group_id, int student_id)
{
	//we check if the student's group already exists 
	Assignment* asg_mptr=*asg_mpptr;
	Student_group* group_ptr=asg_mptr->stu_group;
	int group_exists =0;
	printf("pk1");
	while((group_ptr!=NULL)&&(group_exists==0))
	{
		printf("pk2");
		if(group_ptr->grp_id==group_id)
		{
			printf("done if");
			group_exists==1;
		}
		else
		{
			printf("done else.");
			group_ptr=group_ptr->next;
		}
	}
	if(group_exists==0)
	{
		printf("oh no\n");
		Student_group* sgroup_ptr=(Student_group*)malloc(sizeof(Student_group));
		sgroup_ptr->grp_id=group_id;
		sgroup_ptr->a_sub_s=NOT_SUBMITTED;
		sgroup_ptr->a_eva_s=NOT_EVALUATED;
		sgroup_ptr->marks_given=-1.0;
		sgroup_ptr->next=asg_mptr->stu_group;
		asg_mptr->stu_group=sgroup_ptr;
		*asg_mpptr=asg_mptr;
	}
}


Student* ins_stu_list (Student* student_lptr, Assignment** asg_lpptr, int student_id, char* student_name, int partner_id, int group_id, int assignment_id,char* assignment_topic, Time deadline_ )
{
	//we should check if this student record is already present in the list.
	
	Student* student_ptr=student_lptr;
	Assignment* asg_mptr = NULL;
	Assignment* asg_lptr=*asg_lpptr;
	if(isStudentpresent(student_lptr,student_id))
	{
		printf("\nThis student already exists.");
	}
	else //new student case.
	{
		Student* student_nptr = (Student*)malloc(sizeof(Student));
		student_nptr->stu_id= student_id;
		strcpy(student_nptr->name,student_name);
		student_nptr->part_id=partner_id;
		student_nptr->grp_id=group_id;
		student_nptr->asg_id=assignment_id;
		student_nptr->_deadline=deadline_;
		strcpy(student_nptr->asg_topic,assignment_topic);
		student_nptr->a_sub_s=NOT_SUBMITTED;
		student_nptr->a_eva_s=NOT_EVALUATED;
		student_nptr->viva_marks=-1.0;
		student_nptr->off_marks=-1.0;
		student_nptr->next=student_lptr;
		student_lptr=student_nptr;
	}
	
	//we have added a new student at the start of the student list. 
	//now we update the assignment list.
	//we go to that assignment in the list, and in that we insert the student group.
	asg_mptr=find_asg_ptr(asg_lptr,assignment_id);
	
	if(asg_mptr!=NULL)
	{
		ins_grp_list(&asg_mptr,group_id,student_id);
	}
	else //assignment is not found, we have to create the assignment record.
	{
		
		Assignment* asg_nptr = NULL;
		asg_nptr=(Assignment*)malloc(sizeof(Assignment));
		asg_nptr->asg_id=assignment_id;
		strcpy(asg_nptr->topic,assignment_topic);
		asg_nptr->a_due_s=DUE_NOT_OVER;
		asg_nptr->a_eva_s=NOT_EVALUATED;
		ins_grp_list(&asg_nptr,group_id,student_id);	
		printf("Done1");
		//we have to add this node in the assignment list.
		asg_nptr->next=*asg_lpptr;
		*asg_lpptr=asg_nptr;
	}
	printf("\ndoneee2");
	return student_lptr;
}
	
//	
//	while((asg_mptr!=NULL)&&(asg_found==0))
//	{
//		if(asg_mptr->asg_id==assignment_id)
//		{
//			asg_found=1;
//		}
//		else
//		{
//			asg_mptr=asg_mptr->next;
//		}
//	}
//	//if assignment is found, we will just update the group in assignment.
//	if(asg_found==1)
//	{
//		Student_group* stu_group=ins_grp_list(asg_mptr,group_id,student_id);
//	}
//	//if assignment is not found, we have to create the assignment record.
//	else
//	{
//		Assignment* asg_nptr;
//		asg_nptr=(Assignment*)malloc(sizeof(Assignment));
//		asg_nptr->asg_id=assignment_id;
//		strcpy(asg_nptr->topic,assignment_topic);
//		asg_nptr->a_due_s=DUE_NOT_OVER;
//		asg_nptr->a_eva_s=NOT_EVALUATED;
//		asg_nptr->stu_group=ins_grp_list(asg_nptr,group_id,student_id);	
//		//we have to add this node in the assignment list.
//		asg_nptr->next=*asg_lpptr;
//		*asg_lpptr=asg_nptr;
//	}
//	return student_lptr;


/*  QUE.2.  Insert assignment-record in the assignment-record-list. The insertion function can take
a list of students and allocate the assignment to multiple student groups, thus resulting
into insertions in student-list as well.*/


Student* Concatenate(Student* lptr1, Student* lptr2)
{
	Student *lptr,*ptr;
	if(lptr1==NULL)
	{
		lptr=lptr2;
	}
	else
	{
		ptr=lptr1;
		while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next=lptr2;
		lptr=lptr1;
	}
	return lptr;
}

void removeDuplicates(Student* start)
{
    Student *ptr1, *ptr2, *dup;
    ptr1 = start;
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
        while (ptr2->next != NULL) {
            if (ptr1->stu_id== ptr2->next->stu_id) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}
Student_group* create_student_group(Student *head) 
{
    Student_group* ret_val;
    if (head == NULL) 
	{
        ret_val = NULL;
    }
    Student* current = head;
    Student* compare;
    Student_group* group_lptr=NULL;
    Student_group* group_nptr=NULL;
    while (current != NULL) 
	{
        compare = current->next;
        while (compare != NULL) {
            if (current->grp_id == compare->grp_id) {
                group_nptr = (Student_group*)malloc(sizeof(Student_group));
                group_nptr->student1= current;
                group_nptr->student2 = compare;
                group_nptr->grp_id=current->grp_id;
                group_nptr->marks_given=-1.0;
                group_nptr->a_sub_s=NOT_SUBMITTED;
                group_nptr->a_eva_s=NOT_EVALUATED;
                group_nptr->viva=NO;
                group_nptr->next = group_lptr;
                group_lptr = group_nptr;
            }
            compare = compare->next;
        }
        current = current->next;
    }

    return group_lptr;
}
/*We make a function, which takes a list of students */

void insert_list(Student* student_lptr, Assignment* asg_mptr)
{
	Student *stu_lptr, *stu_nptr;
	stu_lptr=stu_nptr=NULL;
	int stud_id,num_students;
	printf("\nNumber of students you wish to enter?");
	scanf("%d",&num_students);
	for(int i=0;i<num_students;i++)
	{
			stu_nptr=(Student*)malloc(sizeof(Student));
			stu_nptr->asg_id=asg_mptr->asg_id;
			strcpy(stu_nptr->asg_topic,asg_mptr->topic);
			stu_nptr->a_eva_s=NOT_EVALUATED;
			stu_nptr->a_sub_s=NOT_SUBMITTED;
			stu_nptr->off_marks=-1.0;
			stu_nptr->viva_marks=-1.0;
			printf("\nPlease enter student's name.");
			scanf("%s",stu_nptr->name);
			printf("\nPlease enter new student's 4 digit student id.");
			scanf("%d",&stu_nptr->stu_id);
			printf("\nPlease enter student's 4 digit group id.");
			scanf("%d",&stu_nptr->grp_id);
			printf("\nPlease enter student's partner's 4 digit group id.");
			scanf("%d",&stu_nptr->part_id);
			printf("\nDeadline of the assignment in the format DDMMYY min sec");
			scanf("%d%d%d%d%d",&stu_nptr->_deadline.year,&stu_nptr->_deadline.month,&stu_nptr->_deadline.day,&stu_nptr->_deadline.hour,&stu_nptr->_deadline.minute);
			stu_nptr->next=stu_lptr;
			stu_lptr=stu_nptr;
	}
	/*now, we have new student additions linked list with stu_lptr as head
	and our main students linked list, with student_lptr as head, 
	So, now we concatenate these two lists, our new students lists followed by original main list.*/
	
	student_lptr=Concatenate(stu_lptr,student_lptr);

	/* There could be cases where more than one nodes have same student in that, so we remove duplicate nodes with 
	student id, and we remove second appearances, as it is posssible that if the user is re entering a node, it must be having modified data
	so, we keep the new ones and remove the old duplicates. */
	
	removeDuplicates(student_lptr);
	
	
	//now we group the students
	
	Student_group* group_ptr;
	group_ptr=create_student_group(student_lptr);
	asg_mptr->stu_group=group_ptr;
}


Assignment* ins_asg_list(Student* stu_lptr, Assignment* asg_mptr, int assignment_id, char* title)
{
	//first check is the assignment present
	Assignment* asg_ptr=asg_mptr;
	int asg_exists=0;
	int option;
	while((asg_exists==0)&&(asg_ptr!=NULL))
	{
		if(asg_ptr->asg_id==assignment_id)
		{
			asg_exists=1;
		}
		else
		{
			asg_ptr=asg_ptr->next;
		}
	}
	if(asg_exists==1)
	{
		printf("\nAn assignemnt with same id already exists in the assignment list.");
	}
	else 
	{
		Assignment* asg_nptr=(Assignment*)malloc(sizeof(Assignment));
		asg_nptr->asg_id=assignment_id;
		strcpy(asg_nptr->topic,title);
		asg_nptr->a_dec_s=DECLARED;
		asg_nptr->a_due_s=DUE_NOT_OVER;
		asg_nptr->a_eva_s=NOT_EVALUATED;
		printf("\nPress 1 to add student list for this new assignment?");
		scanf("%d",&option);
		if(option==1)
		{
			insert_list(stu_lptr,asg_nptr);
		}
		else
		{
			asg_nptr->stu_group=NULL;
		}
	}
}

/*Change status of assignment and student lists based on different events
a. Student-group submitting the assignment */

int compareTime(Time sub_time, Time deadline)
{
	int ret_val;
	if(sub_time.year>deadline.year)
	{
		ret_val=-1;
	}
	else if(sub_time.year==deadline.year)
	{
		if(sub_time.month>deadline.month)
		{
			ret_val=-1;
		}
		else if (sub_time.month==sub_time.month)
		{
			if(sub_time.day>deadline.day)
			{
				ret_val=-1;
			}
			else if(sub_time.day==deadline.day)
			{
				if(sub_time.hour>deadline.hour)
				{
					ret_val=-1;
				}
				else if(sub_time.hour==sub_time.hour)
				{
					if(sub_time.minute>deadline.minute)
					{
						ret_val=-1;
					}
					else if (sub_time.minute==deadline.minute)
					{
						ret_val=0;
					}
					else
					{
						ret_val=1;
					}
				}
				else
				{
					ret_val=1;
				}
			}
			else
			{
				ret_val=1;
			}
		}
		else
		{
			ret_val=1;
		}
	}
	else
	{
		ret_val=1;
	}
	return ret_val;
}

void make_changes(Student* student_lptr, Assignment* asg_lptr)
{ 
	int submiters_group_id,submiters_asg_id;
	Time current_time; 
	
	printf("\nPlease enter the assignment id of the submitting group.");
	scanf("%d",&submiters_group_id);
	printf("\nPlease enter the group id of the submitting group.");
	scanf("%d",&submiters_asg_id);
	/* We assumed the use of time library is not permissable.
	With the time library, we would have used localtime() function.
	But here, we just take the current time input from the user. */
	printf("\nPlease enter today's date.");
	scanf("%d",&current_time.day);
	printf("\nPlease enter this month's number(e.g. 1 for January, 2 for February, so on.)");
	scanf("%d",&current_time.month);
	printf("\nWhat year is it?");
	scanf("%d",&current_time.year);
	printf("\nPlease enter current time in hours.");
	scanf("%d",&current_time.hour);
	printf("\nIt is %d passed how many minutes?",current_time.hour);
	scanf("%d",&current_time.minute);
	Assignment* asg_ptr;
	Student *stud1, *stud2;
	int asg_found=0,group_found=0;
	while((asg_ptr!=NULL)&&(asg_found==0))
	{
		if(asg_ptr->asg_id==submiters_asg_id)
		{
			asg_found=1;
			Student_group* group_ptr=(asg_ptr->stu_group);
			while((group_ptr!=NULL)&&(group_found==0))
			{
				if(group_ptr->grp_id==submiters_group_id)
				{
					group_ptr->a_dec_s=DECLARED;
					group_ptr->a_sub_s=SUBMITTED;
					group_ptr->a_eva_s=NOT_EVALUATED;
					group_ptr->viva=NO;
					group_ptr->marks_given=-1.0;
					stud1=group_ptr->student1;
					stud2=group_ptr->student2;
				}
				else
				{
					group_ptr=group_ptr->next;
				}
			}
			if(group_found==0)
			{
				printf("Group with group id %d is not present in the entered assignment's groups.",submiters_group_id);
			}
		}
		else
		{
			asg_ptr=asg_ptr->next;
		}
	}
	if(asg_found==0)
	{
		printf("This group's assignment does not exist in current assignments.");
	}
	/* We have made changes in assignment list's group field, when a student group submits their assignment.
	Now we have to find those students in the main student list and change their statuses. */
	stud1->a_sub_s=SUBMITTED;
	stud1->a_eva_s=NOT_EVALUATED;
	stud1->off_marks=-1.0;
	stud1->viva_marks=-1.0;
	stud2->a_sub_s=SUBMITTED;
	stud2->a_eva_s=NOT_EVALUATED;
	stud2->off_marks=-1.0;
	stud2->viva_marks=-1.0;
}
/* 
 3b) Assignment for one specific student group is evaluated. Once a particular
assignment is evaluated for all student-groups to whom the assignment was
given, the status of the assignment itself changes to �evaluated�. */
int all_groups_evaluated(Student_group* group_list) 
{
    int flag = 1;
    while (group_list != NULL && flag) 
	{
        if (group_list->a_eva_s != EVALUATED) 
		{
            flag = 0; 
        }
        group_list = group_list->next;
    }
    return flag; 
}
void asg_evaluated(Assignment* asg_list)
{
    while (asg_list != NULL) {
        int flag = all_groups_evaluated(asg_list->stu_group);
        if(flag==1)
        {
        asg_list->a_eva_s = EVALUATED;
    	}
    	else
    		asg_list->a_eva_s = NOT_EVALUATED;
        asg_list = asg_list->next;
    }
}




void evaluate_asg (Assignment* asg_lptr, Student* stu_lptr)
{
	int aid,gid;
	printf("\nPlease input the assignment id of the student group. ");
	scanf("%d",&aid);
	printf("\nPlease input the group id of that student group. ");
	scanf("%d",&gid);
	Assignment* asg_ptr;
	Student_group* student_group;
	asg_ptr=find_asg_ptr(asg_lptr,aid);
	if(asg_ptr!=NULL)
	{
		Student_group *s_grp=asg_ptr->stu_group;
		student_group=asg_ptr->stu_group;
		//we go to that student's group
		int group_found=0;
		while((s_grp!=NULL)&&(group_found==0))
		{
			if(s_grp->grp_id==gid)
			{
				group_found=1;
				s_grp->student1->a_eva_s=EVALUATED;
				s_grp->student2->a_eva_s=EVALUATED;
				int stud1_off_marks, stud2_off_marks,viva_choice;
				printf("\nOffline marks of student with student id %d? ",s_grp->student1->stu_id);
				scanf("%f",&s_grp->student1->off_marks);
				printf("\nOffline marks of student with student id %d? ",s_grp->student2->stu_id);
				scanf("%f",&s_grp->student2->off_marks);
				printf("\nPress 1 if viva of this group will be taken now.\nPress 0 otherwise. ");
				scanf("%d",&viva_choice);
				if(viva_choice==1)
				{
					s_grp->viva=YES;
					int stud1_vmarks,stud2_vmarks;
					printf("\nViva marks of student with student id %d? ",s_grp->student1->stu_id);
					scanf("%f",&s_grp->student1->viva_marks);
					printf("\nViva marks of student with student id %d? ",s_grp->student2->stu_id);
					scanf("%f",&s_grp->student2->viva_marks);				
				}
				else
				{
					s_grp->viva=NO;
				}
			}
			else
			{
				s_grp=s_grp->next;
			}
		}
		if(group_found==0)
		{
			printf("\nThe given assignment has not been allocated to the students with group id %d",gid);
		}
	}
	else
	{
		printf("\nThe entered assignment is not present in the assignment list. Please add it.");
	}
	int flag=1;
	Assignment* asg_pointer=asg_lptr;
	asg_evaluated(asg_pointer);
}

//4 /*Print the list of assignments that are declared but not evaluated. */
void print_not_evaluated_assignments(Assignment* assignment_lptr)
{
    printf("List of assignments declared but not evaluated:\n");
    Assignment* assignment_ptr = assignment_lptr;
    while (assignment_ptr != NULL)
    {
        if (assignment_ptr->a_dec_s == DECLARED && assignment_ptr->a_eva_s == NOT_EVALUATED)
        {
            printf("Assignment ID: %d\n", assignment_ptr->asg_id);
            printf("Topic: %s\n", assignment_ptr->topic);
            printf("Declaration Status: DECLARED\n");
            printf("Evaluation Status: NOT_EVALUATED\n");
            printf("\n");
        }
        assignment_ptr = assignment_ptr->next;
    }
}





/* 5. Print the list student groups who have not submitted the assignments even if the due-
date is over. */


// Function to print the list of student groups who have not submitted the assignment even if the due-date is over
void printLateSubmissions(Assignment* head) {
    Assignment* curr_asg = head;
    while (curr_asg != NULL) {
        if (curr_asg->a_due_s == DUE_OVER) {
            Student_group* curr_grp = curr_asg->stu_group;
            while (curr_grp != NULL) {
                if (curr_grp->a_sub_s == NOT_SUBMITTED) {
                    printf("Group ID %d has not submitted the assignment '%s'\n", curr_grp->grp_id, curr_asg->topic);
                }
                curr_grp = curr_grp->next;
            }
        }
        curr_asg = curr_asg->next;
    }
}
 
/*  6.  Print the list of student groups for whom the assignment is yet-to-be-evaluated even
though they have been submitted. In case viva is remaining to be taken, that is
explicitly to be mentioned. */ 

//6 
void yet_to_be(Assignment* asg_list)
{
	printf("List of assignments yet to be evaluated after submission:\n");
    Assignment* asg_ptr = asg_list;
    while (asg_ptr != NULL)
    {
        Student_group* group_ptr = asg_ptr->stu_group;
        while (group_ptr != NULL)
        {
            if (group_ptr->a_sub_s == SUBMITTED && group_ptr->a_eva_s == NOT_EVALUATED)
            {
            	printf("Group ID: %d\n", group_ptr->grp_id);
            	printf("Submission Status: SUBMITTED\n");
            	printf("Evaluation Status: NOT_EVALUATED\n");
            	printf("\n");
            	if(group_ptr->viva = NO)
            	{
               	    printf("Viva remaining\n");
            	}
            	else
            	{
			 		printf("Viva is taken\n");
		    	}
        	}
            group_ptr = group_ptr->next;
        }
        asg_ptr = asg_ptr->next;
    }
}


/* 7.) For a given assignment id, print the details of student-groups, in the decreasing order
of marks they have received in the assignment. */
/* Merge two sorted linked lists in descending order */
Student_group* mergeDescending(Student_group* a, Student_group* b) {
    Student_group* result = NULL;

    if (a == NULL) {
        result= b;
    }
    else if (b == NULL) {
        result= a;
    }

    if (a->marks_given >= b->marks_given) {
        result = a;
        result->next = mergeDescending(a->next, b);
    }
    else {
        result = b;
        result->next = mergeDescending(a, b->next);
    }

    return result;
}


/* Split the linked list into two halves */
void split(Student_group* source, Student_group** front_ref, Student_group** back_ref) {
    Student_group* slow = source;
    Student_group* fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL;
}

/* Sort the linked list in decreasing order using merge sort */
void mergeSort(Student_group** head_ref) {
    Student_group* head = *head_ref;
    Student_group* a, * b;
	/* Base case: the list is already sorted */
    if (head == NULL || head->next == NULL) {
         /* Do nothing */
    }
	else{
		/* Split the list into two halves */
    	split(head, &a, &b);
		mergeSort(&a);
    	mergeSort(&b);

    	*head_ref = mergeDescending(a, b);
	}
}

void printList(Student_group* node) {
    while (node != NULL) {
        printf("%d ", node->grp_id);
        node = node->next;
    }
}

//7

void print_decorder_groups(Assignment* asg_list,int assi_id)
{
    Assignment* asg_ptr = asg_list;
    while (asg_ptr != NULL)
    {
	    if(asg_ptr->asg_id==assi_id)
		{
			printf("Assignment %d: %s\n", asg_ptr->asg_id, asg_ptr->topic);
        
        	Student_group* group_ptr = asg_ptr->stu_group;
        
        	while (group_ptr != NULL)
        	{	
        	    mergeSort(&group_ptr);
    			/* Printing the linked list in decreasing order */
  			    printf("Linked List in Decreasing Order: ");
  				printList(group_ptr);
        	}
    	}
        asg_ptr = asg_ptr->next;
    }
}




/* 8.) Print student groups receiving top marks in each of the assignment given.  */

void print_top_groups(Assignment* asg_list)
{
    Assignment* asg_ptr = asg_list;
    while (asg_ptr != NULL)
    {
        printf("Assignment %d: %s\n", asg_ptr->asg_id, asg_ptr->topic);
        
        Student_group* group_ptr = asg_ptr->stu_group;
        Student_group* top_group_ptr = NULL;
        float top_marks = 0.0;
        while (group_ptr != NULL)
        {
            float total_marks = 0.0;
            total_marks = group_ptr->student1->off_marks + group_ptr->student2->off_marks + group_ptr->student1->viva_marks + group_ptr->student2->viva_marks;
            if (total_marks > top_marks)
            {
                top_marks = total_marks;
                top_group_ptr = group_ptr;
            }
            group_ptr = group_ptr->next;
        }
        
        if (top_group_ptr != NULL)
        {
            printf("Top Group:\n");
            printf("Group ID: %d\n", top_group_ptr->grp_id);
            printf("Total Marks: %.2f\n", top_marks);
        }
        else
        {
            printf("No groups submitted for this assignment.\n");
        }
        asg_ptr = asg_ptr->next;
    }
}


int main() 
{
    // Initialize linked lists and other data structures
    Student *students_head = NULL;
    Assignment *assignments_head = NULL;

    // Display a menu and process user input
    int choice = 0;
    do 
	{
        printf("\n\n");
        printf("Please choose a valid option:\n");
        printf("1. Insert a student record\n");
        printf("2. Insert an assignment record\n");
        printf("3. Change status of assignment and student lists\n");
        printf("4. Print list of assignments that are declared but not evaluated\n");
        printf("5. Print list of student groups who have not submitted assignments\n");
        printf("6. Print list of student groups for whom the assignment is yet-to-be-evaluated\n");
        printf("7. Print details of student-groups for a given assignment ID\n");
        printf("8. Print student groups receiving top marks in each assignment\n");
        printf("9. Print student all status assignment evaluated\n");
        printf("10. Print students list.\n ");
        printf("11. Print assignment list.\n ");
        printf("99. Exit program\n");

        scanf("%d", &choice);

        if(choice==1)
		{
            int stu_id,c,d,e;
            Time t;
            char b[30],f[30];
            printf("enter id ");
           	scanf("%d",&stu_id);
           	printf("Please enter student's name. ");
           	scanf("%s",b);
           	printf("partner id? ");
           	scanf("%d",&c);
           	printf("g id ");
           	scanf("%d",&d);
           	printf("assignment id? ");
           	scanf("%d",&e);
           	printf("name topic ");
           	scanf("%s",f);
           	printf("\nPlease enter sub date. ");
			scanf("%d",&t.day);
			printf("\nPlease enter submission month's number(e.g. 1 for January, 2 for February, so on.) ");
			scanf("%d",&t.month);
			printf("\nSubmission year? ");
			scanf("%d",&t.year);
			printf("\nAt what time(in 24 hour format? Just input hour. E.g. 2:50, input 2. for 22:30, input 22.)");
			scanf("%d",&t.hour);
			printf("\n%d passed how many minutes?",t.hour);
			scanf("%d",&t.minute);
			printf("scanned");
           	students_head=ins_stu_list(students_head, &assignments_head, stu_id, b, c, d, e, f,t);
			   
			printf("\ndoneee");
		}
        else if (choice==2)
        {
		
            int i;
           	char j[30];
           	printf("Please enter assignment id. ");
           	scanf("%d",&i);
           	printf("Topic of the assignment? ");
           	scanf("%s",j);
            ins_asg_list(students_head, assignments_head,i,j);
    	}
        else if (choice==3)
        {
            printf("3.a");
            make_changes(students_head, assignments_head);
		}
		else if (choice==4)
		{
            print_not_evaluated_assignments(assignments_head);
		}
		else if (choice==5)
		{
        	printLateSubmissions(assignments_head);
    	}
		else if (choice==6)
		{
            yet_to_be(assignments_head);
		}
		else if (choice==7)
		{
		
            int p;
            printf("ass id ");
            scanf("%d",&p);
            print_decorder_groups(assignments_head, p);
		}
		else if (choice==8)
		{
            print_top_groups(assignments_head);
		}
		else if (choice==9)
		{
		
            printf("3.b");
            evaluate_asg(assignments_head, students_head);
		}
		else if (choice==10)
		{
			display_students(students_head);
		}
		else if(choice==11)
		{
			display_assignments(assignments_head);
		}
	}while (choice != 99);



    return 0;
}

