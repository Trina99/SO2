#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

Person new_person(char* name, int age)
{
    Person new;
    new.name = malloc (strlen(name) * sizeof(char) +1);
    strcpy(new.name, name);
    new.age = age;
    return new;
}

Person clone_person(Person* p)
{
    Person clone;
    clone.name = strdup(p->name);
    clone.age = p->age;
    return clone;
}

void destroy_person(Person* p)
{
    free(p->name);
}

int person_age(Person* p)
{
    return (p->age);
}

void person_change_age(Person* p, int age)
{
    p->age = age;
}

void printPerson(Person p)
{
    printf("Name: %s\nAge: %d\n",p.name, p.age);
}