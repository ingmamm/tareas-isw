/*
 * integrantes: Adrian Gutierrez Gil
 * 				Miguel Marabolí Mendez
 * 				Valery Soto Lastra
 * */

#include <iostream>
#include <libpq-fe.h>

using namespace std;




int main(int argc, char * argv[])
{
	PGconn *cnn = NULL; //iniciando variables
	PGresult *result = NULL;


    int i;

   cnn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");// datos de conexion

    if (PQstatus(cnn) != CONNECTION_BAD) { // si la conexion no falla 
        cout << "\t\t--------------------------------------" << endl;
        cout << "\t\t|  Conexion al Servidor Establecida  |" << endl;
        cout << "\t\t--------------------------------------" << endl << endl;

        result = PQexec(cnn,
        		"SELECT c.asignatura, AVG(A.nota) as \"Promedio Notas\", STDDEV(A.nota) "
        		"as \"Desviacion Estandar\""
        		" FROM cursos C INNER JOIN asignaturas_cursadas A ON A.curso_id = C.curso_id "
        		"GROUP BY C.asignatura"); // esta es la consulta sql 

        if (result != NULL) {
            int filas = PQntuples(result);
            int columnas = PQnfields(result);
            cout << "No. Filas:" << filas << endl;
            cout << "No. Columnas:" << columnas << endl << endl;

        // Aqui se despliegan los nombres de las columnas

            cout << "Los nombres de las columnas son:" << endl << endl;

            for (i=0; i<columnas; i++) {
                cout << PQfname(result,i) << "\t\t|\t\t";
            }

            cout << endl;

        // Aqui se despliegan los valores de cada fila

            for (i=0; i<filas; i++) {
                for (int j=0; j<columnas; j++) {
                    cout  << PQgetvalue(result,i,j) << "\t\t\t";
                }
                cout << endl;
            }
        }

        // Ahora nos toca liberar la memoria
        PQclear(result);

    } else {
        cout << "Error de conexion" << endl;
        return 0;
    }

    PQfinish(cnn);

    return 0;
}
