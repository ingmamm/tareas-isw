/*
 * integrantes: Adrian Gutierrez Gil
 *              Miguel Marabolí Mendez
 *              Valery Soto Lastra
 * */

#include <iostream>
#include <libpq-fe.h>
#include <string.h>


using namespace std;

void conexion(const char *sentencia);
void mostrarAsiganturas();

int main(int argc, char * argv[])
{


	int i;
	std::string asignatura;

	cout<<"\nlas asignaturas disponibles para mostrar su promedio y desviacion estandar son :";
	mostrarAsiganturas();




	std::string cadena = "SELECT c.asignatura, AVG(A.nota) , STDDEV(A.nota) FROM cursos C INNER JOIN asignaturas_cursadas A ON A.curso_id = C.curso_id WHERE c.asignatura = ";
	std::string finSentencia = "GROUP BY C.asignatura;";
	std::string csimpleIncio = " '";
	std::string csimpleFin = "' ";

	cout <<"\nIngrese el nombre de la asignatura:";
	getline(cin,asignatura); // COMO LOS NOMBRES DE LAS ASIGANTURAS LLEVAN ESPACIO NO SE PUEDE USAR cin 


	cadena.append((csimpleIncio));
//	cout<<"\n"<<cadena;
	cadena.append((asignatura));
//	cout<<"\n"<<cadena;
	cadena.append((csimpleFin));
//	cout<<"\n"<<cadena;
	cadena.append((finSentencia));
//	cout<<"\n"<<cadena;
	const char *completo= cadena.c_str();

//	cout<<"\n"<<&completo;
 	conexion(completo);



}
void conexion(const char *sentencia)
{
	PGconn *cnn = NULL;
	PGresult *consulta = NULL;
	int i;

	cnn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");// datos de conexion

	if (PQstatus(cnn) != CONNECTION_BAD)
	{

		consulta = PQexec(cnn, sentencia);

		if (consulta != NULL)
		{
			int filas = PQntuples(consulta);
			int columnas = PQnfields(consulta);
//			cout << "No. Filas:" << filas << endl;
//			cout << "No. Columnas:" << columnas << endl << endl;

			cout << endl<<endl;

			for (i=0; i<columnas; i++)
			{
				cout << "      " <<PQfname(consulta,i) << "     ";
			}

			cout << endl<<endl;

			// Aqui se despliegan los valores de cada fila

			for (i=0; i<filas; i++)
			{
				for (int j=0; j<columnas; j++)
				{
					cout  << "  " <<PQgetvalue(consulta,i,j) << "   ";
				}
				cout << endl;
			}
		}

		// Ahora nos toca liberar la memoria
		PQclear(consulta);

	}

	else
	{
		cout << "\t\t--------------------------------------" << endl;
		cout << "\t\t|          Error de Conexion         |" << endl;
		cout << "\t\t--------------------------------------" << endl << endl;

	}

	PQfinish(cnn);
}

void mostrarAsiganturas(){

	PGconn *cnn = NULL; //iniciando variables
	PGresult *result = NULL;


	int i;

	cnn = PQsetdbLogin("146.83.181.4","6432",NULL,NULL,"iswdb","isw","isw");// datos de conexion

	if (PQstatus(cnn) != CONNECTION_BAD) { // si la conexion no falla


		result = PQexec(cnn,"SELECT asignatura FROM cursos  GROUP BY asignatura"); // esta es la consulta sql que busca todas las asignaturas distintas en la bd

		if (result != NULL) {
			int filas = PQntuples(result);
			int columnas = PQnfields(result);
			/*cout << "No. Filas:" << filas << endl;
			cout << "No. Columnas:" << columnas << endl << endl;

			// Aqui se despliegan los nombres de las columnas

			cout << "Los nombres de las columnas son:" << endl << endl;*/

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

	}

	PQfinish(cnn);

};

};
