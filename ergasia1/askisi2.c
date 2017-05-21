#include <stdio.h>
#include <math.h>

int shapeCode;
double perimeter;
double squarePerimeter();
double rectanglePerimeter();
double trianglePerimeter();
double circlePerimeter();

int main(){

	int shapeCode;
    printf("Shape codes:\nSquare 1\nRectancle 2\nTriangle 3\nCircle 4\nExit 0\n");

	do{

	    printf("Give shape code\n");
		scanf("%d", &shapeCode);

		if(shapeCode == 0){

		    return 0;
		}
		if(shapeCode == 1){

			double side;
			printf("Give square side\n");
			scanf("%lf", &side);
			perimeter = squarePerimeter(side);
			printf("The perimeter of the square is:%.2lf\n", perimeter);
			continue;
		}
		if(shapeCode == 2){

			double sideA, sideB;
			printf("Give side A\n");
			scanf("%lf", &sideA);
			printf("Give side B\n");
			scanf("%lf", &sideB);
			perimeter = rectanglePerimeter(sideA, sideB);
			printf("The perimeter of the rectangle is:%.2lf\n", perimeter);
			continue;
		}
		if(shapeCode == 3){

			double sideA, sideB;
			printf("Give side A\n");
			scanf("%lf", &sideA);
			printf("Give side B\n");
			scanf("%lf", &sideB);
			perimeter = trianglePerimeter(sideA, sideB);
			printf("The perimeter of the triangle is:%.2lf\n", perimeter);
			continue;
		}
		if(shapeCode == 4){

			double radius;
			printf("Give circle radius\n");
			scanf("%lf", &radius);
			perimeter = circlePerimeter(radius);
			printf("The perimeter of the circle is:%.2lf\n", perimeter);
			continue;

		}
		else {

			printf("Invalid input. Please try again.\n");
		}

	}while(shapeCode != 0);

	return 0;
}

double squarePerimeter(double side){

    return 4*side;
}

double rectanglePerimeter(double side1, double side2){

    return 2*(side1+side2);
}

double trianglePerimeter(double side1, double side2){

    int side3 = sqrt(side1*side1 + side2*side2);

    return side1+side2+side3;
}

double circlePerimeter(double radius){

    return 2*M_PI*radius;
}
