#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main() {
  MYSQL my_connection;
  int res;
  
  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection,
						 "localhost",
						 "proxy",
						 NULL,
						 "LETENO_DB",
						 0,
						 NULL,
						 0)){
	printf("Connection success\n");

	res = mysql_query(&my_connection,
					  "INSERT INTO student (sname, age) values ('new', 17)");
	if (!res) {
	  printf("Inserted %lu rows\n",
			 (unsigned long)mysql_affected_rows(&my_connection));
	} else {
	  fprintf(stderr, "Insert error %d: %s\n",
			  mysql_errno(&my_connection),
			  mysql_error(&my_connection));
	}
	
	mysql_close(&my_connection);
  } else {
	fprintf(stderr, "Connection failed\n");
	if (mysql_errno(&my_connection)){
	  fprintf(stderr, "Connection error %d: %s\n",
			  mysql_errno(&my_connection),
			  mysql_error(&my_connection));
	}
	return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
