#include <stdio.h>
#include <operaciones.h>

int prueba_sumar( double op1, double op2, double esperado )
{
	double resultado = sumar(op1,op2);

	if( resultado != esperado )
	{
		fprintf( stderr, "Fallo al sumar(%lf,%lf)=[%lf]; lo esperado [%lf]\n", op1, op2, resultado, esperado );
		return 1;
	}

	return 0;
}

int prueba_restar( double op1, double op2, double esperado )
{
	double resultado = restar(op1,op2);

	if( resultado != esperado )
	{
		fprintf( stderr, "Fallo al restar(%lf,%lf)=[%lf]; lo esperado [%lf]\n", op1, op2, resultado, esperado );
		return 1;
	}

	return 0;
}

int main(int args, char **argv)
{
	int resultado = 0;

// Prueba funcion SUMA
//-------------------------------------------------
	resultado = prueba_sumar( 12.0, 25.0, 37.0 );
	printf( "Test 1  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_sumar( -12.0, -25.0, -37.0 );
	printf( "Test 2  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_sumar( -12.0, 25.0, 13.0 );
	printf( "Test 3  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_sumar( 12.0, -25.0, -13.0 );
	printf( "Test 4  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_sumar( 12.0, 0.0, 12.0 );
	printf( "Test 5  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_sumar( 0.0, 25.0, 25.0 );
	printf( "Test 6  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;

// Prueba funcion RESTA
//-------------------------------------------------
	resultado = prueba_restar( 12.0, 25.0, -13.0 );
	printf( "Test 7  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_restar( -12.0, -25.0, 13.0 );
	printf( "Test 8  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_restar( -12.0, 25.0, -37.0 );
	printf( "Test 9  [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_restar( 12.0, -25.0, 37.0 );
	printf( "Test 10 [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_restar( 12.0, 0.0, 12.0 );
	printf( "Test 11 [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;
//-------------------------------------------------
	resultado = prueba_restar( 0.0, 25.0, -25.0 );
	printf( "Test 12 [%d] %s\n", resultado, resultado?"Falló":"Ok" );
	if( resultado )
		return resultado;

	return 0;
}
