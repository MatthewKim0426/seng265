/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// explicit function declarations since main is written first
void useCase1(int argc, char *argv[]);
void useCase2(int argc, char *argv[]);
void useCase3(int argc, char *argv[]);


/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    // TODO: your code
    
	//argument check
	if (argc < 4 || argc > 6) {
		printf("Usage: arguments must align with the three use cases provided in assignment outline");
		exit(1);
	}
	if (argc == 4) {
		printf("use case1");
		useCase1(argc,argv);
	} else if (argc == 5) {
		useCase2(argc, argv);
	} else if (argc == 6) {
		useCase3(argc,argv);
	}
	return 0;
}


/**
 * FUNCTION: useCase1
 * -------------------
 * @brief A function that searches and formats file according to use case 1
 * 
 * function will print out appropriate flight information as 
 * detailed in assignment writeup for use case two. Expects 3 specific arguments being
 * DATA AIRLINE DEST_COUNTRY to print out formatted flight info as follow. 
 * 
 * Format:
 * FLIGHTS TO DEST_COUNTRY BY airline_name (AIRLINE):
 * FROM: from_airport_icao_unique_code, from_airport_city, from_airport_country TO: to_airport_name (to_airport_icao_unique_code), to_airport_city
 *
 * @param argv the list of search criteria that we will be sorting through to find
 * @param argc count of arguments
 * @return void. All output will be printed to output .txt
 */
void useCase1(int argc, char *argv[]) {
	//initialize results_found, will see if matching flights are found so the "no results" message can be printed if count = 0.
	int results_found = 0;
	
	//initialize ints for the position of each of the search criteria in each line
	int icao = 1;
	int dest = 10;
	

	//parse argv for required search fields	and save them in variables for later use
	char *data = NULL;
	char *search_code = NULL;
	char *dest_country = NULL;

	for (int i=1;i<argc;i+=1) {
       	//note: using i+ in for loop because of the way that variables arguments are stored when inputed as shown ie --DATA = "..."
		if (strncmp(argv[i], "--DATA=", 7) == 0) {
			data = argv[i]+7;
		} else if (strncmp(argv[i], "--AIRLINE=", 10) == 0) {
			search_code = argv[i]+10;
		} else if (strncmp(argv[i], "--DEST_COUNTRY=",15) == 0) {
			dest_country = argv[i]+15;
		} else {
			//program will exit if arguments specified are not present as some search criteria are unknown
			printf("Invalid argument present: %s", argv[i]);
			exit(1);
		}
	}

	// open our input file for reading and our output file for writing
	FILE *fp;
	fp = fopen(data,"r");

	FILE *op;
	op = fopen("output.txt","w");
	
	//first line of desired output has been printed or not
	int intro_printed = 0;


	char line[1024];
	//store items in line to an array as well to make it easier to come back to later
	char *items[13] = {NULL};
	//parse through each line of fp and check the approrpriate positions to see if seatch criteria are met
	while (fgets(line, sizeof(line), fp)) {
		char *token;
		token = strtok(line,",");
		int i = 0;
		int test1 = 0;
		int test2 = 0;
		while (token != NULL) {
			items[i] = token;
			if (i == icao && strcmp(token, search_code) == 0) {
				test1 = 1;
			} else if  (i == dest && strcmp(token, dest_country) == 0) {
				test2 = 1;
			}
		token = strtok(NULL, ",");
		i++;
		}
	
		if (test1 == 1 && test2 == 1) {
			//formatting as described in outline
			if (intro_printed == 0) {
				fprintf(op,"FLIGHTS TO %s BY %s (%s):\n", items[10], items[0], items[1]); 
				intro_printed = 1;
			}
			fprintf(op,"FROM: %s, %s, %s TO: %s (%s), %s\n",items[6], items[4], items[5], items[8], items[11], items[9]);
			results_found = 1;

		}
	}

	if (results_found == 0) {
		fprintf(op, "NO RESULTS FOUND.\n");
	}

	fclose(fp);
	fclose(op);
	return;	
}


