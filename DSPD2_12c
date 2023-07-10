//Using AVL trees.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {NOT_SUBMITTED, SUBMITTED} asg_sub_status;
typedef enum {NOT_DECLARED, DECLARED} asg_declare_status;
typedef enum {DUE_NOT_OVER, DUE_OVER} asg_due_status;
typedef enum {NOT_EVALUATED, EVALUATED} asg_eval_status;
typedef enum {NO,YES}isVivaTaken;
typedef enum{FAILURE,SUCCESS}status_code;

typedef struct Time_tag {
	int day;
	int month;
	int year;
	int hour;
	int minute;
}Time;

typedef struct Student_tag {
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
	struct Student_tag* left;
	struct Student_tag* right;
	int height;
} Student;

typedef struct student_group_tag {
	Student *student1, *student2;
	int grp_id;
	asg_declare_status a_dec_s;
	asg_sub_status a_sub_s;
	asg_eval_status a_eva_s;
	isVivaTaken viva;
	float marks_given;
	struct student_group_tag* left;
	struct student_group_tag* right;
	int height;
} Student_group;

typedef struct assg_tag {
	int asg_id;
	char topic[30];
	asg_declare_status a_dec_s;
	asg_due_status a_due_s;
	asg_eval_status a_eva_s;
	Time _deadline;
	Student_group* stu_group;
	struct assg_tag* left;
	struct assg_tag* right;
	int height;
} Assignment;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////student

int max(int a, int b) {
	if (a > b) {
		return a;
	} 
	else {
		return b;
	}
}

int get_height_stu(Student* student) {
	if (student == NULL) {
		return 0;
	}
 	return student->height;
}

int get_balance_stu(Student* student_root) {
	if (student_root == NULL) {
		return 0;
	}
	return get_height_stu(student_root->left) - get_height_stu(student_root->right);
}
Student* right_rotate_stu(Student* student_root) {
	Student* new_root = student_root->left;
	Student* right_subtree = new_root->right;

	// Perform rotation
	new_root->right = student_root;
	student_root->left = right_subtree;

	// Update heights
	student_root->height = 1 + max(get_height_stu(student_root->left), get_height_stu(student_root->right));
	new_root->height = 1 + max(get_height_stu(new_root->left), get_height_stu(new_root->right));

	// Return the new root
	return new_root;
}
Student* left_rotate_stu(Student* student_root) {
	Student* new_root = student_root->right;
	Student* left_child = new_root->left;
	
	// Perform rotation
	new_root->left = student_root;
	student_root->right = left_child;
	
	// Update heights
	student_root->height = max(get_height_stu(student_root->left), get_height_stu(student_root->right)) + 1;
	new_root->height = max(get_height_stu(new_root->left), get_height_stu(new_root->right)) + 1;
	
	// Return new root
	return new_root;
}


