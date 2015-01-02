#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

int main(int argc, char** argv)
{
//Make sure number of arguments correct
  if(argc != 4)
    {
      fprintf(stderr, "USAGE: %s <database file> <table name> <CSV file>\n", argv[0]);
      return 1;
    }
	//Open database and exit if failed
	sqlite3 *db;
	int rc;
	rc = sqlite3_open(argv[1], &db);
	if(rc) {
			printf("Failed to open database: %s", sqlite3_errmsg(db));
			sqlite3_close(db);
			return 1;
	}

	//Perform select statement using user input table
	 sqlite3_stmt *sqlstate;
	char query[500] = "SELECT * FROM ";
	strcat(query, argv[2]);
	strcat(query, ";");
	FILE *f_point = fopen(argv[3], "w");
	//Prepare the query
	if (sqlite3_prepare_v2(db, query, -1, &sqlstate, 0) == SQLITE_OK) {
		int ctotal = sqlite3_column_count(sqlstate);
		int row = 0;
		int i, num;
		char *s;
		//for each row returned
		while ((row = sqlite3_step(sqlstate)) == SQLITE_ROW) {
			//for each column
			for (i=0; i<ctotal; i++) {
				//If it is an integer, save to an int and print it to the file in csv format
				if(sqlite3_column_type(sqlstate, i) == SQLITE_INTEGER){
					num = (int)sqlite3_column_int(sqlstate, i);
					fprintf(f_point, "%d", num);
				}
				//If it is a string, print it to the file in csv format
				else if(sqlite3_column_type(sqlstate, i) == SQLITE_TEXT){
					s = (char*)sqlite3_column_text(sqlstate, i);
					fprintf(f_point,"'%s'", s);
				}
				//Print error if neither, should never happen, exit
				else{
					printf("Error reading type\n");
					sqlite3_close(db);
					return 1;
				}
				//Add comma when not the last entry in a csv format line to keep csv format
				if(i+1 != ctotal){
					fprintf(f_point, ",");
				}
			}
			//Go to new line when done with a row
			fprintf(f_point, "\n");
		}
	}
	else{
		printf("Failed: %s", sqlite3_errmsg(db));
	}
	//Close file, finalize sqlstate and close sqlite pointer
	fclose(f_point);
	sqlite3_finalize(sqlstate);
	sqlite3_close(db);


  return 0;
}
