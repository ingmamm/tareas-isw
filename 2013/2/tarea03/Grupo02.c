
#include <stdio.h>

#include <string.h>
#include <libpq-fe.h>

int main(int argc, char** argv)
{
PGconn *conn;
PGresult *res;
PGresult *rep;
int i,j;
//char *entrada;
//printf("ingrese el curso con el siguiente formato 'NOMBRECURSO'\n");
//printf("ejemplo si quiere ver calculo 2 debe ingresarlo como 'CÁLCULO II'\n");


conn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");
char *s1 ="select cur.asignatura, asig.nota from isw.asignaturas_cursadas asig, isw.cursos cur where (cur.curso_id = asig.curso_id) and asig.nota >=4 and cur.asignatura='CÁLCULO VECTORIAL'";
char *s2 ="select cur.asignatura, asig.nota from isw.asignaturas_cursadas asig, isw.cursos cur where (cur.curso_id = asig.curso_id) and asig.nota <4 and cur.asignatura='CÁLCULO VECTORIAL'";

//strcat(s1,enter);
//strcat(s2,enter);
if (PQstatus(conn) != CONNECTION_BAD)
{
res = PQexec(conn, s1);
rep = PQexec(conn, s2);
if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res) && rep != NULL && PGRES_TUPLES_OK == PQresultStatus(rep))
{
	printf("Aprobados\n");
for (i = PQntuples(res)-1; i >= 0; i--)
	{

		for (j = PQnfields(res)-1; j >= 0; j--)
			printf("%s\t",PQgetvalue(res,i,j));
			printf("\n");
	}
	PQclear(res);
	printf("Reprobados \n" );
	for (i = PQntuples(rep)-1; i >= 0; i--)
	{
		for (j = PQnfields(rep)-1; j >= 0; j--)
			printf("%s\t",PQgetvalue(rep,i,j));
			printf("\n");
	}
	
	PQclear(rep);
}
}

PQfinish(conn);
return 0;
}