/**
 * Function: useCase2
 * -------------------
 * @brief A function that searches and formats file according to use case 2
 * 
 * function will print out appropriate and flight information as 
 * detailed in assignment writeup for use case 2. Expects 4 specific arguments being:
 * DATA, SRC_COUNTRY, DEST_CITY, and DEST_COUNTRY to print all applicable flgihts into the following format in a newly created output.txt file:
 * 
 * Format:
 * "FLIGHTS FROM SRC_COUNTRY TO DEST_CITY, DEST_COUNTRY:
 * AIRLINE: airline_name (airline_icao_unique_code) ORIGIN: from_airport_name (from_airport_icao_unique_code), from_airport_city"
 * ...
 * 
 * @param argv the list of search criteria that we will be sorting through to find
 * @param argc count of arguments
 * @return void. All output will be printed to output .txt
 */
void useCase2(int argc, char *argv[]) {
	//initialize results_found, will see if matching flights are found so the "no results" message can be printed if count = 0.
	int results_found = 0;

	//initialize variables for the position of the search criteria we are interested in
	int frCountry = 5;
	int toCity = 9;
	int toCountry = 10;
	
	//parse argv for required search fields	and save them in variables for later use
	char *data = NULL;
	char *src_country = NULL;
	char *dest_city = NULL;
	char *dest_country = NULL;

	for (int i=1;i<argc;i+=1) {
       	//note: Floating numbers, ie. the 7 in first IF, are there to overlook the tag ("--DATA") and isolate the search criteria
		if (strncmp(argv[i], "--DATA=", 7) == 0) {
			data = argv[i]+7;
		} else if (strncmp(argv[i], "--SRC_COUNTRY=", 14) == 0) {
			src_country = argv[i]+14;
		} else if (strncmp(argv[i], "--DEST_CITY=", 12) == 0) {
			dest_city = argv[i]+12;
		} else if (strncmp(argv[i], "--DEST_COUNTRY=",15) == 0) {
			dest_country = argv[i]+15;
		} else {
			printf("Invalid argument present: %s", argv[i]);
			exit(1);
		}

	}


	// open our input file for reading and our output file for writing
	FILE *fp;
	fp = fopen(data,"r");

	FILE *op;
	op = fopen("output.txt","w");
	
	//first line of desired output has been printed or not
	int intro_printed = 0;

	//Allocate space for the lines to be stored during the coming while loop.
	char line[1500];

	//store items in line to an array as well to make it easier to come back to later
	char *items[13] = {NULL};

	//parse through each line of fp and check the approrpriate positions to see if seatch criteria are met
	while (fgets(line, sizeof(line), fp)) {
		char *token;
		token = strtok(line,",");
		int i = 0;
		int test1 = 0;
		int test2 = 0;
		int test3 = 0;
		while (token != NULL) {
			items[i] = token;
			if (i == frCountry && strcmp(token, src_country) == 0) {
				test1 = 1;
			} else if (i == toCity && strcmp(token, dest_city) == 0) {
				test2 = 1;
			} else if  (i == toCountry && strcmp(token, dest_country) == 0) {
				test3 = 1;
			} 
		token = strtok(NULL, ",");
		i++;
		}
	
		if (test1 == 1 && test2 == 1 && test3 == 1) {
			//formatting as described in outline
			if (intro_printed == 0) {
				fprintf(op,"FLIGHTS FROM %s TO %s, %s:\n", items[frCountry], items[toCity], items[toCountry]); 
				intro_printed = 1;
			}
			fprintf(op,"AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n" ,items[0], items[1], items[3], items[6], items[4]);
			results_found = 1;

		}
	}

	if (results_found == 0) {
		fputs("NO RESULTS FOUND.\n", op);
	}

	fclose(fp);
	fclose(op);
	return;	
}

