#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INF_SOLUTIONS -1
#define PRECISION 1e-5

struct ComplexNumber
{
    double real;
    double imaginary;

    ComplexNumber()
    {
        real = 0;
        imaginary = 0;
    }

    ComplexNumber(double real, double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }
};

int isApproximatelyZero(double value)
{
    if (value > -PRECISION && value < PRECISION)
        return 1;
    else
        return 0;
}

//-----------------------------------------------------------------------------
//! Solves a quadratic equation ax2 + bx + c = 0
//! @param [in]  a  a-coefficient
//! @param [in]  b  b-coefficient
//! @param [in]  c  c-coefficient
//! @param [out] x1 pointer to the smallest solution
//! @param [out] x2 pointer to the greatest solution
//!
//! @return Number of solutions
//!
//! @note If there's only one solution then both x1 and x2
//!       will be set to this value.
//!
//!       In case of infinite number of roots,
//!       returns INF_SOLUTIONS.
//-----------------------------------------------------------------------------
int solveQuadraticEquation(double a, double b, double c,
                           ComplexNumber *x1, ComplexNumber *x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if      (isApproximatelyZero(a) && isApproximatelyZero(b) && isApproximatelyZero(c))
    {
        return INF_SOLUTIONS;

    }
    else if (isApproximatelyZero(a) && isApproximatelyZero(b) && !isApproximatelyZero(c))
    {
        return 0;
    }
    else if (isApproximatelyZero(a) && !isApproximatelyZero(b) && !isApproximatelyZero(c))
    {
        x1->real = -c / b;
        return 1;
    }
    else
    {
        double d = b * b - 4 * a * c;
        double sqrtD;
        double inverseDoubleA = 1 / (2 * a);

        if (d < 0)
        {
            sqrtD = sqrt(-d);

            x1->real = -b * inverseDoubleA;
            x1->imaginary = sqrtD * inverseDoubleA;
            x2->real = x1->real;
            x2->imaginary = -x1->imaginary;

            return 2;
        }
        else
        {
            sqrtD = sqrt(d);

            if (sqrtD == 0)
            {
                x1->real = -b * inverseDoubleA;
                x2->real = x1->real;

                return 1;
            }
            else
            {
                x1->real = (-b - sqrtD) * inverseDoubleA;
                x2->real = (-b + sqrtD) * inverseDoubleA;

                return 2;
            }
        }
    }
}

void printComplexNumber(ComplexNumber number)
{
    if (number.imaginary == 0)
        printf("%lg", number.real);
    else if (number.imaginary > 0)
        printf("%lg + %lgi", number.real, number.imaginary);
    else
        printf("%lg - %lgi", number.real, -number.imaginary);
}

int main()
{
    printf("=== Quadratic equation solver ===\n");
    printf("=== Equation ax2 + bx + c = 0 ===\n");
    printf("Enter the coefficients in the following format \"a b c\": ");

    double a = 0, b = 0, c = 0;
    scanf("%lg %lg %lg", &a, &b, &c);

    printf("(%lg) * x2 + (%lg) * x + (%lg) = 0\n", a, b, c);

    ComplexNumber x1, x2;
    int numberOfSolutions = solveQuadraticEquation(a, b, c, &x1, &x2);
    switch(numberOfSolutions)
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
        return 1;
    }

}


