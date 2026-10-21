#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0

double objective(double x)
{
    double result = pow((2 * x + 3 - 11 ), 2);
    return result;
}

/* between [-1 : 1] */
double rand_step(float step)
{
    return (step * 2.0) * ((double)rand() / RAND_MAX) - step;
}

/* between [0.0 : 1.0] */
double rand_num(void)
{
    return (double)rand() / RAND_MAX;
}

double acceptance(double delta, double temp)
{
    return  exp(-delta/ temp);
}

int main(void)
{
    double optimal, new_x, curr_x;
    double curr_value, new_value;
    double temp, cooling, probability, delta, step, random;
    int iteraions, accept;

    srand((unsigned)time(NULL));

    /* Parameters */
    temp = 10;
    cooling = 0.9;
    step = 1.0;
    iteraions = 100;

    /* iteration 0 */
    new_x = curr_x = 1.0;
    curr_value = objective(curr_x);

    /* core loop */
    while(iteraions-- > 0)
    {
        new_x += rand_step(step);
        new_value = objective(new_x);
        delta = new_value - curr_value;

        if(delta < 0)
        {
            accept = TRUE;
            probability = 1.0;
            optimal = new_x;
        }else{
            probability = acceptance(delta, temp);
            random = rand_num();
            accept = random < probability;
        }

        if(accept){
            curr_value = new_value;
            curr_x = new_x;
            optimal = new_x;
        }

        printf("\ni: %d | curr_x: %.3f | curr_val: %.3f | temp: %.3f\n", iteraions, curr_x, curr_value, temp);

        temp *= cooling;
    }

    printf("\nOptimal solution: %.3f\n", optimal);
    printf("\nOptimal solution: %.1f\n", optimal);
}