/**
 * Function: useCase3
 * -------------------
 * @brief A function that searches and formats output into an output file as described in use case 3
 * 
 * function will print out appropriate and flight information as 
 * detailed in assignment writeup for use case 3. Expects 5 specific arguments being:
 * DATA, SRC_CITY, SRC_COUNTRY, DEST_CITY, DEST_COUNTRY to print all applicable flights into the following format in a newly created output.txt file:
 * 
 * Format:
 * "FLIGHTS FROM SRC_COUNTRY TO DEST_CITY, DEST_COUNTRY:
 * AIRLINE: airline_name (airline_icao_unique_code) ORIGIN: from_airport_name (from_airport_icao_unique_code), from_airport_city"
 * ...
 * 
 * @param argv the list of search criteria that we will be sorting through to find
 * @param argc count of arguments
 * @return void. All output will be printed to output .txt
 */
void useCase3(int argc, char *argv[]) {
	//initialize results_found, will see if matching flights are found so the "no results" message can be printed if count = 0.
	int results_found = 0;

	//initialize variables for the position of the search criteria we are interested in
	int frCity = 4;
	int frmCountry = 5;
	int toCity = 9;
	int toCountry = 10;
	
	//parse argv for required search fields	and save them in variables for later use
	char *data = NULL;
	char *src_city = NULL;
	char *src_country = NULL;
	char *dest_city = NULL;
	char *dest_country = NULL;

	for (int i=1;i<argc;i+=1) {
       	//note: Floating numbers, ie. the 7 in first IF, are there to overlook the tag ("--DATA") and isolate the search criteria
		if (strncmp(argv[i], "--DATA=", 7) == 0) {
			data = argv[i]+7;
		} else if (strncmp(argv[i], "--SRC_CITY=", 11) == 0) {
			src_city = argv[i]+11;
		} else if (strncmp(argv[i], "--SRC_COUNTRY=", 14) == 0) {
			src_country = argv[i]+14;
		} else if (strncmp(argv[i], "--DEST_CITY=", 12) == 0) {
			dest_city = argv[i]+12;
		} else if (strncmp(argv[i], "--DEST_COUNTRY=",15) == 0) {
			dest_country = argv[i]+15;
		}else {
			printf("Invalid argument present: %s", argv[i]);
			exit(1);
		}
	}


	// open our input file for reading and our output file for writing
	FILE *fp;
	fp = fopen(data,"r");

	FILE *op;
	op = fopen("output.txt","w");
	
	//first line of desired output has been printed or not
	int intro_printed = 0;

	//Allocate space for the lines to be stored during the coming while loop.
	char line[1500];

	//store items in line to an array as well to make it easier to come back to later
	char *items[13] = {NULL};

	//parse through each line of fp and check the approrpriate positions to see if seatch criteria are met
	while (fgets(line, sizeof(line), fp)) {
		char *token;
		token = strtok(line,",");
		int i = 0;
		int test1 = 0;
		int test2 = 0;
		int test3 = 0;
		int test4 = 0;
		while (token != NULL) {
			items[i] = token;
			if (i == frmCountry && strcmp(token, src_country) == 0) {
				test1 = 1;
			} else if (i == toCity && strcmp(token, dest_city) == 0) {
				test2 = 1;
			} else if  (i == toCountry && strcmp(token, dest_country) == 0) {
				test3 = 1;
			} else if (i == frCity && strcmp(token, src_city) == 0) {
				test4 = 1;
			}
		token = strtok(NULL, ",");
		i++;
		}
	
		if (test1 == 1 && test2 == 1 && test3 == 1 && test4 == 1) {
			//formatting as described in outline
			if (intro_printed == 0) {
				fprintf(op,"FLIGHTS FROM %s, %s TO %s, %s:\n", items[frCity], items[frmCountry], items[toCity], items[toCountry]); 
				intro_printed = 1;
			}
			fprintf(op,"AIRLINE: %s (%s) ROUTE: %s-%s\n" ,items[0], items[1], items[6], items[11]);
			results_found = 1;

		}
	}

	if (results_found == 0) {
		fputs("NO RESULTS FOUND.\n", op);
	}

	fclose(fp);
	fclose(op);
	return;	
}
