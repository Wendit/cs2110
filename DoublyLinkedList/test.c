#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  /* What does an empty list contain?  Lets use our handy traversal function */
  printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets remove that person and then print */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  	/* Lets kill the list */
  empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	 //Let's make a list of people, and remove certain ones! 
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);
  printf("\n");

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */

  empty_list(llist, free_person);
  printf("TEST CASE 8\nTest for empty_list with a list of size greater than 0\nShould empty the list:\n");
  traverse(llist, print_person);
  printf("\n");

  empty_list(llist, free_person);
  printf("TEST CASE 9\nTest for empty_list with a list of size 0\nShould print nothing:\n");
  traverse(llist, print_person);
  printf("\n");

  push_back(llist,create_person("Ada",30)); 
  printf("TEST CASE 10\nTest for push_back with a list of size 0\nShould print 1 person:\n");
  traverse(llist, print_person);
  printf("\n");

  push_back(llist,create_person("Ruvik",30)); 
  printf("TEST CASE 11\nTest for push_back with a list of size greater than 0\nShould print 2 person:\n");
  traverse(llist, print_person);
  printf("\n");

  remove_back(llist,free_person); 
  remove_back(llist,free_person);
  printf("TEST CASE 12\nTest for remove_back with a list of size greater than 1\nShould print 1 person:\n");
  traverse(llist, print_person);
  printf("\n");

  remove_back(llist,free_person); 
  printf("TEST CASE 13\nTest for remove_back with a list of size 0\nShould print empty list:\n");
  traverse(llist, print_person);
  printf("\n");

  printf("TEST CASE 14\nTest for front and back with a list of size 0\nShould print two \"NULL\":\n");
  if(!front(llist))
  printf("NULL\n");
  if(!back(llist))
  printf("NULL\n");
  printf("\n");

  empty_list(llist2, free_person);
  free(llist2);
  llist2 = copy_list(llist,copy_person); 
  printf("TEST CASE 15\nTest to copy empty list\nShould print empty list:\n");
  traverse(llist2, print_person);
  printf("\n");

  printf("TEST CASE 16\nTest for size  for empty list\nShould print 0:\n");
  printf("%d\n", size(llist));
  traverse(llist, print_person);
  printf("\n");

  push_front(llist,create_person("Leon",40)); 
  push_front(llist,create_person("Kid",10)); 
  push_front(llist,create_person("Alex",30)); 
  printf("TEST CASE 17\nTest for front and back with a list of size 0\nShould print two person:\n");
  print_person(front(llist));
  print_person(back(llist));
  printf("\n");

  printf("TEST CASE 18\nTest for size  for a list of size greater than 0\nShould print 3:\n");
  printf("%d\n", size(llist));
  traverse(llist, print_person);
  printf("\n");

  empty_list(llist2, free_person);
  free(llist2);
  llist2 = copy_list(llist,copy_person);
  printf("TEST CASE 19\nTest for size  for a copied list of size greater than 0\nShould print 3:\n");
  printf("%d\n", size(llist2));
  traverse(llist, print_person);
  printf("\n");

  remove_front(llist,free_person);
  printf("TEST CASE 20\nChange original list, test if the copied list changes\nShould print same three people:\n");
  traverse(llist2, print_person);
  printf("The original list should only print two people now:\n");
  traverse(llist, print_person);
  printf("\n");

 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);

  	return 0;
}

