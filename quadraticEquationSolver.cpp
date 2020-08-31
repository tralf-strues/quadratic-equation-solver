#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

#define INF_SOLUTIONS -1
#define PRECISION 1e-5
#define ERROR_CODE 1
#define CORRECT_CODE 0

struct ComplexNumber
{
	double real = 0;
	double imaginary = 0;
};

//-----------------------------------------------------------------------------
//! Initializes a complexNumber
//! @param [out] complexNumber pointer to the complexNumber that is to be
//!                            initialized
//! @param [in]  real          real value of the new complexNumber
//! @param [in]  imaginary     imaginary value of the new complexNumber
//! @note By default before initialization both values of a complexNumber are
//!       set to zero.
//-----------------------------------------------------------------------------
void initComplexNumber(ComplexNumber* complexNumber, double real, double imaginary)
{
	complexNumber->real = real;
	complexNumber->imaginary = imaginary;
}

bool isApproximatelyX(double value, double x);
int solveQuadraticEquation(double a, double b, double c,
						   ComplexNumber* x1, ComplexNumber* x2);
void printComplexNumber(ComplexNumber number);
void solverTest();

//-----------------------------------------------------------------------------
//! Requests 3 coefficients of a quadratic equation from the user and solves
//! the equation.
//! @return CORRECT-CODE if there were no errors and ERROR_CODE
//!         otherwise.
//-----------------------------------------------------------------------------
int main()
{
	solverTest();

	printf("=== Quadratic equation solver ===\n");
	printf("=== Equation ax2 + bx + c = 0 ===\n");
	printf("Enter the coefficients in the following format \"a b c\": ");

	double a = 0, b = 0, c = 0;
	while (scanf_s("%lg %lg %lg", &a, &b, &c) != 3)
	{
		while (getchar() != '\n')
			;
		printf("Incorrect input format. Note that you are supposed to type in 3 numbers, e.g. \"1 2 3\". Please re-run the program.\n");
	}

	printf("(%lg) * x2 + (%lg) * x + (%lg) = 0\n", a, b, c);

	ComplexNumber x1 = {}, x2 = {};
	int numberOfSolutions = solveQuadraticEquation(a, b, c, &x1, &x2);
	switch (numberOfSolutions)
	{
		case 0:
		printf("No solution\n");
		break;

		case 1:
		printf("Solution: x = %lg", x1.real);
		break;

		case 2:
		printf("Solution: x = ");
		printComplexNumber(x1);
		printf(" OR x = ");
		printComplexNumber(x2);
		printf("\n");
		break;

		case INF_SOLUTIONS:
		printf("Solution is any number\n");
		break;

		default:
		printf("main(): ERROR, the number of solutions is %d\n", numberOfSolutions);
		return ERROR_CODE;
	}

	return CORRECT_CODE;
}

//-----------------------------------------------------------------------------
//! Shows whether or not value is approximately equal to x (with respect to the
//! PRECISION constant).
//! @param [in] value
//! @param [in] x
//!
//! @return Whether or not value is approximately equal to x.
//-----------------------------------------------------------------------------
bool isApproximatelyX(double value, double x)
{
	return fabs(value - x) < PRECISION;
}

//-----------------------------------------------------------------------------
//! Solves a quadratic equation ax2 + bx + c = 0.
//! @param [in]  a  a-coefficient
//! @param [in]  b  b-coefficient
//! @param [in]  c  c-coefficient
//! @param [out] x1 pointer to the smallest solution
//! @param [out] x2 pointer to the greatest solution
//!
//! @return Number of solutions.
//!
//! @note If there's only one solution then both x1 and x2
//!       will be set to this value.
//!       In case of infinite number of solutions,
//!       returns INF_SOLUTIONS.
//-----------------------------------------------------------------------------
int solveQuadraticEquation(double a, double b, double c,
						   ComplexNumber* x1, ComplexNumber* x2)
{
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (isApproximatelyX(a, 0) && isApproximatelyX(b, 0) && isApproximatelyX(c, 0))
	{
		return INF_SOLUTIONS;
	}
	else if (isApproximatelyX(a, 0) && isApproximatelyX(b, 0) && !isApproximatelyX(c, 0))
	{
		return 0;
	}
	else if ((isApproximatelyX(a, 0) && !isApproximatelyX(b, 0) && isApproximatelyX(c, 0)) ||
		(!isApproximatelyX(a, 0) && isApproximatelyX(b, 0) && isApproximatelyX(c, 0)))
	{
		x1->real = 0;
		x2->real = 0;
		return 1;
	}
	else if (isApproximatelyX(a, 0) && !isApproximatelyX(b, 0) && !isApproximatelyX(c, 0))
	{
		x1->real = -c / b;
		x2->real = x1->real;
		return 1;
	}

	int resultNumberOfSolutions = 0;
	double d = b * b - 4 * a * c;
	double sqrtD = sqrt(fabs(d));
	double inverseDoubleA = 1 / (2 * a);

	if (isApproximatelyX(sqrtD, 0))
	{
		x1->real = -b * inverseDoubleA;
		x2->real = x1->real;

		resultNumberOfSolutions = 1;
	}
	else if (d < 0)
	{
		x1->real = -b * inverseDoubleA;
		x1->imaginary = sqrtD * inverseDoubleA;
		x2->real = x1->real;
		x2->imaginary = -x1->imaginary;

		resultNumberOfSolutions = 2;
	}
	else
	{
		x1->real = (-b - sqrtD) * inverseDoubleA;
		x2->real = (-b + sqrtD) * inverseDoubleA;

		resultNumberOfSolutions = 2;
	}

	// getting rid of negative zeros
	if (isApproximatelyX(x1->real,      0)) x1->real      = 0;
	if (isApproximatelyX(x1->imaginary, 0)) x1->imaginary = 0;
	if (isApproximatelyX(x2->real,      0)) x2->real      = 0;
	if (isApproximatelyX(x2->imaginary, 0)) x2->imaginary = 0;

	// sorting the values
	if (isApproximatelyX(x1->real, x2->real))
	{
		x2->real = x1->real;
		if (x1->imaginary > x2->imaginary)
		{
			ComplexNumber temp;
			temp = *x1;
			*x1 = *x2;
			*x2 = temp;
		}
	}
	else if (x1->real > x2->real)
	{
		ComplexNumber temp;
		temp = *x1;
		*x1  = *x2;
		*x2  = temp;
	}

	return resultNumberOfSolutions;
}

