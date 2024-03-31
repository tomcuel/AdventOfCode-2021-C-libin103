#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 


#define MAX_STRING_LENGTH 100


// Function to count the number of unique strings in a file
int count_unique_strings(const char* filename, int nb_lines) {
    char unique_strings[nb_lines][MAX_STRING_LENGTH];
    int unique_count = 0;

    // Open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return -1;
    }

    // Read each line of the file
    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract strings
        char* token = strtok(line, "-\n");
        while (token != NULL) {
            // Check if the string is already in the unique_strings array
            int found = 0;
            for (int i = 0; i < unique_count; i++) {
                if (strcmp(unique_strings[i], token) == 0) {
                    found = 1;
                    break;
                }
            }
            // If not found, add it to the unique_strings array
            if (!found) {
                strncpy(unique_strings[unique_count], token, MAX_STRING_LENGTH);
                unique_count++;
            }
            // Move to the next token
            token = strtok(NULL, "-\n");
        }
    }

    // Close the file
    fclose(file);

    return unique_count;
}


// function to know if a string is in an array of strings
bool is_in_array(char** array, int size, char* string){
    for (int i = 0; i < size; i++){
        if (strcmp(array[i], string) == 0){
            return true;
        }
    }
    return false;
}


// function that get the posistion of a character in a string
int get_pos(char* string, char c){
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == c){
            return i;
        }
    }
    return -1;
}


// Function to check if a string is lowercase
int is_lowercase(const char* string) {
    // Iterate through each character of the string
    while (*string != '\0') {
        // Check if the character is not a lowercase letter
        if (!islower(*string)) {
            return 0; // The string contains at least one character that is not a lowercase letter
        }
        string++; // Move to the next character
    }
    return 1; // All characters in the string are lowercase letters
}


// Function to get the index of a string in a list of strings
int get_string_index(char** string_list, int list_size, char* target) {
    for (int i = 0; i < list_size; i++) {
        if (strcmp(string_list[i], target) == 0) {
            return i; // Return the index if a match is found
        }
    }
    return -1; // Return -1 if the target string is not found in the list
}


// global variable to store the answer
int answer = 0;

// function that does the depth first search on the caves, by starting from the cave "cave"
// we will use it by starting from the "strat" cave
// we want the number of caves that are not visited if we follow the rule : there has been a change in the rule
// two paths are now allowed for a small cave, as much as we want for a big cave
// it's only this function that will be changed
void dfs(char** caves, int* visited, char*** adjacent_list, int nb_strings, char* cave){
    

    // if we reached the "end" cave, we stop the search
    // we've found a path, so we increment the answer
    if (strcmp(cave, "end") == 0){
        answer++;
        return;
    }


    // still getting the index of the cave
    int index = get_string_index(caves, nb_strings, cave);


    // we change the part concerning what to do if we reach a small cave
    if (is_lowercase(cave)){
        // we mark the small cave as visited
        visited[index]++;

        // we look at the number of small caves that have been visited more than once
        // and if one has been visited more than twice, we stop the search and decrement the visited number for the next path
        int number_visited_more_than_once = 0;
        for (int i = 0; i < nb_strings; i++){
            if (visited[i] > 1 && is_lowercase(caves[i])){
                number_visited_more_than_once++;
            }

            // if we have already visited two small caves, we stop the search, since we can't visit a third one
            if (visited[i] > 2 && is_lowercase(caves[i])){
                visited[index]--;
                return;
            }
        }

        // if we have visited two small caves, we stop the search
        if (number_visited_more_than_once > 1){
            visited[index]--; // needed for the next time we come back to this cave, in others paths 
            return;
        }

    }



    // we now need to consider the neighbours of the cave, to do the dfs again recursively
    for (int k = 0; k < nb_strings; k++){
        // if the cave is the start cave, we don't want to go back to it, so we continue
        if (strcmp(adjacent_list[index][k], "start") == 0){
            continue;
        }
        // we then need to do the dfs on the neighbour if they're not NULL
        if (strcmp(adjacent_list[index][k], "") != 0){
            dfs(caves, visited, adjacent_list, nb_strings, adjacent_list[index][k]);
        }
    }

    // once we've done the dfs on the neighbours, we mark the small cave as not visited
    // why ? because we want to be able to visit it again if we come back to it in another path
    if (is_lowercase(cave)){
        visited[index]--;
    }
}


