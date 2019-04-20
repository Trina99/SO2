// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "person.h"

int main(int argc, char* argv[])
{
    
    Person trina = new_person("Trina", 18);
    printPerson(trina);

    person_change_age(&trina, 19);
    printPerson(trina);

    Person new_trina = clone_person(&trina);

    person_change_age(&new_trina, 20);
    printPerson(new_trina);

    destroy_person(&new_trina);
    destroy_person(&trina);

    return 0;
}