Student* ins_avl_stu(Student* student_root, Student* student_nptr) {
	// perform the regular BST insertion
	if (student_root == NULL) {
		return student_nptr;
	}
	if (student_nptr->stu_id < student_root->stu_id) {
		student_root->left = ins_avl_stu(student_root->left, student_nptr);
	} 
	else if (student_nptr->stu_id > student_root->stu_id) {
		student_root->right = ins_avl_stu(student_root->right, student_nptr);
	}
	
	// update the height of the current node
	student_root->height = 1 + max(get_height_stu(student_root->left), get_height_stu(student_root->right));
	
	// check if the current node is balanced
	int balance_factor = get_balance_stu(student_root);
	
	// if the node is unbalanced, perform rotation to balance it
	if (balance_factor > 1 && student_nptr->stu_id < student_root->left->stu_id) {
		return right_rotate_stu(student_root);
	}
	if (balance_factor < -1 && student_nptr->stu_id > student_root->right->stu_id) {
		return left_rotate_stu(student_root);
	}
	if (balance_factor > 1 && student_nptr->stu_id > student_root->left->stu_id) {
		student_root->left = left_rotate_stu(student_root->left);
		return right_rotate_stu(student_root);
	}
	if (balance_factor < -1 && student_nptr->stu_id < student_root->right->stu_id) {
		student_root->right = right_rotate_stu(student_root->right);
		return left_rotate_stu(student_root);
	}
	
	return student_root;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////asg

int get_height_asg(Assignment* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

int get_balance_asg(Assignment* node) {
	if (node == NULL) {
		return 0;
	}
	return get_height_asg(node->left) - get_height_asg(node->right);
}

Assignment* right_rotate_asg(Assignment* y) {
	Assignment* x = y->left;
	Assignment* T2 = x->right;
	
	// Perform rotation
	x->right = y;
	y->left = T2;
	
	// Update heights
	y->height = 1 + max(get_height_asg(y->left), get_height_asg(y->right));
	x->height = 1 + max(get_height_asg(x->left), get_height_asg(x->right));
	
	// Return new root
	return x;
}
	
Assignment* left_rotate_asg(Assignment* x) {
	Assignment* y = x->right;
	Assignment* T2 = y->left;
	
	// Perform rotation
	y->left = x;
	x->right = T2;
	
	// Update heights
	x->height = 1 + max(get_height_asg(x->left), get_height_asg(x->right));
	y->height = 1 + max(get_height_asg(y->left), get_height_asg(y->right));
	
	// Return new root
	return y;
}


Assignment* ins_avl_asg(Assignment* asg_root, Assignment* asg_nptr) {
	// If the AVL tree is empty, return the new node as the root
	if (asg_root == NULL) {
		return asg_nptr;
	}
	// Insert the new node as a regular BST node
	if (asg_nptr->asg_id < asg_root->asg_id) {
		asg_root->left = ins_avl_asg(asg_root->left, asg_nptr);
	} 
	else if (asg_nptr->asg_id > asg_root->asg_id) {
		asg_root->right = ins_avl_asg(asg_root->right, asg_nptr);
	}
	// Update the height of the current node
	asg_root->height = 1 + max(get_height_asg(asg_root->left), get_height_asg(asg_root->right));
	
	// Calculate the balance factor of the current node
	int balance_factor = get_balance_asg(asg_root);
	
	// If the current node is unbalanced, perform the appropriate rotation(s)
	if (balance_factor > 1 && asg_nptr->asg_id < asg_root->left->asg_id) {
		return right_rotate_asg(asg_root);
	}
	if (balance_factor < -1 && asg_nptr->asg_id > asg_root->right->asg_id) {
		return left_rotate_asg(asg_root);
	}
	if (balance_factor > 1 && asg_nptr->asg_id > asg_root->left->asg_id) {
		asg_root->left = left_rotate_asg(asg_root->left);
		return right_rotate_asg(asg_root);
	}
	if (balance_factor < -1 && asg_nptr->asg_id < asg_root->right->asg_id) {
		asg_root->right = right_rotate_asg(asg_root->right);
		return left_rotate_asg(asg_root);
	}
	
	// Return the current node
	return asg_root;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////group

int get_height(Student_group* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

int get_balance_factor(Student_group* grp_ptr) {
	if (grp_ptr == NULL) {
		return 0;
	}
	return get_height(grp_ptr->left) - get_height(grp_ptr->right);
}

Student_group* rotate_left(Student_group* x) {
	Student_group* y = x->right;
	Student_group* T2 = y->left;
	
	// Perform rotation
	y->left = x;
	x->right = T2;
	
	// Update heights
	x->height = 1 + max(get_height(x->left), get_height(x->right));
	y->height = 1 + max(get_height(y->left), get_height(y->right));
	
	// Return new root
	return y;
}
Student_group* rotate_right(Student_group* y) {
	Student_group* x = y->left;
	Student_group* T2 = x->right;
	
	// Perform rotation
	x->right = y;
	y->left = T2;
	
	// Update heights
	y->height = 1 + max(get_height(y->left), get_height(y->right));
	x->height = 1 + max(get_height(x->left), get_height(x->right));
	
	// Return new root
	return x;
}

void ins_grp_list_avl(Student_group** grp_lpptr, int grp_id, Student* student_nptr) {

	if (*grp_lpptr == NULL) {
	// create new student group node and set its fields
	Student_group* grp_nptr = (Student_group*)malloc(sizeof(Student_group));
	grp_nptr->student1 = student_nptr;
	grp_nptr->student2 = NULL;
	grp_nptr->grp_id = grp_id;
	grp_nptr->a_dec_s = DECLARED;
	grp_nptr->a_sub_s = NOT_SUBMITTED;
	grp_nptr->a_eva_s = NOT_EVALUATED;
	grp_nptr->viva = NO;
	grp_nptr->marks_given = -1.0;
	grp_nptr->left = NULL;
	grp_nptr->right = NULL;
	grp_nptr->height = 1;
	
	// set the new group node as the root of the AVL tree
	*grp_lpptr = grp_nptr;
	return;
	}

	// find the position to insert the new group node
	int balance_factor;
	if (grp_id < (*grp_lpptr)->grp_id) {
		ins_grp_list_avl(&((*grp_lpptr)->left), grp_id, student_nptr);
		balance_factor = get_balance_factor(*grp_lpptr);
		if (balance_factor > 1) {
			if (grp_id < (*grp_lpptr)->left->grp_id) {
				*grp_lpptr = rotate_right(*grp_lpptr);
			} 
			else {
				(*grp_lpptr)->left = rotate_left((*grp_lpptr)->left);
				*grp_lpptr = rotate_right(*grp_lpptr);
			}
		}
	} 
	else if (grp_id > (*grp_lpptr)->grp_id) {
		ins_grp_list_avl(&((*grp_lpptr)->right), grp_id, student_nptr);
		balance_factor = get_balance_factor(*grp_lpptr);
		if (balance_factor < -1) {
			if (grp_id > (*grp_lpptr)->right->grp_id) {
			*grp_lpptr = rotate_left(*grp_lpptr);
			} 
			else {
			(*grp_lpptr)->right = rotate_right((*grp_lpptr)->right);
			*grp_lpptr = rotate_left(*grp_lpptr);
			}
		}
	} 
	else {
		// group already exists, add the new student node to the existing group
		if ((*grp_lpptr)->student2 == NULL) {
			(*grp_lpptr)->student2 = student_nptr;
		}
		else {
			printf("Error: Group already has 2 students!\n");
		}
	}
	
	// update the height of the current group node
	(*grp_lpptr)->height = 1 + max(get_height((*grp_lpptr)->left), get_height((*grp_lpptr)->right));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////tree over

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q1

Assignment* find_asg_ptr(Assignment* asg_ptr, int assignment_id) {
	// traverse the AVL tree until the node with the given assignment ID is found
	while (asg_ptr != NULL) {
		if (assignment_id < asg_ptr->asg_id) {
			asg_ptr = asg_ptr->left;
		} 
		else if (assignment_id > asg_ptr->asg_id) {
			asg_ptr = asg_ptr->right;
		} 
		else {
		// node with given assignment ID is found
		return asg_ptr;
		}
	}
	// node with given assignment ID is not found
	return NULL;
}



Student* ins_stu_list(Student* student_root, Assignment** asg_lpptr, int student_id,const char* student_name, int partner_id, int group_id, int assignment_id,const char* assignment_topic, Time deadline_) {

	// create new student node and set its fields
	Student* student_nptr = (Student*)malloc(sizeof(Student));
	student_nptr->stu_id = student_id;
	strcpy(student_nptr->name, student_name);
	student_nptr->part_id = partner_id;
	student_nptr->grp_id = group_id;
	student_nptr->asg_id = assignment_id;
	strcpy(student_nptr->asg_topic, assignment_topic);
	student_nptr->_deadline = deadline_;
	student_nptr->a_sub_s = NOT_SUBMITTED;
	student_nptr->a_eva_s = NOT_EVALUATED;
	student_nptr->viva_marks = -1.0;
	student_nptr->off_marks = -1.0;
	student_nptr->left = NULL;
	student_nptr->right = NULL;
	student_nptr->height = 1;
	 
	// insert the student node into AVL tree
	student_root = ins_avl_stu(student_root, student_nptr);
	
	// update the assignment list with the new student node
	Assignment* asg_ptr = *asg_lpptr;
	Assignment* asg_mptr = find_asg_ptr(asg_ptr, assignment_id);
	
	if (asg_mptr != NULL) {
		ins_grp_list_avl(&asg_mptr->stu_group, group_id, student_nptr);
	}
	else {
		// create new assignment node and set its fields
		Assignment* asg_nptr = (Assignment*)malloc(sizeof(Assignment));
		asg_nptr->asg_id = assignment_id;
		strcpy(asg_nptr->topic, assignment_topic);
		asg_nptr->a_dec_s = DECLARED;
		asg_nptr->a_due_s = DUE_NOT_OVER;
		asg_nptr->a_eva_s = NOT_EVALUATED;
		asg_nptr->_deadline = deadline_;
		asg_nptr->stu_group = NULL;
		asg_nptr->left = NULL;
		asg_nptr->right = NULL;
		asg_nptr->height = 1;
		
		// insert the new assignment node into AVL tree
		*asg_lpptr = ins_avl_asg(*asg_lpptr, asg_nptr);
		
		// insert the new student node into the new assignment node's group list
		ins_grp_list_avl(&asg_nptr->stu_group, group_id, student_nptr);
	}
	
	return student_root;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q2

Assignment* ins_asg_list(Student** student_lpptr, Assignment* asg_lptr,int assignment_id,const char* assignment_topic,const char* student_name,int student_id,int group_id,int partner_id, Time deadline_) {
	 
	  
	Student* student_nptr = (Student*)malloc(sizeof(Student));
	student_nptr->stu_id = student_id;
	strcpy(student_nptr->name, student_name);
	student_nptr->part_id = partner_id;
	student_nptr->grp_id = group_id;
	student_nptr->asg_id = assignment_id;
	strcpy(student_nptr->asg_topic, assignment_topic);
	student_nptr->_deadline = deadline_;
	student_nptr->a_sub_s = NOT_SUBMITTED;
	student_nptr->a_eva_s = NOT_EVALUATED;
	student_nptr->viva_marks = -1.0;
	student_nptr->off_marks = -1.0;
	student_nptr->left = NULL;
	student_nptr->right = NULL;
	student_nptr->height = 1;
	 
	*student_lpptr = ins_avl_stu(*student_lpptr, student_nptr);
	// update the assignment list with the new student node
	Assignment* asg_ptr = asg_lptr;
	Assignment* asg_mptr = find_asg_ptr(asg_ptr, assignment_id);
	
	if (asg_mptr != NULL) {
		ins_grp_list_avl(&asg_mptr->stu_group, group_id, student_nptr);
	}
	else {
	
		Assignment* asg_nptr = (Assignment*)malloc(sizeof(Assignment));
		asg_nptr->asg_id = assignment_id;
		strcpy(asg_nptr->topic, assignment_topic);
		asg_nptr->a_dec_s = DECLARED;
		asg_nptr->a_due_s = DUE_NOT_OVER;
		asg_nptr->a_eva_s = NOT_EVALUATED;
		asg_nptr->_deadline = deadline_;
		asg_nptr->stu_group = NULL;
		asg_nptr->left = NULL;
		asg_nptr->right = NULL;
		asg_nptr->height = 1;
		 
		asg_lptr = ins_avl_asg(asg_lptr, asg_nptr);
		
		ins_grp_list_avl(&asg_nptr->stu_group, group_id, student_nptr);
	}
	
	return asg_lptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q3.a

int compareTime(Time sub_time, Time deadline) {
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
				else if(sub_time.hour==deadline.hour)
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

Assignment* avl_search_assignment(Assignment* root, int asg_id) {
	if (root == NULL) {
		return NULL; // Tree is empty or the assignment is not found
	}
	
	// Perform binary search in the AVL tree
	if (asg_id < root->asg_id) {
		return avl_search_assignment(root->left, asg_id);
	} 
	else if (asg_id > root->asg_id) {
		return avl_search_assignment(root->right, asg_id);
	} 
	else {
		int ans;
		Time current_time; 
		printf("\ncurrent time of the assignment submission in the format DDMMYY Hr min ");
		scanf("%d%d%d%d%d",&current_time.day,&current_time.month,&current_time.year,&current_time.hour,&current_time.minute);
		ans=compareTime(current_time, root->_deadline);
		
		if(ans==-1)
		{
			root->a_due_s = DUE_OVER;
		}
		else {
			root->a_due_s = DUE_NOT_OVER;
		}
		
		return root; // Found the assignment with the given asg_id
	}
}

Student_group* avl_search_group(Student_group* root, int group_id) {
	if (root == NULL) {
		return NULL; // Tree is empty or the group is not found
	}
	
	// Perform binary search in the AVL tree
	if (group_id < root->grp_id) {
		return avl_search_group(root->left, group_id);
	} 
	else if (group_id > root->grp_id) {
		return avl_search_group(root->right, group_id);
	} 
	else {
		return root; // Found the group with the given group_id
	}
}



void make_changes(Student* student_root,Assignment* assg_root, int asg_id, int group_id) {
 
	if (assg_root == NULL) {
		return; // Assignment tree is empty
	}
	
	// Search for the assignment with the given asg_id in the AVL tree
	Assignment* node = avl_search_assignment(assg_root, asg_id);
	if (node == NULL) {
		printf("Assignment with the given asg_id not found in the tree");
		return;
	}
	
	// Search for the group with the given group_id in the AVL tree of the assignment
	Student_group* group_node = avl_search_group(node->stu_group, group_id);
	if (group_node == NULL) {
		printf("Group with the given group_id not found in this assignment");
		return;
	}
	
	// Change the submission status of the group to "Submitted"
	group_node->a_sub_s = SUBMITTED;
 
}

void update_student_st(Student* student_root, int group_id) {
	if (student_root == NULL) {
		return;
	}
	
	update_student_st(student_root->left, group_id);
	
	if (student_root->grp_id == group_id) {
		student_root->a_sub_s = SUBMITTED;
	}
	
	update_student_st(student_root->right, group_id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q3.b




Assignment* avl_search_assignment_b(Assignment* root, int asg_id) {
	if (root == NULL) {
		return NULL; // Tree is empty or the assignment is not found
	}
	
	// Perform binary search in the AVL tree
	if (asg_id < root->asg_id) {
		return avl_search_assignment_b(root->left, asg_id);
	} 
	else if (asg_id > root->asg_id) {
		return avl_search_assignment_b(root->right, asg_id);
	} 
	else {
		return root; // Found the assignment with the given asg_id
	}
}

Student_group* avl_search_group_b(Student_group* root,Student* stude, int group_id) {
	if (root == NULL) {
		return NULL; // Tree is empty or the group is not found
	}
	
	// Perform binary search in the AVL tree
	if (group_id < root->grp_id) {
		return avl_search_group_b(root->left,stude, group_id);
	} 
	else if (group_id > root->grp_id) {
		return avl_search_group_b(root->right,stude, group_id);
	} 
	else {
	
		float a,b,add,ADD=0;
		float c=-1,d=-1;
		root->a_eva_s=EVALUATED;
		printf("\nOffline marks of student 1? ");
		scanf("%f",&a);
		root->student1->off_marks=a;
		root->student1->a_eva_s = EVALUATED;
		ADD=ADD+a;
		if (root->student2 != NULL) {
			printf("\nOffline marks of student 2? ");
			scanf("%f",&b);
			root->student2->off_marks=b;
			root->student2->a_eva_s = EVALUATED;
			ADD=ADD+b;
		}
		printf("\nPress 1 if viva of this group will be taken now.\nPress 0 otherwise. ");
		int viva_choice;
		scanf("%d", &viva_choice);
		if (viva_choice == 1) {
			root->viva = YES;
			printf("\nViva marks of student 1 ");
			scanf("%f", &c);
			root->student1->viva_marks=c;
			ADD =ADD+c;
			if (root->student2 != NULL) {
				printf("\nViva marks of student 2 ");
				scanf("%f", &d);
				root->student2->viva_marks=d;
				ADD = ADD+ d;
			}
			//add = a+b+c+d;
			root->marks_given=ADD;
		}
		else
		{
			root->viva =NO;
			//add=(a+b);
			root->marks_given=ADD;
		}
		//int count=2;
		//update_student_b(stude, group_id,a,b,c,d,count);
		return root; // Found the group with the given group_id
	}
}

int avl_group_asg_eval(Student_group* group_root, int* found) {
    if (group_root != NULL) {
        avl_group_asg_eval(group_root->left, found);
        if (group_root->a_eva_s == NOT_EVALUATED) {
            *found = 1;
        }
        avl_group_asg_eval(group_root->right, found);
    }
    return *found;
}

void evaluate_asg(Student* student_root,Assignment* assg_root) {
	int aid,gid;
	printf("\nPlease input the assignment id of the student group. ");
	scanf("%d",&aid);
	printf("\nPlease input the group id of that student group. ");
	scanf("%d",&gid);
	if (assg_root == NULL) {
		return; // Assignment tree is empty
	}
	
	// Search for the assignment with the given asg_id in the AVL tree
	Assignment* node = avl_search_assignment_b(assg_root, aid);
	if (node == NULL) {
		printf("Assignment with the given asg_id not found in the tree");
		return;
	}
	Assignment* anode = node;
	Student_group* gnode = node->stu_group;
	// Search for the group with the given group_id in the AVL tree of the assignment
	Student_group* group_node = avl_search_group_b(node->stu_group,student_root, gid);
	if (group_node == NULL) {
		printf("Group with the given group_id not found in this assignment");
		return;
	}
	
	int found = 0;
	int aeva;
	aeva = avl_group_asg_eval(gnode, &found);
	//printf("%d\n", aeva); // Updated format specifier
	if (aeva == 0) {
	   // printf("%d\n", aeva); // Updated format specifier
	   // printf("--\n");
	    node->a_eva_s = EVALUATED; // Changed == to =
	}
	else {
	   // printf("%d\n", aeva); // Updated format specifier
	    //printf("**\n");
	    node->a_eva_s = NOT_EVALUATED; // Changed == to =
	}


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q4

void print_not_evaluated_assignments(Assignment* assg_root) {
	if (assg_root == NULL) {
		printf("Assignment tree is empty\n");
		return;
	}

	if (assg_root->left != NULL) {
		print_not_evaluated_assignments(assg_root->left);
	}

	if (assg_root->a_eva_s == NOT_EVALUATED) {
		printf("Assignment ID: %d\n", assg_root->asg_id);
		printf("Topic: %s\n", assg_root->topic);
		//printf("Description: %s\n", assg_root->asg_description);
		// printf("Deadline: %d/%d/%d %d:%d\n", assg_root->asg_deadline.day, assg_root->asg_deadline.month, assg_root->asg_deadline.year, assg_root->asg_deadline.hour, assg_root->asg_deadline.minute);
		printf("Evaluation Status: Not evaluated\n");
		printf("\n");
	}
	
	if (assg_root->right != NULL) {
		print_not_evaluated_assignments(assg_root->right);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////Q5

void unsbmitted_group(Student_group* group_root) {
	if (group_root != NULL) 
	{
		unsbmitted_group(group_root->left);
	
		if (group_root->a_sub_s == NOT_SUBMITTED) 
		{
			//Student_group* group_node = assg_root->stu_group;
			printf("Group ID: %d\n", group_root->grp_id);
			printf("Partner 1 ID: %d\n", group_root->student1->stu_id);
			printf("Partner 1 Name: %s\n", group_root->student1->name);
			if(group_root->student2!=NULL)
			{
				printf("Partner 2 ID: %d\n", group_root->student2->stu_id);
				printf("Partner 2 Name: %s\n", group_root->student2->name);
			}
			//printf("Assignment ID: %d\n", group_root->stu_group->asg_id);
			// printf("Assignment Topic: %s\n", group_root->topic);
			printf("Assignment Declaration Status: %s\n", (group_root->a_dec_s == DECLARED) ? "Declared" : "Not declared");
			//printf("Assignment Due Status: %s\n", (group_root->a_due_s == DUE_OVER) ? "Due" : "Not due");
			printf("Assignment Submission Status: %s\n", (group_root->a_sub_s == SUBMITTED) ? "Submitted" : "Not submitted");
			printf("Assignment Evaluation Status: %s\n", (group_root->a_eva_s == EVALUATED) ? "Evaluated" : "Not evaluated");
			printf("Viva Taken: %s\n", (group_root->viva == YES) ? "Yes" : "No");
			printf("Marks Given: %.2f\n", group_root->marks_given);
			printf("\n");
		}
	
		unsbmitted_group(group_root->right);
	}
}

void print_unsubmitted_groups(Assignment* assg_root) {
	if (assg_root == NULL) {
		return; // Tree is empty
	}
	
	// Traverse the AVL tree of assignments
	print_unsubmitted_groups(assg_root->left);
	
	// Check if the assignment is due and no group has submitted it
	if (assg_root->a_due_s == DUE_OVER) 
	{
		Student_group* group_node = assg_root->stu_group;
		unsbmitted_group(group_node);
		
		// Traverse the AVL tree of student groups for this assignment
		// while (group_node != NULL) {
		// if (group_node->a_sub_s != SUBMITTED) {
		// printf("Group ID: %d, Group Name: %s\n", group_node->grp_id, group_node->grp_name);
		// }
		// group_node = group_node->right;
		// }
	}
	
	print_unsubmitted_groups(assg_root->right);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q6



void yet_group(Student_group* group_root) {
	if (group_root != NULL) 
	{
		yet_group(group_root->left);
	
		if (group_root->a_sub_s == SUBMITTED && group_root->a_eva_s == NOT_EVALUATED) 
		{
			//Student_group* group_node = assg_root->stu_group;
			printf("Group ID: %d\n", group_root->grp_id);
			printf("Partner 1 ID: %d\n", group_root->student1->stu_id);
			printf("Partner 1 Name: %s\n", group_root->student1->name);
			if(group_root->student2!=NULL)
			{
				printf("Partner 2 ID: %d\n", group_root->student2->stu_id);
				printf("Partner 2 Name: %s\n", group_root->student2->name);
			}
			//printf("Assignment ID: %d\n", group_root->stu_group->asg_id);
			// printf("Assignment Topic: %s\n", group_root->topic);
			printf("Assignment Declaration Status: %s\n", (group_root->a_dec_s == DECLARED) ? "Declared" : "Not declared");
			//printf("Assignment Due Status: %s\n", (group_root->a_due_s == DUE_OVER) ? "Due" : "Not due");
			printf("Assignment Submission Status: %s\n", (group_root->a_sub_s == SUBMITTED) ? "Submitted" : "Not submitted");
			printf("Assignment Evaluation Status: %s\n", (group_root->a_eva_s == EVALUATED) ? "Evaluated" : "Not evaluated");
			printf("Viva Taken: %s\n", (group_root->viva == YES) ? "Yes" : "No");
			printf("Marks Given: %.2f\n", group_root->marks_given);
			printf("\n");
		}
	
		yet_group(group_root->right);
	}
}
void yet_to_be(Assignment* assg_root) {
	if (assg_root != NULL) {
	
		// Traverse the AVL tree of assignments
		yet_to_be(assg_root->left);
		
		// Check if the assignment is due and no group has submitted it
		
		Student_group* group_node = assg_root->stu_group;
		yet_group(group_node);
		
		
		yet_to_be(assg_root->right);
	} 
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Q7





int count_nodes(Student_group *root) 
{
 int ret_val;
 if (root == NULL) 
 {
 	ret_val=0;
 }
 else if (root->left==NULL&&root->right==NULL)
 {
 	ret_val=1;
 }
 else
 	ret_val= count_nodes(root->left) + count_nodes(root->right) + 1;
 return ret_val;
}
void inOrderTraversal(Student_group* root, Student_group** arr , int* i)
{
	//printf("\nInorder traversal inside");
	 if (root != NULL) 
	 {
	 	//printf("\nInside inorder if");
	 inOrderTraversal(root->left, arr , i);
	 arr[*i] = root;
	 (*i)++;
	 inOrderTraversal(root->right, arr , i);
	 }
	 
}
void merge(Student_group** arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    Student_group* L[n1];
	Student_group* R[n2];
	
    for (i = 0; i < n1; i++)
	{
        L[i] = arr[l+i];
	}
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i]->marks_given <= R[j]->marks_given) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
   
}

void mergeSort(Student_group** arr, int l, int r)
{
	
    if (l < r)
    {
        int m = l+(r-l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void groups_in_descending_order(Student_group* group_ptr)
{
	 //printf("\nEntered the function.\n");
	 int num_nodes=count_nodes(group_ptr);
	 Student_group** arr = (Student_group**) malloc(sizeof(Student_group*) * num_nodes);
	 int ind = 0;
	 inOrderTraversal(group_ptr, arr , &ind);
	
	 //printf("\nAfter calling inorder");
	 int i ;
//	 for (i = 0; i >= 0; i--) 
//	 {
//	 	printf("\n%d" , arr[i]->grp_id);
//	 }
	 mergeSort(arr,0,num_nodes-1);
	 printf("\nAfter calling merge sort ");
	 printf("Student groups and their marks in descending order:\n");
	 int n;
	 
	 for (i = num_nodes - 1; i >= 0; i--) 
	 {
	 	printf("Group ID: %d, Marks: %.2f\n", arr[i]->grp_id, arr[i]->marks_given);
 	}
}


void print_decorder_groups(Assignment* root, int asg_id) 
{
	//Assignment* asg;
	//printf("\ninside print_decoder");
	 if (root == NULL) 
	 {
	 	printf("\nRoot null case");
	 	// Tree is empty or the assignment is not found
	 	//printf("Assignment not found\n");
	 	return;
	 }
	Assignment* asg=avl_search_assignment_b(root, asg_id);
	//Student_group* groot=asg->stu_group;
	if(asg==NULL)
	{
		printf("Assignment not found\n");
	}
	else
	{
		if(asg->stu_group==NULL)
		{
			printf("\nNO students were allocated this assignment.\n");
		}
		else
		{
			groups_in_descending_order(asg->stu_group);
		}
	}
}






//Assignment* find_assignment_node(Assignment* root, int asg_id) {
//    if (root == NULL) {
//        return NULL;
//    }
//    if (asg_id < root->asg_id) {
//        return find_assignment_node(root->left, asg_id);
//    } else if (asg_id > root->asg_id) {
//        return find_assignment_node(root->right, asg_id);
//    } else {
//        return root;
//    }
//}
//
//// Helper function to get the number of student-groups in the AVL tree
//int get_num_student_groups(Student_group* root) {
//    if (root == NULL) {
//        return 0;
//    }
//    return get_num_student_groups(root->left) + 1 + get_num_student_groups(root->right);
//}
//
//// Helper function to populate an array of pointers to student-group nodes
//int populate_student_groups_array(Student_group* root, Student_group** arr, int index) {
//    if (root == NULL) {
//        return index;
//    }
//    index = populate_student_groups_array(root->left, arr, index);
//    arr[index] = root;
//    index++;
//    index = populate_student_groups_array(root->right, arr, index);
//    return index;
//}
//
//// Comparison function to sort student-group pointers by marks in decreasing order
//int compare_student_groups_by_marks(const void* a, const void* b) {
//    Student_group* group_a = *(Student_group**)a;
//    Student_group* group_b = *(Student_group**)b;
//    if (group_a->marks_given > group_b->marks_given) {
//        return -1;
//    } else if (group_a->marks_given < group_b->marks_given) {
//        return 1;
//    } else {
//        return 0;
//    }
//}
//
//void print_decorder_groups(Assignment* root, int asg_id) {
//    // Find the assignment node with the given ID
//    Assignment* asg_node = find_assignment_node(root, asg_id);
//    if (asg_node == NULL) {
//        printf("Error: Assignment with ID %d not found.\n", asg_id);
//        return;
//    }
//     
//    // Create an array of pointers to student-group nodes and populate it
//    int num_groups = get_num_student_groups(asg_node->stu_group);
//    //Student_group** groups_arr = malloc(num_groups * sizeof(Student_group*));
//    Student_group** groups_arr = (Student_group**) malloc(num_groups * sizeof(Student_group*));
//
//    populate_student_groups_array(asg_node->stu_group, groups_arr, 0);
//     
//    // Sort the array of student-group pointers by marks in decreasing order
//    qsort(groups_arr, num_groups, sizeof(Student_group*), compare_student_groups_by_marks);
//     
//    // Print the details of student-groups in the sorted array
//    printf("Details of student-groups for assignment %d in decreasing order of marks:\n", asg_id);
//    for (int i = 0; i < num_groups; i++) {
//        Student_group* group = groups_arr[i];
//        printf("Group ID: %d\n", group->grp_id);
//        printf("Student 1 ID: %d, Name: %s\n", group->student1->stu_id, group->student1->name);
//        if (group->student2 != NULL) {
//			printf("Student 2 ID: %d, Name: %s\n", group->student2->stu_id, group->student2->name);
//		}
//        printf("Marks Given: %.2f\n", group->marks_given);
//        printf("------------\n");
//    }
//     
//    // Free the allocated memory for the array of student-group pointers
//    free(groups_arr);
//}













/////////////////////////////////////////////////////////////////////////////////////////////////////////////Q8


//void top_group(Student_group* group_root, float top_marks, Student_group** top_group_ptr) {
// if (group_root != NULL) 
// {
// top_group(group_root->left, top_marks, top_group_ptr);
// 
// float total_marks = group_root->student1->off_marks + group_root->student2->off_marks + group_root->student1->viva_marks + group_root->student2->viva_marks;
// 
// if (total_marks > top_marks)
// {
// top_marks = total_marks;
// *top_group_ptr = group_root;
// }
// 
// top_group(group_root->right, top_marks, top_group_ptr);
// }
//}
//
//void print_top_groups(Assignment* assg_root) {
// if (assg_root != NULL) {
//
// // Traverse the AVL tree of assignments
// print_top_groups(assg_root->left);
//
// // Check if the assignment is due and no group has submitted it
// 
// Student_group* group_node = assg_root->stu_group;
// float top_marks = 0.0;
// Student_group* top_group_ptr = NULL;
// top_group(group_node, top_marks, &top_group_ptr);
// 
// if (top_group_ptr != NULL) {
// printf("Top group for assignment %d is %d:\n", assg_root->asg_id, top_group_ptr->grp_id);
// printf("%s and %s with total marks %.2f\n", top_group_ptr->student1->name, top_group_ptr->student2->name, top_group_ptr->marks_given);
// }
// 
//
// print_top_groups(assg_root->right);
//} 
//}

void top_group(Student_group* group_root, float* top_marks, Student_group** top_group_ptr) {
	if (group_root != NULL) 
	{
		top_group(group_root->left, top_marks, top_group_ptr);
		
		float total_marks = group_root->student1->off_marks + group_root->student1->viva_marks;
		if (group_root->student2 != NULL) {
		    total_marks += group_root->student2->off_marks + group_root->student2->viva_marks;
		}
		
		if (total_marks > *top_marks) {
			*top_marks = total_marks;
			*top_group_ptr = group_root;
		}
		
		top_group(group_root->right, top_marks, top_group_ptr);
	}
}



void print_top_groups(Assignment* assg_root) {
	// printf("00\n");
	if (assg_root != NULL) {
		//printf("#0\n");
		// Traverse the AVL tree of assignments
		print_top_groups(assg_root->left);
		
		// Check if the assignment is due and no group has submitted it
		// printf("#1\n");
		Student_group* group_node = assg_root->stu_group;
		float top_marks = 0.0;
		Student_group* top_group_ptr = NULL;
		top_group(group_node, &top_marks, &top_group_ptr);
		//printf("#2\n");
		//printf("Top group for assignment %d is %d:\n", assg_root->asg_id, top_group_ptr->grp_id);
		if (top_group_ptr != NULL) {
			printf("Top group for assignment %d is %d: ", assg_root->asg_id, top_group_ptr->grp_id);
			//printf("Top group for assignment %d \n", top_group_ptr->grp_id);
			//printf("is %d \n", assg_root->asg_id);
			printf("%s", top_group_ptr->student1->name);
		    if (top_group_ptr->student2 != NULL) {
		        printf(" and %s", top_group_ptr->student2->name);
		    }
		    printf(" with total marks %.2f\n", top_group_ptr->marks_given);
			//printf("%s and %s with total marks %.2f\n", top_group_ptr->student1->name, top_group_ptr->student2->name, top_group_ptr->marks_given);
		}
		else {
		    printf("No group has evaluated assignment %d yet.\n", assg_root->asg_id);
		}
		//  printf("#3\n");
		
		print_top_groups(assg_root->right);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////Q9


void between_asg(Assignment* assg_root, int asg_id1, int asg_id2) {
    if (assg_root == NULL) {
        return; // Tree is empty
    }
    
    // Traverse the AVL tree of assignments
    between_asg(assg_root->left, asg_id1, asg_id2);
    
    // Check if the assignment is due and no group has submitted it
    if (assg_root->asg_id > asg_id1 && assg_root->asg_id < asg_id2) {
        printf("\n");
        printf("Assignment ID: %d\n", assg_root->asg_id);
        printf("Topic: %s\n", assg_root->topic);
        printf("Declare status: %s\n", (assg_root->a_dec_s == DECLARED) ? "Declared" : "Undeclared");
        printf("Evaluate status: %s\n", (assg_root->a_eva_s == EVALUATED) ? "Evaluated" : "Not Evaluated");
        // Traverse the AVL tree of student groups for this assignment
		 // while (group_node != NULL) {
		// if (group_node->a_sub_s != SUBMITTED) {
		// printf("Group ID: %d, Group Name: %s\n", group_node->grp_id, group_node->grp_name);
		// }
		 // group_node = group_node->right;
		 // }
    }
    
    // Check if we've already printed the "no asg in between" message
    static int no_asg_msg_printed = 0;
    if (assg_root->asg_id >= asg_id2 && no_asg_msg_printed == 0) {
      // printf("\nno asg in between\n");
        no_asg_msg_printed = 1;
    }
    
    between_asg(assg_root->right, asg_id1, asg_id2);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////display


void inorder_display_stu(Student* student_root) {
    //static int header_printed_stu = 0; // static variable to track if header line has been printed before
    if (student_root != NULL) {
        inorder_display_stu(student_root->left);
    	// if (!header_printed_stu) {
        //printf("StuID\tName\tPartner\tGroupID\tAsgID\tAsgTOP\tDeadline\t\tSub.\tEval.\toff_marks\tViva_marks\n");
        //  header_printed_stu = 1; // set the static variable to 1 to indicate header line has been printed
    	// }
        printf("%d\t%s\t%d\t%d\t%d\t%s\t%d/%d/%d_%d:%d\t%s\t%s\t%.2f\t\t%.2f\n",
	    student_root->stu_id, student_root->name, student_root->part_id, student_root->grp_id, student_root->asg_id, student_root->asg_topic,
        student_root->_deadline.day, student_root->_deadline.month, student_root->_deadline.year, student_root->_deadline.hour, student_root->_deadline.minute,
        (student_root->a_sub_s == SUBMITTED) ? "Yes" : "No",
		(student_root->a_eva_s == EVALUATED) ? "Yes" : "No",
        student_root->off_marks, student_root->viva_marks);
        printf("\n");
        
        inorder_display_stu(student_root->right);
    }
}


void inorder_display_group(Student_group* group_root) {
//	static int header_printed_grp = 0; // static variable to track if header line has been printed before
	if (group_root != NULL) {
		inorder_display_group(group_root->left);
		//if (!header_printed_grp) {
		//printf("GroupID\tStu.1ID\tStu.1Name\tStu.2ID\tStu.2Name\tDec.\tSub.\tEval.\tViva_taken\tviva_marks\n");
		//header_printed_grp = 1;
		//}
		printf("%d\t%d\t%s\t\t", group_root->grp_id, group_root->student1->stu_id, group_root->student1->name);
		if (group_root->student2 != NULL) {
			printf("%d\t%s\t\t", group_root->student2->stu_id, group_root->student2->name);
		} 
		else {
			printf("N/A\tN/A\t\t");
		}
		printf("%s\t%s\t%s\t%s\t\t%.2f\n",
		(group_root->a_dec_s == DECLARED) ? "Yes" : "No",
		(group_root->a_sub_s == SUBMITTED) ? "Yes" : "No",
		(group_root->a_eva_s == EVALUATED) ? "Yes" : "No",
		(group_root->viva == YES) ? "Yes" : "No",
		group_root->marks_given);
		printf("\n");
		
		inorder_display_group(group_root->right);
	}
}



void inorder_display_assg(Assignment* assg_root) {
	if (assg_root != NULL) {
		inorder_display_assg(assg_root->left);
		
		printf("Assignment ID: %d\n", assg_root->asg_id);
		printf("Topic: %s\n", assg_root->topic);
		printf("Declare status: %s\n", (assg_root->a_dec_s == DECLARED) ? "Declared" : "Undeclared");
		printf("Due status: %s\n", (assg_root->a_due_s == DUE_NOT_OVER) ? "Not Over" : "Over");
		printf("Evaluate status: %s\n", (assg_root->a_eva_s == EVALUATED) ? "Evaluated" : "Not Evaluated");
		printf("\n");
		printf("GroupID\tStu.1ID\tStu.1Name\tStu.2ID\tStu.2Name\tDec.\tSub.\tEval.\tViva_taken\tMarks\n");
		inorder_display_group(assg_root->stu_group);
		
		inorder_display_assg(assg_root->right);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////end


int main() 
{
	// create an empty AVL tree for storing student records
	Student* student_root = NULL;

	// create an empty AVL tree for storing assignment records
	Assignment* asg_root = NULL;
    FILE* stu_fp;
    FILE* asg_fp;
    stu_fp = fopen("students.txt","r");
    asg_fp = fopen("assignments.txt","r");

    // Read student records from file and insert into linked list
 	//char temp[50];

    // Read assignment records from file and insert into linked list
    while(!feof(asg_fp))
    {
        int assign_id;
        char assign_topic[30],name[30];
        int grp_id,stu_id,part_id;
        Time t;
        

        fscanf(asg_fp,"%d %s %s %d %d %d %d %d %d %d %d\n", &assign_id, assign_topic, name, &stu_id, &grp_id, &part_id,&t.day,&t.month,&t.year,&t.hour,&t.minute);
    	asg_root=ins_asg_list(&student_root,asg_root, assign_id, assign_topic, name, stu_id, grp_id, part_id, t);
    }
	
	//while(fscanf(stu_fp,"%s",temp)!=EOF)
	while(!feof(stu_fp))
	{
		int stu_id, partner_id, group_id, assign_id;
	    char name[30], assign_topic[30];
	    Time submission_time;
			
		fscanf(stu_fp, "%d %s %d %d %d %s %d %d %d %d %d\n", &stu_id, name, &partner_id, &group_id, &assign_id, assign_topic, &submission_time.day, &submission_time.month, &submission_time.year, &submission_time.hour, &submission_time.minute);
		student_root = ins_stu_list(student_root, &asg_root, stu_id, name, partner_id, group_id, assign_id, assign_topic, submission_time);
	}
	
    /*

    // Display a menu and process user input
    char teacher[40]= "RB KESKAR";
    char password[40]="vnit@123";*/

	Time temp;
	temp.day=12;
	temp.month=12;
	temp.year=2023;
	temp.hour=23;
	temp.minute=59;
	student_root=ins_stu_list(student_root, &asg_root, 118, "moin", 119, 1000, 3, "asg1",temp);
	student_root=ins_stu_list(student_root, &asg_root, 119, "rb", 118, 1000, 3, "asg1",temp);
	student_root=ins_stu_list(student_root, &asg_root, 120, "ram", 123, 1004, 3, "asg1",temp);
	student_root=ins_stu_list(student_root, &asg_root, 123, "shyam", 120, 1004, 3, "asg1",temp);
	student_root=ins_stu_list(student_root, &asg_root, 13, "parate", 9, 1005, 4, "asg2",temp);
	student_root=ins_stu_list(student_root, &asg_root, 9, "prashal", 13, 1005, 4, "asg2",temp);
	student_root=ins_stu_list(student_root, &asg_root, 91, "azizo", 92, 1007, 5, "book",temp);
	asg_root=ins_asg_list(&student_root, asg_root, 3, "asg1", "smito",36, 1006, 38, temp);
	asg_root=ins_asg_list(&student_root, asg_root, 3, "asg1", "shubh",38, 1006, 36, temp);
	asg_root=ins_asg_list(&student_root, asg_root, 4, "asg2", "devansh",44, 1003, 32, temp);
    int choice = 0;
	do 
	{
		printf("\n\n--------------------------------------------\n");
		printf("Please choose a valid option:\n");
		printf("1. Insert a student record\n");
		printf("2. Insert an assignment record\n");
		printf("3.a Change status of assignment and student lists\n");
		printf("3.b Print student all status assignment evaluated\n");
		printf("4. Print list of assignments that are declared but not evaluated\n");
		printf("5. Print list of student groups who have not submitted assignments even if due date over\n");
		printf("6. Print list of student groups for whom the assignment is yet-to-be-evaluated\n");
		printf("7. Print details of student-groups in decresing order of marks\n");
		printf("8. Print student groups receiving top marks in each assignment\n");
		printf("9. Print between assignment-id-1 and assignment-id-2\n");
		printf("10. Print students list.\n");
		printf("11. Print assignment list.\n");
		printf("99. Exit program\n\n");
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
			printf("\nDeadline in the format DDMMYY Hr min ");
			scanf("%d%d%d%d%d",&t.day,&t.month,&t.year,&t.hour,&t.minute);
			//	students_head=ins_stu_list(students_head,&assignments_head, stu_id, b, c, d, e, f,t);
			//	student_root = ins_stu_list(student_root, &asg_root, 100, "John", 0, 1, 101, "Assignment 1", "01/05/2023");
			student_root = ins_stu_list(student_root, &asg_root, stu_id, b, c, d, e, f,t);
			
		}
		else if (choice==2)
		{
			int inser;
			printf("do you want to insert by file or by yourself for file press 1 else 0 ");
			scanf("%d",&inser);
			if(inser==1)
			{
    			FILE* asginser_fp;
    			asginser_fp = fopen("assiginser.txt","r");
    			// Read student records from file and insert into linked list
 				//char temp[50];
    			// Read assignment records from file and insert into linked list
    			while(!feof(asginser_fp))
    			{
        			int assig_id;
        			char assig_topic[30],nam[30];
        			int gr_id,st_id,par_id;
        			Time tu;
        			fscanf(asginser_fp,"%d %s %s %d %d %d %d %d %d %d %d\n", &assig_id, assig_topic, nam, &st_id, &gr_id, &par_id,&tu.day,&tu.month,&tu.year,&tu.hour,&tu.minute);
    				asg_root=ins_asg_list(&student_root,asg_root, assig_id, assig_topic, nam, st_id, gr_id, par_id, tu);
    			}
	
			}
			else
			{
			
				int a_id,num_students,grp_id,part_id,stu_id;
				char a_topic[40],name[40];
				Time t;
				
				// if(!find_asg_ptr(assignments_head,a_id))
				printf("\nNumber of students you wish to enter? ");
				scanf("%d",&num_students);
				for(int i=0;i<num_students;i++)
				{
					printf("\nPlease enter assignment id. ");
					scanf("%d",&a_id);
					printf("\nPlease enter the topic of the assignment.\n");
					scanf("%s",a_topic);
					//stu_nptr=(Student*)malloc(sizeof(Student));
					// stu_nptr->asg_id=asg_mptr->asg_id;
					// strcpy(stu_nptr->asg_topic,asg_mptr->topic);
					// stu_nptr->a_eva_s=NOT_EVALUATED;
					// stu_nptr->a_sub_s=NOT_SUBMITTED;
					// stu_nptr->off_marks=-1.0;
					// stu_nptr->viva_marks=-1.0;
					printf("\nenter student %d's name. ",i+1);
					scanf("%s",name);
					printf("\nenter student %d's student id. ",i+1);
					scanf("%d",&stu_id);
					printf("\nenter student's group id. ");
					scanf("%d",&grp_id);
					printf("\nenter student partner's id. ");
					scanf("%d",&part_id);
					printf("\nDeadline of the student assignment in the format DDMMYY Hr min ");
					scanf("%d%d%d%d%d",&t.day,&t.month,&t.year,&t.hour,&t.minute);
					// stu_nptr->next=stu_lptr;
					// stu_lptr=stu_nptr;
					asg_root=ins_asg_list(&student_root, asg_root, a_id, a_topic, name, stu_id, grp_id, part_id, t);
				}
				// {
				
				//	}
				//else
				//{
				//	printf("\n An assignment with same id ALREADY exists.");
				//}
			}
		}
		else if (choice==3)
		{
			int subq;
			printf("enter the sub question no 1 or 2 \n");
			scanf("%d",&subq);
			if(subq==1)
			{
				int ai,g;
				printf("3.a");
				printf("\nPlease enter assignment id. ");
				scanf("%d",&ai);
				printf("\nenter student's group id. ");
				scanf("%d",&g);
				make_changes(student_root, asg_root,ai,g);
				update_student_st(student_root, g);
			}
			else if(subq==2)
			{
				printf("3.b");
				evaluate_asg(student_root,asg_root);
			}
		}
		else if (choice==4)
		{
			print_not_evaluated_assignments(asg_root);
		}
		else if (choice==5)
		{
			print_unsubmitted_groups(asg_root);
		}
		else if (choice==6)
		{
			yet_to_be(asg_root);
		}
		else if (choice==7)
		{
			int p;
			printf("ass id ");
			scanf("%d",&p);
			print_decorder_groups(asg_root, p);
		}
		else if (choice==8)
		{
			print_top_groups(asg_root);
		}
		else if (choice==9)
		{
			int asgid1,asgid2;
			printf("\nPlease enter assignment id1 and assignment id2 ");
			scanf("%d%d",&asgid1,&asgid2);
			between_asg(asg_root, asgid1,asgid2);
		}
		else if (choice==10)
		{
			printf("StuID\tName\tPartner\tGroupID\tAsgID\tAsgTOP\tDeadline\t\tSub.\tEval.\toff_marks\tViva_marks\n");
			inorder_display_stu(student_root);
		}
		else if (choice==11)
		{
			inorder_display_assg(asg_root);
		}
	}while (choice != 99);
	return 0;
}