//-----------------------------------------------------------------------------
//! Prints a complexNumber.
//! @param [in]  number  a-coefficient
//! @note  If the number is real (imaginary part is zero), then the program
//!        prints only the real part (e.g. "1", not "1+0i").
//!        Does not add \n at the end.
//-----------------------------------------------------------------------------
void printComplexNumber(ComplexNumber number)
{
	if (isApproximatelyX(number.imaginary, 0))
		printf("%lg", number.real);
	else if (number.imaginary > 0)
		printf("%lg + %lgi", number.real, number.imaginary);
	else
		printf("%lg - %lgi", number.real, -number.imaginary);
}

struct TestSet
{
	double a;
	double b;
	double c;
	//int programNSolutions;
	int correctNSolutions;
	//ComplexNumber programX1, programX2;
	ComplexNumber correctX1, correctX2;
};


//-----------------------------------------------------------------------------
//! Tests whether the solveQuadraticEquation function works correct or not.
//-----------------------------------------------------------------------------
void solverTest()
{
	TestSet testSets[11];
	int numberOfTestsPassed = 0;
	// some of the coefficients are zero
	testSets[0]  = TestSet{ 0, 0, 0,  INF_SOLUTIONS, {0,               0          }, {0,          0         } };
	testSets[1]  = TestSet{ 0, 0, 5,  0,             {0,               0          }, {0,          0         } };
	testSets[2]  = TestSet{ 0, 5, 0,  1,             {0,               0          }, {0,          0         } };
	testSets[3]  = TestSet{ 0, 5, 3,  1,             {-0.6f,           0          }, {-0.6f,      0         } };
	testSets[4]  = TestSet{ 5, 0, 0,  1,             {0,               0          }, {0,          0         } };								 						          						     
	testSets[5]  = TestSet{ 5, 0, 3,  2,             {0,               -sqrt(0.6f)}, {0,          sqrt(0.6f)} };
	testSets[6]  = TestSet{ 5, 0, -3, 2,             {-sqrt(0.6f),     0          }, {sqrt(0.6f), 0         } };
	testSets[7]  = TestSet{ 5, 3, 0,  2,             {-0.6f,           0          }, {0,          0         } };

	// all the coefficients are non-zero
	testSets[8]  = TestSet{ 1, 2, 1,  1,             {-1,              0          }, {-1,         0         } };
	testSets[9]  = TestSet{ 5, 4, 1,  2,             {-0.4f,           -0.2f      }, {-0.4f,      0.2f      } };
	testSets[10] = TestSet{ 1, 1, -2, 2,             {-2,              0          }, {1,          0         } };

	int numberOfSolutions = 0;
	ComplexNumber x1, x2;
	for (int i = 0; i < 11; i++)
	{
		printf("Test %2d: (%lg) * x2 + (%lg) * x + %lg = 0\n\t", i, testSets[i].a, testSets[i].b, testSets[i].c);
		numberOfSolutions = solveQuadraticEquation(testSets[i].a, testSets[i].b, testSets[i].c, &x1, &x2);

		if (numberOfSolutions == testSets[i].correctNSolutions              && 
			isApproximatelyX(x1.real,      testSets[i].correctX1.real)      &&
			isApproximatelyX(x1.imaginary, testSets[i].correctX1.imaginary) &&
			isApproximatelyX(x2.real,      testSets[i].correctX2.real)      &&
			isApproximatelyX(x2.imaginary, testSets[i].correctX2.imaginary))
		{
			printf("Correct. x1 = ");
			printComplexNumber(x1);
			printf(", x2 = ");
			printComplexNumber(x2);
			printf("\n");

			numberOfTestsPassed++;
		}
		else
		{
			printf("Incorrect.\n\tOutput: x1 = ");
			printComplexNumber(x1);
			printf(", x2 = ");
			printComplexNumber(x2);

			printf("\n\tAnswer: x1 = ");
			printComplexNumber(testSets[i].correctX1);
			printf(", x2 = ");
			printComplexNumber(testSets[i].correctX2);
			printf("\n");
		}

		initComplexNumber(&x1, 0, 0);
		initComplexNumber(&x2, 0, 0);
	}

	printf("---------------------------------------------------------------------\n");
	printf("Number of tests successfully passed is %d/11.\n", numberOfTestsPassed);
	printf("---------------------------------------------------------------------\n\n");

}