int main (){

    // getting the input 
    const char* filename = "input12.txt";
    FILE* file = fopen(filename, "r");
    char line[10];
    int nb_lines = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        nb_lines++;
    }
    char*** lines = malloc(nb_lines * sizeof(char**));
    for (int i = 0; i < nb_lines; i++){
        lines[i] = malloc(2 * sizeof(char*));
        for (int j = 0; j < 2; j++){
            lines[i][j] = malloc(10 * sizeof(char));
        }
    }

    rewind(file);
    int i = 0;
    // parsing the input to get the two strings that have a link
    while(fgets(line, sizeof(line), file) != NULL){
        int pos = get_pos(line, '-');
        for (int j = 0; j < pos; j++){
            lines[i][0][j] = line[j];
        }
        lines[i][0][pos] = '\0';
        for (int j = pos + 1; j < strlen(line) - 1; j++){
            lines[i][1][j - pos - 1] = line[j];
        }
        lines[i][1][strlen(line) - pos - 1] = '\0';
        i++;
    }

    
    // printing the input
    printf("Input :\n");
    for (int i = 0; i < nb_lines; i++){
        for (int j = 0; j < 2; j++){
            printf("%s ", lines[i][j]);
        }
        printf("\n");
    }
    

    // counting the number of different strings
    int nb_strings = count_unique_strings(filename, nb_lines);
    printf("Number of different strings in the file: %d\n", nb_strings);
    char** caves = malloc(nb_strings * sizeof(char*));
    for (int i = 0; i < nb_strings; i++){
        caves[i] = malloc(10 * sizeof(char));
    }
    int k=0;
    for (int i = 0; i <= nb_strings; i++){
        if (is_in_array(caves, nb_strings, lines[i][0])==false){
            strcpy(caves[k], lines[i][0]);
            ++k;
        }
        if (is_in_array(caves, nb_strings, lines[i][1])==false){
            strcpy(caves[k], lines[i][1]);
            ++k;
        }
    }


    // printing the caves
    printf("Different Caves :\n");
    for (int i = 0; i < nb_strings; i++){
        printf("%s\n", caves[i]);
    }
    printf("\n");
    

    // correspond to each cave, to see if it has been visited, will be usefull for the little cave
    // it has changed, since now we have to consider that the small caves can be visited two times 
    // it's not only true of false anymore
    // it's 0 if not visited, 1 if visited one time, 2 if visited two times
    int* visited = malloc(nb_strings * sizeof(int));
    for (int i = 0; i < nb_strings; i++){
        visited[i] = 0;
    }

    // making the adjacency matrix
    char*** adjacent_list = malloc(nb_strings * sizeof(char**));
    int index = 0;
    // adjacent_list[i] will be the list of caves that are linked to the cave i
    for (int i = 0; i < nb_strings; i++){
        // it will be the index of the adjacency list of the cave i
        index = 0;
        adjacent_list[i] = malloc(nb_strings * sizeof(char*));
        for (int j = 0; j < nb_strings; j++){
            adjacent_list[i][j] = malloc(10 * sizeof(char));
        }
        // searching the caves that are adjacent to the cave i
        for (int j = 0; j < nb_strings; j++){
            if (i != j){
                // searching in the lines array
                for (int k = 0; k < nb_lines; k++){
                    // if the caves is on the left, we add the right cave to the adjacency matrix
                    if (strcmp(caves[i], lines[k][0]) == 0 && strcmp(caves[j], lines[k][1]) == 0){
                        strcpy(adjacent_list[i][index], caves[j]);
                        index++;
                    }
                    // if the caves is on the right, we add the left cave to the adjacency matrix
                    else if (strcmp(caves[i], lines[k][1]) == 0 && strcmp(caves[j], lines[k][0]) == 0){
                        strcpy(adjacent_list[i][index], caves[j]);
                        index++;
                    }
                }
                
            }
        }
    }

    // printing the adjacency matrix
    printf("Adjacency List :\n");
    for (int i = 0; i < nb_strings; i++){
        printf("%s : ", caves[i]);
        for (int j = 0; j < nb_strings; j++){
            printf("%s ", adjacent_list[i][j]);
        }
        printf("\n");
    }


    // we have as datas : 
    // - caves : the list of caves
    // - visited : the states (visited or not) of the caves
    // - adjacent_list : the list of caves that are linked to the cave i

    dfs(caves, visited, adjacent_list, nb_strings, "start");

    printf("\nAnswer : %d\n\n", answer);




    // free the memory
    for (int i = 0; i < nb_lines; i++){
        for (int j = 0; j < 2; j++){
            free(lines[i][j]);
        }
        free(lines[i]);
    }
    free(lines);

    for (int i = 0; i < nb_strings; i++){
        free(caves[i]);
    }
    free(caves);

    free(visited);

    for (int i = 0; i < nb_strings; i++){
        for (int j = 0; j < nb_strings; j++){
            free(adjacent_list[i][j]);
        }
        free(adjacent_list[i]);
    }
    free(adjacent_list);

    // close the file
    fclose(file);

    return EXIT_SUCCESS;
}


// we need to add an empty line at the end of the .txt file to avoid mistakes
// we found as expected for : 
// - little_test.txt : 36
// - test.txt : 103
// - larger_test.txt : 3309 for this one, where it might have been 3509, but the final result is correct, so don't know why this one doesn't work